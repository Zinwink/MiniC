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

/// @brief 智能指针对象
/// @param _IRModule
/// @param _machineModule
/// @return
ArmInstGenPtr ArmInstGen::get(ModulePtr _IRModule, MModulePtr _machineModule)
{
    ArmInstGenPtr arm = std::make_shared<ArmInstGen>(_IRModule, _machineModule);
    return arm;
}

/// @brief IR指令对应的处理
/// @param IRinst
/// @return
bool ArmInstGen::IR2Arm(InstPtr IRinst)
{
    bool result = false;
    Opcode op = IRinst->getOpcode();
    if (IRinst->isICmpInst())
    {
        op = Opcode::ICMP;
    }
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
        offsetImm = MachineOperand::AutoDealWithImm(offsetImm, machineModule, true);
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
    MBlockPtr curblk = machineModule->getCurBlock();
    // IR 的LoadInst 的操作数 可以是 AllocaInst 也可以是 getelementptr 也可以是 globalVariable
    ValPtr srcAddr = load->getOperand(0);
    if (srcAddr->isAllocaInst())
    {
        AllocaInstPtr alloca = std::static_pointer_cast<AllocaInst>(srcAddr); // 转型
        int64_t offset = alloca->getOffset();                                 // 获取偏移
        // 创建load指令
        MOperaPtr offsetImm = MachineOperand::get(MachineOperand::IMM, offset);
        offsetImm = MachineOperand::AutoDealWithImm(offsetImm, machineModule, true); // 自动处理offsetImm
        MLoadInstPtr ldr = MLoadInst::get(curblk, MachineInst::LDR, MachineOperand::get(load, machineModule), MachineOperand::createReg(11), offsetImm);
        curblk->addInstBack(ldr);
        if (alloca->isAllocaArgument())
        {
            // 是对形参的alloca  对于后4形参 偏移需要修正
            ArgPtr arg = alloca->getAllocaArg();
            if (arg->getArgNo() > 3)
            {
                machineModule->getCurFun()->addAdjustInst(ldr); // 加入到需要修订的列表中
            }
        }
    }
    else if (srcAddr->isGlobalVariable())
    {
        // 需要先从 全局变量地址标签中 取出全局变量地址
        // 然后通过 存储地址的寄存器 取出值
        MOperaPtr addrLabel = MachineOperand::get(srcAddr, machineModule); // 标签地址
        // 2. 创建 ldr 指令将 标签地址加载到寄存器
        MOperaPtr addrReg = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo()); // 存放标签地址
        MLoadInstPtr ldrAddrLabel = MLoadInst::get(curblk, MachineInst::LDR, MachineOperand::copy(addrReg), addrLabel);
        // 3. 从 ldrAddrLabel 中加载全局变量的值
        MLoadInstPtr ldrValReg = MLoadInst::get(curblk, MachineInst::LDR, MachineOperand::get(load, machineModule), addrReg);
        curblk->addInstBack(ldrAddrLabel);
        curblk->addInstBack(ldrValReg);
    }
    else
    {
        assert(srcAddr->isGetelemPtrInst());
        MOperaPtr addrReg = MachineOperand::get(srcAddr, machineModule); // 获取存储地址的寄存器
        MLoadInstPtr ldr = MLoadInst::get(curblk, MachineInst::LDR, MachineOperand::get(load, machineModule), addrReg);
        curblk->addInstBack(ldr);
    }
    return true;
}

