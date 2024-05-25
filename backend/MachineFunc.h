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
    uint64_t stackSize;

    /// @brief 函数需要保存记录的寄存器 例如push {r1,r3,fp,lr} 然后在函数末尾 pop恢复
    std::vector<int> regsSave;

    

public:
    MachineFunc(/* args */);
    ~MachineFunc();
};
