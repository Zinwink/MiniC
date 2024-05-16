/**
 * @file DerivedTypes.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 继承类型 派生类
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "DerivedTypes.h"
#include <cassert>

//********************************* IntegerType ***********************************
/// @brief 拷贝副本
/// @param copied
/// @return
IntegerType *IntegerType::copy(IntegerType *copied)
{
    assert(copied->isIntegerType() && "not IntegerType!");
    IntegerType *res = new IntegerType(*copied);
    return res;
}

/// @brief 构造函数
/// @param result 返回类型
/// @param argTys 参数类型
FunctionType::FunctionType(Type *result, std::vector<Type *> &argTys) : Type(Type::FunctionTyID)
{
    NumContainedTys = 1 + argTys.size();
    ContainedTys.push_back(result);
    for (auto &ty : argTys)
    {
        ContainedTys.push_back(ty);
    }
}

// *********************************  FunctionType *************************************
/// @brief 构造函数
/// @param result 返回类型
FunctionType::FunctionType(Type *result) : Type(Type::FunctionTyID)
{
    NumContainedTys = 1;
    ContainedTys.push_back(result);
}

/// @brief 拷贝生成副本
/// @param copied
/// @return
FunctionType *FunctionType::copy(FunctionType *copied)
{
    assert(copied->isFunctionType() && "not FunctionType!");
    FunctionType *funTy = new FunctionType();
    for (auto &c : copied->ContainedTys)
    {
        funTy->ContainedTys.push_back(Type::copy(c));
    }
    funTy->NumContainedTys = copied->NumContainedTys;
    return funTy;
}

// ************************* ArrayType ******************************
/// @brief 拷贝生成副本
/// @param copied
/// @return
ArrayType *ArrayType::copy(ArrayType *copied)
{
    assert(copied->isArrayType() && "not ArrayType!");
    ArrayType *arrTy = new ArrayType();
    arrTy->NumElems = copied->NumElems;
    arrTy->ContainedTy = Type::copy(copied->ContainedTy);
    return arrTy;
}

/// @brief 获取该数组类型每一个维度的数值
/// @return
std::vector<int> ArrayType::getDimValues()
{
    std::vector<int> dims;
    dims.push_back(NumElems);
    Type *nextTy = ContainedTy;
    while (nextTy->isArrayType())
    { // 迭代获取
        ArrayType *arr = static_cast<ArrayType *>(nextTy);
        dims.push_back(arr->NumElems);
        nextTy = arr->ContainedTy;
    }
    return dims;
}

//********************************* PointerType ****************************************
/// @brief 拷贝生成副本
/// @param copied
/// @return
PointerType *PointerType::copy(PointerType *copied)
{
    assert(copied->isPointerType() && "not pointerType!");
    PointerType *ptrTy = new PointerType();
    ptrTy->ElemntTy = Type::copy(copied->ElemntTy);
    return ptrTy;
}
