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

/// @brief 构造函数
/// @param result 返回类型
/// @param argTys 参数类型
FunctionType::FunctionType(TypePtr result, std::vector<TypePtr> &argTys) : Type(Type::FunctionTyID)
{
    NumContainedTys = 1 + argTys.size();
    ContainedTys.push_back(result);
    for (auto &ty : argTys)
    {
        ContainedTys.push_back(ty);
    }
}

/// @brief 构造函数
/// @param result 返回类型
FunctionType::FunctionType(TypePtr result) : Type(Type::FunctionTyID)
{
    NumContainedTys = 1;
    ContainedTys.push_back(result);
}