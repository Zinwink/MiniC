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
class StoreInst;
class BinaryOperator;
class LoadInst;
class RetInst;
class CallInst;

using AllocaInstPtr = std::shared_ptr<AllocaInst>;
using StoreInstPtr = std::shared_ptr<StoreInst>;
using BinaryOperatorPtr = std::shared_ptr<BinaryOperator>;
using LoadInstPtr = std::shared_ptr<LoadInst>;
using RetInstPtr = std::shared_ptr<RetInst>;
using CallInstPtr = std::shared_ptr<CallInst>;

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

    /// @brief 创建指令StoreInst
    /// @param val
    /// @param Ptr
    /// @return
    static StoreInstPtr get(ValPtr val, ValPtr Ptr);

    /// @brief 在atBack基本快后创建指令(有条件判断)
    /// @param val
    /// @param Ptr
    /// @return
    static StoreInstPtr create(ValPtr val, ValPtr Ptr, BasicBlockPtr atBack);
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

    /// @brief 创建获取LoadInst
    /// @param Ptr
    /// @return
    static LoadInstPtr get(ValPtr Ptr);
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

        // 目前只设置为int结果类型 后面可以根据  val1,val2类型编写函数获取结果类型进行设置
        setType(Type::getIntNType(32));
    }

    /// @brief 创建BInaryOperator指令
    /// @param _op
    /// @param val1
    /// @param val2
    /// @return
    static BinaryOperatorPtr get(Opcode _op, ValPtr val1, ValPtr val2);

    /// @brief 在Block末尾创建BinaryOperator指令(该创建方法具有自动识别类型的功能)
    /// @param _op
    /// @param val1
    /// @param val2
    /// @param atBack
    /// @return
    static BinaryOperatorPtr create(Opcode _op, ValPtr val1, ValPtr val2, BasicBlockPtr atBack);
};

/// @brief RetInst
class RetInst : public Instruction
{
    friend class Instruction;

public:
    /// @brief 析构
    ~RetInst() = default;

    /// @brief 构造
    /// @param val
    RetInst(ValPtr val)
    {
        operands.push_back(val);
        setOpcode(Opcode::Ret);
    }

    static RetInstPtr get(ValPtr val);
};

class CallInst : public Instruction
{
public:
    /// @brief 析构
    ~CallInst() = default;

    /// @brief 构造函数
    /// @param fun
    /// @param relArgs
    CallInst(ValPtr fun, std::vector<ValPtr> &relArgs)
    {
        setOpcode(Opcode::Call);
        operands.push_back(fun);
        for (auto &arg : relArgs)
        {
            operands.push_back(arg);
        }
    }

    /// @brief 创建CallInst
    /// @param fun
    /// @param relArgs
    /// @return
    static CallInstPtr get(ValPtr fun, std::vector<ValPtr> &relArgs);
};

class ICmpInst : public Instruction
{
public:
    /// @brief 析构
    ~ICmpInst() = default;

    /// @brief 构造函数
    /// @param _op
    /// @param val1
    /// @param val2
    ICmpInst(Opcode _op, ValPtr val1, ValPtr val2)
    {
        setOpcode(_op);
        operands.push_back(val1);
        operands.push_back(val2);
        setType(Type::getIntNType(1));
    }

    static I
};