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

    default:
        name = string("Unknown");
        break;
    }
    return name;
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