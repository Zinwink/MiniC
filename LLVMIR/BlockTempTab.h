/**
 * @file BlockTempTab.h
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
#include "FuncTab.h"

/// @brief 函数全局域中出现的block表，block代码块可以嵌套或者并列
class BlockTempTab : public BaseSymTab
{
public:
    /// @brief 构造函数
    BlockTempTab(BaseSymTabPtr _parent = nullptr)
    {
        type = TabAttr::BLOCKTEMP_TAB;
        parent = _parent;
    }

    /// @brief 析构函数
    ~BlockTempTab();

    /// @brief 查找声明变量引用 (只用于确定使用的变量来源，搜索域为当前符号表以及所有上层父符号表)
    /// @param 查找变量名
    /// @return 声明变量指针
    ValPtr findDeclVar(string &name) override;

    /// @brief 为当前表新增声明变量
    /// @param  变量
    /// @return 变量
    ValPtr newDeclVar(ValPtr var) override;

    /// @brief 创建BlockTempTab表
    /// @param _parent
    /// @return
    static BaseSymTabPtr get(BaseSymTabPtr _parent = nullptr);
};