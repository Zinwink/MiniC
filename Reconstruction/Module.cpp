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
        std::cout << "销毁" << std::endl;
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
        for (auto &gloabV : globalVarList)
        {
            // 目前只有int 只获取int
            string initiStr;
            ConstantPtr initi = gloabV->getInitilizer();
            if (initi == nullptr)
            {
                initiStr = (gloabV->getType()->isArrayType() ? string("zeroinitializer") : string("0"));
            }
            else
            {
                // 如果是 int类型
                ConstantIntPtr conInt = std::static_pointer_cast<ConstantInt>(gloabV->getInitilizer());
                initiStr = std::to_string(conInt->getValue());
            }

            string str = string("@") + gloabV->getName() + string(" = global ") + gloabV->getElemTy()->TypeStr() + string(" ") + initiStr;
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
    assert(!val->hasName() && "val has name!");
    auto iter = countMap.find(val);
    int64_t ord;
    if (iter != countMap.end()) // 找到该变量
    {
        ord = iter->second;
    }
    else
    { // 没到该编号
        ord = ValCount;
        ValCount++;
    }
    return ord;
}