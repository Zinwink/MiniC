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
#include "MachineOperand.h"
#include "PlatformArm32.h"
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
            // 对于后4函数形参alloca 偏移后继可能需要修正
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
    ValPtr strVal = store->getOperand(0);            // 存放的值
    ValPtr Ptr = store->getOperand(1);               // 存放的地址
    MBlockPtr curblk = machineModule->getCurBlock(); // 当前块

    // 1. 先处理strVal   需要得到一个寄存器(虚拟或者物理)类型操作数
    MOperaPtr MStrval = MachineOperand::get(strVal, machineModule);
    if (MStrval->isImm())
    {
        // 需要加载到寄存器    对象不复用
        MStrval = MachineOperand::imm2VReg(MStrval, machineModule);
    }
    // 处理Ptr
    // 对于Ptr 可能是alloca地址 也可能是 getemelemptr 地址
    // 也可能是GlobalVariable 全局变量或者其他地址类型
    if (Ptr->isAllocaInst())
    {
        AllocaInstPtr alloca = std::static_pointer_cast<AllocaInst>(Ptr);
        int64_t offset = alloca->getOffset();
        MOperaPtr offsetImm = MachineOperand::get(MachineOperand::IMM, offset); // 操作数
        // 自动处理IMM 操作数
        // 可直接使用则返回本身 否则进行ldr 并返回存储该值的寄存器
        offsetImm = MachineOperand::AutoDealWithImm(offsetImm, machineModule);
        // 创建 str指令   str r1, [fp,#-4] 或者 str r1, [fp,r2]
        MStorePtr str = MStore::get(curblk, MachineInst::STR, MStrval, MachineOperand::get(MachineOperand::REG, 11), offsetImm);
        // 将该指令加入
        curblk->addInstBack(str);

        // 如果alloca是函数形参的alloca并且是后4个形参的alloca  则需要修正
        if (alloca->isAllocaArgument())
        {
            uint32_t argNo = alloca->getAllocaArg()->getArgNo();
            if (argNo > 3)
            {
                // 需要修正
                machineModule->getCurFun()->addAdjustInst(str);
            }
        }

        return true;
    }
    else if (Ptr->isGlobalVariable())
    {
        MOperaPtr addrL = MachineOperand::get(Ptr, machineModule); // 创建地址标签
        // 需要先将 标签地址 加载到寄存器， 最后通过 str 将寄存器值保存至 [全局变量标签地址寄存器]
        MOperaPtr glbvAddrReg = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo()); // 存放全局变量地址的寄存器
        MLoadInstPtr ldr = MLoadInst::get(curblk, MachineInst::LDR, glbvAddrReg, addrL);
        // 创建 str将值保存到全局变量地址对应的内存中
        MStorePtr str = MStore::get(curblk, MachineInst::STR, MStrval, MachineOperand::copy(glbvAddrReg));
        // 将指令 加入当前块后
        curblk->addInstBack(ldr);
        curblk->addInstBack(str);
        return true;
    }
    else if (Ptr->isGetelemPtrInst())
    {
        // getelementptr 可直接得到存放地址的寄存器
        MOperaPtr addrReg = MachineOperand::get(Ptr, machineModule);
        // 创建store指令
        MStorePtr str = MStore::get(curblk, MachineInst::STR, MStrval, addrReg);
        curblk->addInstBack(str);
        return true;
    }
    std::cout << "not support this usage currently" << std::endl;
    return false;
}

