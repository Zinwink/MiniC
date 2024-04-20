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
#include "IDCounter.h"
#include <vector>

/// @brief IR指令操作类型
enum class IROperator : int
{
    IR_VAR_ALLOCA, // 变量声明,分配内存
    IR_DATA_LOAD,  // load指令
    IR_ADD_INT,    // 整数相加
    IR_SUB_INT,    // 整数减法
    IR_MUL_INT,    // 整数乘法
    IR_DIV_INT,    // 除法
    IR_MOD_INT,    // 取余
    IR_BREAK,      // break
    IR_CONTINUE,   // continue
    IR_RETURN,     // 返回指令
    IR_ASSIGN,     // 赋值操作
    IR_UNKNOWN     // 未知类型
};

/// @brief LLVM IR指令基类
class IRInst
{
public:
    /// @brief 析构函数 采用默认实现
    virtual ~IRInst() = default;

protected:
    IROperator OpType;          // 指令类型
    std::vector<Var *> srcVars; // 源操作数(有序)
    Var *dstVar;                // 目的操作数
public:
    /// @brief 获取指令操作码
    /// @return 指令操作码类型
    IROperator getOp() { return OpType; }

    /// @brief 获取源操作数列表
    /// @return 源操作数列表
    std::vector<Var *> &getSrc() { return srcVars; }

    /// @brief 获取目的操作数
    /// @return 目的操作数
    Var *getDst() { return dstVar; }

    /// @brief 获取IR指令的字符串表述
    /// @param str IR指令字符串存储
    /// @return
    virtual std::string &toString(std::string &str, Counter *counter) = 0;
};

/// @brief 变量分配内存指令(将于此对变量进行编号)
class AllocaIRInst : public IRInst
{
public:
    /// @brief 析构函数
    ~AllocaIRInst() override;

    /// @brief 构造函数
    /// @param _dstvar 目标变量
    AllocaIRInst(Var *_dstvar);

    /// @brief 获取IR指令的字符串表述
    /// @param str IR指令字符串存储
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief LLVMIR load指令
class LoadIRInst : public IRInst
{
public:
    /// @brief 析构函数
    ~LoadIRInst() override;

    /// @brief 构造函数
    /// @param _srcVar 源操作数
    /// @param _dstVar 目的操作数
    LoadIRInst(Var *_srcVar, Var *_dstVar);

    /// @brief 获取IR指令对应的字符串表示
    /// @param str 对应字符串
    /// @param counter 分配编号计数器
    /// @return IR字符串
    std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief 二元运算指令(+，-，*，/,%)
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

    /// @brief 指令对应的字符串
    /// @param str 字符串
    /// @return 返回参数str的引用
    virtual std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief 赋值IR指令
class AssignIRInst : public IRInst
{
public:
    /// @brief 析构函数
    ~AssignIRInst() override;

    /// @brief 构造函数
    /// @param result 目的操作数
    /// @param srcVal 源操作数
    AssignIRInst(Var *result, Var *srcVal);

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};

class ReturnIRInst : public IRInst
{
public:
    /// @brief 析构函数
    ~ReturnIRInst() override;

    /// @brief 构造函数
    /// @param _dstvar 返回值目的操作数
    ReturnIRInst(Var *_dstvar);

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @param counter 计数器
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};