/// @brief 处理 Call  IR
/// @param call
/// @return
bool ArmInstGen::Call2ArmInst(InstPtr call)
{
    MBlockPtr &curblk = machineModule->getCurBlock();
    ValPtr funv = call->getOperand(0); // 获取调用的函数
    // 创建函数名 对应的Label操作数
    if (funv->getName() == "llvm.memset.p0i8.i64")
    {
        MOperaPtr LabelFun = MachineOperand::get("memset");
        std::vector<ValPtr> &operands = call->getOperandsList();
        // bl指令
        MBranchInstPtr bl = MBranchInst::get(curblk, MachineInst::BL, LabelFun);
        BitCastPtr bit = std::static_pointer_cast<BitCastInst>(operands[1]);
        ValPtr addr = bit->getOperand(0);                             // 地址操作数
        ValPtr bytes = operands[3];                                   // 字节数目
        MOperaPtr arg1 = nullptr;                                     // 存放数组的首地址
        MOperaPtr arg2 = MachineOperand::get(MachineOperand::IMM, 0); // 第二个参数 为0
        MOperaPtr arg3 = MachineOperand::get(bytes, machineModule);   // 存放字节数 立即数
        // 下面根据addr的类型 进行处理 主要因为全局变量数组和函数局部变量数组地址处理方式不一样
        if (addr->isAllocaInst())
        {
            AllocaInstPtr alloca = std::static_pointer_cast<AllocaInst>(addr);
            assert(!alloca->isAllocaArgument() && "IR may have some errors!"); // 一定是函数中的数组声明
            int allocaOffset = alloca->getOffset();                            // 相对于fp的偏移 负数
            MOperaPtr offset = MachineOperand::get(MachineOperand::IMM, allocaOffset);
            offset = MachineOperand::AutoDealWithImm(offset, machineModule); // 自动处理 数值 能作为立即数操作数 则保持不变 否则使用ldr伪指令加载
            // 使用 fp+offset的加法指令获取
            MOperaPtr dst = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo());
            MBinaryInstPtr add = MBinaryInst::get(curblk, MachineInst::ADD, dst, MachineOperand::createReg(11), offset);
            curblk->addInstBack(add);
            arg1 = MachineOperand::copy(dst); // 参数1的数组首地址地址得到
        }
        else if (addr->isGlobalVariable())
        {
            // 全局变量数组
            MOperaPtr addrL = MachineOperand::get(addr, machineModule);
            MOperaPtr glbvAddrReg = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo()); // 存放全局变量地址的寄存器
            MLoadInstPtr ldr = MLoadInst::get(curblk, MachineInst::LDR, glbvAddrReg, addrL);
            curblk->addInstBack(ldr);
            arg1 = MachineOperand::copy(glbvAddrReg); // 参数1数组首地址地址得到
        }
        else
        {
            // 目前来看没有其他情况
            // assert(arg1 != nullptr && "some erros may occur!");
        }
        assert(arg1 != nullptr && "some erros may occur!");
        // 将 arg1 arg2 arg3 分别移动到 r0,r1,r2
        MMovInstPtr mov1 = MMovInst::get(curblk, MachineInst::MOV, MachineOperand::createReg(0), arg1);
        curblk->addInstBack(mov1);
        MMovInstPtr mov2 = MMovInst::get(curblk, MachineInst::MOV, MachineOperand::createReg(1), arg2);
        curblk->addInstBack(mov2);
        MachineOperand::imm2Reg(arg3, 2, machineModule);
        bl->addUse(MachineOperand::createReg(0));
        bl->addUse(MachineOperand::createReg(1));
        bl->addUse(MachineOperand::createReg(2));
        bl->addDef(MachineOperand::createReg(0)); // 由于 r0-r3 不默认保护 认为调用时 都 def 了
        bl->addDef(MachineOperand::createReg(1));
        bl->addDef(MachineOperand::createReg(2));
        bl->addDef(MachineOperand::createReg(3));
        curblk->addInstBack(bl);
    }
    else
    {
        MOperaPtr LabelFun = MachineOperand::get(funv->getName());
        std::vector<ValPtr> &operands = call->getOperandsList();

        // bl指令
        MBranchInstPtr bl = MBranchInst::get(curblk, MachineInst::BL, LabelFun);

        for (size_t i = 1; i < operands.size(); i++)
        {
            MOperaPtr MparamOp = MachineOperand::get(operands[i], machineModule);
            // 前4号 形参使用 r0-r3
            if (i <= 4)
            {
                // 创建 mov 指令 会自动加入当前块
                MMovInst::create(curblk, MachineOperand::createReg(i - 1), MparamOp, machineModule);
                bl->addUse(MachineOperand::createReg(i - 1));
            }
            else
            {
                // 后4 形参  使用 str 指令将 形参值保存到栈内存中(偏移需要修正)
                int offset = 4 * (i - 5); // 形参的初始偏移  sp+#0  sp+#4
                MOperaPtr offsetImm = nullptr;
                if (offset != 0)
                {
                    offsetImm = MachineOperand::get(MachineOperand::IMM, offset);
                    offsetImm = MachineOperand::AutoDealWithImm(offsetImm, machineModule, true); // 自动修正IMM
                }

                // 创建 STR 指令
                if (MparamOp->isImm())
                {
                    MparamOp = MachineOperand::imm2VReg(MparamOp, machineModule);
                }
                MStorePtr str = MStore::get(curblk, MachineInst::STR, MparamOp, MachineOperand::createReg(13), offsetImm);
                // 加入当前块
                curblk->addInstBack(str);
            }
        }
        // 加入 bl 跳转指令
        bl->addDef(MachineOperand::createReg(0)); // 由于 r0-r3 不默认保护 认为调用时 都 def 了
        bl->addDef(MachineOperand::createReg(1));
        bl->addDef(MachineOperand::createReg(2));
        bl->addDef(MachineOperand::createReg(3));
        curblk->addInstBack(bl);
        // 跳转调用完毕后 使用mov 指令将 r0存放的返回值取出
        if (!(call->getType()->isVoidType()))
        {
            MMovInstPtr move_vreg_r0 = MMovInst::get(curblk, MachineInst::MOV, MachineOperand::get(call, machineModule), MachineOperand::createReg(0));
            curblk->addInstBack(move_vreg_r0);
        }
    }
    return true;
}