/// @brief 处理 Ret IR
/// @param ret
/// @return
bool ArmInstGen::Ret2ArmInst(InstPtr ret)
{
    // 先使用 mov sp, fp 释放占空间   sp:13 fp:11 lr:14
    // 然后使用 pop 恢复寄存器
    // 最后使用 bx lr 跳转
    MBlockPtr curblk = machineModule->getCurBlock();
    std::vector<ValPtr> &operands = ret->getOperandsList();

    // 创建 mov 指令释放栈空间  mov sp,fp
    MMovInstPtr mov_sp_fp = MMovInst::get(curblk, MachineInst::MOV, MachineOperand::createReg(13), MachineOperand::createReg(11));
    // 创建 pop pop 的寄存器还无法确定 需要寄存器分配之后
    MStackInstPtr pop = MStackInst::get(curblk, MachineInst::POP, {});
    // 创建 bx lr指令 供后继使用
    MBranchInstPtr bx = MBranchInst::get(curblk, MachineInst::BX, MachineOperand::createReg(14));

    if (operands.size() == 0)
    {
        // 函数无返回值 先使用mov_sp_fp释放栈空间 再pop 然后 bx lr
        curblk->addInstBack(mov_sp_fp);
        curblk->addInstBack(pop);
        // pop 的操作数需要后期 修改
        machineModule->getCurFun()->addAdjustInst(pop);
        curblk->addInstBack(bx);
    }
    else
    {
        // 函数有 返回值 先将返回值移动到 r0寄存器 然后再同样操作
        ValPtr irRetval = ret->getOperand(0);
        MOperaPtr retMop = MachineOperand::get(irRetval, machineModule);
        // 主要检查一下retMop的类型 如果是IMM 需要检查是否符合立即数规则  否则是VREG,REG 直接使用即可
        // 创建返回值寄存器 r0
        MOperaPtr r0 = MachineOperand::createReg(0);
        // 将返回值加载到r0
        if (retMop->isImm())
        {
            int32_t immV = retMop->getVal();   // 获取值
            if (!Arm32::canBeImmOperand(immV)) // 数值不能作为立即数使用
            {
                // 加载到r0
                MLoadInstPtr ldr = MLoadInst::get(curblk, MachineInst::LDR, r0, retMop);
                curblk->addInstBack(ldr);
            }
            else
            {
                // 可以直接作为立即数 使用mov指令
                MMovInstPtr mov = MMovInst::get(curblk, MachineInst::MOV, r0, retMop);
                curblk->addInstBack(mov);
            }
        }
        else
        {
            // 使用mov 指令
            MMovInstPtr mov = MMovInst::get(curblk, MachineInst::MOV, r0, retMop);
            curblk->addInstBack(mov);
        }
        // 释放栈空间
        curblk->addInstBack(mov_sp_fp);
        curblk->addInstBack(pop);
        // pop 的操作数需要后期 修改
        machineModule->getCurFun()->addAdjustInst(pop);
        curblk->addInstBack(bx);
    }
    return true;
}

/// @brief 处理load iR
/// @param load
/// @return
bool ArmInstGen::Load2ArmInst(InstPtr load)
{
    // IR 的LoadInst 的操作数 可以是 AllocaInst 也可以是 getelementptr

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
    MBlockPtr curblk = machineModule->getCurBlock();
    ValPtr irop = _goto->getOperand(0); // 获取跳转目标 是BasicBlock类型
    MOperaPtr LBB = MachineOperand::get(irop, machineModule);
    MBranchInstPtr B = MBranchInst::get(curblk, MachineInst::B, LBB);
    curblk->addInstBack(B);
    return true;
}

