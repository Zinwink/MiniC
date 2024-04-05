/**
 * @file Literal_Val.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 字面量管理实现文件
 * @version 1.0
 * @date 2024-04-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Literal_Val.h"

/// @brief 默认无参构造
Literal_Val::Literal_Val()
{
    line_no = -1;
    type.type = BasicValueType::TYPE_MAX;
}

/// @brief uint32字面量构造
/// @param val uint32值
/// @param line_no 所在行号
Literal_Val::Literal_Val(uint32_t val, uint32_t line_no)
{
    digit.uint32_digit = val;
    this->line_no = line_no;
    type.type = BasicValueType::TYPE_UINT32;
}

/// @brief int32字面量构造
/// @param val 字面量数值
/// @param line_no 所在行号
Literal_Val::Literal_Val(int32_t val, uint32_t line_no)
{
    digit.int32_digit = val;
    this->line_no = line_no;
    type.type = BasicValueType::TYPE_INT32;
}

/// @brief float字面量构造
/// @param val 构造数值
/// @param line_no 所在行号
Literal_Val::Literal_Val(float val, uint32_t line_no)
{
    digit.float_digit = val;
    this->line_no = line_no;
    type.type = BasicValueType::TYPE_FLOAT;
}

/// @brief 字符串字面量构造
/// @param id 构造字符串  标识符名字
/// @param line_no 所在行号
Literal_Val::Literal_Val(const char *id, uint32_t line_no)
{
    digit.id = id;
    this->line_no = line_no;
    type.type = BasicValueType::TYPE_STR;
}

/// @brief 重载 = 赋值
/// @param literal = 右边的字面量值
/// @return 返回本对象引用
Literal_Val &Literal_Val::operator=(const Literal_Val &literal)
{
    this->line_no = literal.line_no;
    this->digit = literal.digit;
    this->type = literal.type;
    return *this;
}

/// @brief 重载 = 赋值， 字符串
/// @param id
/// @return 本对象
Literal_Val &Literal_Val::operator=(const char *id)
{
    this->type.type = BasicValueType::TYPE_STR;
    this->digit.id = id;
    return *this;
}

/// @brief 重载 =赋值 浮点数
/// @param float_digit
/// @return 本对象
Literal_Val &Literal_Val::operator=(float float_digit)
{
    this->type.type = BasicValueType::TYPE_FLOAT;
    this->digit.float_digit = float_digit;
    return *this;
}

/// @brief 重载= 赋值，无符号整型
/// @param uint32_digit
/// @return 本对象
Literal_Val &Literal_Val::operator=(uint32_t uint32_digit)
{
    this->type.type = BasicValueType::TYPE_UINT32;
    this->digit.uint32_digit = uint32_digit;
    return *this;
}

/// @brief 重载等于号 等于有符号整型
/// @param int32_digit
/// @return 本对象
Literal_Val &Literal_Val::operator=(int32_t int32_digit)
{
    this->type.type = BasicValueType::TYPE_INT32;
    this->digit.int32_digit = int32_digit;
    return *this;
}