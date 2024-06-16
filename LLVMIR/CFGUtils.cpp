/**
 * @file CFGUtils.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 控制流图的一些工具 可视化 求支配节点
 * @version 1.0
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "CFGUtils.h"
#include <queue>

/// @brief 计算基本块的必经节点集
/// @param fun
/// @return
std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> CFGUtils::computeDoms(FuncPtr fun)
{
    std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> Doms; // 基本块的必经节点集
    auto &blockList = fun->getBasicBlocks();
    // 进行初始化
    BasicBlockPtr &entry = fun->getEntryBlock();
    Doms[entry].insert(entry); // 入口块加入自己

    /// 用于记录活动队列  如果前驱的dom 都不变 那么本块也不变；如果本快变了将直接后继块加入队列
    std::deque<BasicBlockPtr> workList;
    auto nextIter = std::next(blockList.begin());
    for (auto iter = nextIter; iter != blockList.end(); iter++)
    { // 除入口 其他块初始为全集
        auto &blk = *iter;
        Doms[blk].insert(blockList.begin(), blockList.end());
        workList.push_back(blk);
    }
    // 下面进行迭代数据流 获取结果
    while (!workList.empty())
    {
        BasicBlockPtr blk = workList.front();
        workList.pop_front(); // 弹出该块

        // dom[n]=n U {所有前驱 dom的交集}
        std::set<BasicBlockPtr> oldDom = Doms[blk];
        std::vector<BasicBlockPtr> preds = blk->getImmedPreds();
        std::set<BasicBlockPtr> predInsert; // 记录所有前驱的交集
        Doms[blk] = {blk};
        if (preds.size() > 0)
        {
            predInsert = Doms[preds[0]];
        }
        for (size_t i = 1; i < preds.size(); i++)
        {
            std::set<BasicBlockPtr> tmp;
            std::set_intersection(predInsert.begin(), predInsert.end(),
                                  Doms[preds[i]].begin(), Doms[preds[i]].end(), std::inserter(tmp, tmp.end()));
            predInsert = tmp; // 迭代
        }
        Doms[blk].insert(predInsert.begin(), predInsert.end());
        if (oldDom != Doms[blk])
        {
            // 如果发生了 改变 根据数据流方程会影响后继 DOms计算 因此将后继块加入队列
            auto succes = blk->getJumpList();
            for (auto &succ : succes)
            {
                workList.push_back(succ);
            }
        }
    }
    return Doms;
}