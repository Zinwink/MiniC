/**
 * @file Type.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Type.h"
#include "DerivedTypes.h"

/// @brief 获取 VoidType类型
/// @return
Type *Type::getVoidType()
{
    Type *ptr = new Type(Type::VoidTyID);
    return ptr;
}

/// @brief 获取Label类型
/// @return
Type *Type::getLabelType()
{
    Type *ptr = new Type(Type::LabelTyID);
    return ptr;
}

/// @brief 获取 int类型(有符号)
/// @param N 位数
/// @return
IntegerType *Type::getIntNType(unsigned N)
{
    IntegerType *intptr = new IntegerType(N, true);
    return intptr;
}

/// @brief 获取 uint类型(无符号)
/// @param N 位数
/// @return
IntegerType *Type::getUintNType(unsigned N)
{
    IntegerType *uint = new IntegerType(N, false);
    return uint;
}

/// @brief 创建拷贝副本
/// @param copyed
/// @return
Type *Type::copy(Type *copyed)
{
    Type *res = nullptr;

    if (copyed->isIntegerType())
    {
        IntegerType *intTy = static_cast<IntegerType *>(copyed);
        res = IntegerType::copy(intTy);
    }
    else if (copyed->isPointerType())
    {
        PointerType *ptrTy = static_cast<PointerType *>(copyed);
        res = PointerType::copy(ptrTy);
    }
    else if (copyed->isArrayType())
    {
        ArrayType *arrTy = static_cast<ArrayType *>(copyed);
        res = ArrayType::copy(arrTy);
    }
    else if (copyed->isVoidType())
    {
        res = new Type(*copyed);
    }
    else if (copyed->isFunctionType())
    {
        FunctionType *funTy = static_cast<FunctionType *>(copyed);
        res = FunctionType::copy(funTy);
    }
    else if (copyed->isLabelType())
    {
        res = new Type(*copyed);
    }
    else
    {
        res = nullptr;
    }
    return res;
}