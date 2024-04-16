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
#include "Function.h"

/// @brief 符号表管理基类
class SymTab
{
private:
    /// @brief 变量名  变量指针 散列表  用于查找已经声明的变量 语义分析
    std::unordered_map<std::string, Var *> varMap;
    /// @brief 查找函数，用于调用时查找进行检查
    std::unordered_map<std::string, Function *> funMap;

public:
    /// @brief 变量列表 对于全局符号表以及函数的整体符号表有用
    std::vector<Var *> VarList;
    /// @brief 函数列表 对于全局符号表有用
    std::vector<Function *> FunList;

    /// @brief 无参构造
    SymTab(){};
    /// @brief 父 符号表
    SymTab *parent;

public:
    /// @brief 获取变量名 变量散列表
    /// @return
    std::unordered_map<std::string, Var *> &getVarMap()
    {
        return varMap;
    }

    /// @brief 根据变量名查找变量
    /// @param varName 变量名
    /// @return 变量指针
    virtual Var *findVar(std::string &varName);

    /// @brief 添加变量
    /// @param var 变量指针
    ///  @return 插入是否成功
    bool AddVar(Var *var);

    /// @brief 根据变量名，变量值类型进行构造 用户自定义变量
    /// @param name
    /// @param _type
    /// @return 变量指针
    Var *AddVar(std::string &name, const ValueType &_type);

    /// @brief 添加 整型字面常量
    /// @param int32_digit
    /// @return 常量指针
    Var *AddConstVar(int32_t int32_digit);

    /// @brief 根据函数名查找函数
    /// @param funName 函数名
    /// @return 函数指针
    Function *findFunction(std::string &funName);

    /// @brief 根据 函数名 函数返回值类型 加入函数
    /// @param funName 函数名
    /// @param retType 返回类型
    /// @return 函数指针
    Function *AddFun(std::string &funName, const ValueType &retType = BasicValueType::TYPE_VOID);
};