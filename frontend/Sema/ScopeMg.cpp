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
    // 转型得到管理器的全局符号表
    curGlobalTab = dynamic_cast<GlobalSymTab *>(globalTab);
}

/// @brief 析构函数
ScopeMg::~ScopeMg()
{
    // 暂时未完成  @todo
}

/// @brief 获取当前管理栈的全局符号表
/// @return 全局符号表指针(使用基类指针转型得到)
GlobalSymTab *ScopeMg::globalTab()
{
    return curGlobalTab;
}