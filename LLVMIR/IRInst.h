/**
 * @file IRInst.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief LLVM IR指令类
 * @version 1.0
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

/// @brief IR指令操作类型
enum class IROperator : int
{
    IR_ADD_INT, // 整数相加
    IR_RETURN,  // 返回指令
    IR_ASSIGN,  // 赋值操作
    IR_UNKNOWN  // 未知类型
};

/// @brief LLVM IR指令基类
class IRInst
{
public:
    IRInst() { OpType = IROperator::IR_UNKNOWN; }

protected:
    IROperator OpType; // 指令类型
};
