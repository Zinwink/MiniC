/**
 * @file Module.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Module.h"
#include "Instruction.h"
#include "BasicBlock.h"
#include "GlobalVariable.h"
#include <cassert>
#include <fstream>
#include <iostream>

/// @brief 构造函数
Module::Module()
{
    cnt = new Counter();
}

/// @brief 析构函数
Module::~Module()
{
    /// 循环进行clear的目的是打破存在的环，释放彻底
    for (auto &g : globalVarList)
    {
        g->clear();
    }
    globalVarList.clear();
    for (auto &f : funcList)
    {
        f->clear();
    }
    funcList.clear();
    delete cnt;
    cnt = nullptr;
}

/// @brief 获取Module
/// @return
ModulePtr Module::get()
{
    ModulePtr mod = std::make_shared<Module>();
    return mod;
}

/// @brief 将IR指令打印至文件中
/// @param filePath
void Module::printIR(string filePath)
{
    std::ofstream file(filePath);
    if (file.is_open())
    {
        // 全局变量翻译
        for (auto &gloabV : globalVarList)
        {
            string str = GlobalVariable::toIRstr(gloabV, nullptr);
            file << str;
            file << "\n";
        }
        // 翻译函数块
        for (auto &fun : funcList)
        {
            string str = Function::toIRstr(fun, cnt);
            cnt->reset();  //翻译玩一个函数后重置
            file << str;
            file << "\n";
        }
    }
    else
    {
        // 文件打开失败
        std::cerr << "output IR instruction to" << filePath << " failed!" << std::endl;
    }
}

/// @brief 获取Val的编号 val 一定是需要编号的变量 对于常量无需编号不行
/// @param val
/// @return
int64_t Counter::getCount(ValPtr val)
{
    auto iter = countMap.find(val);
    int64_t ord;
    if (iter != countMap.end()) // 找到该变量
    {
        ord = iter->second;
    }
    else
    { // 没到该编号
        ord = ValCount;
        countMap.emplace(val, ord); // 插入该记录
        ValCount++;
    }
    return ord;
}