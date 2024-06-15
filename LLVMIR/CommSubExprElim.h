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
#include "CFGUtils.h"
#include "Value.h"
#include "DerivedInst.h"
#include "Constant.h"

class equalCmp
{

    /// @brief 哈希比较函数
    /// @param left
    /// @param right
    /// @return
    bool operator()(const InstPtr &left, const InstPtr &right) const;
};

/// @brief 局部公共子表达式删除(对于并列分支间的公共表达式不处理，因为不可达)
class LocalSubExprElim
{
private:
};

/// @brief 判断两个二元运算指令的结果是否相同
/// @param left
/// @param right
/// @return
bool equalBianaryInst(const InstPtr &left, const InstPtr &right);

/// @brief 判断两个数组地址计算指令的结果是否相同
/// @param left
/// @param right
/// @return
bool equalGetelementInst(const InstPtr &left, const InstPtr &right);

/// @brief 判断两个常数相同
/// @param left 
/// @param right 
/// @return 
bool equalConstInt(const ConstantIntPtr &left, const ConstantIntPtr &right);
