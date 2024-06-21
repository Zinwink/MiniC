/**
 * @file Value.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Value.h"
#include "User.h"
#include "Module.h"
#include "Instruction.h"
#include "DerivedInst.h"

/// @brief User,Value中的属性形成了环，释放时需要先调用释放内部引用计数
void Value::clear()
{
    UserList.clear();
}

/// @brief 将所有使用本对象的User的本对象指针替换(可能用于优化时)
/// @param _self 本对象
/// @param newVal
void Value::replaceAllUsesWith(ValPtr _self, ValPtr newVal)
{
    for (auto iter = _self->UserList.begin(); iter != _self->UserList.end();)
    {
        (*iter)->replaceUseWith(_self, newVal);
        // 替换User中操作数完成后 将User冲UserList中删除
        iter = _self->UserList.erase(iter);
    }
}

/// @brief 是否是指令产生的临时变量 如 call,BinaryInst,load,Icmp等指令产生的结果
/// @return
bool Value::isTemporary()
{
    // 临时变量由指令产生
    if (!isInstruct())
    {
        return false;
    }
    else
    {
        Instruction *inst = static_cast<Instruction *>(this);
        if (inst->isBinaryInst())
        {
            return true;
        }
        else if (inst->isICmpInst())
        {
            return true;
        }
        else if (inst->isZextInst())
        {
            return true;
        }
        else if (inst->isLoadInst())
        {
            return true;
        }
        else if (inst->isCallInst())
        {
            if (inst->getType()->isVoidType())
            {
                // 调用函数无返回值
                return false;
            }
            else
            {
                return true;
            }
        }
        else if (inst->isGetelemPtrInst())
        {
            // 该指令产生 一个数组元素地址的临时变量寄存器
            return true;
        }
    }
    return false;
}

/// @brief 是否是Alloca
/// @return
bool Value::isAllocaInst()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isAllocaInst();
    }
    return res;
}

/// @brief 是否是 getelementptr 指令
/// @return
bool Value::isGetelemPtrInst()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isGetelemPtrInst();
    }
    return res;
}

/// @brief 是否是STore
/// @return
bool Value::isStoreInst()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isStoreInst();
    }
    return res;
}

/// @brief 是否是load
/// @return
bool Value::isLoadInst()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isLoadInst();
    }
    return res;
}

/// @brief 是否是整数比较指令
/// @return
bool Value::isICmpInst()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isICmpInst();
    }
    return res;
}

/// @brief 是不是 zextinst
/// @return
bool Value::isZextInst()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isZextInst();
    }
    return res;
}

/// @brief 是否是分支指令
/// @return
bool Value::isBranchInst()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isBranchInst();
    }
    return res;
}

/// @brief 判断是否时phi节点
/// @return
bool Value::isPhiNode()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isPhiNode();
    }
    return res;
}

/// @brief 判断是 callInst
/// @return
bool Value::isCallInst()
{
    bool res = false;
    if (isInstruct())
    {
        Instruction *inst = static_cast<Instruction *>(this);
        res = inst->isCallInst();
    }
    return res;
}

/// @brief 获取 Val的 llvm 标识  可以是函数 全局变量 常量 %编号形式
/// @param val
/// @param cnt
/// @return
string getllvmID(ValPtr val, Counter *cnt)
{
    string str = "unknown";
    if (val->getSubclassID() == Value::FunctionVal)
    {
        str = string("@") + val->getName();
    }
    else if (val->getSubclassID() == Value::ArgumentVal)
    {
        int64_t ord = cnt->getCount(val);
        str = string("%") + std::to_string(ord);
    }
    else if (val->getSubclassID() == Value::GlobalVari)
    {
        str = string("@") + val->getName();
    }
    else if (val->getSubclassID() == Value::BasicBlockVal)
    {
        if (val->hasName())
        {
            str = string("%") + val->getName();
        }
        else
        {
            int64_t ord = cnt->getCount(val);
            str = string("%L") + std::to_string(ord);
        }
    }
    else if (val->getSubclassID() == Value::Constant)
    {
        // 目前只有 int类型常量
        if (val->getType()->isIntegerType())
        {
            ConstantIntPtr ctant = std::static_pointer_cast<ConstantInt>(val);
            str = std::to_string(ctant->getValue());
        }
    }
    else if (val->getSubclassID() == Value::InstructionVal)
    {
        InstPtr inst = std::static_pointer_cast<Instruction>(val);
        if (!inst->isPhiNode())
        {
            int64_t ord = cnt->getCount(val);
            str = string("%t") + std::to_string(ord);
        }
        else
        {
            int64_t ord = cnt->getCount(val);
            str = string("%t") + std::to_string(ord);
        }
    }
    return str;
}