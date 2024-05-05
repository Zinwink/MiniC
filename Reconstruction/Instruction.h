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
    Goto,        // 无条件跳转  BranchInst
    ConditionBr, // 有条件跳转
    AddInteger,  // 整数加法
    SubInteger,  // 整数减法
    DivInteger,  // 整数除法
    MulInteger,  // 整数乘法
    ModInteger,  // 整数取余

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
};