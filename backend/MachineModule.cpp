/**
 * @file MachineModule.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineModule.h"

/// @brief 手动清理
void MachineModule::clear()
{
    for (auto &Mfun : funcList)
    {
        Mfun->clear();
    }
    funcList.clear();
    funcList.shrink_to_fit();
    globalVaris.clear();
    globalVaris.shrink_to_fit();
}

/// @brief  析构函数
MachineModule::~MachineModule()
{
    clear();
}