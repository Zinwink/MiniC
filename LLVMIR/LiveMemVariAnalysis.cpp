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
        // 下面分析 def use(只考虑局部变量 全局变量不考虑)
        auto &instList = blk->getInstLists();
        for (auto &inst : instList)
        {
            if (inst->isStoreInst())
            {
                auto memAddr = inst->getOperand(1);
                if (memAddr->isAllocaInst())
                {
                    // 定值前无引用
                    def[blk].insert(memAddr);
                }
            }
            else if (inst->isLoadInst())
            {
                auto memAddr = inst->getOperand(0);
                if (memAddr->isAllocaInst())
                { // 引用前不定值
                    auto iter = def[blk].find(memAddr);
                    if (iter == def[blk].end())
                    {
                        LoadInstPtr ldr = std::static_pointer_cast<LoadInst>(inst);
                        use[blk].insert(ldr);
                    }
                }
            }
        }
    }
}

/// @brief 计算 函数 基本块的Live In LiveOut
/// @param fun
void LiveMemVariAnalysis::computeInOut(FuncPtr fun)
{
    reset();            // 清空旧数据
    computeDefUse(fun); // 计算函数每个基本块的 def use
    std::list<BasicBlockPtr> &blockList = fun->getBasicBlocks();
    std::deque<BasicBlockPtr> workList; // 操作队列
    for (auto &blk : blockList)
    {
        workList.push_back(blk); // 加入队列中
    }
    while (!workList.empty())
    {
        BasicBlockPtr blk = workList.front();
        workList.pop_front();                                   // 弹出该块
        std::unordered_set<LoadInstPtr> oldIn = In[blk];        // 记录旧值
                                                                // 更新Out  所有后继In 的并集
        std::vector<BasicBlockPtr> succes = blk->getJumpList(); // 后继基本块
        for (auto &succ : succes)
        {
            Out[blk].insert(In[succ].begin(), In[succ].end());
        }
        // 更新 In(n)=Use(n) U ( Out(n)-def(n))  (def 在计算时已经去除)
        std::set_union(use[blk].begin(), use[blk].end(),
                       Out[blk].begin(), Out[blk].end(), std::inserter(In[blk], In[blk].end()));
        if (oldIn != In[blk])
        {
            for (auto &pred : blk->getImmedPreds())
            {
                workList.push_back(pred);
            }
        }
    }
}

/// @brief 根据 LiveIn LiveOut 进行传播优化
/// @param fun
void LiveMemVariAnalysis::Pass(FuncPtr fun)
{
    computeInOut(fun); // 计算本函数的 liveIn liveOut
    std::list<BasicBlockPtr> &blockList = fun->getBasicBlocks();
    // 下面根据 liveIn liveOut 得到对应的 def-uses 以及 use-defs
    // 最后 根据 def-uses 以及 use-defs来 进行 到达-定值分析； 如果一个use有 多个 def 到达 那么不确定不能传播
    // 如果 一个use 只有一个定值到达 可以替换传播
    // 根据 def-uses 进行判断删除 store(仅对局部变量alloca而言 全局变量不分析)

    for (auto &blk : blockList)
    {
        std::unordered_map<ValPtr, std::unordered_set<LoadInstPtr>> addrLoadLive; // 按地址分类的活跃 use(即Load的值)
        for (auto &elem : Out[blk])
        {
            ValPtr addr = elem->getOperand(0); // 获取地址
            addrLoadLive[addr].insert(elem);   // 插入地址对应的 load取值
        }
        // 逆序遍历基本块的指令
        std::list<InstPtr> &instList = blk->getInstLists();
        for (auto riter = instList.rbegin(); riter != instList.rend(); riter++)
        {
            auto &inst = *(riter);
            // 逆序遍历每一条指令
            if (inst->isLoadInst())
            {
                ValPtr memaddr = inst->getOperand(0);
                if (memaddr->isAllocaInst())
                {
                    LoadInstPtr ldr = std::static_pointer_cast<LoadInst>(inst);
                    addrLoadLive[memaddr].insert(ldr);
                }
            }
            else if (inst->isStoreInst())
            {
                ValPtr memaddr = inst->getOperand(1);
                if (memaddr->isAllocaInst())
                {
                    StoreInstPtr str = std::static_pointer_cast<StoreInst>(inst);
                    // def_use[str].insert(addrLoad[memaddr].begin(), addrLoad[memaddr].end());
                    def_use[str].insert(addrLoadLive[memaddr].begin(), addrLoadLive[memaddr].end());
                    for (auto &elem : addrLoadLive[memaddr])
                    {
                        // 同时创建 use_def
                        use_def[elem].insert(str);
                    }
                    // 清空
                    addrLoadLive[memaddr].clear();
                }
            }
        }
    }
    // 得到了use-def 和 def_use 下面进行替换优化 以及删除不必要的 store(进行标记)
    for (auto &elem : def_use)
    {
        auto &str = elem.first;
        auto &ldrs = elem.second;
        if (ldrs.empty())
        {
            str->setDeadSign(); // 标记为死的
        }
        else
        {
            for (auto &ldr : ldrs)
            {
                if (use_def[ldr].size() == 1)
                {
                    // 只有一个定值到达 load 值确定 进行替换
                    ValPtr strVal = str->getOperand(0); // 存入的值
                    ldr->replaceAllUsesWith(ldr, strVal);
                }
            }
        }
    }
    // 下面找出具有相同 defs 的load指令; 
}

/// @brief 对整个单元进行分析优化
/// @param module
void LiveMemAnalysisPass(ModulePtr module)
{
    auto &funList = module->getFunList();
    LiveMemVariAnalysis liveAny;
    for (auto &fun : funList)
    {
        liveAny.Pass(fun);
    }
}