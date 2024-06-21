/**
 * @file PhiElim.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief phi指令消除
 * @version 1.0
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Function.h"
#include "Module.h"
#include "DerivedInst.h"
#include "BasicBlock.h"

/// @brief 删除phi节点
/// @param fun
void PhiElim(FuncPtr fun);

/// @brief 删除phi节点
/// @param module
void PhiElim(ModulePtr module);