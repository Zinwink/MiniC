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
    uint32_t argNo; // 标定函数形参的编号 从0开始

public:
    /// @brief 析构
    ~Argument() = default;

    /// @brief 构造函数
    /// @param _ty
    /// @param name
    Argument(Type *_ty, string name) : Value(_ty, Value::ArgumentVal)
    {
        argName = name;
    }

    /// @brief 获取Value名
    /// @return
    inline string getName() override { return argName; }

    /// @brief 获取形参编号
    /// @return
    inline uint32_t getArgNo() { return argNo; }

    /// @brief 设置形参编号
    /// @param no
    inline void setArgNo(uint32_t no) { argNo = no; }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        argName = name;
        HasName = 1;
    }

    /// @brief 创建形参
    /// @param _ty
    /// @param name
    /// @return
    static ArgPtr get(Type *_ty, string name);
};
