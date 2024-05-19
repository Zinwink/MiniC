/**
 * @file ElimBasicBlock.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 对基本块的操作
 * @version 1.0
 * @date 2024-05-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ElimBasicBlock.h"
#include <algorithm>
#include <iostream>

/// @brief 消除函数中无用基本块
/// @param fun
void ElimUseLessBBlock(FuncPtr fun)
{
    // 从Entry开始遍历基本块 标记可达基本块
    ReachableAnalysis(fun->getEntryBlock());
    std::list<BasicBlockPtr> &blockList = fun->getBasicBlocks();
    for (bblockIter it = blockList.begin(); it != blockList.end();)
    {
        if (!(*it)->hasSign())
        {
            // 该基本块跳转的块
            std::vector<BasicBlockPtr> jumpB = (*it)->getJumpList();
            for (auto &j : jumpB)
            {
                // 从 j的 的userList中删除 当前基本块
                auto iterUser = std::find(j->getUseList().begin(), j->getUseList().end(), (*it)->getInstLists().back()); // 将该基本快的br语句从 j的UseList中删除
                j->getUseList().erase(iterUser);
            }
            (*it)->getInstLists().clear();
            it = blockList.erase(it); // 删除
        }
        else
        {
            it = mergeBasicBlocks((*it), it);
        }
    }
}

/// @brief 处理Module
/// @param _modul Module 包含 functionList
void ElimUseLessBBlock(ModulePtr _modul)
{
    for (auto &fun : _modul->getFunList())
    {
        ElimUseLessBBlock(fun);
    }
}

/// @brief 基本块可达性分析
/// @param blcok
void ReachableAnalysis(BasicBlockPtr blcok)
{
    if (blcok->hasSign())
    {
        return;
    }
    blcok->setSign();
    std::vector<BasicBlockPtr> jumps = blcok->getJumpList();
    for (auto &j : jumps)
    {
        ReachableAnalysis(j);
    }
}

/// @brief 合并基本块
/// @param block 当前基本块
/// @param it 当前基本块的迭代器
/// @return 若可合并，当前基本块删除后 返回迭代器
bblockIter &mergeBasicBlocks(BasicBlockPtr block, bblockIter &it)
{
    // 判断当前基本块是否可合并
    // 当前基本块只有一条 branch语句时 可以删除
    FuncPtr fun = block->getParentFun();
    assert(fun != nullptr && "Error: block has no parent function");
    std::vector<BasicBlockPtr> presList = block->getImmedPreds();
    std::vector<BasicBlockPtr> next = block->getJumpList(); // 后继
    if (block->getName() == "entry")
    {
        // 无操作
        ++it;
        return it;
    }
    if (block->getInstLists().size() == 1 && block->getName() != "exit")
    {
        // 若只有一条指令 则一定是无条件跳转指令
        Value::replaceAllUsesWith(block, next[0]); // 替换前驱节点的跳转为本基本块的跳转
        // 将本节点删除
        it = fun->getBasicBlocks().erase(it);
        return it;
    }
    else if (presList.size() == 1)
    {
        // 只有一个前驱
        // 若前驱也只有一个跳转
        std::vector<BasicBlockPtr> preJumps = presList[0]->getJumpList();
        if (preJumps.size() == 1)
        {
            // 前驱只有一个后继
            // 删除前驱的跳转指令 将本基本块合并到前驱中并删除
            presList[0]->getInstLists().pop_back();
            for (auto &inst : block->getInstLists())
            {
                inst->setBBlockParent(presList[0]);
                presList[0]->AddInstBack(std::move(inst));
            }
            it = fun->getBasicBlocks().erase(it);
            return it;
        }
    }
    ++it;
    return it;
}