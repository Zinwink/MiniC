/**
 * @file Symtab.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 符号表管理
 * @version 1.0
 * @date 2024-04-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Symtab.h"
#include "Var.h"

/// @brief 根据变量名查找变量 查找声明的变量
/// @param varName 变量名
/// @return 变量指针 未找到则nullptr
Var *SymTab::FindDeclVar(std::string &varName)
{
    SymTab *tab = this;
    while (tab != nullptr)
    {
        auto iter = tab->DeclvarMap.find(varName);
        if (iter == tab->DeclvarMap.end())
        {
            // 未找到 继续
            tab = tab->parent;
        }
        else
        {
            // 找到
            return iter->second;
        }
    }
    return nullptr;
}

/// @brief 添加变量(声明 添加到散列表)
/// @param var
/// @return 添加是否成功
bool SymTab::AddDeclVar(Var *var)
{
    if (DeclvarMap.find(var->getVarName()) == DeclvarMap.end()) // 未查找到该变量
    {
        // 使用 emplace插入，如果存在该变量名 则不会插入成功
        DeclvarMap.emplace(var->getVarName(), var);
        return true;
    }
    else
        return false;
}

/// @brief 根据变量名，变量值类型进行构造 用户自定义变量
/// @param name
/// @param _type
/// @return 变量指针  本作用域符号表中已经存在 返回nullptr 表明redifined错误
Var *SymTab::DeclAddVar(std::string &name, const ValueType &_type)
{
    if (DeclvarMap.find(name) == DeclvarMap.end())
    {
        // 未查找到该符号
        Var *var = new Var(name, _type);
        DeclvarMap.emplace(var->getVarName(), var);
        return var;
    } // 以及存在 则返回null
    else
        return nullptr;
}

/// @brief 添加 整型字面常量
/// @param int32_digit
/// @return 常量指针
// Var *SymTab::AddConstVar(int32_t int32_digit)
// {
//     std::string name = std::to_string(int32_digit);
//     Var *var = new Var(name, BasicValueType::TYPE_INT32, VarTag::CONST_VAR, VarLoc::IMIDIATE);
//     bool flag = AddVar(var);
//     if (flag)
//     {
//         return var;
//     }
//     else
//     {
//         delete var;
//         return nullptr;
//     }
// }

/// @brief 根据函数名查找函数
/// @param funName 函数名
/// @return 函数指针
Function *SymTab::findDeclFun(std::string &funName)
{
    auto funIter = DeclfunMap.find(funName);
    if (funIter == DeclfunMap.end())
    {
        // 未找到
        return nullptr;
    }
    else
    {
        return funIter->second;
    }
}

/// @brief 根据 函数名 函数返回值类型 加入函数
/// @param funName 函数名
/// @param retType 返回类型
/// @return 函数指针
Function *SymTab::AddDeclFun(std::string &funName, const ValueType &retType)
{
    if (findDeclFun(funName) == nullptr)
    { // 全局符号表中无法找到
        Function *fun = new Function(funName, retType);
        DeclfunMap.emplace(funName, fun);
        return fun;
    }
    else
    {
        return nullptr; // 表示添加失败,返回nullptr
    }
}