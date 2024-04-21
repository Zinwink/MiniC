/**
 * @file IDCounter.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  LLVMIR 编号计数器 用于给变量，临时变量等分配IR 编号
 * 分配编号在IR 翻译成字符串指令时使用  (每个函数都有一个计数器对象)
 * @version 1.0
 * @date 2024-04-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <cstdint>
#include "Var.h"

class Counter
{
private:
    // 计数器值 当前值表示为未使用的值，当被获取使用时，自增
    int32_t count = 0;

public:
    /// @brief 默认析构函数
    ~Counter() = default;
    /// @brief 构造函数
    Counter() { count = 0; };

    /// @brief 重置编号为指定数值
    /// @param num
    void reset(int32_t num) { count = num; };

    /// @brief 获取计数器
    /// @return 计数器值
    int32_t getCount();

    /// @brief 为变量分配相关编号
    /// @param var 变量指针
    /// @return 编号
    int32_t setCount(Var *var);
};