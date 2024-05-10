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
}