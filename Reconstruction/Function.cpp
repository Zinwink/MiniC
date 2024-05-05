/**
 * @file Function.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Function.h"
#include "Value.h"

/// @brief 构造函数
/// @param _ty 函数类型 包含返回类型  参数类型列表
/// @param _name
Function::Function(Type *_ty, string _name) : Value(_ty, Value::FunctionVal)
{
    funcName = _name;
    HasName = 1;
}