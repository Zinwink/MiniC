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

/// @brief 构造函数
ScopeMg::ScopeMg()
{
    // 创建全局符号表 加入栈中
    BaseSymTab *globalTab = new GlobalSymTab();
    stk.push(globalTab);
}

/// @brief 析构函数
ScopeMg::~ScopeMg()
{
    // 暂时未完成  @todo
}