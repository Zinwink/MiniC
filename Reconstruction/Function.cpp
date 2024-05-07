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
#include <algorithm>
#include <stdexcept>

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

/// @brief 构造
/// @param _ty
/// @return
FuncPtr Function::get(Type *_ty)
{
    FuncPtr fun = std::make_shared<Function>(_ty);
    BasicBlockPtr block = BasicBlock::get(fun, "entry"); // 每个function一定有一个entry基本快
    fun->BlocksList.push_back(std::move(block));         // 加入函数内
    return fun;
}

/// @brief 构造
/// @param _ty functiontype
/// @param name 函数名
/// @return
FuncPtr Function::get(Type *_ty, string name)
{
    FuncPtr fun = std::make_shared<Function>(_ty, name);
    BasicBlockPtr block = BasicBlock::get(fun, "entry");
    fun->BlocksList.push_back(std::move(block));
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

