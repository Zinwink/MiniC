/**
 * @file ValueType.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 变量值类型管理
 * @version 1.0
 * @date 2024-03-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <string>

/// @brief 基本类型枚举类
enum class BasicValueType : int
{               // 基本值类型
    TYPE_NONE,  // 类型不存在
    TYPE_INT,   // 有符号整型
    TYPE_UINT,  // 无符号整型
    TYPE_FLOAT, // float型
    TYPE_VOID,  // void型 函数返回
    TYPE_BOOL,  // 布尔类型
    TYPE_MAX,   // 其他未知类型
};

/// @brief 变量类型管理类
class ValueType
{

public:
    /// @brief 值的类型
    BasicValueType type;

    /// @brief 构造函数 类型不存在
    ValueType();

    /// @brief  指定类型构造
    /// @param _type 指定类型
    ValueType(BasicValueType _type);

    /// @brief 拷贝构造
    /// @param _type ValueType类型值引用
    ValueType(const ValueType &_type);

    /// @brief  将变量值类型转换为相应字符串
    /// @return string  对应的值类型IR 字符串
    std::string toString();

    /// @brief 赋值运算
    /// @param _type 等号右边的变量值类型
    /// @return 本对象引用
    ValueType &operator=(const ValueType &_type);
};