/// @brief 无条件跳转IR处理
/// @param _goto
/// @return
bool ArmInstGen::Goto2ArmInst(InstPtr _goto)
{
    MBlockPtr &curblk = machineModule->getCurBlock();
    ValPtr irop = _goto->getOperand(0); // 获取跳转目标 是BasicBlock类型
    MOperaPtr LBB = MachineOperand::get(irop, machineModule);
    MBranchInstPtr B = MBranchInst::get(curblk, MachineInst::B, LBB);
    curblk->addInstBack(B);
    return true;
}

/// @brief ICmp IRInst 对应的操作
/// @param icmp
/// @return
bool ArmInstGen::ICmp2ArmInst(InstPtr icmp)
{
    MBlockPtr &curblk = machineModule->getCurBlock();
    // 直接创建 icmp指令
    ValPtr left = icmp->getOperand(0);
    ValPtr right = icmp->getOperand(1);
    MOperaPtr leftM = MachineOperand::get(left, machineModule);

    /// 如果是立即数 则加载到 寄存器
    if (leftM->isImm())
    {
        leftM = MachineOperand::imm2VReg(leftM, machineModule);
    }
    MOperaPtr rightM = MachineOperand::get(right, machineModule);
    if (rightM->isImm())
    {
        rightM = MachineOperand::AutoDealWithImm(rightM, machineModule);
    }

    MCmpInstPtr cmp = MCmpInst::get(curblk, MachineInst::CMP, std::move(leftM), std::move(rightM));
    curblk->addInstBack(cmp);

    return true;
}

