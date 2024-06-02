/**
 * @file MachineInst.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineInst.h"
#include "MachineBlock.h"
#include "MachineOperand.h"
#include <cassert>
#include <algorithm>
#include "Instruction.h"
#include "DerivedInst.h"
#include "PlatformArm32.h"
#include "MachineModule.h"

//************************** MachineInst **************************************
MBlockPtr &MachineInst::getParent()
{
    return parent;
}

void MachineInst::setParent(MBlockPtr _parent)
{
    parent = _parent;
}

void MachineInst::clear()
{
    parent.reset();
    for (auto &def : defs)
    {
        def->clear();
    }
    for (auto &use : uses)
    {
        use->clear();
    }
    defs.clear();
    uses.clear();
    defs.shrink_to_fit();
    uses.shrink_to_fit();
}

/// @brief 输出指令操作类型对应字符串
/// @return
std::string MachineInst::MinstTyStr()
{
    string str;
    switch (type)
    {
    case LDR:
        str = "ldr";
        break;
    case STR:
        str = "str";
        break;
    case MOV:
        str = "mov";
        break;
    case CMP:
        str = "cmp";
        break;
    case PUSH:
        str = "push";
        break;
    case POP:
        str = "pop";
        break;
    case ADD:
        str = "add";
        break;
    case SUB:
        str = "sub";
        break;
    case MUL:
        str = "mul";
        break;
    case SDIV:
        str = "sdiv";
        break;
    case AND:
        str = "add";
        break;
    case OR:
        str = "orr";
        break;
    case LSL:
        str = "lsl";
        break;
    case LSR:
        str = "lsr";
        break;
    case ASR:
        str = "asr";
        break;
    case B:
        str = "b";
        break;
    case BL:
        str = "bl";
        break;
    case BX:
        str = "bx";
        break;
    default:
        str = "unknown inst type";
        break;
    }
    return str;
}

/// @brief 将旧的操作数替换为新的
/// @param srcOld
/// @param srcNew
void MachineInst::replaceUsesWith(MOperaPtr srcOld, MOperaPtr srcNew)
{
    auto iter = std::find(uses.begin(), uses.end(), srcOld);
    if (iter != uses.end())
    {
        srcNew->setParent(shared_from_this());
        *iter = srcNew;
    }
}

/// @brief 输出条件后缀字符串
/// @return
std::string MachineInst::condSuffixStr()
{
    std::string str;
    switch (cond)
    {
    case EQ:
        str = "eq";
        break;
    case NE:
        str = "ne";
        break;
    case LT:
        str = "lt";
        break;
    case LE:
        str = "le";
        break;
    case GT:
        str = "gt";
        break;
    case GE:
        str = "ge";
        break;
    case NONE:
        str = "";
        break;
    default:
        str = "unkonw condition type!";
        break;
    }
    return str;
}

//************************** MBinaryInst **************************************
/// @brief 析构函数
MBinaryInst::~MBinaryInst()
{
    clear();
}

/// @brief 构造函数
/// @param parent
/// @param instTy
/// @param dst
/// @param src1
/// @param src2
/// @param cond
MBinaryInst::MBinaryInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr src2, condSuffix _cond)
{
    parent = p;
    type = instTy;
    cond = _cond;
    defs.push_back(dst);
    uses.push_back(src1);
    uses.push_back(src2);
}

/// @brief 创建智能指针对象
/// @param parent
/// @param instTy
/// @param dst
/// @param src1
/// @param src2
/// @param cond
/// @return
MBinaryInstPtr MBinaryInst::get(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr src2, condSuffix _cond)
{
    MBinaryInstPtr binary = std::make_shared<MBinaryInst>(p, instTy, dst, src1, src2, _cond);
    dst->setParent(binary);
    src1->setParent(binary);
    src2->setParent(binary);
    return binary;
}

/// @brief 输出字符串
/// @return
std::string MBinaryInst::toStr()
{
    string str = MinstTyStr();
    str += " ";
    str += defs[0]->toStr();
    str += ", ";
    str += uses[0]->toStr();
    str += ", ";
    str += uses[1]->toStr();
    return str;
}

//********************************* MLoadInst ****************************************

/// @brief ldr r1,#10  ldr r1, .addr_(标签地址) ldr r1, =1000000  ldr r1,[r2];
/// @param p
/// @param instTy
/// @param dst
/// @param src1
MLoadInst::MLoadInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1) : MachineInst()
{
    parent = p;
    type = instTy;
    defs.push_back(dst);
    uses.push_back(src1);
}

/// @brief ldr r1, [r1,#2] ldr r1, [fp,r2]   带有偏移的指令或偏移为0
/// @param p
/// @param instTy
/// @param dst
/// @param src1
/// @param offset
MLoadInst::MLoadInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr offset) : MachineInst()
{
    parent = p;
    type = instTy;
    defs.push_back(dst);
    uses.push_back(src1);
    uses.push_back(offset);
}

/// @brief 对偏移进行修正 加上偏置bias 主要用于修正 函数后4形参的偏移
/// @param bias
void MLoadInst::AddOffsetBias(int64_t bias)
{
    assert(uses.size() == 2 && "this loadInst has no offset! don't need to correct");
    assert(uses[1]->isImm() && "the offset is not Imm !");
    int64_t originOffset = uses[1]->getVal();
    int64_t newOffset = originOffset + bias;
    MOperaPtr offsetOp = MachineOperand::get(MachineOperand::IMM, newOffset);
    offsetOp->setParent(getSharedThis<MLoadInst>());
    uses[1] = std::move(offsetOp); // 设置新的偏移
}

/// @brief 创建智能指针对象
/// @param p
/// @param instTy
/// @param dst
/// @param src1
/// @param offset
/// @return
MLoadInstPtr MLoadInst::get(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr offset)
{
    if (offset == nullptr)
    {
        MLoadInstPtr ldr = std::make_shared<MLoadInst>(p, instTy, dst, src1);
        dst->setParent(ldr);
        src1->setParent(ldr);
        return ldr;
    }
    else
    {
        MLoadInstPtr ldr = std::make_shared<MLoadInst>(p, instTy, dst, src1, offset);
        dst->setParent(ldr);
        src1->setParent(ldr);
        offset->setParent(ldr);
        return ldr;
    }
}

/// @brief 输出字符串
/// @return
std::string MLoadInst::toStr()
{
    string str = MinstTyStr();
    str += " ";
    str += defs[0]->toStr();
    str += ", ";

    // ldr r1, =1000;
    if (uses[0]->isImm())
    {
        str += "=";
        str += std::to_string(uses[0]->getVal());
        return str;
    }
    // ldr r1, addr_np_o  地址标签
    if (uses[0]->isLabel())
    {
        str += uses[0]->getLabel();
        return str;
    }

    // ldr r1, [r2]  ldr r1,[r2,r3]  ldr r1, [r2,#2]
    if (uses[0]->isReg() || uses[0]->isVReg())
    {
        str += "[";
        str += uses[0]->toStr();
        if (uses.size() == 2)
        {
            str += ", ";
            str += uses[1]->toStr();
        }
        str += "]";
        return str;
    }
    return "error ocurred about the LoadInst";
}

//******************************* MStore ***************************************

/// @brief str r1,[r1,#1] str r1,[r2], str r2,[r3,r1]
/// @param p
/// @param instTy
/// @param src1
/// @param src2
/// @param offset
MStore::MStore(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2, MOperaPtr offset) : MachineInst()
{
    parent = p;
    type = instTy;
    uses.push_back(src1);
    uses.push_back(src2);
    if (offset != nullptr)
    {
        uses.push_back(offset);
    }
}

/// @brief 对偏移进行修正 加上偏置bias 主要用于修正函数后4形参的偏移
/// @param bias
void MStore::AddOffsetBias(int64_t bias)
{
    assert(uses.size() == 3 && "this StoreInst has no offset! don't need to correct");
    assert(uses[2]->isImm() && "the offset is not Imm !");
    int64_t originOffset = uses[2]->getVal();
    int64_t newOffset = originOffset + bias;
    MOperaPtr offsetOp = MachineOperand::get(MachineOperand::IMM, newOffset);
    offsetOp->setParent(getSharedThis<MStore>());
    uses[2] = std::move(offsetOp); // 设置新的偏移
}

/// @brief 创建智能指针
/// @param p
/// @param instTy
/// @param src1
/// @param src2
/// @param offset
/// @return
MStorePtr MStore::get(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2, MOperaPtr offset)
{
    MStorePtr str = std::make_shared<MStore>(p, instTy, src1, src2, offset);
    src1->setParent(str);
    src2->setParent(str);
    if (offset != nullptr)
    {
        offset->setParent(str);
    }
    return str;
}

/// @brief 输出字符串
/// @return
std::string MStore::toStr()
{
    string str = MinstTyStr();
    str += " ";
    str += uses[0]->toStr();
    str += ", [";
    str += uses[1]->toStr();
    if (uses.size() == 3)
    {
        // 有三个操作数
        str += ", ";
        str += uses[2]->toStr();
    }
    str += "]";
    return str;
}

//****************************************  MMovInst **********************************************
/// @brief 构造函数 mov r1,r2  mov r1,#2 形式  condsuffix 可加mov 条件 如 movne
/// @param p
/// @param instTy
/// @param dst
/// @param src1
/// @param _cond
MMovInst::MMovInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, condSuffix _cond) : MachineInst()
{
    parent = p;
    type = instTy;
    cond = _cond;
    defs.push_back(dst);
    uses.push_back(src1);
}

/// @brief 创建智能指针对象
/// @param p
/// @param instTy
/// @param dst
/// @param src1
/// @param _cond
/// @return
MMovInstPtr MMovInst::get(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, condSuffix _cond)
{
    MMovInstPtr mov = std::make_shared<MMovInst>(p, instTy, dst, src1, _cond);
    dst->setParent(mov);
    src1->setParent(mov);
    return mov;
}

/// @brief 根据操作数类型智能创建mov指令 无条件后缀
/// @param p
/// @param instTy
/// @param dst
/// @param src1
/// @param _cond
/// @return
void MMovInst::create(MBlockPtr p, MOperaPtr dst, MOperaPtr src1, MModulePtr Mmodule)
{
    assert((dst->isReg() || dst->isVReg()) && !src1->isLabel());
    // 不会对 dst src1进行拷贝 如不希望改变 在外应创建副本
    if (src1->isImm())
    {
        int val = src1->getVal();
        if (Arm32::canBeImmOperand(val))
        {
            // 直接创建mov 指令
            MMovInstPtr mov = MMovInst::get(p, MachineInst::MOV, dst, src1);
            Mmodule->getCurBlock()->addInstBack(mov);
            return;
        }
        else
        {
            // 使用ldr 伪指令
            MLoadInstPtr ldr = MLoadInst::get(p, MachineInst::LDR, dst, src1);
            Mmodule->getCurBlock()->addInstBack(ldr);
            return;
        }
    }
    // 其他情况 创建 mov 指令
    else
    {
        MMovInstPtr mov = MMovInst::get(p, MachineInst::MOV, dst, src1);
        Mmodule->getCurBlock()->addInstBack(mov);
    }
}

/// @brief 输出字符串
/// @return
std::string MMovInst::toStr()
{
    string str = MinstTyStr();
    str += condSuffixStr();
    str += " ";
    str += defs[0]->toStr();
    str += ", ";
    str += uses[0]->toStr();
    return str;
}

//*************************************** MCmpInst ******************************************************
/// @brief 构造函数
/// @param p
/// @param instTy
/// @param src1
/// @param src2
MCmpInst::MCmpInst(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2) : MachineInst()
{
    parent = p;
    type = instTy;
    uses.push_back(src1);
    uses.push_back(src2);
}

/// @brief 创建智能指针类型
/// @param p
/// @param instTy
/// @param src1
/// @param src2
/// @return
MCmpInstPtr MCmpInst::get(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2)
{
    MCmpInstPtr cmp = std::make_shared<MCmpInst>(p, instTy, src1, src2);
    src1->setParent(cmp);
    src2->setParent(cmp);
    return cmp;
}

/// @brief 输出字符串
/// @return
std::string MCmpInst::toStr()
{
    string str = MinstTyStr();
    str += " ";
    str += uses[0]->toStr();
    str += ", ";
    str += uses[1]->toStr();
    return str;
}

//******************************* MStackInst ****************************************
/// @brief 构造函数 push,pop 栈相关的指令
/// @param p
/// @param instTy
/// @param srcs
MStackInst::MStackInst(MBlockPtr p, MinstTy instTy, std::vector<MOperaPtr> srcs)
{
    parent = p;
    type = instTy;
    if (instTy == PUSH)
    {
        for (auto &src : srcs)
        {
            uses.push_back(src);
        }
    }
    else if (instTy == POP)
    {
        for (auto &src : srcs)
        {
            defs.push_back(src);
        }
    }
}

/// @brief 设置push pop的操作数  寄存器分配后回填
/// @param regs
void MStackInst::setRegs(std::vector<MOperaPtr> &regs)
{

    if (type == PUSH)
    {
        uses.clear();
        for (auto &src : regs)
        {
            src->setParent(getSharedThis<MStackInst>());
            uses.push_back(std::move(src));
        }
    }
    else if (type == POP)
    {
        defs.clear();
        for (auto &src : regs)
        {
            src->setParent(getSharedThis<MStackInst>());
            defs.push_back(std::move(src));
        }
    }

    regs.clear();
    regs.shrink_to_fit();
}

/// @brief 创建智能指针对象
/// @param p
/// @param instTy
/// @param srcs
/// @return
MStackInstPtr MStackInst::get(MBlockPtr p, MinstTy instTy, std::vector<MOperaPtr> srcs)
{
    MStackInstPtr stk = std::make_shared<MStackInst>(p, instTy, srcs);
    for (auto &src : srcs)
    {
        src->setParent(stk); // 设置parent
    }
    return stk;
}

/// @brief 输出字符串
/// @return
std::string MStackInst::toStr()
{
    string str = MinstTyStr();

    str += "   ";
    str += "{";
    if (type == PUSH)
    {
        for (size_t i = 0; i < uses.size(); i++)
        {
            str += uses[i]->toStr();
            if (i != (uses.size() - 1))
            {
                // 不是最后一个
                str += ", ";
            }
        }
    }
    else if (type == POP)
    {
        for (size_t i = 0; i < defs.size(); i++)
        {
            str += defs[i]->toStr();
            if (i != (defs.size() - 1))
            {
                // 不是最后一个
                str += ", ";
            }
        }
    }

    str += "}";
    return str;
}

//******************************** MBranchInst ***********************************************

/// @brief 构造 b  bne bl bx 等
/// @param p
/// @param instTy
/// @param src
/// @param _cond
MBranchInst::MBranchInst(MBlockPtr p, MinstTy instTy, MOperaPtr src, condSuffix _cond) : MachineInst()
{
    parent = p;
    type = instTy;
    cond = _cond;
    uses.push_back(src);
}

/// @brief 创建智能指针对象 branch
/// @param p
/// @param instTy
/// @param src
/// @param _cond
/// @return
MBranchInstPtr MBranchInst::get(MBlockPtr p, MinstTy instTy, MOperaPtr src, condSuffix _cond)
{
    MBranchInstPtr b = std::make_shared<MBranchInst>(p, instTy, src, _cond);
    src->setParent(b);
    return b;
}

/// @brief 输出字符串
/// @return
std::string MBranchInst::toStr()
{
    string str = MinstTyStr();
    str += condSuffixStr();
    str += " ";
    str += uses[0]->toStr();
    return str;
}

/// @brief 根据ICmp IR比较指令获取条件后缀
/// @param icmp
/// @return
MachineInst::condSuffix IRCond2Machine(ICmpInstPtr icmp)
{
    /*
        GtInteger,        // 大于 icmp sgt/ugt
        LtIntegr,     // 小于  icmp slt/ult
        EqInTeger,    // ==  icmp eq
        GeInTeger,    // >=
        LeInteger,    // <=
        NotEqInteger, // !=
    */
    MachineInst::condSuffix cond;
    switch (icmp->getOpcode())
    {
    case Opcode::GtInteger:
        cond = MachineInst::condSuffix::GT;
        break;

    case Opcode::LtIntegr:
        cond = MachineInst::condSuffix::LT;
        break;
    case Opcode::EqInTeger:
        cond = MachineInst::condSuffix::EQ;
        break;
    case Opcode::GeInTeger:
        cond = MachineInst::condSuffix::GE;
        break;
    case Opcode::LeInteger:
        cond = MachineInst::condSuffix::LE;
        break;
    case Opcode::NotEqInteger:
        cond = MachineInst::condSuffix::NE;
        break;

    default:
        cond = MachineInst::condSuffix::NONE;
        break;
    }
    return cond;
}