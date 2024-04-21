/**
 * @file IRInst.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  IR指令类
 * @version 1.0
 * @date 2024-04-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "IRInst.h"
using string = std::string;

//********************** AllocaIRInst ********************
/// @brief 析构函数
AllocaIRInst::~AllocaIRInst()
{
    srcVars.clear();
    dstVar = nullptr;
}

/// @brief 构造函数
/// @param _dstvar 目标变量
AllocaIRInst::AllocaIRInst(Var *_dstvar)
{
    OpType = IROperator::IR_VAR_ALLOCA;
    dstVar = _dstvar;
}

/// @brief 获取IR指令的字符串表述
/// @param str IR指令字符串存储
/// @return
std::string &AllocaIRInst::toString(std::string &str, Counter *counter)
{
    // alloca分配 需要对变量进行编号分配
    counter->setCount(dstVar);
    str = dstVar->llvmVarIDStr() + string(" = alloca ") + dstVar->llvmVarTypeStr() + string(", align 4");
    return str;
}

//*************** LoadIRInst ********************
/// @brief 析构函数
LoadIRInst::~LoadIRInst()
{
    srcVars.clear(); // 不清除列表中的指针申请的资源
    dstVar = nullptr;
}

/// @brief 构造函数
/// @param _srcVar 源操作数
/// @param _dstVar 目的操作数
LoadIRInst::LoadIRInst(Var *_srcVar, Var *_dstVar)
{
    OpType = IROperator::IR_DATA_LOAD;
    srcVars.push_back(_srcVar);
    dstVar = _dstVar;
}

/// @brief 获取IR指令对应的字符串表示
/// @param str 对应字符串
/// @param counter 分配编号计数器
/// @return IR字符串
std::string &LoadIRInst::toString(std::string &str, Counter *counter)
{
    // 源操作数无需分配 因为最先的alloca指令会分配好
    counter->setCount(dstVar); // 为目的操作数分配编号 一般为临时变量
    str = dstVar->llvmVarIDStr() + string(" = load ") + srcVars[0]->llvmVarTypeStr() + string(", ") + srcVars[0]->llvmVarTypeStr() + string("* ") + srcVars[0]->llvmVarIDStr() + string(", align 4");
    return str;
}

//******************* BinaryIRInst  **********************
/// @brief 析构函数
BinaryIRInst::~BinaryIRInst()
{
    srcVars.clear(); // 只清空vector 释放其中指针所占用的资源
    dstVar = nullptr;
}

/// @brief 根据IR指令类型，源操作数，结果操作数构造
/// @param _op 操作符
/// @param _result 结果操作数
/// @param _srcVal1 源操作数1
/// @param _srcVal2 源操作数2
BinaryIRInst::BinaryIRInst(IROperator _op, Var *_result, Var *_srcVal1, Var *_srcVal2)
{
    dstVar = _result;
    srcVars.push_back(_srcVal1);
    srcVars.push_back(_srcVal2);
    OpType = _op;
}

/// @brief 指令对应的字符串
/// @param str 字符串
/// @return 返回参数str的引用
std::string &BinaryIRInst::toString(std::string &str, Counter *counter)
{
    // 对于二元运算指令(加减乘除)，在运算前需load取数或者是字面常量直接相加，因此对于源操作数不需编号 需对产生的临时变量结果编号
    counter->setCount(dstVar);
    // 暂且只实验加法
    switch (OpType)
    {
    case IROperator::IR_ADD_INT:
        str = dstVar->llvmVarIDStr() + string(" = add nsw ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    default:
        break;
    }
    return str;
}

//******************** AssignIRinst ***************************

/// @brief 析构函数
AssignIRInst::~AssignIRInst()
{
    srcVars.clear(); //  只清空列表
    dstVar = nullptr;
}

/// @brief 构造函数
/// @param result 目的操作数
/// @param srcVal 源操作数
AssignIRInst::AssignIRInst(Var *result, Var *srcVal)
{
    OpType = IROperator::IR_ASSIGN;
    srcVars.push_back(srcVal);
    dstVar = result;
}

/// @brief 获取指令的IR字符串
/// @param str 存取字符串
/// @return
std::string &AssignIRInst::toString(std::string &str, Counter *counter)
{ // 对于赋值指令 左值一定已经编号， 右边的变量也一定已经编号，或者是字面数值无需编号
    str = string("store ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + dstVar->llvmVarTypeStr() + string("* ") + dstVar->llvmVarIDStr() + string(", align 4");

    return str;
}

//****************** ReturnIRInst ********************8

/// @brief 析构函数
ReturnIRInst::~ReturnIRInst()
{
    srcVars.clear();
    dstVar = nullptr;
}

/// @brief 构造函数
/// @param _dstvar 返回值目的操作数
ReturnIRInst::ReturnIRInst(Var *_dstvar)
{
    OpType = IROperator::IR_RETURN;
    dstVar = _dstvar;
}

/// @brief 获取指令的IR字符串
/// @param str 存取字符串
/// @param counter 计数器
/// @return
std::string &ReturnIRInst::toString(std::string &str, Counter *counter)
{
    if (dstVar != nullptr)
    { // 目的操作数不为空
        str = string("ret ") + dstVar->llvmVarTypeStr() + string(" ") + dstVar->llvmVarIDStr();
    }
    else
    {
        // dstVar为空  表示无返回值 void
        str = string("ret void");
    }

    return str;
}