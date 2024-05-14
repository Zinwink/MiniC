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
#include "Constant.h"
class Counter;
class GlobalVariable;
using GlobalVariPtr = std::shared_ptr<GlobalVariable>;

class GlobalVariable : public Value
{
private:
    string Gname; // 名称
    Type *globalValType = nullptr;
    ConstantPtr initilizer = nullptr; // 初始化的值

public:
    /// @brief
    /// @param _ty
    /// @param name
    GlobalVariable(Type *_ty, string name) : Value(PointerType::get(_ty), Value::GlobalVari)
    {
        globalValType = _ty;
        Gname = name;
    }
    /// @brief 析构函数
    ~GlobalVariable()
    {
        initilizer.reset();
        globalValType = nullptr;
    }

    /// @brief 获取全局变量中存放值得类型
    /// @return
    Type *getElemTy() { return globalValType; }

    /// @brief 清理
    void clear() override
    {
        Value::clear();
        initilizer.reset();
    }

    /// @brief 获取Value名
    /// @return
    string getName() override { return Gname; }

    /// @brief 设置binding
    /// @param b
    void setInitilizer(ConstantPtr b)
    {
        initilizer = b;
    }

    /// @brief 获取binding
    /// @return
    ConstantPtr &getInitilizer()
    {
        return initilizer;
    }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        Gname = name;
        HasName = 1;
    }

    static GlobalVariPtr get(Type *_ty, string name)
    {
        GlobalVariPtr ptr = std::make_shared<GlobalVariable>(_ty, name);
        return ptr;
    }

    /// @brief 全局变量翻译为文本
    /// @param g
    /// @param cnt
    /// @return
    static string toIRstr(GlobalVariPtr g, Counter *cnt);
};
