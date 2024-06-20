/**
 * @file Mem2Reg.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief mem2reg实现
 * @version 1.0
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "CFGUtils.h"
#include <map>
#include <stack>
#include <unordered_map>
#include "DerivedInst.h"
#include "Module.h"

using blk_setsMap = std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>>;

class Mem2Reg
{
private:
    /// @brief 每个alloca的assigning nodes entry 认为也是一个
    std::unordered_map<ValPtr, std::set<BasicBlockPtr>> assignNodes;

    std::unordered_map<ValPtr, std::stack<ValPtr>> allocaStack;

public:
    /// @brief 重置
    void reset()
    {
        assignNodes.clear();
        allocaStack.clear();
    }

    /// @brief 获取alloca的assign定义节点
    /// @param fun
    void getAllocaAssignBBlock(FuncPtr fun);

    /// @brief 根据支配边界信息插入phi节点
    /// @param fun
    /// @param DomFronter
    void insertPhiNode(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &DomFronter);

    /// @brief rename操作 使用到达-定值的形式进行替换
    /// @param fun
    /// @param DFtree
    void rename(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &DFtree);

    /// @brief 对单个块的操作
    /// @param blk
    /// @param DFtree
    void rename(BasicBlockPtr blk, std::unordered_map<BasicBlockPtr,
                                                      std::set<BasicBlockPtr>> &DFtree);

    /// @brief 优化函数
    /// @param fun
    void pass(FuncPtr fun, blk_setsMap &DomFronter, blk_setsMap &DFTree);
};

/// @brief mem2reg
/// @param module
void Mem2RegPass(ModulePtr module);