/// @brief 有条件 跳转IR处理
/// @param br
/// @return
bool ArmInstGen::CondBr2ArmInst(InstPtr br)
{
    MBlockPtr &curblk = machineModule->getCurBlock();
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
    MBlockPtr &curblk = machineModule->getCurBlock();
    // 目前来看 getelementptr指令的基地址可以是 Argument，AllocaInst, LoadInst，也可以是全局变量地址 GlobalVariable
    // 基地址为loadInst 对应 load alloca (而alloca是对形参的空间申请)，经过处理会将基地址加载到寄存器
    // 基地址为 Argument 对应优化后 删除了无用的alloca 直接传递的结果，经过处理会将基地址加载到寄存器
    // 基地址为allocaInst 为 函数中声明数组的Alloca 带有偏移信息
    // 对于Argument LoadInst GlobalVaribal 直接使用MachineOperand编写的 get(ValPtr, Mmodule)即可自动处理  对于AllocaInst 处理较为特殊
    // 偏移时是字节偏移 对偏移还要乘以4
    getelemInstPtr gep = std::static_pointer_cast<getelementptrInst>(getelem);
    int gainDim = gep->getgainDim();
    int gainDimBytes = gep->getgainDimBytes();
    ValPtr baseAddr = gep->getOperand(0);
    ValPtr offset = gep->getOperand(1);                             // 偏移 可以是临时变量 也可以是常数
    MOperaPtr Moffset = MachineOperand::get(offset, machineModule); // 获取offset对应操作数
    if (baseAddr->isAllocaInst())
    {
        AllocaInstPtr alloca = std::static_pointer_cast<AllocaInst>(baseAddr);
        assert(!alloca->isAllocaArgument() && "IR may have some errors!"); // 一定是函数中的数组声明
        int allocaOffset = alloca->getOffset();                            // 获取相对于fp的偏移 负数
        // 先讨论 getelementptr指令的offset为常数的情况
        if (Moffset->isImm())
        {
            int offsetval = Moffset->getVal();
            int alloffset = offsetval * gainDimBytes + allocaOffset; // 相对于 fp的总偏移
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
            // 由于数组元素是4字节 需要将 Moffset进行处理
            // 先使用lsl 移位实现 Moffset 乘以 gainDimBytes(由于数组目前元素一定是4字节 因此一定可以化为lsl 不过为了严谨还是增加乘法运算)
            // 下面的步骤主要用于更新Moffset 带有字节的偏移 (下面这段代码会多次复用  没有封装  后面使用是直接复制这段代码)
            int powNum = Arm32::isPowerOfTwo(gainDimBytes);
            if (powNum == -1)
            {
                // 不是幂次方 使用MUl指令 但需要将 gainDimBytes 加载到寄存器
                MOperaPtr gainDimBytesImm = MachineOperand::get(MachineOperand::IMM, gainDimBytes);
                gainDimBytesImm = MachineOperand::imm2VReg(gainDimBytesImm, machineModule);
                // 创建乘法指令
                MOperaPtr mulRes = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo());
                MBinaryInstPtr mul = MBinaryInst::get(curblk, MachineInst::MUL, mulRes, Moffset, gainDimBytesImm);
                curblk->addInstBack(mul);
                Moffset = MachineOperand::copy(mulRes); // 将 Moffset更新为乘以字节数的 偏移结果 后继使用add 基址加偏移
            }
            else if (powNum == 0)
            {
                // 是2的幂次方 但为0  无操作
            }
            else
            {
                // 是不为0的2的幂次方 使用lsl 指令
                MOperaPtr lslRes = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo());
                MOperaPtr powNumImm = MachineOperand::get(MachineOperand::IMM, powNum); // 2的幂次 立即数
                powNumImm = MachineOperand::AutoDealWithImm(powNumImm, machineModule);  // 自动处理
                MBinaryInstPtr lsl = MBinaryInst::get(curblk, MachineInst::LSL, lslRes, Moffset, powNumImm);
                curblk->addInstBack(lsl);
                Moffset = MachineOperand::copy(lslRes); // 将Moffset更新为字节型偏移供后继使用
            }

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
    else if (baseAddr->isGlobalVariable())
    {
        // 基地址是全局变量指示的地址   需要先将标签地址加载到寄存器中
        MOperaPtr addrL = MachineOperand::get(baseAddr, machineModule); // 创建地址标签
        // 需要先将 标签地址 加载到寄存器， 最后通过 str 将寄存器值保存至 [全局变量标签地址寄存器]
        MOperaPtr glbvAddrReg = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo()); // 存放全局变量地址的寄存器
        MLoadInstPtr ldr = MLoadInst::get(curblk, MachineInst::LDR, glbvAddrReg, addrL);
        curblk->addInstBack(ldr);
        // 创建加法 指令 地址寄存器 加偏移
        if (Moffset->isImm())
        {
            // 获取数值 得到字节数偏移
            int offsetval = Moffset->getVal();
            Moffset = MachineOperand::get(MachineOperand::IMM, offsetval * gainDimBytes); // 更新Moffset为字节数偏移立即数
            Moffset = MachineOperand::AutoDealWithImm(Moffset, machineModule);            // 自动处理转化
        }
        else
        {
            // Moffset不是数值类型
            int powNum = Arm32::isPowerOfTwo(gainDimBytes);
            if (powNum == -1)
            {
                // 不是幂次方 使用MUl指令 但需要将 gainDimBytes 加载到寄存器
                MOperaPtr gainDimBytesImm = MachineOperand::get(MachineOperand::IMM, gainDimBytes);
                gainDimBytesImm = MachineOperand::imm2VReg(gainDimBytesImm, machineModule);
                // 创建乘法指令
                MOperaPtr mulRes = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo());
                MBinaryInstPtr mul = MBinaryInst::get(curblk, MachineInst::MUL, mulRes, Moffset, gainDimBytesImm);
                curblk->addInstBack(mul);
                Moffset = MachineOperand::copy(mulRes); // 将 Moffset更新为乘以字节数的 偏移结果 后继使用add 基址加偏移
            }
            else if (powNum == 0)
            {
                // 是2的幂次方 但为0  无操作
            }
            else
            {
                // 是不为0的2的幂次方 使用lsl 指令
                MOperaPtr lslRes = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo());
                MOperaPtr powNumImm = MachineOperand::get(MachineOperand::IMM, powNum); // 2的幂次 立即数
                powNumImm = MachineOperand::AutoDealWithImm(powNumImm, machineModule);  // 自动处理
                MBinaryInstPtr lsl = MBinaryInst::get(curblk, MachineInst::LSL, lslRes, Moffset, powNumImm);
                curblk->addInstBack(lsl);
                Moffset = MachineOperand::copy(lslRes); // 将Moffset更新为字节型偏移供后继使用
            }
        }
        MBinaryInstPtr add = MBinaryInst::get(curblk, MachineInst::ADD, MachineOperand::get(getelem, machineModule), MachineOperand::copy(glbvAddrReg), Moffset);
        curblk->addInstBack(add);
    }
    else
    {
        // 获取基址寄存器
        MOperaPtr MbaseReg = MachineOperand::get(baseAddr, machineModule);
        // 下面讨论 Moffset的情况 并对 Moffset进行更新
        if (Moffset->isImm())
        {
            int offsetval = Moffset->getVal();
            Moffset = MachineOperand::get(MachineOperand::IMM, offsetval * gainDimBytes);
            Moffset = MachineOperand::AutoDealWithImm(Moffset, machineModule); // 自动处理转化
        }
        else
        {
            int powNum = Arm32::isPowerOfTwo(gainDimBytes);
            if (powNum == -1)
            {
                // 不是幂次方 使用MUl指令 但需要将 gainDimBytes 加载到寄存器
                MOperaPtr gainDimBytesImm = MachineOperand::get(MachineOperand::IMM, gainDimBytes);
                gainDimBytesImm = MachineOperand::imm2VReg(gainDimBytesImm, machineModule);
                // 创建乘法指令
                MOperaPtr mulRes = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo());
                MBinaryInstPtr mul = MBinaryInst::get(curblk, MachineInst::MUL, mulRes, Moffset, gainDimBytesImm);
                curblk->addInstBack(mul);
                Moffset = MachineOperand::copy(mulRes); // 将 Moffset更新为乘以字节数的 偏移结果 后继使用add 基址加偏移
            }
            else if (powNum == 0)
            {
                // 是2的幂次方 但为0  无操作
            }
            else
            {
                // 是不为0的2的幂次方 使用lsl 指令
                MOperaPtr lslRes = MachineOperand::get(MachineOperand::VREG, machineModule->getRegNo());
                MOperaPtr powNumImm = MachineOperand::get(MachineOperand::IMM, powNum); // 2的幂次 立即数
                powNumImm = MachineOperand::AutoDealWithImm(powNumImm, machineModule);  // 自动处理
                MBinaryInstPtr lsl = MBinaryInst::get(curblk, MachineInst::LSL, lslRes, Moffset, powNumImm);
                curblk->addInstBack(lsl);
                Moffset = MachineOperand::copy(lslRes); // 将Moffset更新为字节型偏移供后继使用
            }
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
    MBlockPtr curblk = machineModule->getCurBlock();
    ValPtr left = iadd->getOperand(0);
    ValPtr right = iadd->getOperand(1);
    MOperaPtr leftM = MachineOperand::get(left, machineModule);
    MOperaPtr rightM = MachineOperand::get(right, machineModule);
    if (leftM->isImm() && !rightM->isImm())
    {
        // 交换次序
        leftM = MachineOperand::AutoDealWithImm(leftM, machineModule);
        MBinaryInstPtr add = MBinaryInst::get(curblk, MachineInst::ADD, MachineOperand::get(iadd, machineModule), rightM, leftM);
        curblk->addInstBack(add);
        return true;
    }
    if (leftM->isImm() && rightM->isImm())
    {
        // 左右 都是 IMM  为了简单这里不进行常数合并  常数合并在IR完成
        // 先将leftM 加载到寄存器上
        leftM = MachineOperand::imm2VReg(leftM, machineModule);
        // 处理 rightM
        rightM = MachineOperand::AutoDealWithImm(rightM, machineModule);
        // 创建 add指令
        MBinaryInstPtr add = MBinaryInst::get(curblk, MachineInst::ADD, MachineOperand::get(iadd, machineModule), leftM, rightM);
        curblk->addInstBack(add);
        return true;
    }
    // 其他情况
    if (rightM->isImm())
    {
        rightM = MachineOperand::AutoDealWithImm(rightM, machineModule);
    }
    MBinaryInstPtr add = MBinaryInst::get(curblk, MachineInst::ADD, MachineOperand::get(iadd, machineModule), leftM, rightM);
    curblk->addInstBack(add);

    return true;
}

