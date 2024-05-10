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
    DeclVars.clear();
}

/// @brief 纯虚函数 查找声明变脸的引用(包含当前以及所有父作用域)
/// @param 查找变量名
/// @return
ValPtr FuncTab::findDeclVar(string &name)
{
    BaseSymTab *cur = this;
    while (cur != nullptr)
    {
        ValPtr val = cur->findDeclVarOfCurTab(name);
        if (val == nullptr) // cur未找到,迭代下一符号表
            cur = cur->getParent().get();
        else // 找到
            return val;
    }
    cur = nullptr;
    // 循环结束 未找到
    return nullptr;
}

/// @brief 纯虚函数 新增声明变量
/// @param  变量指针
/// @return nullptr表示插入失败，说明已经存在
ValPtr FuncTab::newDeclVar(ValPtr var)
{
    assert(var != nullptr); // 保证参数不为nullpr
    string name = var->getName();
    if (findDeclVarOfCurTab(name) == nullptr)
    {
        // 未找到
        DeclVars.emplace(name, var); // 声明哈希查找表需要插入
        return var;
    }
    else
        return nullptr; // 找到 插入失败
}

/// @brief 创建基本表
/// @param _parent
/// @return
BaseSymTabPtr FuncTab::get(BaseSymTabPtr _parent)
{
    BaseSymTabPtr tab = std::make_shared<FuncTab>(_parent);
    return tab;
}