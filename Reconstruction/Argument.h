/**
 * @file Argument.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "Value.h"

class Argument;
using ArgPtr = std::shared_ptr<Argument>;

class Argument : public Value
{
    friend class Function; // 友元 可以直接访问Argument的private

private:
    string argName;

public:
    /// @brief 析构
    ~Argument() = default;

    /// @brief 构造函数
    /// @param _ty
    /// @param name
    Argument(TypePtr _ty, string name) : Value(_ty, Value::ArgumentVal)
    {
        argName = name;
    }

    /// @brief 获取Value名
    /// @return
    string getName() override { return argName; }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        argName = name;
        HasName = 1;
    }
};