/// @brief 有条件 跳转IR处理
/// @param br
/// @return
bool ArmInstGen::CondBr2ArmInst(InstPtr br)
{
    MBlockPtr curblk = machineModule->getCurBlock();
    // 条件跳转有 三个操作数 和ICmp指令连用
    ValPtr cond = br->getOperand(0);    // 条件
    ValPtr IFTrue = br->getOperand(1);  // 真出口
    ValPtr IFFalse = br->getOperand(2); // 假出口
    // 根据cond 的操作码判断得到对应的 b 汇编指令跳转的条件
    // cond 可以是icmp 也可以是Constant 由Icmp比较结果传播而来(虽然IR优化时会处理 但避免疏忽没处理到)
    if (cond->isConstant())
    {
        // cond是常数 将只有一个 无条件跳转
        // 目前只支持int 故直接转成int
        ConstantIntPtr intv = std::static_pointer_cast<ConstantInt>(cond);
        if (intv->getValue() == 0)
        {
            // 为0 则 直接假出口
            MOperaPtr LBB = MachineOperand::get(IFFalse, machineModule);
            MBranchInstPtr B = MBranchInst::get(curblk, MachineInst::B, LBB);
            curblk->addInstBack(B);
        }
        else
        {
            // 直接真出口
            MOperaPtr LBB = MachineOperand::get(IFTrue, machineModule);
            MBranchInstPtr B = MBranchInst::get(curblk, MachineInst::B, LBB);
            curblk->addInstBack(B);
        }
    }
    else
    {
        assert(cond->isICmpInst() && "condition must be the cmp result");
        if (IFTrue == IFFalse)
        {
            // 无条件跳转  真假出口一样
            MOperaPtr LBB = MachineOperand::get(IFTrue, machineModule);
            MBranchInstPtr B = MBranchInst::get(curblk, MachineInst::B, LBB);
            curblk->addInstBack(B);
        }
        else
        {
            // 先获取条件后缀
            ICmpInstPtr cmp = std::static_pointer_cast<ICmpInst>(cond);
            MachineInst::condSuffix csuffix = IRCond2Machine(cmp);
            // 获取真假出口对应的操作数
            MOperaPtr LBBTrue = MachineOperand::get(IFTrue, machineModule);
            MOperaPtr LBBFalse = MachineOperand::get(IFFalse, machineModule);
            // 创建两个跳转指令
            MBranchInstPtr condB = MBranchInst::get(curblk, MachineInst::B, LBBTrue, csuffix);
            MBranchInstPtr B = MBranchInst::get(curblk, MachineInst::B, LBBFalse);
            // 将创建的指令加入当前块
            curblk->addInstBack(condB);
            curblk->addInstBack(B);
        }
    }

    return true;
}

