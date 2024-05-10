/**
 * @file Module.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief Module类  用于存放 全局变量列表  函数定义列表等
 * @version 1.0
 * @date 2024-05-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "GlobalVariable.h"
#include "Function.h"
#include <deque>

class Module;
using ModulePtr = std::shared_ptr<Module>;

class Module
{
private:
    /// @brief 全局变量表
    std::deque<GlobalVariPtr> globalVarList;

    /// @brief 函数列表
    std::deque<FuncPtr> funcList;

public:
    /// @brief 构造函数
    Module() {}
    /// @brief 析构函数
    ~Module();

    /// @brief 获取全局变量列表
    /// @return
    std::deque<GlobalVariPtr> &getGlobalVars() { return globalVarList; }

    /// @brief 获取函数列表
    /// @return
    std::deque<FuncPtr> &getFunList() { return funcList; }

    /// @brief 添加全局变量
    void addGlobalVar(GlobalVariPtr var) { globalVarList.push_back(var); };

    /// @brief 添加函数
    /// @param fun
    void addFunction(FuncPtr fun) { funcList.push_back(fun); }
};
