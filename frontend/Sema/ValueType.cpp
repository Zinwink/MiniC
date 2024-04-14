/**
 * @file ValueType.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 变量值类型管理
 * @version 1.0
 * @date 2024-03-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ValueType.h"

/// @brief 构造函数 变量值类型不存在
ValueType::ValueType() : type(BasicValueType::TYPE_NONE) {}

/// @brief 构造函数 指定变量值类型
/// @param _type 指定变量值类型
ValueType::ValueType(BasicValueType _type)
{
    type = _type;
}

/// @brief 拷贝构造
/// @param _type ValueType类型
ValueType::ValueType(const ValueType &_type)
{
    type = _type.type;
}

/// @brief 重载赋值符号
/// @param _type 赋值符号右边的类型
/// @return 返回本对象引用
ValueType &ValueType::operator=(const ValueType &_type)
{
    this->type = _type.type;
    return *this;
}

/// @brief 赋值
/// @param _basic_type 基本类型
/// @return 本对象
ValueType &ValueType::operator=(BasicValueType _basic_type)
{
    this->type = _basic_type;
    return *this;
}

/// @brief 将变量值类型转化为相应的字符串  IR指令需要
/// @return string
std::string ValueType::toString()
{
    std::string str;
    switch (type)
    {
    case BasicValueType::TYPE_INT32:
        str = "i32";
        break;
    case BasicValueType::TYPE_FLOAT:
        str = "float";
        break;
    case BasicValueType::TYPE_NONE:
        str = "None";
        break;
    case BasicValueType::TYPE_VOID:
        str = "void";
        break;
    case BasicValueType::TYPE_UINT32:
        str = "ui32";
        break;
    case BasicValueType::TYPE_BOOL:
        str = "i1";
        break;
    case BasicValueType::TYPE_STR:
        str = "const char*";
        break;
    default:
        str = "unknown";
        break;
    }
    return str;
}
