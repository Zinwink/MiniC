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
#include "DerivedTypes.h"

class Counter;
class BasicBlock;
class Function;
using FuncPtr = std::shared_ptr<Function>;
using bblockIter = std::list<BasicBlockPtr>::iterator;
using LabelParams = std::vector<BasicBlockPtr>;

class Function : public Value
{
private:
    string funcName;                     // 函数名
    std::vector<ArgPtr> args;            // 形参列表
    std::list<InstPtr> allocaLists;      // AllocaInst链表
    std::list<BasicBlockPtr> BlocksList; // 基本块列表
    int32_t maxCallFuncArgsNum = 0;     // 函数体中调用函数的最大参数数目

public:
    /// @brief 构造函数
    /// @param _ty
    Function(Type *_ty);

    /// @brief 构造函数
    /// @param _ty 函数类型 包含返回类型
    /// @param _name
    Function(Type *_ty, string _name);

    /// @brief 析构函数
    ~Function()
    {
        args.clear();
        args.shrink_to_fit();
        BlocksList.clear();
        allocaLists.clear();
    }

    /// @brief 存在环 需要打破
    void clear() override
    {
        args.clear();
        args.shrink_to_fit();
        for (auto &b : BlocksList)
        {
            b->clear();
        }
        BlocksList.clear();
    }

    /// @brief 返回最大 调用函数的 参数数目
    /// @return
    inline int32_t getMaxCallFunArgsNum() { return maxCallFuncArgsNum; }

    /// @brief 更新 最大调用函数参数数目
    /// @param argsNum
    inline void updateMaxCallFunArgsNum(int32_t argsNum)
    {
        if (argsNum > maxCallFuncArgsNum)
            maxCallFuncArgsNum = argsNum;
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

    /// @brief 加入形参
    /// @param arg
    void addArg(ArgPtr arg)
    {
        args.push_back(arg);
        FunctionType *functy = static_cast<FunctionType *>(getType());
        functy->addParamType(Type::copy(arg->getType()));
    }

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

    /// @brief 在指定迭代器处插入BasciBlocks  (无检查)
    /// @param blocks  基本块列表
    /// @param iter 插入位置
    void insertBBlock(LabelParams blocks, bblockIter iter);

    /// @brief 获取函数返回类型
    /// @return
    Type *getReturnTy();

    /// @brief 获取第 ord个参数的类型 从0开始
    /// @param ord
    /// @return
    Type *getArgsTy(uint32_t ord);

    /// @brief 获取函数的入口Block
    /// @return
    BasicBlockPtr &getEntryBlock();

    /// @brief 获取函数的出口block标签
    /// @return
    BasicBlockPtr &getExitBlock();

    /// @brief 获取AllocaLists
    /// @return
    std::list<InstPtr> &getAllocaLists() { return allocaLists; }

    /// @brief 插入allocaInst
    /// @param alloca
    void
    insertAllocaInst(InstPtr alloca);

    /// @brief  将AllocaInst加入到Entry入口
    void mergeAllocaToEntry()
    {
        BasicBlockPtr entry = getEntryBlock();
        entry->getInstLists().splice(entry->begin(), allocaLists);
    }

    /// @brief 构造
    /// @param _ty
    /// @return
    static FuncPtr get(Type *_ty);

    /// @brief 构造
    /// @param _ty functiontype
    /// @param name 函数名
    /// @return
    static FuncPtr get(Type *_ty, string name);

    /// @brief 翻译得到函数对应的文本
    /// @param fun
    /// @param cnt
    /// @return
    static string toIRstr(FuncPtr fun, Counter *cnt);
};
