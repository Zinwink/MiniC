/**
 * @file LinearScan.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 使用线性扫描进行寄存器分配 声明：实现参考自2023编译实现赛中南开大学212相关代码 使用 second-chance方法
 * @version 1.0
 * @date 2024-05-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "MachineBlock.h"
#include "MachineFunc.h"
#include "MachineModule.h"

class LinearScan;
struct Interval;
using LinearScanPtr = std::shared_ptr<LinearScan>;
using IntervalPtr = std::shared_ptr<Interval>;

/// @brief 活跃间隔
struct Interval
{
    int start;                // 起始编号处
    int end;                  // 终止编号处
    bool spill = false;       // 是否溢出
    int stackDisp;            // 存放溢出时栈中偏移
    int reg;                  // 分配的物理寄存器编号
    MOperaPtr def;            // def
    std::set<MOperaPtr> uses; // uses

    /// @brief 构造
    /// @param s
    /// @param e
    /// @param _def
    /// @param _uses
    Interval(int s, int e, const MOperaPtr &_def, const std::set<MOperaPtr> &_uses)
    {
        start = s;
        end = e;
        def = _def;
        uses = _uses;
    }

    /// @brief 智能指针对象构造
    /// @param s
    /// @param e
    /// @param _def
    /// @param _uses
    /// @return
    static IntervalPtr get(int s, int e, const MOperaPtr &_def, const std::set<MOperaPtr> &_uses)
    {
        IntervalPtr interv = std::make_shared<Interval>(s, e, _def, _uses);
        return interv;
    }

    // 定义 set需要使用的比较对象方法
    struct cmpLtStart
    {
        bool operator()(const IntervalPtr &inter1, const IntervalPtr &inter2) const
        {
            return inter1->start < inter2->start;
        }
    };

    struct cmpGtEnd
    {
        bool operator()(const IntervalPtr &inter1, const IntervalPtr &inter2) const
        {
            return inter1->end > inter2->end;
        }
    };
};

class LinearScan
{
private:
    /// @brief 存放整型通用寄存器
    std::set<int> regs;

    /// @brief def-use Chain
    std::unordered_map<MOperaPtr, std::set<MOperaPtr>> defUseChains;

    /// @brief 标记是否所有间隔都已经分配寄存器
    bool successAllocaRegs = false;

    /// @brief 间隔
    std::set<IntervalPtr, Interval::cmpLtStart> intervals;

    /// @brief active表 即在目前周期中正在活跃并且已经分配寄存器的间隔
    std::set<IntervalPtr, Interval::cmpGtEnd> active;

    /// @brief 计算def-use Chain
    /// @param fun
    void genDefUseChains(MFuncPtr fun);

    /// @brief 计算活跃间隔
    /// @param fun
    void computeIntervals(MFuncPtr fun);

    /// @brief 获取溢出位置 如果无溢出 返回nullptr
    /// @param inter1
    /// @param inter2
    /// @return
    MInstPtr computeSpillPos(IntervalPtr inter1, IntervalPtr inter2);

    /// @brief 自动处理冲突(和active表中已经分配寄存器的活跃间隔比较)  如果有的话
    /// @param curInter 当前扫描的活跃间隔
    void AutoDealWithConflict(IntervalPtr curInter);

    /// @brief 插入溢出时的代码 def后使用 str, 在firstUsePos前插入ldr
    /// @param inter 活跃间隔
    /// @param firstUsePos  溢出位置(use 处)
    void genSpillCode(IntervalPtr inter, MInstPtr firstUsePos);

public:
    /// @brief 析构函数
    ~LinearScan()
    {
        defUseChains.clear();
        regs.clear();
        intervals.clear();
        active.clear();
    }

    /// @brief 构造函数
    LinearScan()
    {
        // r0-r3 由于存在函数调用 以及函数返回值 目前先不分配 后继 有时间进行分析时考虑
        for (int i = 4; i < 11; i++)
        {
            regs.insert(i);
        }
    }

    /// @brief 线性扫描 进行寄存器 分配 一个 epoch 返回 true 则表示 fun分配完毕
    /// @param fun
    /// @return 是否所有 interval 都分配完毕 没有溢出
    bool LinearScanPassEpoch(MFuncPtr fun);

    /// @brief
    /// @param module
    void allocateReg(MModulePtr module);
};