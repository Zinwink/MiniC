/**
 * @file BasicBlock.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 基本块
 * @version 1.0
 * @date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "Value.h"
#include "Instruction.h"

class Function;
class BasicBlock;
using BasicBlockPtr = std::shared_ptr<BasicBlock>;
using FuncPtr = std::shared_ptr<Function>;

/// @brief 基本块 基本快的类型的Label类型
class BasicBlock : public Value
{
private:
    std::list<InstPtr> InstLists; // 指令列表
    FuncPtr parent;               // 基本块所属的函数
    string Labelname;             // 基本块名字，可以没有

public:
    using InstIterator = std::list<InstPtr>::iterator; // 指令迭代器

public:
    /// @brief 析构函数
    ~BasicBlock()
    {
        parent.reset();
        InstLists.clear();
    }

    /// @brief 引用存在环，需要打破
    void clear() override
    {
        Value::clear();
        parent.reset();
        for (auto &l : InstLists) // 循环对InstList进行clear
        {
            l->clear();
        }
        InstLists.clear();
    }

    /// @brief 无参构造
    BasicBlock() : Value(Type::getLabelType(), Value::BasicBlockVal)
    {
    }

    /// @brief 构造函数
    /// @param _parent
    BasicBlock(FuncPtr _parent) : Value(Type::getLabelType(), Value::BasicBlockVal)
    {
        parent = _parent;
    }

    /// @brief 获取对应的函数
    /// @return
    FuncPtr &getParentFun()
    {
        return parent;
    }

    /// @brief 设置对应的函数
    /// @param _p
    void setParentFun(FuncPtr _p)
    {
        parent = _p;
    }

    /// @brief 获取指令列表
    /// @return
    std::list<InstPtr> &getInstLists()
    {
        return InstLists;
    }

    /// @brief 获取Value名
    /// @return
    string getName() override { return Labelname; }

    /// @brief 设置Value名
    /// @param name
    void setName(string &name) override
    {
        HasName = 1;
        Labelname = name;
    }

    /// @brief 向basicBlock末尾增加指令
    /// @param inst
    void AddInstBack(InstPtr inst);

    /// @brief 在指定指令之前
    /// @param inst
    /// @param AtFront
    void insertInst(InstPtr inst, InstPtr AtFront);

    /// @brief 得到基本块指针
    /// @param _parent
    /// @return
    static BasicBlockPtr get(FuncPtr _parent);

    /// @brief 得到基本块指针
    /// @param _parent
    /// @param _name
    /// @return
    static BasicBlockPtr get(FuncPtr _parent, string _name);
};