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
#include <gvc.h>
#include <set>

class CFGUtils
{
public:
    /// @brief 计算基本块的必经节点集
    /// @param fun
    /// @return
    static std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> computeDoms(FuncPtr fun);

    /// @brief 根据支配节点求解支配边界
    /// @param fun 
    /// @param Doms 
    /// @return 
    static std::unordered_map<BasicBlockPtr,std::set<BasicBlockPtr>> computeDomFronter(FuncPtr fun,std::unordered_map<BasicBlockPtr,std::set<BasicBlockPtr>>& Doms);

    /// @brief 根据支配节点求解 直接支配节点
    /// @param fun 
    /// @param Doms 
    /// @return 
    static std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> computeIDom(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms);

    /// @brief 根据Dom 获取支配树(先获取直接支配节点)
    /// @param fun 
    /// @param Doms 
    /// @return 
    static std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> computeDFT(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms);
};

//******************************** CFG控制流图的可视化 ******************************

/// @brief 根据基本块得到对应的节点
/// @param g
/// @param blk
/// @param cnt
/// @return
Agnode_t *genBasicBlockNode(Agraph_t *g, BasicBlockPtr &blk, Counter *cnt, std::unordered_map<BasicBlockPtr, Agnode_t *> &record);

/// @brief 产生指定函数的控制流图
/// @param fun
/// @param filePath 路径
/// @return
void genCFG(FuncPtr fun, const std::string &filePath);