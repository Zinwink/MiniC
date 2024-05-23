/**
 * @file GlobalSymTab.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "GlobalSymTab.h"
#include <cassert>

/// @brief 析构函数
GlobalSymTab::~GlobalSymTab()
{
    DeclVars.clear();
}

/// @brief 查找声明的全局变量
/// @param name 全局变量名
/// @return 变量指针
ValPtr GlobalSymTab::findDeclVar(string &name)
{ // 全局作用域符号表在最顶部，没有父符号表 就是当前表的查询
    return findDeclVarOfCurTab(name);
}

/// @brief 新增声明变量(DeclVar和varList均进行加入操作)
/// @param  变量指针
/// @return nullptr表示插入失败，说明已经存在
ValPtr GlobalSymTab::newDeclVar(ValPtr var)
{
    assert(var != nullptr);
    string name = var->getName();
    if (findDeclVarOfCurTab(name) == nullptr)
    {
        DeclVars.emplace(name, var);
        return var;
    }
    else
        return nullptr;
}

/// @brief 创建全局符号表
/// @return
BaseSymTabPtr GlobalSymTab::get()
{
    BaseSymTabPtr tab = std::make_shared<GlobalSymTab>();
    return tab;
}