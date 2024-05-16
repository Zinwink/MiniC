/**
 * @file Instruction.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Instruction.h"
#include "Module.h"
#include "DerivedInst.h"

/// @brief 获取指令操作码对应的名字
/// @return
string Instruction::getOpcodeName()
{
    string name;
    switch (op)
    {
    case Opcode::Alloca:
        name = string("alloca");
        break;
    case Opcode::Store:
        name = string("store");
        break;
    case Opcode::Ret:
        name = string("ret");
        break;
    case Opcode::Call:
        name = string("call");
        break;
    case Opcode::Goto:
        name = string("br");
        break;
    case Opcode::ConditionBr:
        name = string("br");
        break;
    case Opcode::Load:
        name = string("load");
        break;
    case Opcode::AddInteger:
        name = string("add");
        break;
    case Opcode::SubInteger:
        name = string("sub");
        break;
    case Opcode::MulInteger:
        name = string("mul");
        break;
    case Opcode::DivInteger:
        name = string("div");
        break;
    case Opcode::ModInteger:
        name = string("mod");
        break;
    case Opcode::GtInteger:
        name = string("icmp sgt");
        break;
    case Opcode::EqInTeger:
        name = string("icmp eq");
        break;
    case Opcode::LtIntegr:
        name = string("icmp slt");
        break;

    case Opcode::GeInTeger:
        name = string("icmp sge");
        break;
    case Opcode::LeInteger:
        name = string("icmp sle");
        break;
    case Opcode::NotEqInteger:
        name = string("icmp ne");
        break;

    default:
        name = string("UnknownOpcodeName");
        break;
    }
    return name;
}

/// @brief 判断是否是分支指令
/// @return
bool Instruction::isBranchInst()
{
    return op == Opcode::Goto || op == Opcode::ConditionBr;
}

/// @brief 获取指令的字符串翻译
/// @param inst
/// @param cnt
/// @return
string Instruction::toIRstr(InstPtr inst, Counter *cnt)
{
    string str = "unknown inst str!";
    switch (inst->getOpcode())
    {
    case Opcode::Alloca:
        str = AllocaInstStr(inst, cnt);
        break;
    case Opcode::Store:
        str = StoreInstStr(inst, cnt);
        break;
    case Opcode::Load:
        str = LoadInstStr(inst, cnt);
        break;
    case Opcode::Ret:
        str = RetInstStr(inst, cnt);
        break;
    case Opcode::AddInteger:
    case Opcode::SubInteger:
    case Opcode::DivInteger:
    case Opcode::MulInteger:
    case Opcode::ModInteger:
        str = BinaryInstStr(inst, cnt);
        break;
    case Opcode::Call:
        str = CallInstStr(inst, cnt);
        break;
    case Opcode::Goto:
    case Opcode::ConditionBr:
        str = BranchInstStr(inst, cnt);
        break;
    case Opcode::GtInteger:
    case Opcode::LtIntegr:
    case Opcode::EqInTeger:
    case Opcode::GeInTeger:
    case Opcode::LeInteger:
    case Opcode::NotEqInteger:
        str = ICmpInstStr(inst, cnt);
        break;

    default:
        break;
    }
    return str;
}

/// @brief AllocaInst文本
/// @param alloca
/// @return
string AllocaInstStr(InstPtr alloca, Counter *cnt)
{
    AllocaInstPtr allonew = std::static_pointer_cast<AllocaInst>(alloca);
    string str = getllvmID(alloca, cnt) + string(" = ") + alloca->getOpcodeName() + string(" ") + allonew->getAllocatedType()->TypeStr();
    return str;
}

/// @brief StoreInst文本
/// @param store
/// @return
string StoreInstStr(InstPtr store, Counter *cnt)
{
    ValPtr src = store->getOperand(0);
    ValPtr dst = store->getOperand(1);
    string str = string("store ") + src->getType()->TypeStr() + string(" ") + getllvmID(src, cnt) + string(", ") + dst->getType()->TypeStr() + string(" ") + getllvmID(dst, cnt);
    return str;
}

/// @brief 二元运算文本
/// @param binaryop
/// @return
string BinaryInstStr(InstPtr binaryop, Counter *cnt)
{
    ValPtr left = binaryop->getOperand(0);
    ValPtr right = binaryop->getOperand(1);
    string str = getllvmID(binaryop, cnt) + string(" = ") + binaryop->getOpcodeName() + string(" ") + binaryop->getType()->TypeStr() + string(" ") + getllvmID(left, cnt) + string(", ") + getllvmID(right, cnt);
    return str;
}

/// @brief LoadInst文本
/// @param load
/// @param cnt
/// @return
string LoadInstStr(InstPtr load, Counter *cnt)
{
    ValPtr loadPtr = load->getOperand(0);
    Type *loadPtrTy = loadPtr->getType();
    PointerType *convertToptrTy = static_cast<PointerType *>(loadPtrTy);
    Type *elemtTy = convertToptrTy->getElemntTy();
    string str = getllvmID(load, cnt) + string(" = ") + load->getOpcodeName() + string(" ") + elemtTy->TypeStr() + string(", ") + loadPtrTy->TypeStr() + string(" ") + getllvmID(loadPtr, cnt);
    return str;
}

/// @brief RetInst文本
/// @param ret
/// @param cnt
/// @return
string RetInstStr(InstPtr ret, Counter *cnt)
{
    string str;
    if (ret->getOperandNum() == 0)
    {
        str = ret->getOpcodeName() + string(" void");
    }
    else
    {
        ValPtr retVal = ret->getOperand(0);
        str = ret->getOpcodeName() + string(" ") + retVal->getType()->TypeStr() + string(" ") + getllvmID(retVal, cnt);
    }
    return str;
}

/// @brief CallInst文本
/// @param call
/// @param cnt
/// @return
string CallInstStr(InstPtr call, Counter *cnt)
{
    ValPtr vfun = call->getOperand(0);
    FuncPtr fun = std::static_pointer_cast<Function>(vfun);
    string argsStr = "";
    int argsNum = call->getOperandNum() - 1;
    for (int ord = 1; ord <= argsNum; ord++)
    {
        ValPtr arg = call->getOperand(ord);
        argsStr += arg->getType()->TypeStr() + string(" ") + getllvmID(arg, cnt);
        if (ord < argsNum)
        {
            argsStr += ", ";
        }
    }
    string str;
    if (call->getType()->isVoidType())
    {
        str = call->getOpcodeName() + string(" void ") + getllvmID(vfun, cnt) + string("(") + argsStr + string(")");
    }
    else
    {
        str = getllvmID(call, cnt) + string(" = ") + call->getOpcodeName() + string(" ") + call->getType()->TypeStr() + string(" ") + getllvmID(vfun, cnt) + string("(") + argsStr + string(")");
    }
    return str;
}

/// @brief branchInst输出文本
/// @param br
/// @param cnt
/// @return
string BranchInstStr(InstPtr br, Counter *cnt)
{
    string str;
    if (br->getOpcode() == Opcode::Goto)
    {
        // 无条件跳转
        ValPtr ifTrue = br->getOperand(0); // br label %编号
        str = br->getOpcodeName() + string(" label ") + getllvmID(ifTrue, cnt);
    }
    else
    {
        ValPtr cond = br->getOperand(0); // 条件
        ValPtr ifTrue = br->getOperand(1);
        ValPtr ifFalse = br->getOperand(2);
        // 条件跳转
        str = br->getOpcodeName() + string(" ") + cond->getType()->TypeStr() + string(" ") + getllvmID(cond, cnt) + string(", label ") + getllvmID(ifTrue, cnt) + string(", label ") + getllvmID(ifFalse, cnt);
    }
    return str;
}

/// @brief 比较语句文本
/// @param icmp
/// @param cnt
/// @return
string ICmpInstStr(InstPtr icmp, Counter *cnt)
{
    ValPtr left = icmp->getOperand(0);
    ValPtr right = icmp->getOperand(1);
    string str;
    str = getllvmID(icmp, cnt) + string(" = ") + icmp->getOpcodeName() + string(" ") + left->getType()->TypeStr() + string(" ") + getllvmID(left, cnt) + string(", ") + getllvmID(right, cnt);
    return str;
}