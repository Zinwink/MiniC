/**
 * @file DeadInstElim.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 死指令消除
 * @version 1.0
 * @date 2024-05-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <algorithm>
#include "DeadInstElim.h"

/// @brief 删除死基本块中 iter指向的死指令
/// @param block 基本块
/// @param iter 指令对应的迭代器
/// @return
BasicBlock::InstIterator eraseDeadInst(BasicBlockPtr block, BasicBlock::InstIterator &iter)
{
    std::list<InstPtr> &instList = block->getInstLists(); // 获取指令列表引用
    if ((*iter)->isDeadInst())
    {
        // 在删除死指令之前 更新该指令操作数的UserList  将删除的指令对象从操作数的UserList中删除
        std::vector<ValPtr> &operands = (*iter)->getOperandsList(); // 获取操作数列表引用
        for (auto &op : operands)
        {
            op->deleteUser((*iter)); // 删除User
            if (op->isInstruct())
            {
                InstPtr instop = std::static_pointer_cast<Instruction>(op);
                eraseDeadInst(instop); // 判断并删除新产生的死指令
            }
        }

        iter = instList.erase(iter);
        return iter;
    }
    // 对于不是死指令 不做处理
    iter++;
    return iter;
}

/// @brief 删除DeadInst
/// @param inst
void eraseDeadInst(InstPtr inst)
{
    if (inst->isDeadInst())
    {
        assert(inst->getBBlockParent() != nullptr && "error");
        BasicBlockPtr parent = inst->getBBlockParent();
        std::list<InstPtr> &instList = parent->getInstLists();
        auto iter = std::find(instList.begin(), instList.end(), inst);
        if (iter != instList.end())
        {
            // 删除User
            std::vector<ValPtr> &operands = (*iter)->getOperandsList(); // 获取操作数列表引用
            for (auto &op : operands)
            {
                op->deleteUser((*iter)); // 删除User
                if (op->isInstruct())
                {
                    InstPtr instop = std::static_pointer_cast<Instruction>(op);
                    if (instop->isDeadInst())
                    {
                        eraseDeadInst(instop); // 删除新产生的死指令
                    }
                }
            }
            instList.erase(iter);
        }
    }
}

/// @brief 不管指令是否是死指令 直接删除一条指令
/// @param block
/// @param iter
BasicBlock::InstIterator eraseInst(BasicBlockPtr block, BasicBlock::InstIterator &iter)
{
    std::list<InstPtr> &instList = block->getInstLists();
    std::vector<ValPtr> &operands = (*iter)->getOperandsList(); // 获取操作数列表引用
    for (auto &op : operands)
    {
        op->deleteUser((*iter)); // 删除User
    }
    iter = instList.erase(iter);
    return iter;
}

/// @brief 删除module中的死指令
/// @param module
void eraseModuleDeadInst(ModulePtr module)
{
    std::deque<FuncPtr> &funList = module->getFunList();
    for (auto &fun : funList)
    {
        std::list<BasicBlockPtr> &bblocks = fun->getBasicBlocks();
        for (auto &block : bblocks)
        {
            std::list<InstPtr> &instLists = block->getInstLists();
            for (BasicBlock::InstIterator iter = instLists.begin(); iter != instLists.end();)
            {
                eraseDeadInst(block, iter); // 删除死指令
            }
        }
    }
}