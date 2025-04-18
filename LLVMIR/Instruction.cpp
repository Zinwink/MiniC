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
    case Opcode::GetelementPtr:
        name = string("getelementptr");
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
        name = string("sdiv");
        break;
    case Opcode::ModInteger:
        name = string("srem");
        break;
    case Opcode::SHl:
        name = string("shl");
        break;
    case Opcode::ASHR:
        name = string("ashr");
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
    case Opcode::Zext:
        name = string("zext");
        break;
    case Opcode::PhiNode:
        name = string("phi");
        break;

    default:
        name = string("UnknownOpcodeName");
        break;
    }
    return name;
}

/// @brief 是否时PhiNode
/// @return
bool Instruction::isPhiNode()
{
    return op == Opcode::PhiNode;
}

/// @brief 判断是否是分支指令
/// @return
bool Instruction::isBranchInst()
{
    return op == Opcode::Goto || op == Opcode::ConditionBr;
}

/// @brief 是否是Alloca
/// @return
bool Instruction::isAllocaInst()
{
    return op == Opcode::Alloca;
}

/// @brief 是否是storeinst
/// @return
bool Instruction::isStoreInst()
{
    return op == Opcode::Store;
}

/// @brief 是否是LoadInst
/// @return
bool Instruction::isLoadInst()
{
    return op == Opcode::Load;
}

/// @brief 是否是二元指令
/// @return
bool Instruction::isBinaryInst()
{
    return (int)op >= (int)Opcode::AddInteger &&
           (int)op <= (int)Opcode::ASHR;
}

/// @brief 是否是 getelementptr 指令
/// @return
bool Instruction::isGetelemPtrInst()
{
    return op == Opcode::GetelementPtr;
}

/// @brief 是否是整数比较指令
/// @return
bool Instruction::isICmpInst()
{
    // 目前 是 13-18是
    return (int)op >= (int)Opcode::GtInteger &&
           (int)op <= (int)Opcode::NotEqInteger;
}

/// @brief 是否是Zext 指令
/// @return
bool Instruction::isZextInst()
{
    return op == Opcode::Zext;
}

/// @brief 是否是ret Inst
/// @return
bool Instruction::isRetInst()
{
    return op == Opcode::Ret;
}

/// @brief 是否是 CallInst
/// @return
bool Instruction::isCallInst()
{
    return op == Opcode::Call;
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
    case Opcode::GetelementPtr:
        str = GetelementInstStr(inst, cnt);
        break;
    case Opcode::Zext:
        str = ZextInstStr(inst, cnt);
        break;
    case Opcode::BitCast:
        str = BitcastStr(inst, cnt);
        break;

    case Opcode::PhiNode:
        str = PhiNodeStr(inst, cnt);
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

/// @brief getelementptr指令翻译
/// @param getelem
/// @param cnt
/// @return
string GetelementInstStr(InstPtr getelem, Counter *cnt)
{
    string str;
    ValPtr arrayBase = getelem->getOperand(0); // 数组基质
    ValPtr offset = getelem->getOperand(1);
    PointerType *arrTy = static_cast<PointerType *>(arrayBase->getType());
    getelemInstPtr elemptr = std::static_pointer_cast<getelementptrInst>(getelem);
    int gain = elemptr->getgainDim();
    string gapstr = "";
    for (int i = 0; i < gain; i++)
    {
        gapstr += "i32 0, ";
    }

    str = getllvmID(getelem, cnt) + string(" = ") + getelem->getOpcodeName() + string(" ") + arrTy->getElemntTy()->TypeStr() + string(", ") + arrayBase->getType()->TypeStr() + string(" ") + getllvmID(arrayBase, cnt) + string(", ") + gapstr + offset->getType()->TypeStr() + string(" ") + getllvmID(offset, cnt);
    return str;
}

/// @brief 获取ZextInst的字符表示
/// @param zext
/// @param cnt
/// @return
string ZextInstStr(InstPtr zext, Counter *cnt)
{
    string str;
    ValPtr src = zext->getOperand(0);
    str = getllvmID(zext, cnt) + string(" = ") + zext->getOpcodeName() + string(" ") + src->getType()->TypeStr() + string(" ") + getllvmID(src, cnt) + string(" to ") + zext->getType()->TypeStr();
    return str;
}

/// @brief 获取phi节点的字符表示
/// @param phi
/// @param cnt
/// @return
string PhiNodeStr(InstPtr phi, Counter *cnt)
{
    PhiNodePtr phi_cast = std::static_pointer_cast<PhiNode>(phi);
    string str;
    str = getllvmID(phi, cnt) + string(" = ") + phi->getOpcodeName() + string(" ") + phi->getType()->TypeStr() + string(" ");
    string srclist = "";
    auto &flowList = phi_cast->getSrc();
    for (auto iter = flowList.begin(); iter != flowList.end(); iter++)
    {
        auto &pair = *iter;
        ValPtr &val = pair.first;
        string item = string("[ ") + getllvmID(val, cnt) + string(", ") + getllvmID(pair.second, cnt) + string(" ]");
        if (iter != std::prev(flowList.end()))
        {
            item += ", ";
        }
        srclist += item;
    }
    str += srclist;
    return str;
}

/// @brief 只用于打印查看  这是自己引入为了方便翻译的伪指令
/// @param phiMov
/// @param cnt
/// @return
string PhiElimMoveStr(InstPtr phiMov, Counter *cnt)
{
    string str = "mov ";
    ValPtr dst = phiMov->getOperand(0);
    ValPtr src = phiMov->getOperand(1);
    str += getllvmID(dst, cnt);
    str += ", ";
    str += getllvmID(src, cnt);
    return str;
}

/// @brief Bitcast指令对应的字符串
/// @param bitcast
/// @param cnt
/// @return
string BitcastStr(InstPtr bitcast, Counter *cnt)
{
    string str = getllvmID(bitcast, cnt);
    str += " = bitcast ";
    str += bitcast->getOperand(0)->getType()->TypeStr();
    str += " ";
    str += getllvmID(bitcast->getOperand(0), cnt);
    str += " to ";
    str += bitcast->getType()->TypeStr();
    return str;
}