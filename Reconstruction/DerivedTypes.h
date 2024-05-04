/**
 * @file DerivedTypes.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 继承类型 派生类
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Type.h"

///******************  IntegerType  ***************************

/// @brief 整型 包含位宽信息
class IntegerType : public Type
{
private:
    bool isSigned = true; // 是否有符号，默认为有

public:
    /// @brief 析构函数
    ~IntegerType() = default;

    /// @brief 构造函数
    IntegerType() : Type(Type::IntegerTyID)
    {
        setSubclassData(32); // 默认为32位整数
    }

    /// @brief 构造函数 指定位数
    /// @param numBits 位数
    /// @param Signed  有符号
    IntegerType(unsigned numBits, bool Signed = true) : Type(Type::IntegerTyID)
    {
        isSigned = Signed;
        setSubclassData(numBits);
    }

    /// @brief 是否是有符号
    /// @return
    bool Signed() { return isSigned; }

    /// @brief 获取位宽
    /// @return
    unsigned getBitsWidth() { return getSubclassData(); }

    /// @brief 类型对应的字符串  i位宽  如i32
    /// @return
    string TypeStr() override
    {
        return string("i") + std::to_string(getBitsWidth());
    }
};

///******************  FunctionType  ***************************

class FunctionType : public Type
{
public:
    /// @brief 析构
    ~FunctionType() = default;

    /// @brief 构造函数
    /// @param result 返回类型
    /// @param argTys 参数类型
    FunctionType(Type *result, std::vector<Type *> &argTys);

    /// @brief 构造函数
    /// @param result 返回类型
    FunctionType(Type *result);

    /// @brief 函数的返回类型
    /// @return
    Type *getReturnType() const { return ContainedTys[0]; }

    /// @brief 获取参数类型指针
    /// @param ord 参数列表索引(从0开始) ContainedTys第一位为返回类型
    /// @return
    Type *getParamType(unsigned ord)
    {
        return ContainedTys[ord + 1];
    };

    /// @brief  返回参数数目
    /// @return
    unsigned getNumParams() const
    {
        return NumContainedTys - 1;
    }

    /// @brief FunctionType是一个复合类型 这里TypeStr只得到返回值字符串
    /// @return
    string TypeStr() override
    {
        return getReturnType()->TypeStr();
    }

    /// @brief 获取函数类型
    /// @param result 返回值类型
    /// @return
    static FunctionType *get(Type *result)
    {
        // FunctionType* fun(new FunctionType(result));
        FunctionType *fun = new FunctionType(result);
        return fun;
    }

    /// @brief 获取函数类型
    /// @param result  返回类型
    /// @param argTypes 参数类型
    /// @return
    static FunctionType *get(Type *result, std::vector<Type *> &argTypes)
    {
        // FunctionType* fun(new FunctionType(result, argTypes));
        FunctionType *fun = new FunctionType(result, argTypes);
        return fun;
    }
};

///******************  ArrayType  ***************************
/// 数组类型
class ArrayType : public Type
{
    friend class Type;

private:
    Type *ContainedTy = nullptr;
    uint64_t NumElems;

public:
    /// @brief 析构函数
    ~ArrayType()
    {
        delete ContainedTy;
        ContainedTy = nullptr;
    }

    /// @brief 构造函数
    /// @param containedTy 元素类型
    /// @param numElems 元素数目
    ArrayType(Type *containedTy, uint64_t numElems) : Type(Type::ArrayTyID)
    {
        ContainedTy = containedTy;
        NumElems = numElems;
    }

    /// @brief 更新设置元素类型
    /// @param _ty
    void setContaintedTy(Type *_ty)
    {
        if (ContainedTy)
        {
            delete ContainedTy;
        }
        ContainedTy = _ty;
    }

    Type *&getContainedTy()
    {
        return ContainedTy;
    }

    /// @brief 获取数组类型的表示形式
    /// @return
    string TypeStr() override
    {
        return string("[") + std::to_string(NumElems) + string(" x ") + ContainedTy->TypeStr() + string("]");
    }

    /// @brief 根据元素类型和元素数构造数组类型
    /// @param containedTy
    /// @param numElems
    /// @return
    static ArrayType *get(Type *containedTy, uint64_t numElems)
    {
        // ArrayType* arr(new ArrayType(containedTy, numElems));
        ArrayType *arr = new ArrayType(containedTy, numElems);
        return arr;
    }

    /// @brief 根据数组的维度列表以及最小单个元素的类型构造数组类型
    /// @param dim 维度列表
    /// @param lastDImTy 单个元素的基本类型(最后一个维度的元素类型)
    /// @return
    static ArrayType *get(std::vector<int> &dim, Type *lastDimTy)
    {
        // 先得到ContainedType
        Type *contain;
        Type *temp = lastDimTy;
        for (auto it = dim.rbegin(); it != dim.rend(); ++it)
        {
            contain = ArrayType::get(temp, *it);
            temp = contain;
        }
        ArrayType *arr = static_cast<ArrayType *>(contain);
        return arr;
    }
};

///******************  PointerType  ***************************
class PointerType : public Type
{
private:
    Type *ElemntTy; // 指针元素类型
public:
    /// @brief 析构
    ~PointerType()
    {
        delete ElemntTy;
        ElemntTy = nullptr;
    };

    /// @brief 构造函数
    /// @param _elemT 指针元素类型
    PointerType(Type *_elemT) : Type(Type::PointerTyID)
    {
        ElemntTy = _elemT;
    }

    /// @brief 获取指针元素类型
    /// @return
    Type *getElemntTy() { return ElemntTy; }

    /// @brief 获取该指针类型的字符串表示
    /// @return
    string TypeStr() override
    {
        return ElemntTy->TypeStr() + string("*");
    }

    /// @brief
    /// @param _elemT
    /// @return
    static PointerType *get(Type *_elemT)
    {
        // PointerType* ptr(new PointerType(_elemT));
        PointerType *ptr = new PointerType(_elemT);
        return ptr;
    }
};