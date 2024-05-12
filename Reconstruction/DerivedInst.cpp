/**
 * @file DerivedInst.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "DerivedInst.h"

/// @brief 静态函数  获取指令对象指针
/// @param name
/// @param _allocatedTy
/// @return
AllocaInstPtr AllocaInst::get(string name, Type *_allocatedTy)
{
    AllocaInstPtr alloca = std::make_shared<AllocaInst>(_allocatedTy);
    alloca->setName(name); // 设置名字
    return alloca;
}
