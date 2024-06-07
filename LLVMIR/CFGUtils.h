/**
 * @file CFGUtils.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  控制流图的一些工具(包括可视化 控制流图 求支配树等)
 * @version 1.0
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <unordered_map>
#include <unordered_set>
#include "BasicBlock.h"
#include "Function.h"
#include <set>

class CFGUtils
{
public:
    /// @brief 计算基本块的必经节点集
    /// @param fun
    /// @return
    static std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> computeDoms(FuncPtr fun);
};