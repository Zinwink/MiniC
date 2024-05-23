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
#include "DeadInstElim.h"
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
            // 没有标记 死基本块删除
            eraseBasicBlock((*it), it);
        }
        else
        {
            // 非死基本块 可用  尝试合并
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
        eraseBasicBlock(block, it);
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
            // 删除前驱的跳转指令 将本基本块合并到前驱中
            std::list<InstPtr> &PreInsts = presList[0]->getInstLists();
            InstPtr lastInst = PreInsts.back(); // 获取最后一条指令
            // 删除该指令前 将其操作数的UserList进行更新
            for (auto &op : lastInst->getOperandsList())
            {
                op->deleteUser(lastInst);
            }
            PreInsts.pop_back(); // 删除最后一条指令 br

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

/// @brief 删除一个基本块
/// @param block
/// @param it
void eraseBasicBlock(BasicBlockPtr block, bblockIter &it)
{
    std::list<InstPtr> &instList = block->getInstLists();
    for (auto iter = instList.begin(); iter != instList.end();)
    {
        // 删除指令  包括删除指令操作数的UserList中对应的User
        iter = eraseInst(block, iter);
    }
    // 下一步删除基本块
    FuncPtr fun = block->getParentFun();
    assert(fun != nullptr && "error");
    std::list<BasicBlockPtr> &bblockList = fun->getBasicBlocks();
    it = bblockList.erase(it);
}