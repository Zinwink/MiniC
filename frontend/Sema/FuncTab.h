/**
 * @file FuncTab.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "BaseSymTab.h"

/// @brief 函数整体符号表
class FuncTab : public BaseSymTab
{
private:
    /// @brief 全域声明的变量列表(包括其下的Block中声明的变量),生成IR时使用，用于事先分配内存(alloca)
    std::vector<Var *> varList;

public:
    /// @brief 构造函数
    /// @param _parent
    FuncTab(BaseSymTab *_parent = nullptr)
    {
        type = TabAttr::FUNC_TAB;
        parent = _parent;
    }

    /// @brief 析构函数
    ~FuncTab() override;

    /// @brief 纯虚函数 查找声明变脸的引用 (包含当前以及所有父作用域)
    /// @param 查找变量名
    /// @return
    Var *findDeclVar(string &name) override;

    /// @brief 纯虚函数 新增声明变量
    /// @param  变量指针
    /// @return nullptr表示插入失败，说明已经存在
    Var *newDeclVar(Var *var) override;

    /// @brief 获取变量列表
    /// @return 变量列表引用
    std::vector<Var *> &getVarList() { return varList; }
};