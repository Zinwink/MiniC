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
/// @param _isGlobal 是否是全局变量
/// @param _loc 变脸的的寻址方式 寄存器，内存，立即数
Var::Var(std::string &name, const ValueType &_vtype, bool _isGlobal, VarTag _tag, VarLoc _loc)
{
    varName = name;
    val_type = _vtype;
    isGlobal = _isGlobal;
    tag = _tag;
    loc = _loc;
}

/// @brief 常量 根据字面量值构造
Var::Var(int32_t digit)
{
    int32val = digit;
    varName = std::to_string(digit);
    val_type = BasicValueType::TYPE_INT32;
    isGlobal = true;
    tag = VarTag::CONST_VAR;
    loc = VarLoc::IMIDIATE;
}

/// @brief 根据字面量浮点数进行构造
Var::Var(float digit)
{
    floatval = digit;
    varName = std::to_string(digit);
    val_type = BasicValueType::TYPE_FLOAT;
    isGlobal = true;
    tag = VarTag::CONST_VAR;
    loc = VarLoc::IMIDIATE;
}

/// @brief 获取变量所在的llvmIR编号对应的表示字符串(加上%,对于字面常量将直接使用数值 对于全局变量使用@ 的形式)
/// @return 字符串
std::string Var::llvmVarIDStr()
{
    // 由于变量存在着诸多类型，对于全局变量，const常量以及字面量翻译得到的字符串是不一样的
    if (tag == VarTag::CONST_VAR)
    {
        // 对于常量 不管是字面常量还是声明的const 都返回数值
        // 常量不可再赋值因此只读 当作数值处理
        std::string str;
        if (val_type.type == BasicValueType::TYPE_INT32)
        {
            str = std::to_string(int32val);
        }
        else if (val_type.type == BasicValueType::TYPE_FLOAT)
        {
            str = std::to_string(floatval);
        }
        return str;
    }
    else if (isGlobal)
    {
        // 不是常量 是全局变量
        return std::string("@") + varName;
    }
    else
    {
        // 不是常量，不是全局变量 返回 %编号
        return std::string("%") + std::to_string(llvmId);
    }
}

// ***************** 一些函数 ************************‘
/// @brief 创建临时变量
Var *newTempVar(ValueType &_valType, const VarLoc &_loc)
{
    std::string name = "tmpvar";
    Var *tmp = new Var(name, _valType, false, VarTag::TEMP_VAR, _loc);
    return tmp;
}