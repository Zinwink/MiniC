/**
 * @file MachineFunc.h
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
#include "MachineBlock.h"

class MachineFunc;
class MachineModule;
using MModulePtr = std::shared_ptr<MachineModule>;
using MFuncPtr = std::shared_ptr<MachineFunc>;

class MachineFunc
{
private:
    /// @brief 所属于的Module
    MModulePtr parent = nullptr;

    /// @brief 基本块列表
    std::list<MBlockPtr> blockList;

    /// @brief 所需申请的栈空间
    uint64_t stackSize = 0;

    /// @brief 函数编号
    uint64_t funcNo;

    /// @brief 当前基本块编号
    uint64_t curBlockNo = 0;

    /// @brief 函数需要保存记录的寄存器 例如push {r1,r3,fp,lr} 然后在函数末尾 pop恢复
    std::set<int> regsSave;

public:
    /// @brief 获取函数的入口块
    /// @return
    inline MBlockPtr &getEntry() { return blockList.front(); }

    /// @brief 获取函数编号
    /// @return
    inline uint64_t getFuncNo() { return funcNo; }

    /// @brief 获取当前基本块编号
    /// @return
    inline uint64_t getcurBlockNo() { return curBlockNo; }

    /// @brief 当前基本块编号自增
    inline void curBlockNoAdd() { curBlockNo++; }

    /// @brief 加入需要保存原值寄存器
    /// @param reg
    inline void addSaveReg(int reg) { regsSave.insert(reg); }

    /// @brief 将块放入到列表尾部
    /// @param block
    inline void addBlockBack(MBlockPtr block) { blockList.push_back(block); }

    /// @brief 获取需要保存的寄存器集合
    /// @return
    inline std::set<int> &getSavedRegSet() { return regsSave; }

    /// @brief 申请栈空间(最后判断并进行8字节对齐)
    /// @return
    uint64_t AllocaStack(uint64_t size)
    {
        stackSize += size;
        return stackSize;
    }

    /// @brief 构造函数
    /// @param p 属于的module
    /// @param _funcNo 函数编号
    MachineFunc(MModulePtr p, uint64_t _funcNo);

    /// @brief 析构函数
    ~MachineFunc();

    /// @brief 手动打破环 使智能指针自动释放
    void clear();
};
