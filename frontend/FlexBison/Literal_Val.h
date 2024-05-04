/**
 * @file Literal_Val.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  字面量管理头文件  可用于语法分析
 * @version 1.0
 * @date 2024-04-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <cstdint>

/// @brief 联合体存储各类型字面量数据
union Literal_digit
{
    /// @brief 标识符名称字面量  常量指针
    const char *id;

    /// @brief 无符号32位整型字面量
    uint32_t uint32_digit;

    /// @brief 有符号32位整型字面量
    int32_t int32_digit;

    /// @brief 8位整型
    int8_t char_digit;

    /// @brief 浮点数字面量
    float float_digit;
};

/// @brief 字面量管理类
class Literal_Val
{
public:
    /// @brief 字面量值
    Literal_digit digit;

    /// @brief 所在行号
    uint32_t line_no;

    /// @brief 默认无参构造
    Literal_Val();

    /// @brief 通过uint32数值构造
    /// @param val uint32数值
    /// @param line_no 所在行号
    Literal_Val(uint32_t val, uint32_t line_no = -1);

    /// @brief 通过int32数值构造
    /// @param val int32数值
    /// @param line_no 所在行号
    Literal_Val(int32_t val, uint32_t line_no = -1);

    /// @brief 通过float数值构造
    /// @param val float数值
    /// @param line_no 所在行号
    Literal_Val(float val, uint32_t line_no = -1);

    /// @brief 通过标识符名称构造
    /// @param id 标识符名称字面量字符串
    /// @param line_no 所在行号
    Literal_Val(const char *id, uint32_t line_no = -1);

    /// @brief 重载 = 赋值
    /// @param literal = 右边的字面量值
    /// @return 返回本对象引用
    Literal_Val &operator=(const Literal_Val &literal);

    /// @brief 重载等于号 等于有符号整型
    /// @param int32_digit
    /// @return 本对象
    Literal_Val &operator=(int32_t int32_digit);

    /// @brief 重载= 赋值，无符号整型
    /// @param uint32_digit
    /// @return 本对象
    Literal_Val &operator=(uint32_t uint32_digit);

    /// @brief 重载 =赋值 浮点数
    /// @param float_digit
    /// @return 本对象
    Literal_Val &operator=(float float_digit);

    /// @brief 重载 = 赋值， 字符串
    /// @param id
    /// @return 本对象
    Literal_Val &operator=(const char *id);
};
