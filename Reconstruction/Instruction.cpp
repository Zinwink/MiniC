/**
 * @file Instruction.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Instruction.h"

/// @brief 获取指令操作码对应的名字
/// @return
string Instruction::getOpcodeName()
{
    string name;
    switch (op)
    {
    case Opcode::Alloca:
        name = string("alloca");
        break;
    case Opcode::Store:
        name = string("store");
        break;
    case Opcode::Ret:
        name = string("ret");
        break;
    case Opcode::Call:
        name = string("call");
        break;
    case Opcode::Goto:
        name = string("br");
        break;
    case Opcode::ConditionBr:
        name = string("br");
        break;
    case Opcode::Load:
        name = string("load");
        break;
    case Opcode::AddInteger:
        name = string("add");
        break;
    case Opcode::SubInteger:
        name = string("sub");
        break;
    case Opcode::MulInteger:
        name = string("mul");
        break;
    case Opcode::DivInteger:
        name = string("div");
        break;
    case Opcode::ModInteger:
        name = string("mod");
        break;

    default:
        name = string("Unknown");
        break;
    }
    return name;
}