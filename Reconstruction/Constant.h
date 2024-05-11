/**
 * @file Constant.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 常量类
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "Value.h"
#include "Type.h"
#include "DerivedTypes.h"

class ConstantInt;
class Constant;
using ConstantIntPtr = std::shared_ptr<ConstantInt>;
using ConstantPtr = std::shared_ptr<Constant>;

/// @brief Constant类
class Constant : public Value
{
protected:
    unsigned SubclassData : 27;

public:
    /// @brief 析构
    ~Constant() = default;

    /// @brief 默认无参构造
    Constant() { setSubClassID(Value::Constant); }

    /// @brief 构造
    /// @param _ty
    Constant(Type *_ty) : Value(_ty, Value::Constant) {}
};

/// @brief ConstantInt类型
class ConstantInt : public Constant
{
private:
    string Cname;
    uint32_t data; // 存放int 的值

public:
    /// @brief 析构
    ~ConstantInt() = default;

    /// @brief 构造函数
    /// @param bits
    /// @param isSign
    ConstantInt(unsigned bits, bool isSign = true)
    {
        if (isSign)
        {
            setType(Type::getIntNType(bits)); // 设置类型  有符号整数
        }
        else
        {
            setType(Type::getUintNType(bits)); // 无符号整数
        }
    }

    /// @brief 获取Value名
    /// @return
    string getName() override { return Cname; }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        Cname = name;
        HasName = 1; // 有名字
    }

    /// @brief 设置值
    /// @param a
    void setValue(unsigned a) { data = a; }

    /// @brief 获取值(只存二进制码),，如果为有符号 使用 int 接受转型
    /// @return 默认为有符号
    int32_t getValue() { return data; }

    /// @brief 获取ConstantInt
    /// @param bits
    /// @param isSign
    /// @return
    static ConstantIntPtr get(unsigned bits, bool isSign = true)
    {
        ConstantIntPtr ptr = std::make_shared<ConstantInt>(bits, isSign);
        return ptr;
    }
};
