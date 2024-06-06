/**
 * @file MachineBlock.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <memory>
#include "MachineInst.h"
#include <set>

class MachineFunc;
class MachineBlock;
using MBlockPtr = std::shared_ptr<MachineBlock>;
using MFuncPtr = std::shared_ptr<MachineFunc>;

/// @brief 汇编block
class MachineBlock
{
private:
    MFuncPtr parent = nullptr;           // 属于的函数
    uint64_t BBno;                       // 汇编基本块编号
    std::string label;                   // 基本块标签名  .LBB1_12 .LBB2_3等
    std::vector<MBlockPtr> preds, succs; // 前驱 后继
    std::list<MInstPtr> MinstList;       // 指令列表

    std::set<MOperaPtr> liveIn; // 活跃变量分析  In  Out
    std::set<MOperaPtr> liveOut;

public:
    /// @brief 返回所属的函数
    /// @return
    inline MFuncPtr &getParent() { return parent; }

    /// @brief 获取指令列表
    /// @return
    inline std::list<MInstPtr> &getInstList() { return MinstList; }

    /// @brief 获取前驱
    /// @return
    inline std::vector<MBlockPtr> &getPreds() { return preds; }

    /// @brief 获取后继
    /// @return
    inline std::vector<MBlockPtr> &getSuccs() { return succs; }

    /// @brief 获取编号
    /// @return
    inline uint64_t getBBno() { return BBno; }

    /// @brief 获取基本块名
    /// @return
    inline std::string &getLabelName() { return label; }

    /// @brief 获取in 流
    /// @return
    inline std::set<MOperaPtr> &getLiveIn() { return liveIn; }

    /// @brief 获取liveOut流
    /// @return
    inline std::set<MOperaPtr> &getLiveOut() { return liveOut; }

    /// @brief 析构函数
    ~MachineBlock();

    /// @brief 手动释放 打破环 使智能指针自动释放
    void clear();

    /// @brief 构造函数
    /// @param p
    /// @param n n=0表示函数人口块
    MachineBlock(MFuncPtr p, uint64_t n);

    /// @brief 将汇编指令添加到末尾
    /// @param inst
    void addInstBack(MInstPtr inst);

    /// @brief 指令加到块前
    /// @param inst 
    void addInstFront(MInstPtr inst);

    /// @brief 在before前插入 inst指令 （用于溢出内存时插入load指令）
    /// @param before
    /// @param inst
    /// @return
    std::list<MInstPtr>::iterator insertInstBefore(MInstPtr before, MInstPtr inst);

    /// @brief 在某条指令后插入一条指令 (寄存器分配时对 def 后插入 store保存旧值至栈中)
    /// @param after
    /// @param inst
    std::list<MInstPtr>::iterator insertInstAfter(MInstPtr after, MInstPtr inst);

    /// @brief 插入指令 在指定迭代器
    /// @param iter
    /// @param inst
    std::list<MInstPtr>::iterator insertInst(std::list<MInstPtr>::iterator iter, MInstPtr inst);

    /// @brief 添加前驱
    /// @param block
    void addPred(MBlockPtr block);

    /// @brief 添加后继
    /// @param block
    void addSucc(MBlockPtr block);

    /// @brief 删除前驱
    /// @param block
    void removePred(MBlockPtr block);

    /// @brief 删除后继
    /// @param block
    void removeSucc(MBlockPtr block);

    /// @brief 块翻译为字符串
    /// @return
    string toStr();

    /// @brief 获取块的智能指针对象
    /// @param p
    /// @param n
    /// @return
    static MBlockPtr get(MFuncPtr p, uint64_t n);
};
