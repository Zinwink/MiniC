/**
 * @file LiveMemVariAnalysis.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 对 内存变量(地址) alloca,getelemptr, globalVarible 等内存地址标识的变量进行活跃分析 (由于时间有限暂不做SSA)
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
#include <unordered_map>
#include <unordered_set>
#include "Function.h"

class LiveMemVariAnalysis
{
private:
    /// @brief 记录基本块的 In Out 以及 def use
    std::unordered_map<BasicBlockPtr, std::unordered_set<ValPtr>> In, Out, def, use;

    /// @brief 记录use_defs
    std::unordered_map<LoadInstPtr, std::unordered_set<StoreInstPtr>> use_def;

    /// @brief 记录 def_uses
    std::unordered_map<StoreInstPtr, std::unordered_set<LoadInstPtr>> def_use;

    /// @brief 计算 基本块的 def use
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
};
