/**
 * @file ValueType.h
 * @brief 变量类型管理文件
*/

#pragma once

#include <string>

/// @brief 基本类型枚举类
enum class BasicValueType:int{ //基本值类型
    TYPE_NONE,  //类型不存在
    TYPE_INT,  //有符号整型
    TYPE_UINT, //无符号整型
    TYPE_FLOAT, //float型
    TYPE_VOID, //void型 函数返回
    TYPE_MAX, // 其他未知类型
};

/// @brief 变量类型管理类
class ValueType{

public:
    /// @brief 值的类型
    BasicValueType type;

    /// @brief 构造函数 类型不存在
    ValueType();

    /// @brief  指定类型构造
    /// @param _type 指定类型
    ValueType(BasicValueType _type);

    /// @brief  将变量值类型转换为相应字符串
    /// @return string 
    std::string toString();

};

