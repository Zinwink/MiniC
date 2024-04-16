/**
 * @file Function.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "ValueType.h"
#include <vector>
#include "Symtab.h"

/// @brief 函数形参类
class FunFormalParam
{
private:
    std::string name; // 参数名
    ValueType type;   // 形参类型
public:
    /// @brief 析构函数
    ~FunFormalParam() {}
    /// @brief 构造函数
    FunFormalParam() : type(BasicValueType::TYPE_MAX) {}

    /// @brief 根据字符串名构造函数形参
    /// @param _name
    FunFormalParam(std::string &_name, const ValueType &_type = BasicValueType::TYPE_MAX)
    {
        name = _name;
        type = _type;
    }

public:
    /// @brief 获取形参名字
    /// @return 形参名
    std::string &getName()
    {
        return name;
    }

    /// @brief 获取形参类型
    /// @return 形参类型
    ValueType &getValType()
    {
        return type;
    }
};

class Function
{
private:
    std::string name;                              // 函数名
    ValueType retType;                             // 函数返回类型
    std::vector<FunFormalParam *> FormalParamList; // 形参列表
public:
    /// @brief 符号表
    SymTab *sym;

    /// @brief 无参构造函数
    Function() : retType(BasicValueType::TYPE_MAX){};

    /// @brief 根据名字以及返回类型进行构造
    /// @param _name
    /// @param retTy
    Function(std::string &_name, const ValueType &retTy = BasicValueType::TYPE_VOID)
    {
        name = _name;
        retType = retTy;
    }

    /// @brief 析构函数
    ~Function();

public:
    /// @brief 获取函数名
    /// @return
    std::string &getName()
    {
        return name;
    }

    /// @brief 获取函数返回值类型
    /// @return
    ValueType &getRetType()
    {
        return retType;
    }

    /// @brief 获取函数形参列表
    /// @return
    std::vector<FunFormalParam *> &getFormalParams()
    {
        return FormalParamList;
    }

    /// @brief 向参数列表添加参数
    /// @param formalParam
    /// @return 本对象
    Function &addFormalParam(FunFormalParam *formalParam)
    {
        FormalParamList.push_back(formalParam);
        return *this;
    }
};