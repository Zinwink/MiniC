/**
 * @file IRCode.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  IR指令序列管理  用于遍历AST时对IR序列进行记录传递
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "IRInst.h"
#include <vector>

/// @brief IR指令序列 管理
class IRBlock
{
private:
    /// @brief IR指令序列
    std::vector<IRInst *> IRList;

public:
    /// @brief 构造函数 默认构造
    IRBlock() = default;

    /// @brief 析构函数
    ~IRBlock();

    /// @brief 添加一个指令块 用于遍历AST向上合并时使用，并释放原指令块
    /// @param block  指令块
    void extend(IRBlock &block);

    /// @brief 追加一条指令
    /// @param inst
    void append(IRInst *inst) { IRList.push_back(inst); }

    /// @brief 获取指令序列
    /// @return
    std::vector<IRInst *> &getIRList() { return IRList; }
};