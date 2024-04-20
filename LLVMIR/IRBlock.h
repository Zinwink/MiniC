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
#include <deque>

/// @brief IR指令序列 管理
class IRBlock
{
private:
    /// @brief IR指令序列前部分 (在函数中如alloca分配指令)
    std::deque<IRInst *> IRFront;

    /// @brief IR指令序列 后部分
    std::deque<IRInst *> IRBack;

public:
    /// @brief 构造函数 默认构造
    IRBlock() = default;

    /// @brief 析构函数
    ~IRBlock();

    /// @brief 返回IRFront 前部分IR指令
    /// @return IRFront引用
    std::deque<IRInst *> &irfront() { return IRFront; }

    /// @brief 返会IRBack引用
    /// @return
    std::deque<IRInst *> &irback() { return IRBack; }

    /// @brief 向IRBack添加一个指令块 用于遍历AST向上合并时使用，并释放原指令块
    /// @param block  指令块
    void extendIRBack(IRBlock &block);
};