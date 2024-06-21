/**
 * @file InitValueList.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 用于表示数组初始化列表
 * @version 1.0
 * @date 2024-06-19
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "Value.h"

class InitValueList;
/// @brief 数组初始化列表
using InitListPtr = std::shared_ptr<InitValueList>;

/// @brief 初始值列表 作为容器使用 本身不设置类型
class InitValueList : public Value
{
private:
    /// @brief 列表元素  由于是value 因此元素也能存放InitValueList进行嵌套
    std::vector<ValPtr> elemList;

    bool hasConstQualifier = false; // 是否是const修饰 即是否是常量列表

public:
    /// @brief 构造函数数
    InitValueList()
    {
        setSubClassID(Value::InitValueList);
    }

public:
    /// @brief 获取数组的初始化列表中存放的元素
    /// @return
    std::vector<ValPtr> &getElems() { return elemList; }

    /// @brief 向数组初始化列表中添加元素
    /// @param val
    void addElem(ValPtr val) { elemList.push_back(val); }

    /// @brief 设置const修饰
    void setConstQualify() override { hasConstQualifier = true; }

    /// @brief 是否由const修饰
    /// @return
    bool isConstQualify() override
    {
        return hasConstQualifier;
    }

    /// @brief 创建InitListPtr指针
    /// @return
    static InitListPtr get()
    {
        InitListPtr res = std::make_shared<InitValueList>();
        return res;
    }
};