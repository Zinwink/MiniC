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
    /// @brief 用户声明的变量 包含(全局变量，局部变量，等)
    DECL_VAR,
    /// @brief  常量  包含字面值常量以及定义的常量 const
    CONST_VAR,
    /// @brief  编译器产生的临时变量
    TEMP_VAR,
    /// @brief 形参
    FORMAL_PARAM
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
protected:
    bool isGlobal = false; // 是否是全局变量
    ValueType val_type;    // 值类型
    std::string varName;   // 变量名
    VarTag tag;            // 变量标签，指定类型 常量,临时量，变量
    VarLoc loc;            // 变量存在的位置
    int32_t llvmId = -1;   // llvmIR分配的编号，-1表示暂时未分配
    int32_t regId = -1;    // 所在寄存器编号,-1表示未分配
    // 数值属性，对于常量需要使用
    int32_t int32val = 0; // 整数值
    float floatval = 0;   // 浮点数值

public:
    /// @brief 析构函数
    ~Var() {}
    /// @brief 无参构造,
    Var() {}

    /// @brief 常量 根据字面量值构造
    Var(int32_t digit);

    /// @brief 根据字面量浮点数进行构造
    Var(float digit);

    /// @brief 有参构造
    /// @param name 变量名
    /// @param _vtype 变量值类型
    /// @param _tag 变量标签 常量 自定义变量 生成的临时变量
    /// @param _isGlobal 是否是全局变量
    /// @param _loc 变脸的的寻址方式 寄存器，内存，立即数
    Var(std::string &name, const ValueType &_vtype, bool _isGlobal = false, VarTag _tag = VarTag::DECL_VAR, VarLoc _loc = VarLoc::MEMORY);

public:
    /// @brief 获取是否是全局变脸的标志
    /// @return 获取是否是全局变量的标志
    bool &getIsGloabl() { return isGlobal; }

    /// @brief 获取llvmIR分配的变量编号
    /// @return llvmIR编号引用
    int32_t &getllvmId() { return llvmId; }

    /// @brief 获取寄存器编号
    /// @return
    int32_t &getregId()
    {
        return regId;
    }

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

    /// @brief 返回int32值引用
    /// @return
    int32_t &int32Value() { return int32val; }

    /// @brief 返回float值引用
    /// @return
    float &floatValue() { return floatval; }

    /// @brief 获取变量类型字符串
    /// @return
    virtual std::string llvmVarTypeStr() { return val_type.toString(); }

    /// @brief 获取变量所在的llvmIR编号对应的表示字符串(加上%,对于字面常量将直接使用数值 对于全局变量使用@ 的形式)
    /// @return 字符串
    virtual std::string llvmVarIDStr();
};

/// @brief 创建临时变量
Var *newTempVar(ValueType &_valType, const VarLoc &_loc = VarLoc::MEMORY);
