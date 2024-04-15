/**
 * @file Var.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Var.h"

/// @brief 有参构造
/// @param name 变量名
/// @param _vtype 变量值类型
/// @param _tag 变量标签 常量 自定义变量 生成的临时变量
/// @param _loc 变脸的的寻址方式 寄存器，内存，立即数
Var::Var(std::string &name, const ValueType &_vtype, VarTag _tag, VarLoc _loc)
{
    varName = name;
    val_type = _vtype;
    tag = _tag;
    loc = _loc;
}
