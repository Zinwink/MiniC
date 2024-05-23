/**
 * @file Argument.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Argument.h"
#include "Module.h"

/// @brief 创建形参
/// @param _ty
/// @param name
/// @return
ArgPtr Argument::get(Type *_ty, string name)
{
    ArgPtr arg = std::make_shared<Argument>(_ty, name);
    return arg;
}
