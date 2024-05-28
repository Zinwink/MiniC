/**
 * @file ArmInstGen.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ArmInstGen.h"
#include <iostream>

/// @brief IR指令对应的处理
/// @param IRinst
/// @return
bool ArmInstGen::IR2Arm(InstPtr IRinst)
{
    bool result = false;
    Opcode op = IRinst->getOpcode();
    auto iter = IR2ArmInst_handers.find(op);
    if (iter != IR2ArmInst_handers.end())
    {
        // 找到了
        result = (this->*(iter->second))(IRinst);
    }
    else
    {
        // 未找到对应操作
        std::cout << "Unkown IRInst type:" << IRinst->getOpcodeName() << std::endl;
    }
    return result;
}

/// @brief 将AllocaInst IR 处理
/// @param alloca
/// @return
bool ArmInstGen::Alloca2ArmInst(InstPtr alloca)
{
    MFuncPtr curfun = machineModule->getCurFun();
    AllocaInstPtr IRalloca = std::static_pointer_cast<AllocaInst>(alloca); // 转型

    // 1. 对于函数形参的alloca 需要特殊处理 尤其是非前4个形参的alloca 其偏移不一样
    if (IRalloca->isAllocaArgument())
    {
        ArgPtr &arg = IRalloca->getAllocaArg();
        uint32_t argNO = arg->getArgNo();
        if (argNO > 3)
        {
            // alloca 非前4个形参 无需申请栈空间 使用 fp+ #num 访问就行
            // 目前函数形参是指针或者int 类型 alloca空间肯定是4
            IRalloca->setOffset(4 * (argNO - 4) + 8);
        }
        else
        {
            // 如果有对 前四个形参的alloca 则申请栈空间 偏移为 fp #-num
            // 一般而言对形参的alloca可以消去
            // 目前函数形参的alloca 一定为4 包括对数组基地址的alloca
            uint64_t off = curfun->AllocaStack(4); // 生气4字节
            IRalloca->setOffset(-(int64_t)(off));  // 偏移相对于fp 应该是负数 低地址
        }
    }
    else
    {
        // 是对变量或者数组的alloca
        uint64_t allocasize = IRalloca->getAllocaSize(); // 获取alloca字节数
        uint64_t off = curfun->AllocaStack(allocasize);
        IRalloca->setOffset(-(int64_t)(off)); // 负数 低地址偏移
    }
    return true;
}

/// @brief 将Store IR处理
/// @param store
/// @return
bool ArmInstGen::Store2ArmInst(InstPtr store)
{
    
    return true;
}

/// @brief 处理 Ret IR
/// @param ret
/// @return
bool ArmInstGen::Ret2ArmInst(InstPtr ret)
{
    return true;
}

/// @brief 处理load iR
/// @param load
/// @return
bool ArmInstGen::Load2ArmInst(InstPtr load)
{
    return true;
}

/// @brief 处理 Call  IR
/// @param call
/// @return
bool ArmInstGen::Call2ArmInst(InstPtr call)
{
    return true;
}

/// @brief 无条件跳转IR处理
/// @param _goto
/// @return
bool ArmInstGen::Goto2ArmInst(InstPtr _goto)
{
    return true;
}

/// @brief 有条件 跳转IR处理
/// @param br
/// @return
bool ArmInstGen::CondBr2ArmInst(InstPtr br)
{
    return true;
}

/// @brief 处理 getelementptr
/// @param getelem
/// @return
bool ArmInstGen::Getelem2ArmInst(InstPtr getelem)
{
    return true;
}

/// @brief 整数加法 IR处理
/// @param iadd
/// @return
bool ArmInstGen::IAdd2ArmInst(InstPtr iadd)
{
    return true;
}

/// @brief 产生ArmInst
/// @return
bool ArmInstGen::run()
{
    std::deque<GlobalVariPtr> &irGlobalVaris = IRModule->getGlobalVars();
    // 将需要使用的全局加入到MachineModule
    for (auto &globalVari : irGlobalVaris)
    {
        machineModule->addGlobalVaris(globalVari);
    }
    // 下面遍历 IR function 以及function下的基本块生成 ArmInst指令
    std::deque<FuncPtr> &irFuns = IRModule->getFunList();
    for (auto &irfun : irFuns)
    {
        std::list<BasicBlockPtr> &irblocks = irfun->getBasicBlocks();
        // 先将 irblocks编号一下
        for (auto &irblk : irblocks)
        {
            machineModule->getNo(irblk);
        }
        // 下面进行正式的Arminst转换

        // 1. 创建一个对应的machineFunc
        MFuncPtr Mfun = MachineFunc::get(machineModule);
        machineModule->addFunc(Mfun);   // 加入函数
        machineModule->setCurFun(Mfun); // 标记当前函数

        // 2. 遍历basicblocks
        for (auto &irblk : irblocks)
        {
            // 创建一个对应的MachineBlock
            MBlockPtr mblk = MachineBlock::get(Mfun, machineModule->getNo(irblk));
            Mfun->addBlockBack(mblk);
            machineModule->setCurBlock(mblk); // 设置当前 mblk

            // 遍历 irblk中的ir指令
            std::list<InstPtr> &irinsts = irblk->getInstLists();
            for (auto &irist : irinsts)
            {
                bool result = IR2Arm(irist);
                if (result == false)
                {
                    return false;
                }
            }
        }
    }
    return true;
}