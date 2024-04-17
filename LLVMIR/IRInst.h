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
#include "Var.h"
#include <vector>

/// @brief IR指令操作类型
enum class IROperator : int
{
    IR_VAR_DECLAR, // 变量声明
    IR_ADD_INT,    // 整数相加
    IR_RETURN,     // 返回指令
    IR_ASSIGN,     // 赋值操作
    IR_UNKNOWN     // 未知类型
};

/// @brief LLVM IR指令基类
class IRInst
{
public:
    /// @brief 构造函数
    IRInst() { OpType = IROperator::IR_UNKNOWN; }

    /// @brief 析构函数 采用默认实现
    virtual ~IRInst() = default;

protected:
    IROperator OpType;          // 指令类型
    std::vector<Var *> srcVars; // 源操作数
    Var *dstVar;                // 目的操作数
public:
    /// @brief 获取IR指令的字符串表述
    /// @param str IR指令字符串存储
    /// @return
    virtual std::string &toString(std::string &str);

    /// @brief 获取指令操作码
    /// @return 指令操作码类型
    IROperator getOp() { return OpType; }

    /// @brief 获取源操作数列表
    /// @return 源操作数列表
    std::vector<Var *> &getSrc() { return srcVars; }

    /// @brief 获取目的操作数
    /// @return 目的操作数
    Var *getDst() { return dstVar; }

    /// @brief  获取源操作数的寄存器id
    /// @return
    int32_t &getSrcRegId();
};

/// @brief 二元运算指令
class BinaryIRInst : public IRInst
{
public:
    /// @brief 析构函数
    virtual ~BinaryIRInst() override;

    /// @brief 根据IR指令类型，源操作数，结果操作数构造
    /// @param _op 操作符
    /// @param _result 结果操作数
    /// @param _srcVal1 源操作数1
    /// @param _srcVal2 源操作数2
    BinaryIRInst(IROperator _op, Var *_result, Var *_srcVal1, Var *_srcVal2);

    std::string &toString(std::string &str) override;
};

/// @brief 赋值IR指令
class AssignIRInst : public IRInst
{
public:
    /// @brief 析构函数
    virtual ~AssignIRInst() override;

    /// @brief 构造函数
    /// @param result 目的操作数
    /// @param srcVal 源操作数
    AssignIRInst(Var *result, Var *srcVal);

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @return
    std::string &toString(std::string &str) override;
};