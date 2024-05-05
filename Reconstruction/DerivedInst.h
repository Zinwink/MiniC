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
};

class StoreInst : public Instruction
{
    friend class Instruction;

public:
    

};
