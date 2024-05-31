/**
 * @file ActiveVariableAnalysis.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 活跃变量分析 用于寄存器分配  声明:相关实现参考自2023年编译原理大赛南开大学的作品(各个队实现的都基本一样)
 * @version 1.0
 * @date 2024-05-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "MachineBlock.h"
#include "MachineFunc.h"
#include "MachineOperand.h"
#include <unordered_map>
#include <set>
#include <map>

/// @brief 活跃变量分析
class ActiveVariAnalysis
{
private:
    /// @brief 主要用于记录 函数中所有 虚拟寄存器的使用位置(可通过map 的键对应指针查看)
    /// MachineOperand中已经重写了 == 号，对于编号相同的虚拟寄存器 其map键是相同的
    std::map<MachineOperand, std::set<MOperaPtr>> AllUsesInfun;

    /// @brief  Arm指令块中 def use 的虚拟寄存器
    std::map<MBlockPtr, std::set<MOperaPtr>> def, use;

    /// @brief 将value 插入 key 对应的集合中
    /// @param key  键
    /// @param value 插入集合中的指针
    inline void insertAllUsesInfun(MachineOperand &key, MOperaPtr value)
    {
        auto iter = AllUsesInfun.find(key);
        if (iter != AllUsesInfun.end())
        {
            // 找到了 key
            AllUsesInfun[key].insert(value);
        }
        else
        {
            // 没找到key 先创建 在插入值
            AllUsesInfun.emplace(key, std::set<MOperaPtr>());
            AllUsesInfun[key].insert(value);
        }
    }

    /// @brief 插入 def 中
    /// @param key
    /// @param value
    inline void insertDef(MBlockPtr &key, MOperaPtr &value)
    {
        auto iter = def.find(key);
        if (iter != def.end())
        {
            // 找到
            def[key].insert(value);
        }
        else
        {
            // 没找到 key
            def.emplace(key, std::set<MOperaPtr>());
            def[key].insert(value);
        }
    }

    /// @brief 插入use 中
    /// @param key
    /// @param value
    inline void insertUse(MBlockPtr &key, MOperaPtr &value)
    {
        auto iter = use.find(key);
        if (iter != use.end())
        {
            // 找到
            use[key].insert(value);
        }
        else
        {
            // 没找到 key
            use.emplace(key, std::set<MOperaPtr>());
            use[key].insert(value);
        }
    }

public:
    /// @brief 析构函数
    ~ActiveVariAnalysis()
    {
        AllUsesInfun.clear();
        def.clear();
        use.clear();
    }

    /// @brief 构造
    ActiveVariAnalysis(){};

    /// @brief 重置相关数据  当切换函数时使用
    void resetAnalysisData()
    {
        AllUsesInfun.clear();
        def.clear();
        use.clear();
    }

    /// @brief 返回记录
    /// @return
    inline std::map<MachineOperand, std::set<MOperaPtr>> &getAllUsesInfun() { return AllUsesInfun; }

    /// @brief 计算 获取 虚拟寄存器的所有使用位置
    void computeAllUsesInfun(MFuncPtr fun);

    /// @brief 计算fun函数中每个MachineBlock的 define Use (后期 计算In Out 流时需要使用)
    /// @param fun
    void computeDefUseInfun(MFuncPtr fun);

    /// @brief 计算fun函数中 每个MachineBlock的 LiveIn  LiveOut
    /// @param fun
    void computeLiveVariInfun(MFuncPtr fun);
};
