/**
 * @file IDCounter.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 计数器管理类 用于LLVMIR指令翻译为字符串时为变量等类型分配所需的编号
 * @version 1.0
 * @date 2024-04-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "IDCounter.h"

/// @brief 获取计数器
/// @return 计数器值
int32_t Counter::getCount()
{
    int32_t cur = count;
    count++; // 计数器自增
    return cur;
}

/// @brief 为变量分配相关编号
/// @param var 变量指针
/// @return 编号
int32_t Counter::setCount(Var *var)
{
    if (var->getllvmId() == -1)
    {
        // 变量未分配编号
        var->getllvmId() = count; // 分配
        count++;                  // 编号自增
    }
    // 变量已经分配编号时，计数器不给编号，保持原状态
    // 返回变量分配的LLVMIR编号(一定不为-1)
    return var->getllvmId();
}