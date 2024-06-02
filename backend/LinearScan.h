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
#include "MachineOperand.h"

class LinearScan;
struct Interval;
using LinearScanPtr = std::shared_ptr<LinearScan>;
using IntervalPtr = std::shared_ptr<Interval>;

// 为了后继方便 这里定义一个 set的比较算子 主要使set根据Moperator的使用指令编号位置为MOperaPtr自动排序
struct cmpUsePosLt
{
    bool operator()(const MOperaPtr &op1, const MOperaPtr &op2) const
    {
        int useNo1 = op1->getParent()->getNo();
        int useNo2 = op2->getParent()->getNo();
        return useNo1 < useNo2;
    }
};

/// @brief 活跃间隔***************************************************************************************************
struct Interval
{
    int start;                                  // 起始编号处
    int end;                                    // 终止编号处
    bool spill = false;                         // 是否溢出
    bool isPreAlloca = false;                   // 是否是预先分配的物理寄存器 如函数参数  函数返回值
    int reg = -1;                               // 分配的物理寄存器编号
    MOperaPtr def;                              // def
    std::multiset<MOperaPtr, cmpUsePosLt> uses; // uses

    /// @brief 构造
    /// @param s
    /// @param e
    /// @param _def
    /// @param _uses
    Interval(int s, int e, const MOperaPtr &_def, const std::multiset<MOperaPtr, cmpUsePosLt> &_uses)
    {
        start = s;
        end = e;
        def = _def;
        for (auto &use : _uses)
        {
            uses.insert(use);
        }
    }

    /// @brief 构造函数 无需记录 def uses(用于物理寄存器 因为在我的策略中不会将预先分配物理寄存器溢出)
    /// @param s
    /// @param e
    /// @param _isPredAlloca
    Interval(int s, int e, bool _isPredAlloca = true)
    {
        start = s;
        end = e;
        isPreAlloca = _isPredAlloca;
    }

    /// @brief 智能指针对象构造
    /// @param s
    /// @param e
    /// @param _def
    /// @param _uses
    /// @return
    static IntervalPtr get(int s, int e, const MOperaPtr &_def, const std::multiset<MOperaPtr, cmpUsePosLt> &_uses)
    {
        IntervalPtr interv = std::make_shared<Interval>(s, e, _def, _uses);
        return interv;
    }

    /// @brief 创建智能指针对象
    /// @param s
    /// @param e
    /// @param _isPredAlloca
    /// @return
    static IntervalPtr get(int s, int e, bool _isPredAlloca = true)
    {
        IntervalPtr interv = std::make_shared<Interval>(s, e, _isPredAlloca);
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

/// @brief 线性扫描**************************************************************************************8
class LinearScan
{
private:
    /// @brief moudle
    MModulePtr machineModule = nullptr;

    /// @brief 存放整型通用寄存器
    std::set<int> regs;

    /// @brief def-use Chain
    std::unordered_map<MOperaPtr, std::multiset<MOperaPtr, cmpUsePosLt>> defUseChains;

    /// @brief 标记是否所有间隔都已经分配寄存器
    bool successAllocaRegs = true;

    /// @brief 间隔
    std::multiset<IntervalPtr, Interval::cmpLtStart> intervals;

    /// @brief active表 即在目前周期中正在活跃并且已经分配寄存器的间隔
    std::multiset<IntervalPtr, Interval::cmpGtEnd> active;

    /// @brief 处理虚拟寄存器 和物理寄存器(对于虚拟寄存器产生def-use(简单，一个虚拟寄存器只会def一次))
    /// @brief 对于物理寄存器根据活跃变量分析获取对应的活跃区间间隔 供后继使用你
    /// @param fun
    void dealWithVregsAndRealRegs(MFuncPtr fun);

    /// @brief 计算活跃间隔(只对虚拟寄存器而言)
    /// @param fun
    void computeIntervals(MFuncPtr fun);

    /// @brief 获取溢出位置 如果无溢出 返回nullptr
    /// @param inter1InActive
    /// @param inter2
    /// @return 返回 str ldr 指令的插入位置
    std::pair<MInstPtr, MInstPtr> computeSpillPos(IntervalPtr inter1InActive, IntervalPtr inter2);

    /// @brief 自动处理冲突(和active表中已经分配寄存器的活跃间隔比较)  如果有的话 更新active表
    /// @param curInter 当前扫描的活跃间隔
    void AutoUpdateActive(IntervalPtr curInter);

    /// @brief 插入溢出时的代码 def后使用 str, 在firstUsePos前插入ldr
    /// @param inter 活跃间隔
    /// @param pos pos的第一 第二个元素对应  插入 str  ldr指令的位置
    void genSpillCode(IntervalPtr interSpilled, std::pair<MInstPtr, MInstPtr> &pos);

    /// @brief 将活跃间隔中的def use 虚拟寄存器操作数 映射为对应的物理寄存器
    /// @param inter
    void MapIntervalToReg(IntervalPtr inter);

    /// @brief 初始化可用寄存器池
    void initAvailableRegsPool()
    {
        regs.clear();
        // r0-r3 由于存在函数调用 以及函数返回值 目前先不分配 后继 有时间进行分析时考虑
        for (int i = 0; i < 11; i++)
        {
            regs.insert(i);
        }
        //  看https://godbolt.org/ 似乎 lr 也可用于分配
        // regs.insert(14);
    }

public:
    /// @brief 析构函数
    ~LinearScan()
    {
        machineModule.reset();
        defUseChains.clear();
        regs.clear();
        intervals.clear();
        active.clear();
    }

    /// @brief 构造函数
    LinearScan(MModulePtr module)
    {
        machineModule = module;
        initAvailableRegsPool();
    }

    /// @brief 创建智能指针类型
    /// @param module
    /// @return
    static LinearScanPtr get(MModulePtr module)
    {
        LinearScanPtr linear = std::make_shared<LinearScan>(module);
        return linear;
    }

    /// @brief 线性扫描 进行寄存器 分配 一个 epoch 返回 true 则表示 fun分配完毕
    /// @param fun
    /// @return 是否所有 interval 都分配完毕 没有溢出
    bool LinearScanPassEpoch(MFuncPtr fun);

    /// @brief
    /// @param module
    void allocateReg();
};