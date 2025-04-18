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
    FuncPtr parent = nullptr;     // 基本块所属的函数
    string Labelname;             // 基本块名字，可以没有
    bool _hasSign = false;        // 是否有外部标记

public:
    using InstIterator = std::list<InstPtr>::iterator; // 指令迭代器
    InstIterator begin() { return InstLists.begin(); }
    InstIterator end() { return InstLists.end(); }
    InstPtr &back() { return InstLists.back(); };

public:
    /// @brief 析构函数
    ~BasicBlock()
    {
        parent.reset();
        InstLists.clear();
    }

    /// @brief 是否是出口基本块
    /// @return
    bool isExit()
    {
        InstPtr last = InstLists.back();
        return last->isRetInst();
    }

    /// @brief 是否有标记
    /// @return
    bool hasSign() { return _hasSign; }

    /// @brief 设置标记
    void setSign() { _hasSign = true; }

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

    /// @brief 在基本块顶部插入指令 主要用于插入phi节点
    /// @param inst 
    void AddInstFront(InstPtr inst);

    /// @brief 在指定指令之前
    /// @param inst
    /// @param AtFront
    void insertInst(InstPtr inst, InstPtr AtFront);

    /// @brief 在指定迭代器前面插入指令
    /// @param inst
    /// @param pos
    void insertInst(InstPtr inst, InstIterator posFront);

    /// @brief 判断基本块是否完整
    /// @return
    bool isCompleted();

    /// @brief 判断基本块是否有直接前驱
    /// @return
    bool hasImmmedPred();

    /// @brief 获取基本块出口列表
    /// @return
    std::vector<BasicBlockPtr> getJumpList();

    /// @brief 获取当前块的直接前驱列表
    /// @return
    std::vector<BasicBlockPtr> getImmedPreds();

    /// @brief 得到基本块指针
    /// @param _parent
    /// @return
    static BasicBlockPtr get(FuncPtr _parent);

    /// @brief 得到基本块指针
    /// @param _parent
    /// @param _name
    /// @return
    static BasicBlockPtr get(FuncPtr _parent, string _name);

    /// @brief 获取一个Block的文本表示
    /// @param block
    /// @param cnt
    /// @return
    static string toIRstr(BasicBlockPtr block, Counter *cnt);
};
