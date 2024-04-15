/**
 * @file Scope.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  作用域管理文件
 * @version 1.0
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Symtab.h"
#include <stack>

class Scope
{
public:
    bool isGlobal = false;
    Scope *parent; // 父作用域
    SymTab *sym;   // 本作用域符号表
public:
    /// @brief 析构函数
    ~Scope()
    {
        delete sym;
        parent = nullptr;
    }
    /// @brief 构造函数
    /// @param isGlobal 是否是全局作用域
    Scope(bool _isGlobal = false);
};

/// @brief  作用域管理类 stack栈管理
class ScopeMg
{
private:
    /// @brief 管理栈  局部作用域完成后将出栈
    std::stack<Scope *> stk;



public:
    /// @brief 添加作用域
    /// @param scp
    /// @return 作用域指针
    Scope *AddScope(Scope *scp);

    /// @brief 弹出并销毁作用域
    void PopScope();

    /// @brief 栈顶作用域
    /// @return 作用域指针
    Scope *TopScope();
};