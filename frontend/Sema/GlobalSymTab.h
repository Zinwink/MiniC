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

class GlobalSymTab : public BaseSymTab
{
private:
    // 一些相对于基类新增的属性
    /// @brief 全局变量列表，用于存放全局变量
    std::vector<Var *> varList;

    /// @brief 函数列表 FUnction* 含有 FuncTab,以此为入口访问产生函数IR
    std::vector<Function *> funList;

    /// @brief 已经声明的函数 查找哈希表 用于函数调用时的查找
    std::unordered_map<string, Function *> DeclFuns;

public:
    /// @brief 构造函数
    GlobalSymTab() { type = TabAttr::GLOBAL_TAB; }

    /// @brief 析构函数
    ~GlobalSymTab() override;

    /// @brief 查找声明的全局变脸
    /// @param name 全局变量名
    /// @return 变量指针
    Var *findDeclVar(string &name) override;

    /// @brief 新增声明变量(DeclVar和varList均进行加入操作)
    /// @param  变量指针
    /// @return nullptr表示插入失败，说明已经存在
    Var *newDeclVar(Var *var) override;

    /// @brief 获取全局变量列表
    /// @return 全局变量列表引用
    std::vector<Var *> &getVarList() { return varList; }

    /// @brief 获取函数列表
    /// @return 函数列表引用
    std::vector<Function *> &getFunList() { return funList; }

    /// @brief 获取函数名-函数 查找哈希表
    /// @return 哈希表引用
    std::unordered_map<string, Function *> &getDeclFuns() { return DeclFuns; }

    /// @brief 根据函数名查找声明的函数
    /// @param funname
    /// @return nullptr表示未找到
    Function *findDeclFun(string &funname);

    /// @brief 新增声明定义的函数 (DeclFuns,funList均进行加入)
    /// @param fun 函数
    /// @return nullptr表示已经存在，新增失败；否曾新增成功
    Function *newDeclFun(Function *fun);
};