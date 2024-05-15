/**
 * @file BasicBlock.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 基本块
 * @version 1.0
 * @date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "BasicBlock.h"
#include <algorithm>
#include <stdexcept>
#include "Instruction.h"
#include "Module.h"
#include "Value.h"
#include <string>

/// @brief 得到基本块指针
/// @param _parent
/// @return
BasicBlockPtr BasicBlock ::get(FuncPtr _parent)
{
    BasicBlockPtr ptr = std::make_shared<BasicBlock>(_parent);
    return ptr;
}

/// @brief 得到基本块指针
/// @param _parent
/// @param _name
/// @return
BasicBlockPtr BasicBlock ::get(FuncPtr _parent, string _name)
{
    BasicBlockPtr ptr = std::make_shared<BasicBlock>(_parent);
    ptr->setName(_name);
    return ptr;
}

/// @brief 向basicBlock末尾增加指令
/// @param inst
void BasicBlock::AddInstBack(InstPtr inst)
{
    InstLists.push_back(inst);
}

/// @brief 在指定迭代器前面插入指令
/// @param inst
/// @param pos
void BasicBlock::insertInst(InstPtr inst, InstIterator posFront)
{
    InstLists.insert(posFront, inst);
}

/// @brief 在指定指令之前
/// @param inst
/// @param AtFront
void BasicBlock::insertInst(InstPtr inst, InstPtr AtFront)
{
    auto iter = std::find(InstLists.begin(), InstLists.end(), AtFront);
    if (iter != InstLists.end())
    {
        InstLists.insert(iter, inst);
    }
    else
    {
        throw std::invalid_argument("The AtFront argument is not valid!");
    }
}

/// @brief 判断基本块是否完整
/// @return
bool BasicBlock::isCompleted()
{
    // 无指令
    if (InstLists.size() == 0)
    {
        return false;
    }
    else
    {
        if (InstLists.back()->isBranchInst())
        {
            return true;
        }
    }
    return false;
}

/// @brief 获取一个Block的文本表示
/// @param block
/// @param cnt
/// @return
string BasicBlock::toIRstr(BasicBlockPtr block, Counter *cnt)
{
    string str;
    if (block->hasName())
    {
        str = block->getName();
    }
    else
    {
        int id = cnt->getCount(block);
        str = string("L") + std::to_string(id);
    }

    str += string(":");
    str += string("\n");
    for (auto &inst : block->getInstLists())
    {
        str += string("  ") + Instruction::toIRstr(inst, cnt);
        str += string("\n");
    }
    return str;
}