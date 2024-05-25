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

//************************** MachineInst **************************************
MBlockPtr MachineInst::getParent()
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
        def->setParent(nullptr);
    }
    for (auto &use : uses)
    {
        use->setParent(nullptr);
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
        *iter = srcNew; // 替换
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
    dst->setParent(shared_from_this());
    src1->setParent(shared_from_this());
    src2->setParent(shared_from_this());
    defs.push_back(std::move(dst));
    uses.push_back(std::move(src1));
    uses.push_back(std::move(src2));
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
MLoadInst::MLoadInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1)
{
    parent = p;
    type = instTy;
    dst->setParent(shared_from_this());
    src1->setParent(shared_from_this());
    defs.push_back(std::move(dst));
    uses.push_back(std::move(src1));
}

/// @brief ldr r1, [r1,#2] ldr r1, [fp,r2]   带有偏移的指令或偏移为0
/// @param p
/// @param instTy
/// @param dst
/// @param src1
/// @param offset
MLoadInst::MLoadInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, MOperaPtr offset)
{
    parent = p;
    type = instTy;
    dst->setParent(shared_from_this());
    src1->setParent(shared_from_this());
    offset->setParent(shared_from_this());
    defs.push_back(std::move(dst));
    uses.push_back(std::move(src1));
    uses.push_back(std::move(offset));
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
        return ldr;
    }
    else
    {
        MLoadInstPtr ldr = std::make_shared<MLoadInst>(p, instTy, dst, src1, offset);
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
            return str;
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
MStore::MStore(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2, MOperaPtr offset)
{
    parent = p;
    type = instTy;
    src1->setParent(shared_from_this());
    src2->setParent(shared_from_this());
    uses.push_back(std::move(src1));
    uses.push_back(std::move(src2));
    if (offset != nullptr)
    {
        offset->setParent(shared_from_this());
        uses.push_back(std::move(offset));
    }
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
MMovInst::MMovInst(MBlockPtr p, MinstTy instTy, MOperaPtr dst, MOperaPtr src1, condSuffix _cond)
{
    parent = p;
    type = instTy;
    cond = _cond;
    dst->setParent(shared_from_this());
    src1->setParent(shared_from_this());
    defs.push_back(std::move(dst));
    uses.push_back(std::move(src1));
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
    return mov;
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
MCmpInst::MCmpInst(MBlockPtr p, MinstTy instTy, MOperaPtr src1, MOperaPtr src2)
{
    parent = p;
    type = instTy;
    src1->setParent(shared_from_this());
    src2->setParent(shared_from_this());
    uses.push_back(std::move(src1));
    uses.push_back(std::move(src2));
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
    for (auto &src : srcs)
    {
        src->setParent(shared_from_this());
        uses.push_back(std::move(src));
    }
}

/// @brief 创建智能指针对象
/// @param p
/// @param instTy
/// @param srcs
/// @return
MStackInstPtr MStackInst::get(MBlockPtr p, MinstTy instTy, std::vector<MOperaPtr> srcs)
{
    MStackInstPtr stk = std::make_shared<MStackInst>(p, instTy, srcs);
    return stk;
}

/// @brief 输出字符串
/// @return
std::string MStackInst::toStr()
{
    string str = MinstTyStr();
    str += " ";
    str += "{";
    for (size_t i = 0; i < uses.size(); i++)
    {
        str += uses[i]->toStr();
        if (i != (uses.size() - 1))
        {
            // 不是最后一个
            str += ", ";
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
MBranchInst::MBranchInst(MBlockPtr p, MinstTy instTy, MOperaPtr src, condSuffix _cond)
{
    parent = p;
    type = instTy;
    cond = _cond;
    src->setParent(shared_from_this());
    uses.push_back(std::move(src));
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
