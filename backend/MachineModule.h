/**
 * @file MachineModule.h
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
#include <deque>
#include "MachineFunc.h"
#include "GlobalVariable.h"

class MachineModule;
using MModulePtr = std::shared_ptr<MachineModule>;

class MachineModule
{
private:
    /// @brief 函数列表
    std::vector<MFuncPtr> funcList;

    /// @brief 全局变量列表
    std::vector<GlobalVariPtr> globalVaris;

    /// @brief 当前函数编号
    uint64_t curFuncNo = 0;

public:
    /// @brief 获取函数列表
    /// @return
    inline std::vector<MFuncPtr> &getFuncList() { return funcList; }

    /// @brief 获取全局变量列表
    /// @return
    inline std::vector<GlobalVariPtr> &getGlobalVars() { return globalVaris; }

    /// @brief 获取当前函数编号
    /// @return
    inline uint64_t getCurFuncNo() { return curFuncNo; }

    /// @brief 当前函数编号自增
    inline void curFuncNoAdd() { curFuncNo++; }

    /// @brief 构造函数
    MachineModule() = default;

    /// @brief  析构函数
    ~MachineModule();

    /// @brief 手动清理
    void clear();
};