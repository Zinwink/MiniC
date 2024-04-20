/**
 * @file ScopeMg.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  作用域管理类 包含并管理全局符号表，函数符号表以及局部符号表等所有表信息
 * @version 1.0
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "GlobalSymTab.h"
#include "FuncTab.h"
#include <stack>

/// @brief 函数表管理类
class ScopeMg
{
private:
    /// @brief 符号表管理栈
    std::stack<BaseSymTab *> stk;

public:
    /// @brief 构造函数
    ScopeMg();
    /// @brief 析构函数
    ~ScopeMg();

    /// @brief 获取管理栈
    /// @return 管理栈
    std::stack<BaseSymTab *> &StkMg() { return stk; }

    /// @brief 获取当前符号表
    /// @return 当前符号表
    BaseSymTab *curTab() { return stk.top(); }

    /// @brief 压入符号表
    /// @param  压入符号表
    /// @return
    BaseSymTab *pushTab(BaseSymTab *tab)
    {
        stk.push(tab);
        return tab;
    }

    /// @brief 弹出当前符号表
    /// @return
    BaseSymTab *popTab()
    {
        BaseSymTab *cur = stk.top();
        stk.pop();
        return cur;
    }

    /// @brief 符号表管理是否为空
    /// @return
    bool isEmpty() { return stk.empty(); }
};
