/**
 * @file Instruction.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "User.h"
class Counter;
class BasicBlock;
class Instruction;
using InstPtr = std::shared_ptr<Instruction>;
using BasicBlockPtr = std::shared_ptr<BasicBlock>;

/// @brief 指令操作码
enum class Opcode
{
    Alloca,      // AllocaInst
    Store,       // StoreInst
    Ret,         // RetInst
    Load,        // LoadInst
    Call,        // CallInst 函数调用
    Goto,        // 无条件跳转  BranchInst  br label ..
    ConditionBr, // 有条件跳转 br condition,label t, label f
    AddInteger,  // 整数加法
    SubInteger,  // 整数减法
    DivInteger,  // 整数除法
    MulInteger,  // 整数乘法
    ModInteger,  // 整数取余
    GtInteger,   // 大于 icmp sgt/ugt
    LtIntegr,    // 小于  icmp slt/ult
    EqInTeger,   // ==  icmp eq

    Unknown // 未知
};

class Instruction : public User
{
protected:
    BasicBlockPtr parent; // 指令所属的基本块
    Opcode op;            // 指令操作码

public:
    /// @brief 析构函数
    ~Instruction() { parent.reset(); };

    virtual void clear() override
    {
        User::clear();
        parent.reset();
    }

    /// @brief 无参构造
    Instruction()
    {
        setSubClassID(Value::InstructionVal);
        op = Opcode::Unknown;
    }

    /// @brief 构造函数
    /// @param _ty
    Instruction(Type *_ty) : User(_ty)
    {
        setSubClassID(Value::InstructionVal);
        op = Opcode::Unknown;
    }

    /// @brief 设置parent
    /// @param _p
    void setBBlockParent(BasicBlockPtr _p)
    {
        parent = _p;
    }

    /// @brief 获取 parent
    /// @return
    BasicBlockPtr &getBBlockParent()
    {
        return parent;
    }

    /// @brief 获取指令操作码
    /// @return
    Opcode &getOpcode() { return op; }

    /// @brief 设置Opcode
    /// @param _op
    void setOpcode(Opcode _op) { op = _op; }

    /// @brief 获取指令操作码对应的名字
    /// @return
    string getOpcodeName();

    /// @brief 判断是否是分支指令
    /// @return
    bool isBranchInst();

    /// @brief 获取指令的字符串翻译
    /// @param inst
    /// @param cnt
    /// @return
    static string toIRstr(InstPtr inst, Counter *cnt);
};

// 下面是一些指令翻译为文本函数

/// @brief AllocaInst文本
/// @param alloca
/// @return
string AllocaInstStr(InstPtr alloca, Counter *cnt);

/// @brief StoreInst文本
/// @param store
/// @return
string StoreInstStr(InstPtr store, Counter *cnt);

/// @brief 二元运算文本
/// @param binaryop
/// @return
string BinaryInstStr(InstPtr binaryop, Counter *cnt);

/// @brief LoadInst文本
/// @param load
/// @param cnt
/// @return
string LoadInstStr(InstPtr load, Counter *cnt);

/// @brief RetInst文本
/// @param ret
/// @param cnt
/// @return
string RetInstStr(InstPtr ret, Counter *cnt);

/// @brief CallInst文本
/// @param call
/// @param cnt
/// @return
string CallInstStr(InstPtr call, Counter *cnt);

/// @brief branchInst输出文本
/// @param br
/// @param cnt
/// @return
string BranchInstStr(InstPtr br, Counter *cnt);

/// @brief 比较语句文本
/// @param icmp
/// @param cnt
/// @return
string ICmpInstStr(InstPtr icmp, Counter *cnt);