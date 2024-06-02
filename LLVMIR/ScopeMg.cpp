/**
 * @file ScopeMg.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 符号表作用域管理类
 * @version 1.0
 * @date 2024-04-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ScopeMg.h"
#include "StdFunc.h"
#include "Function.h"

/// @brief 构造函数
ScopeMg::ScopeMg()
{
    // 创建全局符号表 加入栈中
    BaseSymTabPtr globalTab = GlobalSymTab::get();
    stk.push(globalTab);

    // 加入 对 std.h std.c中提供函数的支持
    std::vector<FuncPtr> stdFuns;
    initStdFunc(stdFuns);
    for (auto &fun : stdFuns)
    {
        // 加入全局变量表中
        globalTab->newDeclVar(fun);
    }

    // 转型得到管理器的全局符号表
    curGlobalTab = globalTab;
}

/// @brief 析构函数
ScopeMg::~ScopeMg()
{
    curGlobalTab.reset();
    while (!stk.empty())
    {
        stk.pop();
    }
}

/// @brief 获取当前管理栈的全局符号表
/// @return 全局符号表指针(使用基类指针转型得到)
BaseSymTabPtr &ScopeMg::globalTab()
{
    return curGlobalTab;
}
