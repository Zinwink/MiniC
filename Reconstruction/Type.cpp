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
TypePtr Type::getVoidType()
{
    TypePtr ptr = std::make_shared<Type>(Type::VoidTyID);
    return ptr;
}

/// @brief 获取Label类型
/// @return
TypePtr Type::getLabelType()
{
    TypePtr ptr = std::make_shared<Type>(Type::LabelTyID);
    return ptr;
}

/// @brief 获取 int类型(有符号)
/// @param N 位数
/// @return
IntegerTyPtr Type::getIntNType(unsigned N)
{
    IntegerTyPtr intptr = std::make_shared<IntegerType>(N, true);
    return intptr;
}

/// @brief 获取 uint类型(无符号)
/// @param N 位数
/// @return
IntegerTyPtr Type::getUintNType(unsigned N)
{
    IntegerTyPtr uint = std::make_shared<IntegerType>(N, false);
    return uint;
}