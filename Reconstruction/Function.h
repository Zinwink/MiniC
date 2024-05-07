/**
 * @file Function.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  函数类
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "Value.h"
#include "BasicBlock.h"
#include "Argument.h"
#include <unordered_map>

class BasicBlock;
class Function;
using FuncPtr = std::shared_ptr<Function>;
using bblockIter = std::list<BasicBlockPtr>::iterator;

class Function : public Value
{
private:
    string funcName;                     // 函数名
    std::vector<ArgPtr> args;            // 形参列表
    std::list<BasicBlockPtr> BlocksList; // 基本块列表

public:
    /// @brief 构造函数
    /// @param _ty
    Function(Type *_ty);

    /// @brief 构造函数
    /// @param _ty 函数类型 包含返回类型  参数类型列表
    /// @param _name
    Function(Type *_ty, string _name);

    /// @brief 析构函数
    ~Function()
    {
        args.clear();
        args.shrink_to_fit();
        BlocksList.clear();
    }

    /// @brief 存在环 需要打破
    void clear() override
    {
        args.clear();
        args.shrink_to_fit();
        BlocksList.clear();
    }

    /// @brief 获取Value名
    /// @return
    string getName() override { return funcName; }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        funcName = name;
        HasName = 1;
    }

    /// @brief 参数列表
    /// @return
    std::vector<ArgPtr> &getArgsList() { return args; }

    /// @brief BasicBlock列表
    /// @return
    std::list<BasicBlockPtr> &getBasicBlocks() { return BlocksList; }

    /// @brief 在BasicBlockList末尾加入BasicBlock
    /// @param block
    void AddBBlockBack(BasicBlockPtr block);

    /// @brief 在AtFront前插入BasicBlock
    /// @param block
    /// @param AtFront
    void insertBBlock(BasicBlockPtr block, BasicBlockPtr AtFront);

    /// @brief 构造
    /// @param _ty
    /// @return
    static FuncPtr get(Type *_ty);

    /// @brief 构造
    /// @param _ty functiontype
    /// @param name 函数名
    /// @return
    static FuncPtr get(Type *_ty, string name);
};
