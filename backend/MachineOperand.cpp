/**
 * @file MachineCode.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 机器指令操作数
 * @version 1.0
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineOperand.h"
#include "MachineInst.h"

//********************** MachineOperand  **********************************'

/// @brief 设置该操作数属于的指令
/// @param minst
void MachineOperand::setParent(MInstPtr minst) { parent = minst; }

/// @brief 获取父亲
/// @return
MInstPtr &MachineOperand::getParent() { return parent; }

/// @brief 构造函数
/// @param ty 操作数类相信
/// @param _val 值
MachineOperand::MachineOperand(OprandType ty, int _val)
{
    type = ty;
    if (type == IMM)
    {
        // 立即数类型
        val = _val;
    }
    else
    {
        // 寄存器类型 虚寄存器  物理寄存器
        reg_no = _val;
    }
}

/// @brief 构造函数
/// @param label 地址标签
MachineOperand::MachineOperand(std::string _label)
{
    type = LABEL;
    label = _label;
}

/// @brief 操作数对应字符串
/// @return
std::string MachineOperand::toStr()
{
    std::string str;
    // 对物理寄存器的命名字符输出
    auto regStr = [&str](int regNo)
    {
        switch (regNo)
        {
        case 11:
            str = "fp";
            break;
        case 12:
            str = "ip";
            break;
        case 13:
            str = "sp";
            break;
        case 14:
            str = "lr";
            break;
        case 15:
            str = "pc";
            break;
        default:
            str = std::string("r") + std::to_string(regNo);
            break;
        }
        return str;
    };

    switch (type)
    {
    case IMM:
        str = std::string("#") + std::to_string(val);
        break;
    case REG:
        str = regStr(reg_no);
        break;
    case VREG:
        str = std::string("vr") + std::to_string(reg_no);
        break;
    case LABEL:
        str = label;
    default:
        str = "unknown machine operand!";
        break;
    }

    return str;
}

/// @brief 判断操作数上是否相等  集合set中有用
/// @param other
/// @return
bool MachineOperand::operator==(MachineOperand &other)
{
    if (type != other.type)
    {
        return false;
    }
    // 立即数相等
    if (type == IMM)
    {
        return val == other.val;
    }
    // 寄存器类型编号相同
    if (type == REG || type == VREG)
    {
        return reg_no = other.reg_no;
    }
    return false;
}

/// @brief 创建操作数
/// @param ty
/// @param _val
/// @return
MOperaPtr MachineOperand::get(OprandType ty, int _val)
{
    MOperaPtr op = std::make_shared<MachineOperand>(ty, _val);
    return op;
}

/// @brief 创建Label操作数
/// @param _label
/// @return
MOperaPtr MachineOperand::get(std::string _label)
{
    MOperaPtr op = std::make_shared<MachineOperand>(_label);
    return op;
}

/// @brief 根据 IR指令操作数得到对应的汇编操作数
/// @param val
/// @return
MOperaPtr MachineOperand::get(ValPtr val)
{
    // todo
    return nullptr;
}

/// @brief 拷贝生成相同的操作数
/// @param op
/// @return
MOperaPtr MachineOperand::copy(MOperaPtr &op)
{
    // 不拷贝 parent 属性
    MOperaPtr res = nullptr;
    OprandType thisTy = op->type;
    int val = op->val;
    int regNo = op->reg_no;
    std::string label = op->label;
    if (thisTy == REG || thisTy == VREG)
    {
        res = get(thisTy, regNo);
    }
    else if (thisTy == IMM)
    {
        res = get(thisTy, val);
    }
    else
    {
        res = get(label);
    }
    return op;
}