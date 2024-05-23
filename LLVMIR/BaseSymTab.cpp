/**
 * @file Symtab.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 符号表管理基类
 * @version 1.0
 * @date 2024-04-08
 *
 * @copyright Copyright (c) 2024
 *
 */
// 在编译器设计中 认为包含 3类全局符号表 (全局变量,函数符号表域)  函数符号表(函数符号表中可能包含定义的块) 块符号表
//
#include "BaseSymTab.h"

/// @brief 析构函数
BaseSymTab::~BaseSymTab()
{
    // 清空容器中的内容
    DeclVars.clear();
    parent.reset();
}


/// @brief 从当前符号表中查找变量(搜搜域只限于当前符号表)
/// @return
ValPtr BaseSymTab::findDeclVarOfCurTab(string &name)
{
    auto iter = DeclVars.find(name);
    if (iter == DeclVars.end())
    {
        // 未找到
        return nullptr;
    }
    else
    {
        return iter->second;
    }
}