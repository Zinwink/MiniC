/**
 * @file Scope.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 作用域管理
 * @version 1.0
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Scope.h"

/// @brief 构造函数
/// @param isGlobal 是否是全局作用域
Scope::Scope(bool _isGlobal = false)
{
    parent = nullptr;
    sym = new SymTab();
    isGlobal = _isGlobal;
}

/// @brief 弹出并销毁作用域
void ScopeMg::PopScope()
{
    stk.pop();
}

/// @brief 栈顶作用域
/// @return 作用域指针
Scope *ScopeMg::TopScope()
{
    return stk.top();
}