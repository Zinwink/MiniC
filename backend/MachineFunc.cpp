/**
 * @file MachineFunc.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineFunc.h"
#include "MachineInst.h"
#include "PlatformArm32.h"

#include <iostream>

/// @brief 构造函数
/// @param p 属于的module
/// @param _funcNo 函数编号
MachineFunc::MachineFunc(MModulePtr p)
{
    parent = p;
    addSaveReg(11); // fp
    addSaveReg(14); // lr
}

/// @brief 创建智能指针类型
/// @param p
/// @return
MFuncPtr MachineFunc::get(MModulePtr p)
{
    MFuncPtr fun = std::make_shared<MachineFunc>(p);
    return fun;
}

/// @brief 手动打破环 使智能指针自动释放
void MachineFunc::clear()
{
    parent.reset();
    for (auto &b : blockList)
    {
        b->clear();
    }
    blockList.clear();
    addrPool.clear();
}

/// @brief 析构函数
MachineFunc::~MachineFunc()
{
    MachineFunc::clear();
}

/// @brief 获取寄存器操作数
/// @return
std::vector<MOperaPtr> MachineFunc::getSavedRegs()
{
    std::vector<MOperaPtr> regs;
    for (auto regNO : regsSave)
    {
        MOperaPtr reg = MachineOperand::createReg(regNO);
        regs.push_back(std::move(reg));
    }
    return regs;
}

/// @brief 修正InstToAdjust中的指令
void MachineFunc::AdjustInsts()
{
    // 目前没有浮点寄存器
    for (auto &minst : InstToAdjust)
    {
        if (minst->isPOP())
        {
            // 获取savedRegs
            std::vector<MOperaPtr> savedRegsVect;
            for (auto &regNo : regsSave)
            {
                // 先创建一下寄存器操作数
                MOperaPtr regOPerator = MachineOperand::get(MachineOperand::REG, regNo);
                // 加入到列表中
                savedRegsVect.push_back(std::move(regOPerator));
            }
            MStackInstPtr stk = std::static_pointer_cast<MStackInst>(minst);
            stk->setRegs(savedRegsVect); // 设置pop的寄存器  pop {r4, r5, r6, fp,lr}
        }
        else if (minst->isLoad())
        {
            // 用于矫正 函数后4形参的偏移  其偏移为高地址
            MLoadInstPtr ldr = std::static_pointer_cast<MLoadInst>(minst);
            int bias = 4 * (regsSave.size() - 2);
            ldr->AddOffsetBias(bias); // 新增偏置
        }
        else if (minst->isStore())
        { // 用于矫正 函数后4形参的偏移  其偏移为高地址
            MStorePtr str = std::static_pointer_cast<MStore>(minst);
            int bias = 4 * (regsSave.size() - 2);
            str->AddOffsetBias(bias); // 新增偏置
        }
    }
}

/// @brief 输出函数使用的标签地址池
/// @return
string MachineFunc::printAddrPool()
{
    string str = "";
    for (auto &elem : addrPool)
    {
        str += elem.second;
        str += ":\n";
        str += "\t.long   ";
        if (elem.first->isGlobalVariable())
        {
            str += elem.first->getName();
        }
        str += "\n"; // 换行
    }
    return str;
}

/// @brief 输出函数对应的汇编
/// @return
string MachineFunc::output()
{
    string str = "";
    // 先得到 函数头
    str += "\t.globl\t";
    str += funcName;
    str += "\n";
    str += "\t.type\t";
    str += funcName;
    str += ",%function";
    str += "\n\t.code\t32\n";
    // 打印 函数入口
    str += funcName;
    str += ":\n";
    // str += "\t.fnstart\n";
    MBlockPtr entry = getEntry();
    std::vector<MOperaPtr> saveRegs = getSavedRegs();
    MStackInstPtr push = MStackInst::get(entry, MachineInst::PUSH, saveRegs);
    MMovInstPtr mov = MMovInst::get(entry, MachineInst::MOV, MachineOperand::createReg(11), MachineOperand::createReg(13)); // fp:11 sp:13
    str += ("\t" + push->toStr() + "\n");
    str += ("\t" + mov->toStr() + "\n");
    // 下面使用sub指令申请空间 在此之前需要8字节对齐
    // 根据调用函数得最大参数数目更新一下 stackSize  参数数目<=4则不变
    int ArgsStackSize = ((maxCallFunParmas - 4) <= 0) ? 0 : (4 * (maxCallFunParmas - 4));
    stackSize += ArgsStackSize; // 加上调用函数所需得栈
    int regRemSize = 4 * (regsSave.size() % 2);
    int flagOffset = regRemSize + stackSize;
    if ((flagOffset % 8) != 0)
    {
        // 没有8字节对齐
        stackSize += 4;
    }

    /// 下面使用sub 指令申请内存
    if (stackSize != 0)
    {
        MOperaPtr sp = MachineOperand::createReg(13);
        if (Arm32::canBeImmOperand((int)stackSize))
        {
            str += "\t";
            str += MBinaryInst::get(entry, MachineInst::SUB, sp, sp, MachineOperand::get(MachineOperand::IMM, stackSize))->toStr();
            str += "\n";
        }
        else
        {
            if (stackSize & 0xff)
            {
                str += "\t";
                str += MBinaryInst::get(entry, MachineInst::SUB, sp, sp, MachineOperand::get(MachineOperand::IMM, stackSize & 0xff))->toStr();
                str += "\n";
            }
            if (stackSize & 0xff00)
            {
                str += "\t";
                str += MBinaryInst::get(entry, MachineInst::SUB, sp, sp, MachineOperand::get(MachineOperand::IMM, stackSize & 0xff00))->toStr();
                str += "\n";
            }

            if (stackSize & 0xff0000)
            {
                str += "\t";
                str += MBinaryInst::get(entry, MachineInst::SUB, sp, sp, MachineOperand::get(MachineOperand::IMM, stackSize & 0xff0000))->toStr();
                str += "\n";
            }

            if (stackSize & 0xff000000)
            {
                str += "\t";
                str += MBinaryInst::get(entry, MachineInst::SUB, sp, sp, MachineOperand::get(MachineOperand::IMM, stackSize & 0xff000000))->toStr();
                str += "\n";
            }
        }
    }
    AdjustInsts(); // 对需要修正的指令进行修正
    // 先遍历entry块的指令
    for (auto &minst : entry->getInstList())
    {
        str += "\t";
        str += minst->toStr();
        str += "\n";
    }
    for (std::list<MBlockPtr>::iterator iter = std::next(blockList.begin()); iter != blockList.end(); ++iter)
    {
        str += (*iter)->toStr();
        // str += "\n";
    }
    str += printAddrPool();

    return str;
}