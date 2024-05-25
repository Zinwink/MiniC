/**
 * @file ArmInstGen.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include <memory>

#include "Instruction.h"
#include "DerivedInst.h"
#include "Function.h"
#include "GlobalVariable.h"
#include "MachineModule.h"
#include "Module.h"

class ArmInstGen;
using ArmInstGenPtr = std::shared_ptr<ArmInstGen>;

/// @brief 产生ArmInst汇编指令
class ArmInstGen
{
private:
    /// @brief 汇编Module
    MModulePtr machineModule = nullptr;

    /// @brief LLVMIR Module
    ModulePtr IRModule = nullptr;

    /// @brief 用于标记当前函数
    MFuncPtr curMFun = nullptr;

public:
    /// @brief 构造函数
    /// @param _IRModule
    /// @param _machineModule
    ArmInstGen(ModulePtr _IRModule, MModulePtr _machineModule)
    {
        IRModule = _IRModule;
        machineModule = _machineModule;
    }

    /// @brief 析构函数
    ~ArmInstGen()
    {
        machineModule.reset();
        IRModule.reset();
    }

    /// @brief 产生ArmInst
    /// @return
    bool run();
};
