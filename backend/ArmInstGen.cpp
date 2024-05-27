/**
 * @file ArmInstGen.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ArmInstGen.h"
#include <iostream>

/// @brief IR指令对应的处理
/// @param IRinst
/// @return
bool ArmInstGen::IR2Arm(InstPtr IRinst)
{
    bool result = false;
    Opcode op = IRinst->getOpcode();
    auto iter = IR2ArmInst_handers.find(op);
    if (iter != IR2ArmInst_handers.end())
    {
        // 找到了
        result = (this->*(iter->second))(IRinst);
    }
    else
    {
        // 未找到对应操作
        std::cout << "Unkown IRInst type:" << IRinst->getOpcodeName() << std::endl;
    }
    return result;
}

/// @brief 将AllocaInst IR 处理
/// @param alloca
/// @return
bool ArmInstGen::Alloca2ArmInst(InstPtr alloca)
{
    
    return true;
}

/// @brief 将Store IR处理
/// @param store
/// @return
bool ArmInstGen::Store2ArmInst(InstPtr store)
{
    return true;
}

/// @brief 处理 Ret IR
/// @param ret
/// @return
bool ArmInstGen::Ret2ArmInst(InstPtr ret)
{
    return true;
}

/// @brief 处理load iR
/// @param load
/// @return
bool ArmInstGen::Load2ArmInst(InstPtr load)
{
    return true;
}

/// @brief 处理 Call  IR
/// @param call
/// @return
bool ArmInstGen::Call2ArmInst(InstPtr call)
{
    return true;
}

/// @brief 无条件跳转IR处理
/// @param _goto
/// @return
bool ArmInstGen::Goto2ArmInst(InstPtr _goto)
{
    return true;
}

/// @brief 有条件 跳转IR处理
/// @param br
/// @return
bool ArmInstGen::CondBr2ArmInst(InstPtr br)
{
    return true;
}

/// @brief 处理 getelementptr
/// @param getelem
/// @return
bool ArmInstGen::Getelem2ArmInst(InstPtr getelem)
{
    return true;
}

/// @brief 整数加法 IR处理
/// @param iadd
/// @return
bool ArmInstGen::IAdd2ArmInst(InstPtr iadd)
{
    return true;
}