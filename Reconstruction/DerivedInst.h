/**
 * @file DerivedInst.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  Instruction的派生类
 * @version 1.0
 * @date 2024-05-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Instruction.h"
#include "DerivedTypes.h"
#include "Type.h"

class AllocaInst;

using AllocaInstPtr = std::shared_ptr<AllocaInst>;

/// @brief AllocaInst (将充当变量)(AllocaInst本身的Type是指针类型)
class AllocaInst : public Instruction
{
    friend class Instruction;

private:
    string AllocaName;   // 名字
    Type *AllocatedType; //  Alloca指令申请的类型

public:
    /// @brief 析构函数
    ~AllocaInst()
    {
        // AllocaInst本身的Type 为PointerType 将复用AllocatedType 因此析构时只需将 AllocatedType=null
        // 防止反复释放
        AllocatedType = nullptr;
    };

    /// @brief 无参构造
    AllocaInst()
    {
        setOpcode(Opcode::Alloca);
    }

    /// @brief 构造函数
    /// @param _ty
    AllocaInst(Type *_allocatedType)
    {
        AllocatedType = _allocatedType;
        setType(PointerType::get(_allocatedType));
        setOpcode(Opcode::Alloca);
    }

    /// @brief 获取Value名
    /// @return
    string getName() override { return AllocaName; }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        AllocaName = name;
        HasName = 1;
    }

    /// @brief 静态函数  获取指令对象指针
    /// @param name
    /// @param _allocatedTy
    /// @return
    static AllocaInstPtr get(string name, Type *_allocatedTy);
};

/// @brief storeInst
class StoreInst : public Instruction
{
    friend class Instruction;

public:
    /// @brief 析构函数
    ~StoreInst() = default;

    /// @brief 无参构造
    StoreInst()
    {
        setOpcode(Opcode::Store);
    }

    /// @brief 构造函数
    /// @param val 存放值
    /// @param Ptr 存放位置  指针类型
    StoreInst(ValPtr val, ValPtr Ptr)
    {
        setOpcode(Opcode::Store);
        operands.push_back(val);
        operands.push_back(Ptr);
    }
};

/// @brief  LoadInst
class LoadInst : public Instruction
{
    friend class Instruction;

public:
    /// @brief 析构函数
    ~LoadInst()
    {
        setType(nullptr); // Value Type来自操作数地elementType
    }

    /// @brief 构造函数
    /// @param Ptr
    LoadInst(ValPtr Ptr)
    {
        assert(Ptr->getType()->isPointerType() && "ValPtr is not a PointerType!");
        setOpcode(Opcode::Load);
        operands.push_back(Ptr);
        PointerType *pointerTy = static_cast<PointerType *>(Ptr->getType());
        setType(pointerTy->getElemntTy());
    }
};

/// @brief 二元运算符
class BinaryOperator : public Instruction
{
    friend class Instruction;

public:
    /// @brief 析构函数
    ~BinaryOperator() = default;

    /// @brief
    /// @param val1
    /// @param val2
    BinaryOperator(Opcode _op, ValPtr val1, ValPtr val2)
    {
        setOpcode(_op);
        operands.push_back(val1);
        operands.push_back(val2);
    }
};