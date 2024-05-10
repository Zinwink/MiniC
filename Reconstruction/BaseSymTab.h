/**
 * @file BaseSymtab.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 符号表管理 在编译器设计中 认为包含 3类符号表 全局作用域表(全局变量,函数符号表域)  函数符号表(函数符号表中可能包含定义的块) 块符号表
 * @version 1.0
 * @date 2024-04-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "DerivedInst.h"
#include "Value.h"

using string = std::string;
class BaseSymTab;
using BaseSymTabPtr = std::shared_ptr<BaseSymTab>;

/// @brief 符号表属性 方便进行指针的类型转换
enum class TabAttr
{
    /// @brief 全局作用表
    GLOBAL_TAB,

    /// @brief 函数全局表
    FUNC_TAB,

    /// @brief 函数块整体作用域的临时block表, 函数中可能存在多个block以及block嵌套
    BLOCKTEMP_TAB
};

/// @brief 符号表基类
class BaseSymTab
{
protected:
    /// @brief 本表中已经声明注册的变量（设计中Value是个基类）
    std::unordered_map<string, ValPtr> DeclVars;
    /// @brief 符号表的类型
    TabAttr type;
    /// @brief 可用于获取相关符号信息的父符号表
    BaseSymTabPtr parent = nullptr;

public:
    /// @brief 析构函数
    ~BaseSymTab();

    /// @brief 判断符号表是否是全局符号表
    /// @return
    bool isGlobalTab()
    {
        if (type == TabAttr::GLOBAL_TAB)
            return true;
        return false;
    }

    /// @brief 获取符号表中的 注册变量声明表
    /// @return 查找表引用
    std::unordered_map<string, ValPtr> &getDeclVars() { return DeclVars; }

    /// @brief 纯虚函数 查找声明变脸的引用
    /// @param 查找变量名
    /// @return
    virtual ValPtr findDeclVar(string &name) = 0;

    /// @brief 纯虚函数 新增声明变量
    /// @param  变量指针
    /// @return nullptr表示插入失败，说明已经存在
    virtual ValPtr newDeclVar(ValPtr) = 0;

    /// @brief 设置父作用表
    /// @param ptr
    virtual void setParent(BaseSymTabPtr ptr) { parent = ptr; }

    /// @brief 获取父作用表
    /// @return BaseSymTab*
    virtual BaseSymTabPtr getParent() { return parent; }

    /// @brief 符号表 类型
    /// @return
    virtual TabAttr &getTabAttr() { return type; }

    /// @brief 从当前符号表中查找变量(搜搜域只限于当前符号表)
    /// @return 变量指针 未找到为nullptr
    virtual ValPtr findDeclVarOfCurTab(string &name);
};