/// @brief 整数乘法
/// @param imul
/// @return
bool ArmInstGen::IMul2ArmInst(InstPtr imul)
{
    // mul 和 add的操作一样   转化时不考虑优化
    MBlockPtr curblk = machineModule->getCurBlock();
    ValPtr left = imul->getOperand(0);
    ValPtr right = imul->getOperand(1);
    MOperaPtr leftM = MachineOperand::get(left, machineModule);
    MOperaPtr rightM = MachineOperand::get(right, machineModule);
    if (leftM->isImm())
    {
        leftM = MachineOperand::imm2VReg(leftM, machineModule);
    }
    if (rightM->isImm())
    {
        rightM = MachineOperand::imm2VReg(rightM, machineModule);
    }
    MBinaryInstPtr mul = MBinaryInst::get(curblk, MachineInst::MUL, MachineOperand::get(imul, machineModule), leftM, rightM);
    curblk->addInstBack(mul);

    return true;
}

/// @brief 整数减法
/// @param isub
/// @return
bool ArmInstGen::ISub2ArmInst(InstPtr isub)
{
    // 减法 不能交换  和add 略微有些差异
    MBlockPtr curblk = machineModule->getCurBlock();
    ValPtr left = isub->getOperand(0);
    ValPtr right = isub->getOperand(1);
    MOperaPtr leftM = MachineOperand::get(left, machineModule);
    MOperaPtr rightM = MachineOperand::get(right, machineModule);
    if (leftM->isImm())
    {
        // 加载到寄存器
        leftM = MachineOperand::imm2VReg(leftM, machineModule);
    }
    if (rightM->isImm())
    {
        // 根据数值 判定是否可以作为立即数 否则 使用伪指令加载
        rightM = MachineOperand::AutoDealWithImm(rightM, machineModule);
    }
    // 创建 sub指令
    MBinaryInstPtr sub = MBinaryInst::get(curblk, MachineInst::SUB, MachineOperand::get(isub, machineModule), leftM, rightM);
    curblk->addInstBack(sub);

    return true;
}

