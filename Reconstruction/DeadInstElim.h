/**
 * @file DeadInstElim.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 死指令消除  提供删除指令函数
 * @version 1.0
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "BasicBlock.h"
#include "Module.h"

/// @brief 删除死指令
/// @param block 基本块
/// @param iter 指令对应的迭代器
/// @return
BasicBlock::InstIterator eraseDeadInst(BasicBlockPtr block, BasicBlock::InstIterator &iter);

/// @brief 删除DeadInst
/// @param inst
void eraseDeadInst(InstPtr inst);

/// @brief 不管指令是否是死指令 直接删除一条指令
/// @param block
/// @param iter
BasicBlock::InstIterator eraseInst(BasicBlockPtr block, BasicBlock::InstIterator &iter);

/// @brief 删除module中的死指令
/// @param module
void eraseModuleDeadInst(ModulePtr module);
