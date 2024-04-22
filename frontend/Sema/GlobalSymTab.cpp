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
    // varList和DeclVars存放的var变量相同，先清理 varList
    for (auto var : varList)
    {
        delete var;
        var = nullptr;
    }
    varList.clear();
    DeclVars.clear(); // 防止重复释放
    // funList和DeclFuns，DeclFuns包含funList (DeclFuns可能包含内建函数)
    for (auto &iter : DeclFuns)
    {
        delete iter.second;
        iter.second = nullptr;
    }
    DeclFuns.clear();
    funList.clear(); // 防止重复清理
}

/// @brief 查找声明的全局变量
/// @param name 全局变量名
/// @return 变量指针
Var *GlobalSymTab::findDeclVar(string &name)
{ // 全局作用域符号表在最顶部，没有父符号表 就是当前表的查询
    return findDeclVarOfCurTab(name);
}

/// @brief 新增声明变量(DeclVar和varList均进行加入操作)
/// @param  变量指针
/// @return nullptr表示插入失败，说明已经存在
Var *GlobalSymTab::newDeclVar(Var *var)
{
    assert(var != nullptr);
    if (findDeclVarOfCurTab(var->getVarName()) == nullptr)
    {
        // 未找到 加入varList, DeclVars
        var->getIsGloabl() = true; // 设置为全局变量
        varList.push_back(var);
        DeclVars.emplace(var->getVarName(), var);
        return var;
    }
    else
        return nullptr;
}

/// @brief 根据函数名查找声明的函数
/// @param funname
/// @return nullptr表示未找到
Function *GlobalSymTab::findDeclFun(string &funname)
{
    auto iter = DeclFuns.find(funname);
    if (iter == DeclFuns.end())
    {
        // 未找到
        return nullptr;
    }
    else
        return iter->second;
}

/// @brief 新增声明定义的函数 (DeclFuns,funList均进行加入)
/// @param fun 函数
/// @return nullptr表示已经存在，新增失败；否曾新增成功
Function *GlobalSymTab::newDeclFun(Function *fun)
{
    assert(fun != nullptr);
    if (findDeclFun(fun->getName()) == nullptr)
    { // 未找到
        funList.push_back(fun);
        DeclFuns.emplace(fun->getName(), fun);
        return fun;
    }
    else // 已经存在
        return nullptr;
}
