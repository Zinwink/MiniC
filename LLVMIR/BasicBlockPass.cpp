/**
 * @file BasicBlockPass.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 对基本块的局部优化 以及获取基本块相关的数据流信息
 * @version 1.0
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "BasicBlockPass.h"
#include "DerivedInst.h"
#include "DeadInstElim.h"
#include <unordered_map>

/// @brief 对基本块进行简单的 局部优化(消减局部不必要的load store)
/// @param blk
void BBlockPass::BasicEasyPass(BasicBlockPtr blk)
{
    auto &instList = blk->getInstLists(); // 获取指令列表

    // 遍历 blk 消减 不必要的 load store
    // 对于 全局变量内存地址 以及数组的内存地址 如果 遇到函数调用 默认认为受到影响
    // 将打断当前 建立的 局部简单 def-use chain
    // 对于 对同一内存地址的多个load 且又没有def 打断 完全可以重用第一个load
    // 对于基本块局部出现的 多次 store， 后面的会覆盖前面的，前面的 store在后继程序中不可达; 前面的 store可以传播消除

    std::unordered_map<ValPtr, InstPtr> memLoad;  // 内存取值
    std::unordered_map<ValPtr, InstPtr> memStore; // 内存存值

    for (auto iter = instList.begin(); iter != instList.end();)
    {
        InstPtr &inst = *iter;
        inst->AutoTransmitWhenIsConst();
        if (inst->isLoadInst())
        {
            // 是Load指令 先查找 memStore中有没有 相关定值记录 如果有则存入
            ValPtr memAddr = inst->getOperand(0); // 获取内存地址
            auto strIter = memStore.find(memAddr);
            if (strIter != memStore.end())
            {
                // 能找到  则将该Load 的User对应的操作数直接替换成Store的值
                ValPtr strVal = strIter->second->getOperand(0);
                inst->replaceAllUsesWith(inst, strVal); // 将使用到load的User 相应操作数直接替换成定值
                iter = eraseInst(blk, iter);            // 删除该无用Load指令
            }
            else
            {
                // load 前没有store  则查找 memLoad表 看有没有重复Load
                auto LoadIter = memLoad.find(memAddr);
                if (LoadIter != memLoad.end())
                {
                    // 查找到了 有可复用的load指令
                    ValPtr loadVal = LoadIter->second;
                    inst->replaceAllUsesWith(inst, loadVal); // 复用替换为新的
                    // 该Load 指令已经无用 可以删除
                    iter = eraseInst(blk, iter);
                }
                else
                {
                    // 没有找到 则先插入 到 memLoad中
                    memLoad.emplace(memAddr, inst);
                    iter++;
                }
            }
            continue; // 下一次循环
        }
        if (inst->isStoreInst())
        {
            // 遇到 StoreInst  先清理  memLoad中对该地址的之前Load
            ValPtr memAddr = inst->getOperand(1); // 获取内存地址
            if (memLoad.find(memAddr) != memLoad.end())
            {
                // 找到了之前的 load 直接删除记录
                memLoad.erase(memAddr);
            }
            // 查找 memStore表 看看又没有Store 有的话 替换 store没有的话插入
            auto strIter = memStore.find(memAddr);
            if (strIter != memStore.end())
            {
                // 找到了 重复的 def 之前的 def 被杀死 设置为 dead
                strIter->second->setDeadSign();
                strIter->second = inst; // 替换为新的 store
            }
            else
            {
                // 没找到 直接插入
                memStore.emplace(memAddr, inst);
            }
            iter++;
            continue;
        }
        if (inst->isCallInst())
        {
            // 如果 是call Inst 则将现有的 memLoad memStore中对于全局变量以及数组指针内存的操作清除
            for (auto &ldr : memLoad)
            {
                if (ldr.first->isGlobalVariable())
                {
                    memLoad.erase(ldr.first);
                }
                if (ldr.first->isGetelemPtrInst())
                {
                    memLoad.erase(ldr.first);
                }
            }
            for (auto &str : memStore)
            {
                if (str.first->isGlobalVariable())
                {
                    memStore.erase(str.first);
                }
                if (str.first->isGetelemPtrInst())
                {
                    memStore.erase(str.first);
                }
            }
        }
        iter++;
    }
}

/// @brief 进行简单的局部 优化 简单删除Load Store
/// @param module
void EasyPass(ModulePtr module)
{
    auto &funList = module->getFunList();
    for (auto &fun : funList)
    {
        auto &blkList = fun->getBasicBlocks();
        for (auto &blk : blkList)
        {
            BBlockPass::BasicEasyPass(blk);
        }
    }
}