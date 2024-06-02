/**
 * @file MachineBlock.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineBlock.h"
#include "MachineFunc.h"

/// @brief 析构函数
MachineBlock::~MachineBlock()
{
    parent.reset();
    preds.clear();
    preds.shrink_to_fit();
    succs.clear();
    succs.shrink_to_fit();
    MinstList.clear();
    liveIn.clear();
    liveOut.clear();
}

/// @brief 手动释放 打破环 使智能指针自动释放
void MachineBlock::clear()
{
    parent.reset();
    preds.clear();
    succs.clear();
    preds.shrink_to_fit();
    succs.shrink_to_fit();
    for (auto &l : MinstList)
    {
        l->clear();
    }
    MinstList.clear();
    liveIn.clear();
    liveOut.clear();
}

/// @brief 构造函数
/// @param p
/// @param n
MachineBlock::MachineBlock(MFuncPtr p, uint64_t n)
{
    parent = p;
    BBno = n;
    label = string(".LBB");
    label += std::to_string(parent->getFuncNo());
    label += "_";
    label += std::to_string(n);
}

/// @brief 将汇编指令添加到末尾
/// @param inst
void MachineBlock::addInstBack(MInstPtr inst)
{
    MinstList.push_back(inst);
}

/// @brief 在before前插入 inst指令 （用于溢出内存时插入load指令）
/// @param before
/// @param inst
std::list<MInstPtr>::iterator MachineBlock::insertInstBefore(MInstPtr before, MInstPtr inst)
{
    auto iter = std::find(MinstList.begin(), MinstList.end(), before);
    if (iter != MinstList.end())
    {
        auto resIter = MinstList.insert(iter, inst);
        return resIter;
    }
    return iter;
}

/// @brief 在某条指令后插入一条指令 (寄存器分配时对 def 后插入 store保存旧值至栈中)
/// @param after
/// @param inst
std::list<MInstPtr>::iterator MachineBlock::insertInstAfter(MInstPtr after, MInstPtr inst)
{
    auto iter = std::find(MinstList.begin(), MinstList.end(), after);
    if (iter != MinstList.end())
    {
        auto resIter = MinstList.insert(std::next(iter), inst);
        return resIter;
    }
    return iter;
}

/// @brief 插入指令 在指定迭代器
/// @param iter
/// @param inst
std::list<MInstPtr>::iterator MachineBlock::insertInst(std::list<MInstPtr>::iterator iter, MInstPtr inst)
{
    if (iter != MinstList.end())
    {
        auto resIter = MinstList.insert(iter, inst);
        return resIter;
    }
    return iter;
}

/// @brief 添加前驱
/// @param block
void MachineBlock::addPred(MBlockPtr block)
{
    auto iter = std::find(preds.begin(), preds.end(), block);
    if (iter == preds.end())
    {
        preds.push_back(block);
    }
}

/// @brief 添加后继
/// @param block
void MachineBlock::addSucc(MBlockPtr block)
{
    auto iter = std::find(succs.begin(), succs.end(), block);
    if (iter == succs.end())
    {
        succs.push_back(block);
    }
}

/// @brief 删除前驱
/// @param block
void MachineBlock::removePred(MBlockPtr block)
{
    auto iter = std::find(preds.begin(), preds.end(), block);
    if (iter != preds.end())
    {
        // 找到
        preds.erase(iter);
    }
}

/// @brief 删除后继
/// @param block
void MachineBlock::removeSucc(MBlockPtr block)
{
    auto iter = std::find(succs.begin(), succs.end(), block);
    if (iter != succs.end())
    {
        // 找到
        succs.erase(iter);
    }
}

/// @brief 获取块的智能指针对象
/// @param p
/// @param n
/// @return
MBlockPtr MachineBlock::get(MFuncPtr p, uint64_t n)
{
    MBlockPtr block = std::make_shared<MachineBlock>(p, n);
    return block;
}

/// @brief 块翻译为字符串
/// @return
string MachineBlock::toStr()
{
    string str = label + ":";
    str += "\n";
    for (auto &minst : getInstList())
    {
        str += "\t";
        str += minst->toStr();
        str += "\n";
    }
    return str;
}