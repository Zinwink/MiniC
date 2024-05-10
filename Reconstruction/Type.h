/**
 * @file Type.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 类型管理基类
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <string>
#include <vector>
#include <memory>

using string = std::string;

class IntegerType;
class FunctionType;
class PointerType;
class ArrayType;
class Type;

/// @brief 类型管理基类
class Type
{
public:
    /// @brief  一些类型ID
    enum TypeID
    {
        IntegerTyID,  // 整型(包含各种bit宽的整型 i1,i32 等)
        PointerTyID,  // 指针类型(比如 AllocaInst)
        ArrayTyID,    // 数组类型
        FunctionTyID, // Function函数类型(包含返回值，形参类型)
        FloatTypeID,  // 浮点类型(不实现)
        DoubleTyID,   // 不实现
        VoidTyID,     // void 类型
        LabelTyID,    // Label类型 (用于BasicBlock)
        UnKnownID     // 未知类型
    };

private:
    TypeID ID;                  // 类型ID
    unsigned SubclassData : 24; // 对于Integer可存储位宽 bits

protected:
    // 主要用于处理数组等复合类型
    unsigned NumContainedTys = 0;     // 当前类型有多少个子类型
    std::vector<Type *> ContainedTys; // 但当前类型所含子类型对应的类型指针

public:
    /// @brief 默认的无参构造  初始化为未知类型
    Type() : ID(UnKnownID) {}

    /// @brief 构造函数
    /// @param _id
    Type(TypeID _id) : ID(_id) {}

    /// @brief 析构函数
    ~Type()
    {
        for (auto &t : ContainedTys)
        {
            delete t;
            t = nullptr;
        }
    };

    /// @brief 返回类型的字符串
    /// @return 虚函数 可重写
    virtual string TypeStr() { return "Unknown"; }

    /// @brief 获取子类存储的信息
    /// @return  Integer可以通过此设置位宽
    unsigned getSubclassData() { return SubclassData; }

    /// @brief 设置数据 位宽
    /// @param data
    void setSubclassData(unsigned data) { SubclassData = data; }

    /// @brief 获取TypeID
    /// @return
    TypeID getTypeID() const
    {
        return ID;
    }

    /// @brief 判断是否是 整型
    /// @return
    bool isIntegerType() const { return getTypeID() == IntegerTyID; }

    /// @brief 是否为指针类型
    /// @return
    bool isPointerType() const { return getTypeID() == PointerTyID; }

    /// @brief 是否是数组类型
    /// @return
    bool isArrayType() const { return getTypeID() == ArrayTyID; }

    /// @brief 是否是函数类型
    /// @return
    bool isFunctionType() const { return getTypeID() == FunctionTyID; }

    /// @brief void类型
    /// @return
    bool isVoidType() const { return getTypeID() == VoidTyID; }

    /// @brief Label类型
    /// @return
    bool isLabelType() const { return getTypeID() == LabelTyID; }

    /// **** 一些基本类型 ******

    /// @brief 获取 VoidType类型
    /// @return
    static Type *getVoidType();

    /// @brief 获取Label类型
    /// @return
    static Type *getLabelType();

    /// @brief
    /// @return
    static Type *getFloatType()
    {
        Type *floatT = new Type(Type::FloatTypeID);
        return floatT;
    }

    /// @brief 获取 int类型(有符号)
    /// @param N 位数
    /// @return
    static IntegerType *getIntNType(unsigned N);

    /// @brief 获取 uint类型(无符号)
    /// @param N 位数
    /// @return
    static IntegerType *getUintNType(unsigned N);

    /// @brief 创建拷贝副本
    /// @param copyed
    /// @return
    static Type *copy(Type *copyed);
};
