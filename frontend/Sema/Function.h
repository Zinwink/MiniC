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
#include "FuncTab.h"
#include "IRBlock.h"

/// @brief 函数形参类
class FunFormalParam : public Var // 形参是一类特殊的变量
{
private:
    // std::string name;    // 参数名
    // ValueType type;      // 形参类型
    // int32_t llvmid = -1; // 函数形参分配的编号
    Var *_value; // 形参对应的变量(可以认为是函数中传参时的拷贝)

public:
    /// @brief 析构函数
    ~FunFormalParam() {}
    /// @brief 构造函数
    FunFormalParam()
    {
        val_type = BasicValueType::TYPE_MAX;
    }

    /// @brief 根据字符串名构造函数形参
    /// @param _name
    FunFormalParam(std::string &_name, const ValueType &_type = BasicValueType::TYPE_MAX)
    {
        varName = _name;
        val_type = _type;
        _value = new Var(_name, _type); // 构造对应的形参拷贝变量
    }

public:
    /// @brief 返回对应的拷贝变量
    /// @return
    Var *Value() { return _value; };

    /// @brief 获取对应的IR字符串表示
    /// @param cnt 使用的计数器指针
    /// @return
    string toString(Counter *cnt);
};

class Function
{
private:
    FuncTab *funTab;   // 本函数的全局符号表
    Counter *cnter;    // 计数器对象，供本函数翻译llvmir 分配相关编号时使用
    IRBlock *IRCodes;  // 本函数的IR块(block中的iR指令)
    std::string name;  // 函数名
    ValueType retType; // 函数返回类型

    IRInst *entryLabel = nullptr; // 函数入口Label,nullptr表示还未指定
    IRInst *exitLabel = nullptr;  // 函数出口Label,nullptr表示还未指定

    std::vector<FunFormalParam *> FormalParamList; // 形参列表
public:
    /// @brief 符号表
    // SymTab *sym;
    /// @brief 无参构造函数
    Function();

    /// @brief 根据名字以及返回类型进行构造
    /// @param _name
    /// @param retTy
    Function(std::string &_name, const ValueType &retTy = BasicValueType::TYPE_VOID);

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

    /// @brief 获取本函数符号表的计数器
    /// @return 获取本函数符号表计数器
    Counter *counter() { return cnter; }

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

    /// @brief 获取本函数的IR指令块
    /// @return
    IRBlock *getIRBlock() { return IRCodes; }

    /// @brief 获取本函数的符号表
    /// @return
    FuncTab *getFuncTab() { return funTab; }

    /// @brief 获取函数入口标签(引用)
    /// @return
    IRInst *&EntryLabel() { return entryLabel; }

    /// @brief 获取函数出口标签(指针引用)
    /// @return
    IRInst *&ExitLabel() { return exitLabel; }

    /// @brief 将函数转化为IR string表示
    /// @param str 用于存储字符串
    /// @return 字符串
    string &toString(string &str);
};