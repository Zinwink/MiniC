/**
 * @file LinearScan.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 使用线性扫描进行寄存器分配 声明：参考https://blog.csdn.net/sexyluna/article/details/132287291 实现流程
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
#include <unordered_set>

class LinearScan;
struct Interval;

using LinearScanPtr = std::shared_ptr<LinearScan>;
using IntervalPtr = std::shared_ptr<Interval>;

// 定义比较操作数使用位置的函数
struct cmpUsePosLt
{
    bool operator()(const MOperaPtr &op1, const MOperaPtr &op2) const
    {
        int useNo1 = op1->getParent()->getNo();
        int useNo2 = op2->getParent()->getNo();
        return useNo1 < useNo2;
    }
};

/// @brief *******************************  活跃间隔 ***********************************************
struct Interval
{
    int start = -1;           // 起始编号处
    int end = -1;             // 终止编号处
    bool isPreAlloca = false; // 是否是预先分配的物理寄存器 如函数参数  函数返回值
    int reg = -1;             // 分配的物理寄存器编号

    MOperaPtr def;                              // def
    std::multiset<MOperaPtr, cmpUsePosLt> uses; // def 对应的 uses

    /// @brief 创建智能指针对象
    /// @param _def
    /// @param uses
    /// @param _isPreAlloca
    /// @return
    static IntervalPtr get(const MOperaPtr &_def, const std::unordered_set<MOperaPtr> &uses,
                           bool _isPreAlloca = false);

    //***********************************  比较函数  *********************************************
    static bool cmpLtStart(const IntervalPtr &inter1, const IntervalPtr &inter2)
    {
        int start1 = inter1->start;
        int end1 = inter1->end;
        int start2 = inter2->start;
        int end2 = inter2->end;
        if (start1 < start2)
        {
            return true;
        }
        else if (start1 == start2)
        {
            // 相同起始点 比较间隔长短 间隔短的先分配
            return (end1 - start1) < (end2 - start2);
        }
        else
        {
            return false;
        }
    }

    static bool cmpGtEnd(const IntervalPtr &inter1, const IntervalPtr &inter2)
    {
        int start1 = inter1->start;
        int end1 = inter1->end;
        int start2 = inter2->start;
        int end2 = inter2->end;
        if (end1 > end2)
        {
            return true;
        }
        else if (end1 == end2)
        {
            // 结尾一样比较 间隔长短 间隔长的溢出
            return (end1 - start1) > (end2 - start2);
        }
        else
        {
            return false;
        }
    }
};

/// @brief 定义一个寄存器池 方便管理寄存器状态
class RegsPool
{
private:
    /// @brief 记录使用当前寄存器的间隔
    std::unordered_map<int, IntervalPtr> regIntersMap;

    /// @brief 可用寄存器集合
    std::set<int> regsCanUse;

    /// @brief 记录寄存器被使用的最后时间线
    std::unordered_map<int, int> regsLastUse;

public:
    /// @brief 析构函数
    ~RegsPool()
    {
        regIntersMap.clear();
        regsLastUse.clear();
        regsCanUse.clear();
    }

    /// @brief 构造函数
    RegsPool();

    /// @brief 重置寄存器池
    void resetRegsPool();

    /// @brief 回收已经结束的间隔占用的寄存器
    void empireOldIntervals(IntervalPtr inter);

    /// @brief 判断某一号寄存器是否可以使用
    /// @param regNo
    /// @return
    bool isAvailable(int regNo);

    /// @brief 获取占用寄存器的间隔
    /// @param regNo
    /// @return
    IntervalPtr &getInterval(int regNo)
    {
        return regIntersMap[regNo];
    }

    /// @brief 溢出指定间隔
    /// @param inter
    void spillAtInterval(IntervalPtr inter);

    /// @brief 为间隔分配指定寄存器
    /// @param inter
    /// @param regNo
    void allocaReg(IntervalPtr inter, int regNo);

    /// @brief 获取间隔可以切换的寄存器编号
    /// @param inter
    /// @return
    int getSwitchReg(IntervalPtr inter);

    // std::vector<int> getOccupyRegs(IntervalPtr inter)
    // {
    //     for (auto &elem : regIntersMap)
    //     {
    //         if(elem)
    //     }
    // }

    /// @brief 获取可以使用的寄存器
    /// @return
    std::set<int> &getRegsCanUse() { return regsCanUse; }

    /// @brief 返回占用寄存器的间隔
    /// @return
    std::vector<IntervalPtr> getActive();
};

/// @brief 线性扫描**************************************************************************************8
class LinearScan
{
private:
    /// @brief moudle
    MModulePtr machineModule = nullptr;

    RegsPool pool = RegsPool();

    /// @brief def-use chain; 对于虚拟寄存器已经确定；对于物理寄存器 没有def 或者有多个def的不定状态将创建一个def标记
    std::unordered_map<MOperaPtr, std::unordered_set<MOperaPtr>> defUseChains;

    /// @brief 活跃间隔(包括分配的物理寄存器r0-r3的活跃间隔以及虚拟寄存器的活跃间隔)
    std::vector<IntervalPtr> intervals; // 最终的活跃间隔结果

    /// @brief 用于记录 虚拟寄存器的溢出偏移位置 防止重复申请 占用太多内存
    std::unordered_map<int, MOperaPtr> vregSpillOffset;

    /// @brief 计算 fun的虚拟寄存器 物理寄存器的 def-use chain
    /// @param fun
    void computeDefUseChain(MFuncPtr fun);

    /// @brief 计算活跃间隔(只对虚拟寄存器而言)
    /// @param fun
    void computeIntervals(MFuncPtr fun);

    /// @brief 插入溢出时的代码 def后使用 str, 在firstUsePos前插入ldr
    /// @param inter 活跃间隔
    void genSpillCode(IntervalPtr interSpilled);

    /// @brief 更新寄存器池
    /// @param inter
    /// @return 是否有溢出
    bool updateRegsPool(IntervalPtr inter);

    /// @brief 将活跃间隔中的def use 虚拟寄存器操作数 映射为对应的物理寄存器
    /// @param inter
    void MapIntervalToReg(IntervalPtr inter);

public:
    /// @brief 析构函数
    ~LinearScan()
    {
        machineModule.reset();
        defUseChains.clear();
        intervals.clear();
    }

    /// @brief 构造函数
    LinearScan(MModulePtr module)
    {
        machineModule = module;
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
