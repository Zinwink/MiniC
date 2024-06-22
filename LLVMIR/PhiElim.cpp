/**
 * @file PhiElim.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief phi指令消除
 * @version 1.0
 * @date 2024-06-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "PhiElim.h"
#include <set>

/// @brief 删除phi节点
/// @param fun
void PhiElim(FuncPtr fun)
{
    // 建立一个blkList副本 不使用引用 因为可能会插入块 导致分析错误
    auto blkList = std::vector<BasicBlockPtr>(fun->getBasicBlocks().begin(), fun->getBasicBlocks().end());
    std::unordered_map<BasicBlockPtr, std::vector<PhiElimMovePtr>> needInserts;
    for (auto &blk : blkList)
    {
        InstPtr &firstInst = *(blk->begin());
        if (!firstInst->isPhiNode())
            continue;
        auto preds = blk->getImmedPreds();
        for (auto &pred : preds)
        {
            auto predJumps = pred->getJumpList();
            // 识别关键 边  前驱有多个后继 本块有多个前驱
            if (predJumps.size() > 1 && preds.size() > 1)
            {
                // 进行分割
                BasicBlockPtr splitEdge = BasicBlock::get(fun);
                // 获取前驱pred的跳转指令 进行替换
                InstPtr &br = pred->back();
                BasicBlockPtr trueBlk = std::static_pointer_cast<BasicBlock>(br->getOperand(1));
                if (trueBlk == blk)
                {
                    br->getOperandsList()[1] = splitEdge;
                }
                else
                {
                    br->getOperandsList()[2] = splitEdge;
                }
                fun->insertBBlockAtBack(splitEdge, pred); // 在pred后插入该块
                BranchInstPtr splitBr = BranchInst::get(blk);
                splitEdge->AddInstBack(splitBr); // 为split插入跳转语句
                for (auto &inst : blk->getInstLists())
                {
                    if (!inst->isPhiNode())
                        break;
                    // 在splitEdge中创建mov指令
                    PhiNodePtr phi = std::static_pointer_cast<PhiNode>(inst);
                    ValPtr src = phi->getSrcFromBlk(pred);           // 获取pred对应的项的值
                    phi->removeUse(pred);                            // 去除pred对应的项
                    PhiElimMovePtr mov = PhiElimMove::get(phi, src); // 创建对应的mov指令
                    mov->setBBlockParent(splitEdge);                 // 指定属于的parent
                    needInserts[splitEdge].push_back(mov);           // 加入记录中
                }
            }
            else
            {
                // 不是关键边
                for (auto &inst : blk->getInstLists())
                {
                    if (!inst->isPhiNode())
                        break;
                    // 在splitEdge中创建mov指令
                    PhiNodePtr phi = std::static_pointer_cast<PhiNode>(inst);
                    ValPtr src = phi->getSrcFromBlk(pred);           // 获取pred对应的项的值
                    phi->removeUse(pred);                            // 去除pred对应的项
                    PhiElimMovePtr mov = PhiElimMove::get(phi, src); // 创建对应的mov指令
                    mov->setBBlockParent(pred);                      // 指定属于的parent
                    needInserts[pred].push_back(mov);                // 加入记录中
                }
            }
        }
        // 结束后 删除 phi节点
        for (auto iter = blk->begin(); iter != blk->end();)
        {
            InstPtr &isnt = *iter;
            if (!isnt->isPhiNode())
                break;
            iter = blk->getInstLists().erase(iter); // 删除phi节点
        }
    }
    // 下面根据 needInserts记录 进行插入需要插入的指令
    // 需要对指令进行处理 减少重复def
    for (auto &pair : needInserts)
    {
        auto &blk = pair.first;
        auto &instsInsert = pair.second;
        std::set<ValPtr> defs; // 记录指令中def了哪些值
        for (auto &inst : instsInsert)
        {
            defs.insert(inst->getDef());
        }
        // 根据指令的use是否有对应的def进行过滤 如果use没有对应的def则加入
        std::vector<PhiElimMovePtr> tmp;
        for (auto iter = instsInsert.begin(); iter != instsInsert.end();)
        {
            auto &inst = *iter;
            if (defs.find(inst->getUse()) == defs.end())
            { // use不在def中 不使用phi指令结果作为use的指令
                tmp.push_back(inst);
                iter = instsInsert.erase(iter);
            }
            else
            {
                iter++;
            }
        }
        // 遍历剩下的指令
        // 主要可能存在swap 这种循环引用的情况  需要引入临时变量解决
        for (auto &inst : instsInsert)
        {
        }
    }
}

/// @brief 删除phi节点
/// @param module
void PhiElim(ModulePtr module)
{
    auto &funcList = module->getFunList();
    for (auto &fun : funcList)
    {
        PhiElim(fun);
    }
}