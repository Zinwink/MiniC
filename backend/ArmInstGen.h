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

    /// @brief 标记当前基本块
    MBlockPtr curBlock = nullptr;

private:
    /// @brief 将LLVM IR转化为MachineInst
    typedef bool (ArmInstGen::*IR2ArmInst_handler_t)(InstPtr IRinst);

    /// @brief IR指令类型--对应转化ArmInst处理函数
    std::unordered_map<Opcode, IR2ArmInst_handler_t> IR2ArmInst_handers;

    /// @brief IR指令对应的处理
    /// @param IRinst
    /// @return
    bool IR2Arm(InstPtr IRinst);

    /// @brief 将AllocaInst IR 处理
    /// @param alloca
    /// @return
    bool Alloca2ArmInst(InstPtr alloca);

    /// @brief 将Store IR处理
    /// @param store
    /// @return
    bool Store2ArmInst(InstPtr store);

    /// @brief 处理 Ret IR
    /// @param ret
    /// @return
    bool Ret2ArmInst(InstPtr ret);

    /// @brief 处理load iR
    /// @param load
    /// @return
    bool Load2ArmInst(InstPtr load);

    /// @brief 处理 Call  IR
    /// @param call
    /// @return
    bool Call2ArmInst(InstPtr call);

    /// @brief 无条件跳转IR处理
    /// @param _goto
    /// @return
    bool Goto2ArmInst(InstPtr _goto);

    /// @brief 有条件 跳转IR处理
    /// @param br
    /// @return
    bool CondBr2ArmInst(InstPtr br);

    /// @brief 处理 getelementptr
    /// @param getelem
    /// @return
    bool Getelem2ArmInst(InstPtr getelem);

    /// @brief 整数加法 IR处理
    /// @param iadd
    /// @return
    bool IAdd2ArmInst(InstPtr iadd);

public:
    /// @brief 构造函数
    /// @param _IRModule
    /// @param _machineModule
    ArmInstGen(ModulePtr _IRModule, MModulePtr _machineModule)
    {
        IRModule = _IRModule;
        machineModule = _machineModule;
        IR2ArmInst_handers[Opcode::Alloca] = &ArmInstGen::Alloca2ArmInst;
        IR2ArmInst_handers[Opcode::Store] = &ArmInstGen::Store2ArmInst;
        IR2ArmInst_handers[Opcode::Ret] = &ArmInstGen::Ret2ArmInst;
        IR2ArmInst_handers[Opcode::Load] = &ArmInstGen::Load2ArmInst;
        IR2ArmInst_handers[Opcode::Call] = &ArmInstGen::Call2ArmInst;
        IR2ArmInst_handers[Opcode::Goto] = &ArmInstGen::Goto2ArmInst;
        IR2ArmInst_handers[Opcode::ConditionBr] = &ArmInstGen::CondBr2ArmInst;
        IR2ArmInst_handers[Opcode::GetelementPtr] = &ArmInstGen::Getelem2ArmInst;
        IR2ArmInst_handers[Opcode::AddInteger] = &ArmInstGen::IAdd2ArmInst;
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
