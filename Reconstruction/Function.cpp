/**
 * @file Function.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Function.h"
#include "Value.h"
#include "BasicBlock.h"
#include "DerivedInst.h"
#include <algorithm>
#include <stdexcept>
#include "Module.h"

/// @brief 构造函数
/// @param _ty
Function::Function(Type *_ty) : Value(_ty, Value::FunctionVal)
{
}

/// @brief 构造函数
/// @param _ty 函数类型 包含返回类型  参数类型列表
/// @param _name
Function::Function(Type *_ty, string _name) : Value(_ty, Value::FunctionVal)
{
    funcName = _name;
    HasName = 1;
}

/// @brief 获取函数返回类型
/// @return
Type *Function::getReturnTy()
{
    FunctionType *funTy = static_cast<FunctionType *>(getType());
    return funTy->getReturnType();
}

/// @brief 获取第 ord个参数的类型 从0开始
/// @param ord
/// @return
Type *Function::getArgsTy(uint32_t ord)
{
    FunctionType *funTy = static_cast<FunctionType *>(getType());
    return funTy->getParamType(ord);
}

/// @brief 构造
/// @param _ty
/// @return
FuncPtr Function::get(Type *_ty)
{
    FuncPtr fun = std::make_shared<Function>(_ty);
    return fun;
}

/// @brief 构造
/// @param _ty functiontype
/// @param name 函数名
/// @return
FuncPtr Function::get(Type *_ty, string name)
{
    FuncPtr fun = std::make_shared<Function>(_ty, name);
    return fun;
}

/// @brief 在BasicBlockList末尾加入BasicBlock
/// @param block
void Function::AddBBlockBack(BasicBlockPtr block)
{
    BlocksList.push_back(block);
}

/// @brief 在AtFront前插入BasicBlock
/// @param block
/// @param AtFront
void Function::insertBBlock(BasicBlockPtr block, BasicBlockPtr AtFront)
{
    auto iter = std::find(BlocksList.begin(), BlocksList.end(), AtFront);
    if (iter != BlocksList.end())
    {
        BlocksList.insert(iter, block);
    }
    else
    {
        throw std::invalid_argument("The AtFront param is invalid!");
    }
}

/// @brief 在指定迭代器处插入BasciBlock (无检查)
/// @param block 基本块列表
/// @param iter 插入位置
void Function::insertBBlock(LabelParams blocks, bblockIter iter)
{
    BlocksList.insert(iter, blocks.begin(), blocks.end());
}

/// @brief 获取函数的入口Block
/// @return
BasicBlockPtr &Function::getEntryBlock()
{
    assert(BlocksList.size() >= 2 && "no Entry Block has been constructed!");
    return BlocksList.front();
}

/// @brief 获取函数的出口block标签
/// @return
BasicBlockPtr &Function::getExitBlock()
{
    assert(BlocksList.size() >= 2 && "no Exit Block has been constructed!");
    return BlocksList.back();
}

/// @brief 插入allocaInst
/// @param alloca
void Function ::insertAllocaInst(InstPtr alloca)
{
    assert(alloca->getOpcode() == Opcode::Alloca && "not allocaInst type!");
    allocaLists.push_back(alloca);
}

/// @brief 翻译得到函数对应的文本
/// @param fun
/// @param cnt
/// @return
string Function::toIRstr(FuncPtr fun, Counter *cnt)
{
    string str = "\ndefine " + fun->getReturnTy()->TypeStr() + string(" ") + string("@") + fun->getName() + string("(");
    for (uint32_t i = 0; i < fun->getArgsList().size(); i++)
    {
        string paramStr = fun->getArgsTy(i)->TypeStr() + string(" ") + getllvmID(fun->getArgsList()[i], cnt);
        str += paramStr;
        if (i != (fun->getArgsList().size() - 1))
        { // 不是最后一个形参
            str += string(", ");
        }
    }
    str += string(") {\n");
    for (auto &blk : fun->getBasicBlocks())
    {
        // 按顺序先为每个Label编号
        getllvmID(blk, cnt);
    }
    for (auto &blk : fun->getBasicBlocks())
    {
        str += BasicBlock::toIRstr(blk, cnt);
        str += "\n";
    }
    str.pop_back();
    str += "}";
    return str;
}