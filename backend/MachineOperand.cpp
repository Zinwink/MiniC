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
#include "PlatformArm32.h"
#include "DerivedInst.h"
#include "Constant.h"
#include "MachineModule.h"

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

/// @brief 重载 < 主要用于 set 排序
/// @param other
/// @return
bool MachineOperand::operator<(MachineOperand &other)
{
    if (type == other.type)
    {
        if (type == IMM)
        {
            return val < other.val;
        }
        return reg_no < other.reg_no;
    }
    else
    {
        // 无用
        return type < other.type;
    }
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

/// @brief 创建物理寄存器类型
/// @param regNo 物理寄存器编号
/// @return
MOperaPtr MachineOperand::createReg(uint32_t regNo)
{
    MOperaPtr op = get(REG, regNo);
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
MOperaPtr MachineOperand::get(ValPtr val, MModulePtr Mmodule)
{
    MOperaPtr mop = nullptr;
    // 是常数
    if (val->isConstant())
    {
        // 整数类型
        if (val->getType()->isIntegerType())
        {
            ConstantIntPtr intval = std::static_pointer_cast<ConstantInt>(val);
            mop = get(IMM, intval->getValue());
        }
    }
    else if (val->isBasicBlockVal())
    {
        // 操作数是跳转基本块标签
        string MachineBlockStr = ".LBB";
        MachineBlockStr += std::to_string(Mmodule->getCurFuncNo());
        MachineBlockStr += "_";
        MachineBlockStr += std::to_string(Mmodule->getNo(val));
        mop = get(MachineBlockStr);
    }
    else if (val->isGlobalVariable())
    {
        string Addrlabel = ".LCPI";
        Addrlabel += std::to_string(Mmodule->getCurFuncNo());
        Addrlabel += "_";
        Addrlabel += std::to_string(Mmodule->getNo(val));
        Mmodule->getCurFun()->insertAddrPool(val, Addrlabel);
        mop = get(Addrlabel);
    }
    else if (val->isTemporary())
    {
        // 临时变量将 使用虚拟寄存器
        mop = get(VREG, Mmodule->getNo(val));
    }
    else if (val->isArgument())
    {
        ArgPtr arg = std::static_pointer_cast<Argument>(val);
        if (arg->getArgNo() < 4)
        {
            // 0-3 号形参  采用r0-r3寄存器
            mop = get(REG, arg->getArgNo());
        }
        else
        {
            // >=4  大于等于4采用栈内存的形式
            MOperaPtr argVreg = get(VREG, Mmodule->getNo(val));
            MOperaPtr ldrDst = copy(argVreg);
            MOperaPtr ldrSrc1 = get(REG, 11);
            MOperaPtr offset = get(IMM, 4 * (arg->getArgNo() - 4) + 8); // 相对于fp
            MLoadInstPtr ldr = MLoadInst::get(Mmodule->getCurBlock(), MachineInst::LDR, ldrDst, ldrSrc1, offset);
            Mmodule->getCurBlock()->addInstBack(ldr); // 加入到当前块中

            // 后继可能有 saveRegs 需要对该后4函数形参进行修正
            Mmodule->getCurFun()->addAdjustInst(ldr);

            mop = argVreg;
        }
    }
    assert(mop != nullptr && "not support this usage!");
    return mop;
}

/// @brief 将立即数加载到寄存器
/// @param imm
/// @param Mmodule
/// @return
MOperaPtr MachineOperand::imm2VReg(MOperaPtr imm, MModulePtr Mmodule)
{
    assert(imm->isImm() && "imm is not a imm type!");
    int value = imm->getVal();
    MOperaPtr vreg = get(VREG, Mmodule->getRegNo()); // 生成寄存器
    if (Arm32::canBeImmOperand(value))
    {
        // 使用 MOV 指令
        MMovInstPtr mov = MMovInst::get(Mmodule->getCurBlock(), MachineInst::MOV, vreg, imm);
        Mmodule->getCurBlock()->addInstBack(mov);
    }
    else
    {
        MLoadInstPtr ldr = MLoadInst::get(Mmodule->getCurBlock(), MachineInst::LDR, vreg, imm);
        Mmodule->getCurBlock()->addInstBack(ldr);
    }
    return copy(vreg);
}

/// @brief 自动处理 Imm 类型操作数 如果Imm 符合立即数规范则保持原样 否则使用ldr伪指令加载到寄存器
/// @param imm
/// @param MModulePtr
/// @return
MOperaPtr MachineOperand::AutoDealWithImm(MOperaPtr imm, MModulePtr Mmodule)
{
    assert(imm->isImm() && "imm is not a imm type!");
    int value = imm->getVal();
    if (Arm32::canBeImmOperand(value))
    {
        return imm;
    }
    else
    {
        MOperaPtr vreg = get(VREG, Mmodule->getRegNo()); // 生成寄存器
        MLoadInstPtr ldr = MLoadInst::get(Mmodule->getCurBlock(), MachineInst::LDR, vreg, imm);
        Mmodule->getCurBlock()->addInstBack(ldr);
        return copy(vreg);
    }
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