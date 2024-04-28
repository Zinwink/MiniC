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
#include "Function.h"
using string = std::string;

//********************* EntryIRInst ******************************

/// @brief 构造函数
EntryIRInst::EntryIRInst()
{
    OpType = IROperator::IR_OP_ENTRY;
}

/// @brief 析构函数
EntryIRInst::~EntryIRInst()
{
}

/// @brief 获取IR指令的字符串表述
/// @param str IR指令字符串存储
/// @return
std::string &EntryIRInst::toString(std::string &str, Counter *counter)
{
    str = "entry"; // 函数入口指令
    return str;
}

//******************  GlobalVarIRInst *****************

/// @brief 析构函数
GlobalVarIRInst::~GlobalVarIRInst()
{
    srcVars.clear();
    dstVar = nullptr;
}

/// @brief 构造函数
/// @param _dstvar 全局变量
GlobalVarIRInst::GlobalVarIRInst(Var *_dstvar)
{
    OpType = IROperator::IR_GLOBAL_VAR;
    dstVar = _dstvar;
}

/// @brief 获取IR指令的字符串表述
/// @param str IR指令字符串存储
/// @return
std::string &GlobalVarIRInst::toString(std::string &str, Counter *counter)
{
    // 全局变量不使用编号
    str = dstVar->llvmVarIDStr() + string(" = global ") + dstVar->llvmVarTypeStr() + string(" ") + std::to_string(dstVar->int32Value()) + string(", align 4");
    return str;
}

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
    case IROperator::IR_ADD_INT: // 有符号加法
        str = dstVar->llvmVarIDStr() + string(" = add nsw ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    case IROperator::IR_SUB_INT: // 有符号减法
        str = dstVar->llvmVarIDStr() + string(" = sub nsw ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    case IROperator::IR_MUL_INT: // 有符号乘法
        str = dstVar->llvmVarIDStr() + string(" = mul nsw ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    case IROperator::IR_DIV_INT: // 有符号除法
        str = dstVar->llvmVarIDStr() + string(" = sdiv ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    case IROperator::IR_MOD_INT:
        str = dstVar->llvmVarIDStr() + string(" = srem ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    case IROperator::IR_CMP_LESS:
        str = dstVar->llvmVarIDStr() + string(" = icmp slt ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    case IROperator::IR_CMP_GREATER:
        str = dstVar->llvmVarIDStr() + string(" = icmp sgt ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    case IROperator::IR_CMP_EQUAL:
        str = dstVar->llvmVarIDStr() + string(" = icmp eq ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
        break;

    case IROperator::IR_CMP_UNEQUAL:
        str = dstVar->llvmVarIDStr() + string(" = icmp ne ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(", ") + srcVars[1]->llvmVarIDStr();
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

/// @brief 拷贝形参
/// @param result
/// @param param
AssignIRInst::AssignIRInst(Var *result, FunFormalParam *param)
{
    OpType = IROperator::IR_ASSIGN;
    dstVar = result;
    Var *srcVar = param;
    srcVars.push_back(srcVar);
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

//****************** CallIRInst ********************
/// @brief 析构函数
CallIRInst::~CallIRInst()
{
    dstVar = nullptr;
    srcVars.clear();
}

/// @brief 无参函数调用
/// @param  _fun 调用的函数
/// @param _dstvar 函数调用结果
CallIRInst::CallIRInst(Function *_fun, Var *_dstvar)
{
    fun = _fun;
    dstVar = _dstvar;
}

/// @brief 构造函数
/// @param  _fun 调用的函数
/// @param _dstvar 目的操作数 函数调用结果(无返回值，直接写nullptr)
/// @param params 函数实参列表
CallIRInst::CallIRInst(Function *_fun, Var *_dstvar, std::vector<Var *> &params)
{
    fun = _fun;
    dstVar = _dstvar;
    for (auto param : params)
    {
        srcVars.push_back(param);
    }
}

// @brief 获取指令的IR字符串
/// @param str 存取字符串
/// @param counter 计数器
/// @return
std::string &CallIRInst::toString(std::string &str, Counter *counter)
{
    if (dstVar == nullptr)
    { // 无返回值 为void
        str = string("call ") + fun->getRetType().toString() + string(" @") + fun->getName() + string("(");
    }
    else
    {
        // 有返回值
        counter->setCount(dstVar); // 对目的操作数编号，即产生的临时变量
        str = dstVar->llvmVarIDStr() + string(" = call ") + fun->getRetType().toString() + string(" @") + fun->getName() + string("(");
    }
    if (srcVars.size() == 0)
        str += string(")");
    else
    {
        std::vector<FunFormalParam *> &formalparams = fun->getFormalParams();
        for (uint32_t i = 0; i < formalparams.size(); i++)
        {
            str += formalparams[i]->llvmVarTypeStr() + string(" ") + srcVars[i]->llvmVarIDStr() + string(",");
        }
        str.pop_back();
        str += string(")");
    }
    return str;
}

//****************** LabelIRInst ***********************

/// @brief 构造函数
LabelIRInst::LabelIRInst()
{
    OpType = IROperator::IR_OP_LABEL;
}

/// @brief 析构函数
LabelIRInst::~LabelIRInst()
{
}

/// @brief 获取指令的IR字符串
/// @param str 存取字符串
/// @param counter 计数器
/// @return
std::string &LabelIRInst::toString(std::string &str, Counter *counter)
{
    // Label指令的llvm ir的字符串表示
    counter->setCount(this); // 分配编号，函数设置如果已经分配子不会重复操作
    // 设置标签名字(使用llvm ir的形式  %编号)
    labelname = string("%") + std::to_string(_llvmId);
    // 翻译得到对应的str
    str = std::to_string(_llvmId) + string(":");
    return str;
}

//************************* ZextIRInst *****************************
/// @brief 构造函数
/// @param _result 扩展结果
/// @param _srcVal1 要扩展的源操作数
/// @param _srcVal1 扩展类型
ZextIRInst::ZextIRInst(Var *_result, Var *_srcVal1, ValueType &_extType)
{
    OpType = IROperator::IR_OP_ZEXT;
    dstVar = _result;
    srcVars.push_back(_srcVal1);
    extendType = _extType;
}

/// @brief 析构函数
ZextIRInst::~ZextIRInst()
{
    srcVars.clear();
    dstVar = nullptr;
}

/// @brief 获取指令的IR字符串
/// @param str 存取字符串
/// @param counter 计数器
/// @return
std::string &ZextIRInst::toString(std::string &str, Counter *counter)
{
    // srcVar源操作数一定已经分配了编号 ，只需对dstVar目的操作数编号
    counter->setCount(dstVar); // 为结果编号
    str = dstVar->llvmVarIDStr() + string(" = zext ") + srcVars[0]->llvmVarTypeStr() + string(" ") + srcVars[0]->llvmVarIDStr() + string(" to ") + extendType.toString();
    return str;
}

//********************** GotoIRInst *************************
/// @brief 构造函数
/// @param label 跳转标签
GotoIRInst::GotoIRInst(IRInst *label)
{
    OpType = IROperator::IR_OP_GOTO; // GOTO无条件跳转类型
    trueLabel = label;               // 跳转标签
}

/// @brief 析构函数
GotoIRInst::~GotoIRInst()
{
}

/// @brief 获取指令的IR字符串
/// @param str 存取字符串
/// @param counter 计数器
/// @return
std::string &GotoIRInst::toString(std::string &str, Counter *counter)
{
    str = string("br label ") + trueLabel->getLabelName();
    return str;
}

//******************** BrIRInst ************************
/// @brief 构造函数
/// @param _dstvar 条件值
/// @param _trueLabel 真标签入口
/// @param _falseLabel 假标签入口
BrIRInst::BrIRInst(Var *_dstvar, IRInst *_trueLabel, IRInst *_falseLabel)
{
    OpType = IROperator::IR_OP_BR; // 条件跳转类型
    dstVar = _dstvar;
    trueLabel = _trueLabel;
    falseLabel = _falseLabel;
}

/// @brief 析构函数
BrIRInst::~BrIRInst()
{
    // 暂时不写 之后使用智能指针管理
}

/// @brief 获取指令的IR字符串
/// @param str 存取字符串
/// @param counter 计数器
/// @return
std::string &BrIRInst::toString(std::string &str, Counter *counter)
{
    str = string("br ") + dstVar->llvmVarTypeStr() + string(" ") + dstVar->llvmVarIDStr() + string(", label ") + trueLabel->getLabelName() + string(", label ") + falseLabel->getLabelName();
    return str;
}