/// @brief 整数除法
/// @param idiv
/// @return
bool ArmInstGen::IDiv2ArmInst(InstPtr idiv)
{
    // 除法 不能交换  和add 略微有些差异
    // 转化时不考虑优化
    MBlockPtr curblk = machineModule->getCurBlock();
    ValPtr left = idiv->getOperand(0);
    ValPtr right = idiv->getOperand(1);
    MOperaPtr leftM = MachineOperand::get(left, machineModule);
    MOperaPtr rightM = MachineOperand::get(right, machineModule);
    if (leftM->isImm())
    {
        // 加载到寄存器
        leftM = MachineOperand::imm2VReg(leftM, machineModule);
    }
    if (rightM->isImm())
    {
        // 根据数值 判定是否可以作为立即数 否则 使用伪指令加载
        rightM = MachineOperand::imm2VReg(rightM, machineModule);
    }
    // 创建 DIV指令
    MBinaryInstPtr div = MBinaryInst::get(curblk, MachineInst::SDIV, MachineOperand::get(idiv, machineModule), leftM, rightM);
    curblk->addInstBack(div);
    return true;
}

/// @brief 整数取余
/// @param srem
/// @return
bool ArmInstGen::ISrem2ArmInst(InstPtr srem)
{
    // 使用 __aeabi_idivmod实现
    // 需要将 被除数 除数 放入 r0,r1
    MBlockPtr curblk = machineModule->getCurBlock();
    MFuncPtr curfun = machineModule->getCurFun();
    ValPtr left = srem->getOperand(0);
    ValPtr right = srem->getOperand(1);
    MOperaPtr leftM = MachineOperand::get(left, machineModule);
    MOperaPtr rightM = MachineOperand::get(right, machineModule);
    // 2024-6-5 删除了push -pop 用来保护 r0 r1 的操作  LinearScan寄存器分配会做

    if (leftM->isImm())
    {
        leftM = MachineOperand::imm2Reg(leftM, 0, machineModule);
        if (rightM->isImm())
        {
            rightM = MachineOperand::imm2Reg(rightM, 1, machineModule);
        }
        else
        {
            // rightM 不是 r1  (简单优化 省去 mov r1,r1)
            // 创建mov 指令
            rightM = MachineOperand::AutoMovReg(rightM, 1, machineModule);
        }
    }
    else
    {
        leftM = MachineOperand::AutoMovReg(leftM, 0, machineModule);
        if (rightM->isImm())
        {
            rightM = MachineOperand::imm2Reg(rightM, 1, machineModule);
        }
        else
        {
            // rightM 不是 r1  (简单优化 省去 mov r1,r1)
            // 创建mov 指令
            rightM = MachineOperand::AutoMovReg(rightM, 1, machineModule);
        }
    }
    // 创建 bl 指令 调用 __aeabi_idivmod
    MBranchInstPtr bl = MBranchInst::get(curblk, MachineInst::BL, MachineOperand::get("__aeabi_idivmod"));
    bl->addDef(MachineOperand::createReg(0)); // 该函数调用会def r0 r1
    bl->addDef(MachineOperand::createReg(1)); //
    bl->addDef(MachineOperand::createReg(2));
    bl->addDef(MachineOperand::createReg(3));
    bl->addUse(MachineOperand::createReg(0));
    bl->addUse(MachineOperand::createReg(1));
    curblk->addInstBack(bl);
    // 将取余结果r1取出(商保存在r0  余数保存在r1)  会产生冗余 但为了简便先这样写
    MMovInstPtr mov_modRes = MMovInst::get(curblk, MachineInst::MOV, MachineOperand::get(srem, machineModule), MachineOperand::createReg(1));
    curblk->addInstBack(mov_modRes);
    return true;
}

