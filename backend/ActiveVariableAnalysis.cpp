/**
 * @file ActiveVariableAnalysis.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 活跃变量分析 用于寄存器分配  声明:相关实现参考自2023年编译原理大赛南开大学的作品212，参考自课件CH8-DataflowAnalysis
 * @version 1.0
 * @version 1.0
 * @date 2024-05-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ActiveVariableAnalysis.h"
#include <iostream>
#include <deque>

/// @brief 计算 获取 虚拟寄存器 物理寄存器的所有使用位置
void ActiveVariAnalysis::computeAllUsesInfun(MFuncPtr fun)
{
    AllUsesInfun.clear(); // 清理一下 不同函数结果不同
    // 获取块列表
    std::list<MBlockPtr> &blockList = fun->getBlockList();
    for (auto &blk : blockList)
    {
        std::list<MInstPtr> &instList = blk->getInstList();
        for (auto &inst : instList)
        {
            for (auto &use : inst->getUse())
            {
                // 记录使用的对象指针
                insertAllUsesInfun(*use, use);
            }
        }
    }
}

/// @brief 计算fun函数中每个MachineBlock的 define Use (后期 计算In Out 流时需要使用)
/// @param fun
void ActiveVariAnalysis::computeDefUseInfun(MFuncPtr fun)
{

    // 虚拟寄存器 只会def 一次；只需计算 r0-r3的 def use 即可

    def.clear(); // 清理一下def use
    use.clear();
    std::list<MBlockPtr> &blockList = fun->getBlockList();
    for (auto &blk : blockList)
    {
        // std::cout << "基本块" << std::endl;
        std::list<MInstPtr> &instList = blk->getInstList();
        for (auto &inst : instList)
        {
            // 计算本块的  def 和 use
            std::vector<MOperaPtr> &uses = inst->getUse();
            std::set<MOperaPtr> usesSet;
            for (auto &use : uses)
            {
                usesSet.insert(use);
            }
            // use 引用前未定值的集合
            std::set_difference(usesSet.begin(), usesSet.end(), def[blk].begin(), def[blk].end(), inserter(use[blk], use[blk].end()));
            // def 定值前未引用的集合
            for (auto &d : inst->getDef())
            {
                def[blk].insert(AllUsesInfun[*d].begin(), AllUsesInfun[*d].end());
            }
        }
    }
}

/// @brief 计算fun函数中 每个MachineBlock的 LiveIn  LiveOut (使用改进算法 跟踪基本块的后继)
/// @param fun
void ActiveVariAnalysis::computeLiveVariInfun(MFuncPtr fun)
{
    // 计算 函数中所有 MachineOperand 的使用指针 对象
    // 计算函数所有 block的 def use
    computeAllUsesInfun(fun);
    computeDefUseInfun(fun);
    // 计算函数中所有块的 In Out
    // 改进迭代法(参考自课件CH8-DataflowAnalysis) 初始每个基本块的 In Out 流为空集 并创建一个队列记录
    std::list<MBlockPtr> &blockList = fun->getBlockList();
    std::deque<MBlockPtr> blkQue; // 改进算法的 队列
    for (auto &blk : blockList)
    {
        blk->getLiveIn().clear();
        blk->getLiveOut().clear();
        blkQue.push_back(blk);
    }
    // 使用改进算法 只需跟踪基本块的后继 如果后继不变 则该基本块的流也不变
    while (!blkQue.empty()) // 队列不空
    {
        MBlockPtr blk = blkQue.front();
        blkQue.pop_front();
        std::set<MOperaPtr> oldIn = blk->getLiveIn(); // 记录旧值
        // 更新Out  即所有后继的并集
        for (auto &succ : blk->getSuccs())
        {
            blk->getLiveOut().insert(succ->getLiveIn().begin(), succ->getLiveIn().end());
        }
        // 更新 In(n)=Use(n) U ( Out(n)-def(n))
        blk->getLiveIn() = use[blk];
        std::set_difference(blk->getLiveOut().begin(), blk->getLiveOut().end(),
                            def[blk].begin(), def[blk].end(), inserter(blk->getLiveIn(), blk->getLiveIn().begin()));
        if (oldIn != blk->getLiveIn())
        {
            for (auto &pred : blk->getPreds())
            {
                blkQue.push_back(pred);
            }
        }
    }
}
