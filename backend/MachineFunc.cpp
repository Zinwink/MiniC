/**
 * @file MachineFunc.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineFunc.h"

/// @brief 构造函数
/// @param p 属于的module
/// @param _funcNo 函数编号
MachineFunc::MachineFunc(MModulePtr p)
{
    parent = p;
}

/// @brief 创建智能指针类型
/// @param p
/// @return
MFuncPtr MachineFunc::get(MModulePtr p)
{
    MFuncPtr fun = std::make_shared<MachineFunc>(p);
    return fun;
}

/// @brief 手动打破环 使智能指针自动释放
void MachineFunc::clear()
{
    parent.reset();
    for (auto &b : blockList)
    {
        b->clear();
    }
    blockList.clear();
}

/// @brief 析构函数
MachineFunc::~MachineFunc()
{
    MachineFunc::clear();
}