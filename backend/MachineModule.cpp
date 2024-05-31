/**
 * @file MachineModule.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineModule.h"
#include <fstream>

/// @brief 构造函数
MachineModule::MachineModule()
{
    counter = std::make_shared<MCount>();
}

/// @brief 获取指针智能对象
/// @return
MModulePtr MachineModule::get()
{
    MModulePtr mod = std::make_shared<MachineModule>();
    return mod;
}

/// @brief 手动清理
void MachineModule::clear()
{
    counter.reset();
    curBlock.reset();
    curFun.reset();
    for (auto &Mfun : funcList)
    {
        Mfun->clear();
    }
    funcList.clear();
    funcList.shrink_to_fit();
    globalVaris.clear();
    globalVaris.shrink_to_fit();
}

/// @brief  析构函数
MachineModule::~MachineModule()
{
    clear();
}

/// @brief 获取编号 全局变脸 常量标签地址  临时变量的虚拟寄存器编号
/// @param val
/// @return
uint32_t MachineModule::getNo(ValPtr val) { return counter->getNo(val); }

/// @brief 不插入记录 获取相应的
/// @return
uint32_t MachineModule::getRegNo()
{
    return counter->getRegNo();
}

/// @brief 重置计数器
void MachineModule::CnterReset()
{
    counter->reset();
}

//************************************* MCount ******************************************

/// @brief 获取编号 当记录中存在时 取出 不存在时放入 并增加计数
/// @param val
/// @return
uint32_t MCount::getNo(ValPtr val)
{
    uint32_t res = -1;
    auto iter = record.find(val);
    if (iter != record.end())
    {
        // 找到了
        return iter->second;
    }
    else
    {
        // 没找到 根据val 类型进行判断
        if (val->isBasicBlockVal())
        {
            res = MachineBlockNo;
            record.emplace(val, MachineBlockNo);
            MachineBlockNo++; // 自增
        }
        else if (val->isGlobalVariable())
        { // 全局变量 或者 常量池 使用标签地址
            res = LabelAddr;
            record.emplace(val, LabelAddr);
            LabelAddr++;
        }
        else if (val->isTemporary())
        {
            // 需要寄存器编号 虚拟寄存器(物理寄存器已经确定)
            res = RegNo;
            record.emplace(val, RegNo);
            RegNo++;
        }
        else if (val->isArgument())
        {
            // 函数形参  （传入的应该是 除了前4个的形参 需要从栈中加载到寄存器）
            ArgPtr arg = std::static_pointer_cast<Argument>(val);
            assert(arg->getArgNo() >= 4 && "not support this usage,the first four argument's reg is r0-r3");
            res = RegNo;
            record.emplace(val, RegNo);
            RegNo++;
        }
        else if (val->isConstant())
        {
            res = RegNo;
            RegNo++;
        }
    }
    assert(res != -1 && "the counter not support the usage!");
    return res;
}

/// @brief 产生全局变量声明
/// @return
void MachineModule::genGlobalVariDecl()
{
    // 根据 initilizer区分 .data 段和 .bss段
    for (auto &g : globalVaris)
    {
        if (g->getInitilizer() != nullptr)
        {
            // data段
            string str = "\ttype    " + g->getName() + ",%object\n";
            str += "\t.globl    " + g->getName() + "\n";
            str += g->getName() + ":\n";
            if (!g->getElemTy()->isArrayType())
            {
                ConstantIntPtr intv = std::static_pointer_cast<ConstantInt>(g->getInitilizer());
                str += "\t.long  " + std::to_string(intv->getValue()) + "\n";
                str += "\t.size   " + g->getName() + ", " + "4";
            }
            else
            {
                // 暂未编写 因为前端还不支持
            }
            dataSection.push_back(str);
        }
        else
        {
            // bss段
            string str = "\ttype    " + g->getName() + ",%object\n";
            str += "\t.globl    " + g->getName() + "\n";
            str += g->getName() + ":\n";
            if (g->getElemTy()->isArrayType())
            {
                str += "\t.zero   " + std::to_string(g->byteSizes()) + "\n";
            }
            else
            {
                str += "\t.long  " + string("0\n");
            }
            str += "\t.size " + g->getName() + " " + std::to_string(g->byteSizes()) + "\n";
            bssSection.push_back(str);
        }
    }
}

/// @brief 将Arm指令打印至文件中
/// @param filePath
void MachineModule::printArm(string filePath)
{
    std::ofstream file(filePath);
    // 先产生 Arch cpu 等信息
    string headArch = R"(.arch armv7ve
.arm
.fpu vfpv4

.macro mov32, cond, reg, val
    movw\cond \reg, #:lower16:\val
    movt\cond \reg, #:upper16:\val
.endm
    )";
    file << headArch;
    file << "\n";
    file << "\t.text" << "\n";
    for (auto &fun : funcList)
    {
        file << fun->output();
        file << "\n";
    }

    // 下面打印 .data  .bss段
    genGlobalVariDecl();
    // .data 段
    if (dataSection.size() != 0)
        file << "\t.section .data" << "\n";
    for (auto &str : dataSection)
    {
        file << str << "\n";
    }
    // .bss 段
    file << "\n";
    if (bssSection.size() != 0)
        file << "\t.section .bss" << "\n";
    for (auto &str : bssSection)
    {
        file << str << "\n";
    }
}
