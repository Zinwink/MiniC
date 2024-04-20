/**
 * @file IRCode.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "IRBlock.h"

/// @brief 析构函数
IRBlock::~IRBlock()
{
    // 暂时不实现
}


/// @brief 向IRBack添加一个指令块 用于遍历AST向上合并时使用，并释放原指令块
/// @param block  指令块
void IRBlock::extendIRBack(IRBlock &block)
{
    // 先将原block加入
    for (auto inst : block.IRBack)
    {
        IRBack.push_back(inst);
    }
    // 清空原block, 只清空指针不删除对象
    block.IRBack.clear();
    block.IRFront.clear();
}