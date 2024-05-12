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
public:
    /// @brief 构造函数
    /// @param _parent
    FuncTab(BaseSymTabPtr _parent = nullptr)
    {
        type = TabAttr::FUNC_TAB;
        parent = _parent;
    }

    /// @brief 析构函数
    ~FuncTab();

    /// @brief 纯虚函数 查找声明变脸的引用 (包含当前以及所有父作用域)
    /// @param 查找变量名
    /// @return
    ValPtr findDeclVar(string &name) override;

    /// @brief 纯虚函数 新增声明变量
    /// @param  变量指针
    /// @return nullptr表示插入失败，说明已经存在
    ValPtr newDeclVar(ValPtr var) override;

    /// @brief 创建基本表
    /// @param _parent
    /// @return
    static BaseSymTabPtr get(BaseSymTabPtr _parent = nullptr);

};