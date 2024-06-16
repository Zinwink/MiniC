/**
 * @file LiveMemVariAnalysis.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 对 内存变量(地址) alloca,globalVarible 等内存地址标识的变量进行活跃分析 (由于时间有限暂不做SSA)
 *  目前只对alloca分析 全局变量有副作用 数组地址也不好处理 不进行处理
 * @version 1.0
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "Value.h"
#include "DerivedInst.h"
#include "BasicBlock.h"
#include "GlobalVariable.h"
#include <unordered_map>
#include <set>
#include "Function.h"
#include "Module.h"

// 活跃 变量分析
class LiveMemVariAnalysis
{
private:
    /// @brief 记录基本块的 In Out 以及 def use  这些变量都是 计算同一函数使用  切换函数时重置清空
    std::unordered_map<BasicBlockPtr, std::set<ValPtr>> def; // 记录str def了哪些 mem

    /// @brief 活跃变量分析本质就是分析处哪些被新的定值杀死截断的use
    std::unordered_map<BasicBlockPtr, std::set<LoadInstPtr>> In, Out, use; // 记录 In Out和Use

    /// @brief 记录use_defs
    std::unordered_map<LoadInstPtr, std::set<StoreInstPtr>> use_def;

    /// @brief 记录 def_uses
    std::unordered_map<StoreInstPtr, std::set<LoadInstPtr>> def_use;

    /// @brief 计算 函数基本块的 def use
    /// @param fun
    void computeDefUse(FuncPtr fun);

public:
    /// @brief 构造函数
    LiveMemVariAnalysis() = default;

    /// @brief
    void reset()
    {
        In.clear();
        Out.clear();
        def.clear();
        use.clear();
        use_def.clear();
        def_use.clear();
    }

    /// @brief 计算 函数 基本块的Live In LiveOut
    /// @param fun
    void computeInOut(FuncPtr fun);

    /// @brief 建立 use_def def_use 链接记录
    /// @param fun
    void buildChain(FuncPtr fun);

    /// @brief 拷贝传播阶段1(只对alloca,传播常数以及非常数,其余的内存地址只局部优化)
    /// @param fun
    void copyProp1(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms);

    /// @brief 拷贝传播阶段2(根据必经节点信息进一步传播更远)
    /// @param fun 
    /// @param Doms 
    void copyProp2(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms);

    /// @brief 根据 LiveIn LiveOut 进行传播优化
    /// @param Doms 必经节点记录
    /// @param fun
    void Pass(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms);
};

/// @brief 对整个单元进行分析优化(将子表达式替换也加了进来)
/// @param module
void LiveMemAnalysisPass(ModulePtr module);