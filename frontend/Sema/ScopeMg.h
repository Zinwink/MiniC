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

    /// @brief 符号管理栈的全局符号表
    GlobalSymTab *curGlobalTab;

    /// @brief 指向当前函数
    Function *curfunc = nullptr;

public:
    /// @brief 构造函数
    ScopeMg();
    /// @brief 析构函数
    ~ScopeMg();

    /// @brief 获取管理栈
    /// @return 管理栈
    std::stack<BaseSymTab *> &StkMg() { return stk; }

    /// @brief 获取当前管理栈的全局符号表
    /// @return 全局符号表指针(使用基类指针转型得到)
    GlobalSymTab *globalTab();

    /// @brief 获取当前符号表
    /// @return 当前符号表
    BaseSymTab *curTab() { return stk.top(); }

    /// @brief 获得当前指向的函数指针
    /// @return
    Function *curFun() { return curfunc; }

    /// @brief 设置当前指向的函数指针
    /// @param fun
    void setCurFun(Function *fun) { curfunc = fun; }

    /// @brief 压入符号表
    /// @param  压入符号表
    /// @return
    BaseSymTab *pushTab(BaseSymTab *tab)
    {
        tab->setParent(this->curTab()); // 设置要压栈的符号表的父表为当前栈顶表
        stk.push(tab);
        return tab;
    }

    /// @brief 弹出当前符号表
    /// @return
    BaseSymTab *popTab()
    {
        BaseSymTab *cur = stk.top();
        cur->setParent(nullptr);
        stk.pop();
        return cur;
    }

    /// @brief 符号表管理是否为空
    /// @return
    bool isEmpty() { return stk.empty(); }
};
