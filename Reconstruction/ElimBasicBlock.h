/**
 * @file ElimBasicBlock.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  对基本块的处理 (删除无用基本块，合并基本块)
 * @version 1.0
 * @date 2024-05-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Module.h"

/// @brief 基本块可达性分析
/// @param blcok
void ReachableAnalysis(BasicBlockPtr blcok);

/// @brief 合并基本块
/// @param block 当前基本块
/// @param it 当前基本块的迭代器
/// @return 若可合并，当前基本块删除后 返回迭代器
bblockIter &mergeBasicBlocks(BasicBlockPtr block, bblockIter &it);

/// @brief 消除函数中无用基本块
/// @param fun 处理函数中的基本块
void ElimUseLessBBlock(FuncPtr fun);

/// @brief 处理Module
/// @param _modul Module 包含 functionList
void ElimUseLessBBlock(ModulePtr _modul);
