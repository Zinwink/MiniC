/**
 * @file Symtab.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 符号表管理
 * @version 1.0
 * @date 2024-04-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <unordered_map>
#include "Var.h"

/// @brief 符号表管理类
class SymTab
{
public:
    /// @brief 变量名  变量指针
    std::unordered_map<std::string, Var *> varMap;

    
};