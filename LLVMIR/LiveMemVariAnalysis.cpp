/**
 * @file LiveMemVariAnalysis.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 对 内存变量(地址) alloca,getelemptr, globalVarible 等内存地址标识的变量进行活跃分析 (由于时间有限暂不做SSA)
 * @version 1.0
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "LiveMemVariAnalysis.h"
#include "BasicBlockPass.h"

/// @brief 计算 基本块的 def use
/// @param fun
void LiveMemVariAnalysis::computeDefUse(FuncPtr fun)
{
    def.clear();
    use.clear();
    auto &blockList = fun->getBasicBlocks();
    for (auto &blk : blockList)
    {
        // 下面分析 def use
        auto &instList = blk->getInstLists();
        for (auto &inst : instList)
        {
            if (inst->isStoreInst())
            {
                auto memAddr = inst->getOperand(1);
                def[blk].insert(memAddr);
            }
            if (inst->isLoadInst())
            {
                auto memAddr = inst->getOperand(0);
                use[blk].insert(memAddr);
            }
        }
    }
}