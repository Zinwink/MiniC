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

    /// @brief IR基本块和MachinBlock的对应
    std::unordered_map<BasicBlockPtr, MBlockPtr> IRBlk2MBlk;

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

    /// @brief ICmp IRInst 对应的操作
    /// @param icmp
    /// @return
    bool ICmp2ArmInst(InstPtr icmp);

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

    /// @brief 整数乘法
    /// @param imul
    /// @return
    bool IMul2ArmInst(InstPtr imul);

    /// @brief 整数减法
    /// @param isub
    /// @return
    bool ISub2ArmInst(InstPtr isub);

    /// @brief 整数除法
    /// @param idiv
    /// @return
    bool IDiv2ArmInst(InstPtr idiv);

    /// @brief 整数取余
    /// @param srem
    /// @return
    bool ISrem2ArmInst(InstPtr srem);

    /// @brief 逻辑左移
    /// @param shl
    /// @return
    bool Shl2ArmInst(InstPtr shl);

    /// @brief 算数右移
    /// @param ashr
    /// @return
    bool Ashr2ArmInst(InstPtr ashr);

    /// @brief 将 Zext翻译为对应的arm32指令
    /// @param zext
    /// @return
    bool Zext2ArmInst(InstPtr zext);

    /// @brief bitcast对应的翻译  不用翻译
    /// @param bitcast
    /// @return
    bool BitCastArmInst(InstPtr bitcast) { return true; }

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
        IR2ArmInst_handers[Opcode::ICMP] = &ArmInstGen::ICmp2ArmInst;
        IR2ArmInst_handers[Opcode::ConditionBr] = &ArmInstGen::CondBr2ArmInst;
        IR2ArmInst_handers[Opcode::GetelementPtr] = &ArmInstGen::Getelem2ArmInst;
        IR2ArmInst_handers[Opcode::AddInteger] = &ArmInstGen::IAdd2ArmInst;
        IR2ArmInst_handers[Opcode::MulInteger] = &ArmInstGen::IMul2ArmInst;
        IR2ArmInst_handers[Opcode::SubInteger] = &ArmInstGen::ISub2ArmInst;
        IR2ArmInst_handers[Opcode::DivInteger] = &ArmInstGen::IDiv2ArmInst;
        IR2ArmInst_handers[Opcode::ModInteger] = &ArmInstGen::ISrem2ArmInst;
        IR2ArmInst_handers[Opcode::SHl] = &ArmInstGen::Shl2ArmInst;
        IR2ArmInst_handers[Opcode::ASHR] = &ArmInstGen::Ashr2ArmInst;
        IR2ArmInst_handers[Opcode::Zext] = &ArmInstGen::Zext2ArmInst;
        IR2ArmInst_handers[Opcode::BitCast] = &ArmInstGen::BitCastArmInst;
    }

    /// @brief 智能指针对象
    /// @param _IRModule
    /// @param _machineModule
    /// @return
    static ArmInstGenPtr get(ModulePtr _IRModule, MModulePtr _machineModule);

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
