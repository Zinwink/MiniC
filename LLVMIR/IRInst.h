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
using string = std::string;

class Function; // 前置声明

/// @brief IR指令操作类型
enum class IROperator : int
{
    IR_GLOBAL_VAR,  // 全局变量对应的 = 指令
    IR_VAR_ALLOCA,  // 变量声明,分配内存
    IR_DATA_LOAD,   // load指令
    IR_OP_ENTRY,    // 函数入口指令
    IR_ADD_INT,     // 整数相加
    IR_SUB_INT,     // 整数减法
    IR_MUL_INT,     // 整数乘法
    IR_DIV_INT,     // 除法
    IR_MOD_INT,     // 取余
    IR_CMP_LESS,    // 比较符 小于 bool  目前都是有符号整型的比较
    IR_CMP_GREATER, // 比较符 大于 bool
    IR_CMP_EQUAL,   // 比较符 等于 bool
    IR_CMP_UNEQUAL, // 比较符，不等于 !=
    IR_OP_LABEL,    // Label指令 用于跳转
    IR_OP_ZEXT,     // 扩展 zero extend (用于将bool i1结果扩展为i32 存入赋值中)
    IR_OP_BR,       // LLVMIR中的 br 跳转指令(对于无条件跳转 br label形式另外加指令类型，如下IR_OP_GOTO无条件跳转)
    IR_OP_GOTO,     // 无条件跳转指令
    IR_BREAK,       // break
    IR_CONTINUE,    // continue
    IR_RETURN,      // 返回指令  函数出口指令
    IR_FUNCALL,     // 函数调用指令
    IR_ASSIGN,      // 赋值操作
    IR_UNKNOWN      // 未知类型
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
    Var *dstVar = nullptr;      // 目的操作数
    bool dead = false;          // 指令是否是dead指令
    string labelname;           // label指令的名字

    IRInst *trueLabel = nullptr;  // 目标真出口指令,用于有条件的跳转
    IRInst *falseLabel = nullptr; // 目标假出口指令，用于有条件跳转

public:
    /// @brief 获取指令操作码
    /// @return 指令操作码类型
    IROperator getOp() { return OpType; }

    /// @brief 获取标签指令的名字
    /// @return 标签指令名
    string &getLabelName() { return labelname; }

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

/// @brief 函数入口指令
class EntryIRInst : public IRInst
{
public:
    /// @brief 构造函数
    EntryIRInst();

    /// @brief 析构函数
    ~EntryIRInst() override;

    /// @brief 获取IR指令的字符串表述
    /// @param str IR指令字符串存储
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief 全局变量翻译的IR指令
class GlobalVarIRInst : public IRInst
{
public:
    /// @brief 析构函数
    ~GlobalVarIRInst() override;

    /// @brief 构造函数
    /// @param _dstvar 全局变量
    GlobalVarIRInst(Var *_dstvar);

    /// @brief 获取IR指令的字符串表述
    /// @param str IR指令字符串存储
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
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

/// @brief 二元运算指令(+，-，*，/,%，< > == )
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

    /// @brief 拷贝形参
    /// @param result
    /// @param param
    AssignIRInst(Var *result, FunFormalParam *param);

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief return 指令()
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

/// @brief  函数调用IR指令
class CallIRInst : public IRInst
{
private:
    Function *fun; // 调用的函数

public:
    /// @brief 析构函数
    ~CallIRInst() override;

    /// @brief 无参函数调用
    /// @param  _fun 调用的函数
    /// @param _dstvar 函数调用结果
    CallIRInst(Function *_fun, Var *_dstvar);

    /// @brief 构造函数
    /// @param  _fun 调用的函数
    /// @param _dstvar 目的操作数 函数调用结果(无返回值，直接写nullptr)
    /// @param params 函数实参列表
    CallIRInst(Function *_fun, Var *_dstvar, std::vector<Var *> &params);

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @param counter 计数器
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief 函数Label指令
class LabelIRInst : public IRInst
{
private:
    int32_t _llvmId = -1; // 分配的llvmIR编号

public:
    /// @brief 获取Label的llvmir编号
    /// @return 编号引用
    int32_t &getllvmId() { return _llvmId; }

    /// @brief 构造函数
    LabelIRInst();

    /// @brief 析构函数
    ~LabelIRInst() override;

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @param counter 计数器
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief zero extension指令
class ZextIRInst : public IRInst
{
private:
    ValueType extendType = BasicValueType::TYPE_INT32; // 默认扩展类型

public:
    /// @brief 构造函数
    /// @param _result 扩展结果
    /// @param _srcVal1 要扩展的源操作数
    /// @param _srcVal1 扩展类型
    ZextIRInst(Var *_result, Var *_srcVal1, ValueType &_extType);

    /// @brief 析构函数
    ~ZextIRInst() override;

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @param counter 计数器
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief 无条件跳转IR指令  br label %1
class GotoIRInst : public IRInst
{
public:
    /// @brief 构造函数
    /// @param label 跳转标签
    GotoIRInst(IRInst *label);

    /// @brief 析构函数
    ~GotoIRInst() override;

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @param counter 计数器
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};

/// @brief 条件跳转指令 br i1 %5, label %6, label %9
class BrIRInst : public IRInst
{
public:
    /// @brief 构造函数
    /// @param _dstvar 条件值
    /// @param _trueLabel 真标签入口
    /// @param _falseLabel 假标签入口
    BrIRInst(Var *_dstvar, IRInst *_trueLabel, IRInst *_falseLabel);

    /// @brief 析构函数
    ~BrIRInst() override;

    /// @brief 获取指令的IR字符串
    /// @param str 存取字符串
    /// @param counter 计数器
    /// @return
    std::string &toString(std::string &str, Counter *counter) override;
};