/// @brief 逻辑左移
/// @param shl
/// @return
bool ArmInstGen::Shl2ArmInst(InstPtr shl)
{
    MBlockPtr curblk = machineModule->getCurBlock();
    ValPtr left = shl->getOperand(0);
    ValPtr right = shl->getOperand(1);
    MOperaPtr leftM = MachineOperand::get(left, machineModule);
    MOperaPtr rightM = MachineOperand::get(right, machineModule);
    if (leftM->isImm())
    {
        // 加载到寄存器
        leftM = MachineOperand::imm2VReg(leftM, machineModule);
    }
    // 翻译汇编时不做优化及常数合并 这个在IR里做
    assert(rightM->isImm() && "the shift must be imm");
    // 创建 lsl
    MBinaryInstPtr lsl = MBinaryInst::get(curblk, MachineInst::LSL, MachineOperand::get(shl, machineModule), leftM, rightM);
    curblk->addInstBack(lsl);
    return true;
}

/// @brief 算数右移
/// @param ashr
/// @return
bool ArmInstGen::Ashr2ArmInst(InstPtr ashr)
{
    MBlockPtr curblk = machineModule->getCurBlock();
    ValPtr left = ashr->getOperand(0);
    ValPtr right = ashr->getOperand(1);
    MOperaPtr leftM = MachineOperand::get(left, machineModule);
    MOperaPtr rightM = MachineOperand::get(right, machineModule);
    if (leftM->isImm())
    {
        // 加载到寄存器
        leftM = MachineOperand::imm2VReg(leftM, machineModule);
    }
    // 翻译汇编时不做优化及常数合并 这个在IR里做
    assert(rightM->isImm() && "the shift must be imm");
    // 创建 asr
    MBinaryInstPtr asr = MBinaryInst::get(curblk, MachineInst::ASR, MachineOperand::get(ashr, machineModule), leftM, rightM);
    curblk->addInstBack(asr);
    return true;
}

/// @brief 将 Zext翻译为对应的arm32指令
/// @param zext
/// @return
bool ArmInstGen::Zext2ArmInst(InstPtr zext)
{
    MBlockPtr &curblk = machineModule->getCurBlock();
    ValPtr condRes = zext->getOperand(0); // 获取条件 值 是icmp指令
    assert(condRes->isICmpInst() && "The LLVM IR maybe error or forget dealing with it!");
    MOperaPtr vreg = MachineOperand::get(zext, machineModule);
    ICmpInstPtr cmp = std::static_pointer_cast<ICmpInst>(condRes);
    MachineInst::condSuffix csuffix = IRCond2Machine(cmp);
    MZextInstPtr MZext = MZextInst::get(curblk, std::move(vreg), csuffix);
    curblk->addInstBack(MZext);
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
        Mfun->setFuncName(irfun->getName());                      // 函数名
        Mfun->setFuncArgsNum(irfun->getArgsList().size());        // 函数参数数目
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