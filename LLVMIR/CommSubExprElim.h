/**
 * @file CommSubExprElim.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  公共子表达式删除 （应在 进行活跃变量分析消减load store alloca 后做(类似于Mem2reg效果)）
 * @version 1.0
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "BasicBlock.h"

/// @brief 局部公共子表达式删除(对于并列分支间的公共表达式不处理，因为不可达)
class LocalSubExprElim
{
private:
    

    /// @brief 判断从 src 基本块是否可以到达 dst基本块
    /// @param src 
    /// @param dst 
    /// @return 
    bool isReachable(BasicBlockPtr src, BasicBlockPtr dst);
};