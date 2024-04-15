/**
 * @file Var.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  变量，常量等管理的头文件
 * @version 1.0
 * @date 2024-04-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "ValueType.h"

/// @brief 变量标签
enum class VarTag : int
{
    /// @brief  常量  包含字面值常量以及定义的常量 const
    CONST_VAR,
    /// @brief  编译器产生的临时变量
    TEMP_VAR,
    /// @brief 用户自定义的变量  非常量
    DEL_VAR
};

enum class VarLoc : int
{
    /// @brief 存放于寄存器
    REGISTER,
    /// @brief 存放于内存
    MEMORY,
    /// @brief 立即数
    IMIDIATE
};

/// @brief Value 变量管理类
class Var
{
    // 属性
private:
    ValueType val_type;  // 值类型
    std::string varName; // 变量名
    VarTag tag;          // 变量标签，指定类型 常量,临时量，变量
    VarLoc loc;          // 变量存在的位置

public:
    /// @brief 析构函数
    ~Var() {}
    /// @brief 无参构造
    Var() {}

    /// @brief 有参构造
    /// @param name 变量名
    /// @param _vtype 变量值类型
    /// @param _tag 变量标签 常量 自定义变量 生成的临时变量
    /// @param _loc 变脸的的寻址方式 寄存器，内存，立即数
    Var(std::string &name, const ValueType &_vtype, VarTag _tag = VarTag::DEL_VAR, VarLoc _loc = VarLoc::MEMORY);

public:
    /// @brief 获取变脸值类型
    /// @return 返回变量值类型引用
    ValueType &getValType()
    {
        return val_type;
    }

    /// @brief 获取变量名字
    /// @return 变量名
    std::string &getVarName()
    {
        return varName;
    }

    /// @brief 获取变脸标识 常量 变量 临时变量
    /// @return 变脸标识
    VarTag &getVarTag()
    {
        return tag;
    }

    /// @brief 获取变脸
    /// @return
    VarLoc &getVarLoc()
    {
        return loc;
    }
};
