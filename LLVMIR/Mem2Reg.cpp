/**
 * @file Mem2Reg.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 实现mem2reg
 * @version 1.0
 * @date 2024-06-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Mem2Reg.h"
#include <stack>
#include <iostream>

/// @brief 获取alloca的assign定义节点
/// @param fun
void Mem2Reg::getAllocaAssignBBlock(FuncPtr fun)
{
    auto &entry = fun->getEntryBlock();
    for (auto &inst : entry->getInstLists())
    {
        if (!inst->isAllocaInst())
            break;
        assignNodes[inst].insert(entry);
    }
    // 根据alloca的userlist进行更新
    for (auto &elem : assignNodes)
    {
        auto &alloca = elem.first;
        for (auto &user : alloca->getUseList())
        {
            if (user->isStoreInst())
            {
                StoreInstPtr str = std::static_pointer_cast<StoreInst>(user);
                BasicBlockPtr blk = str->getBBlockParent();
                assignNodes[alloca].insert(blk);
            }
        }
    }
}

/// @brief 根据支配边界信息插入phi节点
/// @param fun
/// @param DomFronter
void Mem2Reg::insertPhiNode(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &DomFronter)
{
    // 对alloca插入phi节点
    // 实现参考自 课件ppt Ch08.pdf
    auto insertPhiAlloca = [&](ValPtr alloca)
    {
        std::set<BasicBlockPtr> alreadyList, everOnWorkList, workList;
        workList = assignNodes[alloca];
        everOnWorkList = assignNodes[alloca];
        while (!workList.empty())
        {
            BasicBlockPtr N = *(workList.begin());
            workList.erase(N);
            for (auto M : DomFronter[N])
            {
                if (alreadyList.find(M) == alreadyList.end())
                {
                    // M not in alreadylist
                    // 在M 前插入对alloca的Phi节点
                    PhiNodePtr phi = PhiNode::get(alloca);
                    M->AddInstFront(phi);
                    alreadyList.insert(M);
                }
                if (everOnWorkList.find(M) == everOnWorkList.end())
                {
                    // M not in EverOnworkList
                    everOnWorkList.insert(M);
                    workList.insert(M);
                }
            }
        }
    };

    // 下面遍历对每一条alloca处理
    for (auto &elem : assignNodes)
    {
        auto &alloca = elem.first;
        insertPhiAlloca(alloca);
    }
}

/// @brief rename操作 使用到达-定值的形式进行替换
/// @param fun
/// @param DFtree
void Mem2Reg::rename(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &DFtree)
{
    BasicBlockPtr &entry = fun->getEntryBlock();
    // 先对entry的alloca进行初始化为0 防止只声明无定义引起的错误
    // for (auto &inst : entry->getInstLists())
    // {
    //     if (!inst->isAllocaInst())
    //         break;
    //     allocaStack[inst]
    // }
    rename(entry, DFtree);
}

/// @brief 对单个块的操作
/// @param blk
/// @param DFtree
void Mem2Reg::rename(BasicBlockPtr blk, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &DFtree)
{
    auto &instList = blk->getInstLists();
    std::unordered_map<ValPtr, int> counter; // 计数,用于当本快结束后 清理弹栈
    for (auto &inst : instList)
    {
        if (inst->isPhiNode())
        {
            PhiNodePtr phi = std::static_pointer_cast<PhiNode>(inst);
            ValPtr alloca = phi->getAddr();
            allocaStack[alloca].push(phi); // 加入到栈顶
            if (counter.find(alloca) == counter.end())
            {
                // 说明是本块的第一次def
                counter.emplace(alloca, 1);
            }
            else
            {
                // 找到了
                counter[alloca]++;
            }
        }
        if (inst->isStoreInst())
        {
            ValPtr val = inst->getOperand(0);    // 存储值
            ValPtr alloca = inst->getOperand(1); // 存储地址
            allocaStack[alloca].push(val);
            if (counter.find(alloca) == counter.end())
            {
                // 说明是本块的第一次def
                counter.emplace(alloca, 1);
            }
            else
            {
                // 找到了
                counter[alloca]++;
            }
        }
        if (inst->isLoadInst())
        {
            ValPtr alloca = inst->getOperand(0);
            auto &stk = allocaStack[alloca];
            assert(!stk.empty());
            ValPtr top = stk.top();
            Value::replaceAllUsesWith(inst, top);
        }
    }
    // 下面填写后继基本块中的phi参数
    auto succes = blk->getJumpList();
    for (auto &succ : succes)
    {
        for (auto &inst : succ->getInstLists())
        {
            if (!inst->isPhiNode())
                break;
            PhiNodePtr phi = std::static_pointer_cast<PhiNode>(inst);
            ValPtr alloca = phi->getAddr();
            auto &stk = allocaStack[alloca];
            if (!stk.empty())
            {
                phi->addSrc(stk.top(), blk);
            }
            else
            {
                ConstantIntPtr zero = ConstantInt::get(32);
                zero->setValue(0);
                phi->addSrc(zero,blk);
            }
        }
    }
    // 递归遍历支配树blk的后继节点
    for (auto &node : DFtree[blk])
    {
        rename(node, DFtree);
    }
    // 当该节点运行完成后 恢复栈空间状态
    for (auto &cnt : counter)
    {
        ValPtr alloca = cnt.first;
        int pushNum = cnt.second;
        for (int i = 0; i < pushNum; i++)
        { // 根据入栈的次数进行弹栈
            allocaStack[alloca].pop();
        }
    }
}

/// @brief 优化函数
/// @param fun
void Mem2Reg::pass(FuncPtr fun, blk_setsMap &DomFronter, blk_setsMap &DFTree)
{
    reset();                        // 重置状态
    getAllocaAssignBBlock(fun);     // 计算定值所在的node
    insertPhiNode(fun, DomFronter); // 插入phi节点
    rename(fun, DFTree);            // 重命名
}

/// @brief mem2reg
/// @param module
void Mem2RegPass(ModulePtr module)
{
    Mem2Reg mem2regPass;
    auto &funList = module->getFunList();
    for (auto &fun : funList)
    {
        // 先计算支配节点集
        blk_setsMap Doms, DFTree, DomFronter;
        Doms = CFGUtils::computeDoms(fun);
        DomFronter = CFGUtils::computeDomFronter(fun, Doms);
        DFTree = CFGUtils::computeDFT(fun, Doms);
        mem2regPass.pass(fun, DomFronter, DFTree);
    }
}