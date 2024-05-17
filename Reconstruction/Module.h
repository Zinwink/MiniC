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
class Counter;
using ModulePtr = std::shared_ptr<Module>;

class Module
{
private:
    /// @brief 全局变量表
    std::deque<GlobalVariPtr> globalVarList;

    /// @brief 函数列表 本文件中定义的函数
    std::deque<FuncPtr> funcList;

    /// @brief 本文件中使用的外部函数 不在本文件中定义
    std::deque<FuncPtr> funcDeclareExtern;

    Counter *cnt = nullptr;

public:
    /// @brief 构造函数
    Module();
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

    /// @brief 添加非本文件定义的函数
    /// @param fun
    void addExternFunction(FuncPtr fun) { funcDeclareExtern.push_back(fun); }

    /// @brief 将IR指令打印至文件中
    /// @param filePath
    void printIR(string filePath);

    /// @brief 获取Module
    /// @return
    static ModulePtr get();
};

/// @brief 获取delcare 声明外部函数的文本表示
/// @param fun
/// @return
string DeclareFunStr(FuncPtr fun);

/// @brief 翻译为文本时所需使用的计数器
class Counter
{
private:
    int64_t ValCount = 0; // Value编号 不对BasicBlock编号 BasicBlock是Label
    int64_t LabelCount = 0;
    std::unordered_map<ValPtr, int64_t> countMap; // 用于查找已有的编号
public:
    /// @brief 析构函数
    ~Counter()
    {
        countMap.clear();
    }

    /// @brief 构造函数
    Counter() {}

    /// @brief 获取Val的编号 val 一定是需要编号的变量 对于常量无需编号不行
    /// @param val
    /// @return
    int64_t getCount(ValPtr val);

    /// @brief 重置
    void reset()
    {
        ValCount = 0;
        countMap.clear();
    }
};
