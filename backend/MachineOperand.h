/**
 * @file MachineOperand.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief Arm32 机器指令操作数
 * @version 1.0
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Value.h"

class MachineOperand;
class MachineInst;
/// @brief 智能指针
using MOperaPtr = std::shared_ptr<MachineOperand>;
using MInstPtr = std::shared_ptr<MachineInst>;
class MachineModule;
using MModulePtr = std::shared_ptr<MachineModule>;

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
    /// @param label 地址标签,函数名，跳转基本块标签等
    MachineOperand(std::string _label);

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

    /// @brief 替换成虚拟寄存器 类型(目前主要用于后面的LinearScan寄存器溢出时进行的代码修正)
    /// @param regno
    void replaceWithVreg(int regno)
    {
        type = VREG;
        reg_no = regno;
    }

    /// @brief 获取标签
    /// @return
    std::string &getLabel() { return label; }

    /// @brief 设置该操作数属于的指令
    /// @param minst
    void setParent(MInstPtr minst);

    /// @brief 获取父亲
    /// @return
    MInstPtr &getParent();

    /// @brief 操作数对应字符串
    /// @return
    std::string toStr() const;

    /// @brief 相等比较 在之后使用 set Map时使用
    /// @param left
    /// @param right
    /// @return
    friend bool operator==(const MachineOperand &left, const MachineOperand &right);

    /// @brief < 比较 之后使用 set 时使用
    /// @param left
    /// @param right
    /// @return
    friend bool operator<(const MachineOperand &left, const MachineOperand &right);

    /// @brief 创建操作数
    /// @param ty 操作数类型
    /// @param _val 数据 如果是 VREG,REG val表示寄存器编号 如果是IMM val表示数值
    /// @return
    static MOperaPtr get(OprandType ty, int _val);

    /// @brief 创建Label操作数
    /// @param _label
    /// @return
    static MOperaPtr get(std::string _label);

    /// @brief 根据 IR指令操作数得到对应的汇编操作数
    /// @param val
    /// @return
    static MOperaPtr get(ValPtr val, MModulePtr Mmodule);

    /// @brief 创建物理寄存器类型
    /// @param regNo 物理寄存器编号
    /// @return
    static MOperaPtr createReg(uint32_t regNo);

    /// @brief 将立即数加载到寄存器，符合寄存器规范的使用mov指令，不符合的使用ldr伪指令
    /// @param imm
    /// @param Mmodule
    /// @return
    static MOperaPtr imm2VReg(MOperaPtr imm, MModulePtr Mmodule);

    /// @brief 将立即数加载到物理寄存器
    /// @param imm
    /// @param regNo
    /// @param Mmodule
    /// @return
    static MOperaPtr imm2Reg(MOperaPtr imm, uint32_t regNo, MModulePtr Mmodule);

    /// @brief 将 vreg 或者 reg 移动到 reg  如果重复则不移动
    /// @param reg vreg 或者reg
    /// @param regNo
    /// @param Mmodule
    /// @return
    static MOperaPtr AutoMovReg(MOperaPtr reg, uint32_t regNo, MModulePtr Mmodule);

    /// @brief 自动处理 Imm 类型操作数 如果Imm 符合立即数规范则保持原样 否则使用ldr伪指令加载到寄存器
    /// @param imm
    /// @param MModulePtr
    /// @return
    static MOperaPtr AutoDealWithImm(MOperaPtr imm, MModulePtr Mmodule, bool isDisp = false);

    /// @brief 拷贝生成相同的操作数
    /// @param op
    /// @return
    static MOperaPtr copy(MOperaPtr &op);
};
