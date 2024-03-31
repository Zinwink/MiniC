/**
 * @file ValueType.cpp
 * @brief 变量值类型管理实现
 */

#include <ValueType.h>

/// @brief 构造函数 变量值类型不存在
ValueType::ValueType() : type(BasicValueType::TYPE_NONE) {}

/// @brief 构造函数 指定变量值类型
/// @param _type 指定变量值类型
ValueType::ValueType(BasicValueType _type)
{
    type = _type;
}

/// @brief 将变量值类型转化为相应的字符串
/// @return string
std::string ValueType::toString()
{
    std::string str;
    switch (type)
    {
    case BasicValueType::TYPE_INT:
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
    case BasicValueType::TYPE_UINT:
        str = "ui32";
        break;
    default:
        str = "unknown";
        break;
    }
    return str;
}
