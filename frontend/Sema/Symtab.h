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

/// @brief 符号表管理类
class SymTab
{
private:
    /// @brief 变量名  变量指针 散列表
    std::unordered_map<std::string, Var *> varMap;

    /// @brief 函数名 函数指针散列表
    std::unordered_map<std::string, Function *> FuncMap;

public:
    /// @brief 无参构造
    SymTab(){};
    /// @brief 析构函数
    ~SymTab(){};

public:
    /// @brief 获取变量名 变量散列表
    /// @return
    std::unordered_map<std::string, Var *> &getVarMap()
    {
        return varMap;
    }

    /// @brief 获取函数名 函数 散列表
    /// @return
    std::unordered_map<std::string, Function *> &getFuncMap()
    {
        return FuncMap;
    }

    /// @brief 根据变量名查找变量
    /// @param varName 变量名
    /// @return 变量指针
    Var *findVar(std::string &varName);

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

    /// @brief 添加 float字面量常量
    /// @param float_digit
    /// @return 常量指针
    Var *AddConstVar(float float_digit);

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