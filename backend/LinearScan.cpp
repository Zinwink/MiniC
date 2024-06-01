/**
 * @file LinearScan.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 使用线性扫描进行寄存器分配 声明：实现参考自2023编译实现赛中南开大学212相关代码
 * @version 1.0
 * @date 2024-05-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "LinearScan.h"
#include "ActiveVariableAnalysis.h"

/// @brief 计算def-use Chain
/// @param fun
void LinearScan::genDefUseChains(MFuncPtr fun)
{
    defUseChains.clear();
    // 先计算这个函数的liveIn  liveOut
    ActiveVariAnalysis LiveAnalysis;
    LiveAnalysis.computeAllUsesInfun(fun); // 根据 IR相关的设计 以指针地址作为一个value的唯一标识 对于一个MachineOperand(同一虚拟寄存器编号 他只会def一次 之后是使用 因此获取函数fun的 AllUses 进行查找相应的def 即可获取 def-use chain)
    // 遍历fun 获取 def-use chain 同时对指令进行编号
    auto &allUsesOfFun = LiveAnalysis.AllUsesInfun; // fun 中 AllUsesInFun 列表记录
    std::list<MBlockPtr> &blockList = fun->getBlockList();
    int instNo = 0; // 设置编号
    for (auto &blk : blockList)
    {
        std::list<MInstPtr> &instList = blk->getInstList();
        for (auto &inst : instList)
        {
            inst->setNo(instNo++);
            auto &defs = inst->getDef();
            for (auto &def : defs)
            {
                defUseChains[def].insert(allUsesOfFun[*def].begin(), allUsesOfFun[*def].end());
            }
        }
    }
}

/// @brief 计算活跃间隔
/// @param fun
void LinearScan::computeIntervals(MFuncPtr fun)
{
    // 根据def-Use chain 获取 interval;
    for (auto &defUse : defUseChains)
    {
        // 获取 InterVal的 start end
        uint32_t start = defUse.first->getParent()->getNo();
        uint32_t end = 0;
        for (auto &use : defUse.second)
        {
            end = std::max(end, use->getParent()->getNo());
        }
        IntervalPtr interval = Interval::get(start, end, defUse.first, defUse.second);
        // 加入到 Intervals中
        intervals.insert(interval);
    }
}

/// @brief 获取溢出位置 如果无溢出 返回nullptr
/// @param inter1
/// @param inter2
/// @return
MInstPtr computeSpillPos(IntervalPtr inter1, IntervalPtr inter2);

/// @brief 自动处理冲突(和active表中已经分配寄存器的活跃间隔比较)  如果有的话
/// @param curInter 当前扫描的活跃间隔
void LinearScan::AutoDealWithConflict(IntervalPtr curInter)
{
}

/// @brief 插入溢出时的代码 def后使用 str, 在firstUsePos前插入ldr
/// @param inter 活跃间隔
/// @param firstUsePos  溢出位置(use 处)
void LinearScan::genSpillCode(IntervalPtr inter, MInstPtr firstUsePos)
{
}

/// @brief 线性扫描 进行寄存器 分配 一个 epoch 返回 true 则表示 fun分配完毕
/// @param fun
/// @return 是否所有 interval 都分配完毕 没有溢出
bool LinearScan::LinearScanPassEpoch(MFuncPtr fun)
{
    
}

/// @brief 寄存器分配
/// @param module
void LinearScan::allocateReg(MModulePtr module)
{
}