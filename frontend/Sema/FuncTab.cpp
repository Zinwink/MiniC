/**
 * @file FuncTab.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "FuncTab.h"
#include <cassert>

/// @brief 析构函数
FuncTab::~FuncTab()
{
    // 当前域声明变量 清空 因为varList包涵DeclVars内容 防止反复释放
    DeclVars.clear();
    // 下面释放 varList
    for (auto val : varList)
    {
        delete val;
        val = nullptr;
    }
    varList.clear();
    DeclVars.clear();
}

/// @brief 纯虚函数 查找声明变脸的引用(包含当前以及所有父作用域)
/// @param 查找变量名
/// @return
Var *FuncTab::findDeclVar(string &name)
{
    BaseSymTab *cur = this;
    while (cur != nullptr)
    {
        Var *val = cur->findDeclVarOfCurTab(name);
        if (val == nullptr) // cur未找到,迭代下一符号表
            cur = cur->getParent();
        else // 找到
            return val;
    }
    // 循环结束 未找到
    return nullptr;
}

/// @brief 纯虚函数 新增声明变量
/// @param  变量指针
/// @return nullptr表示插入失败，说明已经存在
Var *FuncTab::newDeclVar(Var *var)
{
    assert(var != nullptr); // 保证参数不为nullpr
    if (findDeclVarOfCurTab(var->getVarName()) == nullptr)
    {
        // 未找到
        DeclVars.emplace(var->getVarName(), var); // 声明哈希查找表需要插入
        varList.push_back(var);                   // 使用到的变量列表也要插入
        return var;
    }
    else
        return nullptr; // 找到 插入失败
}