/// @brief 处理 getelementptr
/// @param getelem
/// @return
bool ArmInstGen::Getelem2ArmInst(InstPtr getelem)
{
    MBlockPtr curblk = machineModule->getCurBlock();
    // 目前来看 getelementptr指令的基地址可以是 Argument，AllocaInst, LoadInst，也可以是全局变量地址 GlobalVariable
    // 基地址为loadInst 对应 load alloca (而alloca是对形参的空间申请)，经过处理会将基地址加载到寄存器
    // 基地址为 Argument 对应优化后 删除了无用的alloca 直接传递的结果，经过处理会将基地址加载到寄存器
    // 基地址为allocaInst 为 函数中声明数组的Alloca 带有偏移信息
    // 对于Argument LoadInst GlobalVaribal 直接使用MachineOperand编写的 get(ValPtr, Mmodule)即可自动处理  对于AllocaInst 处理较为特殊
    getelemInstPtr gep = std::static_pointer_cast<getelementptrInst>(getelem);
    int gainDim = gep->getgainDim();
    int gainDimBytes = gep->getgainDimBytes();
    ValPtr baseAddr = gep->getOperand(0);
    ValPtr offset = gep->getOperand(1);                             // 偏移 可以是临时变量 也可以是常数
    MOperaPtr Moffset = MachineOperand::get(offset, machineModule); // 获取offset对应操作数
    if (baseAddr->isAllocaInst())
    {
        AllocaInstPtr alloca = std::static_pointer_cast<AllocaInst>(baseAddr);
        assert(alloca->isAllocaArgument() && "IR may have some errors!"); // 一定是函数中的数组声明
        int allocaOffset = alloca->getOffset();                           // 获取相对于fp的偏移 负数
        // 先讨论 getelementptr指令的offset为常数的情况
        if (Moffset->isImm())
        {
            int offsetval = Moffset->getVal();
            int alloffset = offsetval + allocaOffset; // 相对于 fp的总偏移
            MOperaPtr newOffset = MachineOperand::get(MachineOperand::IMM, alloffset);
            newOffset = MachineOperand::AutoDealWithImm(newOffset, machineModule); // 自动处理
            // 下面创建 fp + 偏移 获取数组索引地址
            MBinaryInstPtr add = MBinaryInst::get(curblk, MachineInst::ADD, MachineOperand::get(getelem, machineModule), MachineOperand::createReg(11), newOffset);
            // 将指令加入块中
            curblk->addInstBack(add);
        }
        else
        {
            // getelementptr指令的offset不为常数
            //  先将 Moffset 和 allocaOffset 进行加法运算
            MOperaPtr addVreg = Moffset;
            if (allocaOffset != 0)
            {
                MOperaPtr allocaOffsetImm = MachineOperand::get(MachineOperand::IMM, allocaOffset);
                allocaOffsetImm = MachineOperand::AutoDealWithImm(allocaOffsetImm, machineModule); // 自动处理IMM
                // 偏移结果 addVreg
                addVreg = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo());
                MBinaryInstPtr add1 = MBinaryInst::get(curblk, MachineInst::ADD, MachineOperand::copy(addVreg), Moffset, allocaOffsetImm);
                curblk->addInstBack(add1);
            }
            // 下面创建 加法指令 获取 fp + reg  地址
            MBinaryInstPtr add2 = MBinaryInst::get(curblk, MachineInst::ADD, MachineOperand::get(getelem, machineModule), MachineOperand::createReg(11), addVreg);
            curblk->addInstBack(add2);
        }
    }
    else
    {
        // 获取基址寄存器
        MOperaPtr MbaseReg = MachineOperand::get(baseAddr, machineModule);
        // 下面讨论 Moffset的情况
        if (Moffset->isImm())
        {
            Moffset = MachineOperand::AutoDealWithImm(Moffset, machineModule); // 自动处理转化
        }
        // 创建 加法 获取最终位置
        MBinaryInstPtr add = MBinaryInst::get(curblk, MachineInst::ADD, MachineOperand::get(getelem, machineModule), MbaseReg, Moffset);
        curblk->addInstBack(add);
    }

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

        // 1. 创建一个对应的machineFunc
        MFuncPtr Mfun = MachineFunc::get(machineModule);
        Mfun->setmaxCallFunParmas(irfun->getMaxCallFunArgsNum()); // 设置最大调用函数参数数目
        machineModule->addFunc(Mfun);                             // 加入函数
        machineModule->setCurFun(Mfun);                           // 标记当前函数

        // 先将 irblocks编号一下 并顺便对应创建一个MachineBlock
        for (auto &irblk : irblocks)
        {
            machineModule->getNo(irblk);
            MBlockPtr mblk = MachineBlock::get(Mfun, machineModule->getNo(irblk));
            IRBlk2MBlk.emplace(irblk, mblk); // 加入到映射表中
            Mfun->addBlockBack(mblk);        // 加入函数中
        }
        // 下面进行正式的Arminst转换

        // 2. 遍历basicblocks
        for (auto &irblk : irblocks)
        {
            MBlockPtr curblk = IRBlk2MBlk[irblk];
            machineModule->setCurBlock(curblk); // 设置当前块  根据映射表
            // 顺带更新一下machineBlock的前驱后继
            auto irPreds = irblk->getImmedPreds(); // 前驱
            auto irSuccs = irblk->getJumpList();   // 后继
            for (auto &blk : irPreds)
            {
                // 更新前驱
                curblk->addPred(IRBlk2MBlk[blk]);
            }
            for (auto &blk : irSuccs)
            {
                // 更新后继
                curblk->addSucc(IRBlk2MBlk[blk]);
            }

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

        // 遍历完当前函数后 将记录计数器重置
        machineModule->CnterReset();
    }
    return true;
}