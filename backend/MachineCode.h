/**
 * @file MachineCode.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief Arm32 机器指令表示
 * @version 1.0
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <memory>
#include <string>

class MachineModule;
class MachineFunction;
class MachineBlock;
class MachineInst;
class MachineOperand;

/// @brief 智能指针
using MModulePtr = std::shared_ptr<MachineModule>;
using MFuncPtr = std::shared_ptr<MachineFunction>;
using MBlockPtr = std::shared_ptr<MachineBlock>;
using MInstPtr = std::shared_ptr<MachineInst>;
using MOperaPtr = std::shared_ptr<MachineOperand>;

/// @brief 机器指令操作数  可以是立即数 寄存器值 标签地址
class MachineOperand
{
public:
    /// @brief 机器操作数类型
    enum OprandType
    {
        IMM,  // 立即数(可能可以直接作为立即数运算 也可能需要先load加载至寄存器)
        VREG, // 虚拟寄存器
        REG,  // 物理寄存器类型
        LABEL // 标签类型 如全局变量地址标签 常量池标签 基本块标签 调用函数时函数名
    };

private:
    MInstPtr parent = nullptr; // 属于的指令
    OprandType type;           // 操作数类型
    int val;                   // 存储立即数的值
    int reg_no = -1;           // 寄存器编号
    std::string label;         // 地址标签
public:
    /// @brief 析构函数
    ~MachineOperand() { parent.reset(); }

    /// @brief 存在环 需要打破 使智能指针正常析构
    void clear() { parent.reset(); }

    /// @brief 构造函数
    /// @param ty 操作数类相信
    /// @param _val 值
    MachineOperand(OprandType ty, int _val);

    /// @brief 构造函数
    /// @param label 地址标签
    MachineOperand(std::string label);

    /// @brief 是否是立即数类型
    /// @return
    bool isImm() { return type == IMM; }

    /// @brief 是否是物理寄存器
    /// @return
    bool isReg() { return type == REG; }

    /// @brief 是否是虚寄存器
    /// @return
    bool isVReg() { return type == VREG; }

    /// @brief 是否是标签地址
    /// @return
    bool isLabel() { return type == LABEL; }

    /// @brief 获取立即数值
    /// @return
    int getVal() { return val; }

    /// @brief 获取寄存器编号
    /// @return
    int getRegNo() { return reg_no; }

    /// @brief 设置寄存器编号 可以是虚拟寄存器编号
    /// @param regno
    void setRegNo(int regno) { reg_no = regno; }

    /// @brief 设置为寄存器类型，并给上编号 用于 虚拟寄存器映射至物理寄存器使用
    /// @param regno
    void setReg(int regno)
    {
        type = REG;
        reg_no = regno;
    }

    /// @brief 获取标签
    /// @return
    std::string &getLabel() { return label; }

    /// @brief 设置该操作数属于的指令
    /// @param minst
    void setParent(MInstPtr minst) { parent = minst; }

    /// @brief 获取父亲
    /// @return
    MInstPtr &getParent() { return parent; }

    /// @brief 操作数对应字符串
    /// @return
    std::string toStr();
};
