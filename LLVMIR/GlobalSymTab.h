/**
 * @file GlobalSymTab.h
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
#include "Function.h"
#include "GlobalVariable.h"
#include <deque>

class GlobalSymTab : public BaseSymTab
{
public:
    /// @brief 构造函数
    GlobalSymTab()
    {
        type = TabAttr::GLOBAL_TAB;
    }

    /// @brief 析构函数
    ~GlobalSymTab();

    /// @brief 查找声明的全局变脸
    /// @param name 全局变量名
    /// @return 变量指针
    ValPtr findDeclVar(string &name) override;

    /// @brief 新增声明变量(DeclVar和varList均进行加入操作)
    /// @param  变量指针
    /// @return nullptr表示插入失败，说明已经存在
    ValPtr newDeclVar(ValPtr var) override;

    /// @brief 创建全局符号表
    /// @return
    static BaseSymTabPtr get();
};