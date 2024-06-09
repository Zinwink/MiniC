/**
 * @file CommSubExprElim.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 公共子表达式删除 （应在 进行活跃变量分析消减load store alloca 后做(类似于Mem2reg效果)）
 * @version 1.0
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "CommSubExprElim.h"

/// @brief 哈希比较函数
/// @param left
/// @param right
/// @return
bool equalCmp::operator()(const InstPtr &left, const InstPtr &right) const
{
    return true;
}