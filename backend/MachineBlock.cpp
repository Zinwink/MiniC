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
void MachineBlock::insertInstBefore(MInstPtr before, MInstPtr inst)
{
    auto iter = std::find(MinstList.begin(), MinstList.end(), before);
    if (iter != MinstList.end())
    {
        MinstList.insert(iter, inst);
    }
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