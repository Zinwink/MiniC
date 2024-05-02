/**
 * @file GlobalVariable.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "Value.h"

class GlobalVariable;
using GlobalVariPtr = std::shared_ptr<GlobalVariable>;

class GlobalVariable : public Value
{
private:
    string Gname;   // 名称
    ValPtr binding; // 绑定的Value

public:
    /// @brief
    /// @param _ty
    /// @param name
    GlobalVariable(TypePtr _ty, string name) : Value(_ty, Value::GlobalVari)
    {
        Gname = name;
    }
    /// @brief 析构函数
    ~GlobalVariable() = default;

    /// @brief 获取Value名
    /// @return
    string getName() override { return Gname; }

    /// @brief 设置binding
    /// @param b
    void setBinding(ValPtr b)
    {
        binding = b;
    }

    /// @brief 获取binding
    /// @return
    ValPtr getBinding()
    {
        return binding;
    }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        Gname = name;
        HasName = 1;
    }

    static GlobalVariPtr get(TypePtr _ty, string name)
    {
        GlobalVariPtr ptr = std::make_shared<GlobalVariable>(_ty, name);
        return ptr;
    }
};
