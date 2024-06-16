/**
 * @file CommSubExprElim.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 公共子表达式删除 （应在 进行活跃变量分析消减load store alloca 后做(类似于Mem2reg效果)）
 * @version 1.0
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "CommSubExprElim.h"
#include <iostream>

/// @brief 哈希比较函数
/// @param left
/// @param right
/// @return
bool equalCmp::operator()(const InstPtr &left, const InstPtr &right) const
{
    // 指令类型要相同
    if (left->getOpcode() != right->getOpcode())
    {
        return false;
    }
    if (left->isBinaryInst())
    {
        return equalBianaryInst(left, right);
    }
    else if (left->isGetelemPtrInst())
    {
        return equalGetelementInst(left, right);
    }
    return false;
}

/// @brief 判断两个二元运算指令的结果是否相同
/// @param left
/// @param right
/// @return
bool equalBianaryInst(const InstPtr &left, const InstPtr &right)
{
    Opcode leftOpty = left->getOpcode();
    Opcode rightOpty = right->getOpcode();
    if (leftOpty != rightOpty)
    {
        return false;
    }
    if (leftOpty == Opcode::AddInteger || leftOpty == Opcode::MulInteger)
    {
        return equalAddInst(left, right);
    }
    else if (leftOpty == Opcode::SubInteger || leftOpty == Opcode::DivInteger ||
             leftOpty == Opcode::ModInteger || leftOpty == Opcode::ASHR ||
             leftOpty == Opcode::SHl)
    {
        return equalSubInst(left, right);
    }
    return false;
}

/// @brief 用于比较 加法和乘法(加法和乘法满足交换律)
/// @param left
/// @param right
/// @return
bool equalAddInst(const InstPtr &left, const InstPtr &right)
{
    ValPtr leftOp1 = left->getOperand(0);
    ValPtr leftOp2 = left->getOperand(1);
    ValPtr rightOp1 = right->getOperand(0);
    ValPtr rightOp2 = right->getOperand(1);
    bool cond1 = (equalOperand(leftOp1, rightOp1) && equalOperand(leftOp2, rightOp2));
    bool cond2 = (equalOperand(leftOp1, rightOp2) && equalOperand(leftOp2, rightOp1));
    return (cond1 || cond2);
}

/// @brief 用于比较 减法 除法 取余 以及移位运算
/// @param left
/// @param right
/// @return
bool equalSubInst(const InstPtr &left, const InstPtr &right)
{
    ValPtr leftOp1 = left->getOperand(0);
    ValPtr leftOp2 = left->getOperand(1);
    ValPtr rightOp1 = right->getOperand(0);
    ValPtr rightOp2 = right->getOperand(1);
    return equalOperand(leftOp1, rightOp1) && equalOperand(leftOp2, rightOp2);
}

/// @brief 判断两个数组地址计算指令的结果是否相同
/// @param left
/// @param right
/// @return
bool equalGetelementInst(const InstPtr &left, const InstPtr &right)
{
    assert(left->isGetelemPtrInst() && right->isGetelemPtrInst());
    getelemInstPtr left_g = std::static_pointer_cast<getelementptrInst>(left);
    getelemInstPtr right_g = std::static_pointer_cast<getelementptrInst>(right);
    if (left_g->getgainDim() == right_g->getgainDim())
    {
        // 获取基地址
        ValPtr leftAddr = left->getOperand(0);
        ValPtr rightAddr = right->getOperand(0);
        // 获取偏移
        ValPtr leftOff = left->getOperand(1);
        ValPtr rightOff = right->getOperand(1);
        return (equalOperand(leftAddr, rightAddr) && equalOperand(leftOff, rightOff));
    }
    else
    {
        return false;
    }
}

/// @brief 判断两个常数相同
/// @param left
/// @param right
/// @return
bool equalConstInt(const ConstantIntPtr &left, const ConstantIntPtr &right)
{
    return (left->getValue() == right->getValue());
}

/// @brief 判断左右操作数是否相等(综合了constant 虽然InstPtr也是ValPtr 但还是只比较地址)
/// @param left
/// @param right
/// @return
bool equalOperand(const ValPtr &left, const ValPtr &right)
{
    if (left->isConstantInt() && right->isConstantInt())
    {
        ConstantIntPtr leftC = std::static_pointer_cast<ConstantInt>(left);
        ConstantIntPtr rightC = std::static_pointer_cast<ConstantInt>(right);
        return equalConstInt(leftC, rightC);
    }
    else
    { // 其他情况 比较地址即可
        return (left == right);
    }
}

//********************************* SubExprElim  ***************************************************
/// @brief 查找记录中是否有可用的公共子表达式(会结合必经节点查找)
/// @param Doms 支配节点记录
/// @param inst 当前指令
/// @return 没有公共表达式记录则 返回nullptr
InstPtr SubExprElim::searchRecord(InstPtr inst, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms)
{
    InstPtr res = nullptr;
    BasicBlockPtr &blk = inst->getBBlockParent();
    assert(blk != nullptr && Doms.find(blk) != Doms.end());
    auto &DomNodes = Doms[blk];
    for (auto &node : DomNodes)
    {
        auto iter = blk_insts.find(node);
        if (iter != blk_insts.end())
        {
            // 找到该节点有有表达式记录
            auto &instRecords = iter->second;
            auto instIter = instRecords.find(inst);
            if (instIter != instRecords.end())
            {
                // 必经节点中有公共子表达式
                res = *instIter;
                break;
            }
        }
    }
    return res;
}

/// @brief 对fun函数处理 以删除公共子表达式
/// @param fun
/// @param Doms 必经节点记录
void SubExprElim::ExperElimPass(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms)
{
    reset();  //清空旧函数信息
    auto &blkList = fun->getBasicBlocks();
    for (auto &blk : blkList)
    {
        auto &instList = blk->getInstLists();
        for (auto &inst : instList)
        {
            // 只查找二元运算以及 数组地址计算
            if (inst->isBinaryInst() || inst->isGetelemPtrInst())
            {
                InstPtr res = searchRecord(inst, Doms);
                if (res == nullptr)
                {
                    // 没有公共表达式记录 插入当前块的记录中
                    blk_insts[blk].insert(inst); // 插入记录
                }
                else
                {
                    // 能查找到 则不插入记录 使用查找的res进行替换
                    // 将使用本表达式的结果作为操作数的指令的操作数进行替换为已有的记录复用
                    Value::replaceAllUsesWith(inst, res);
                }
            }
        }
    }
}

// @brief 公共子表达式优化
/// @param module
void CommSubExprElim(ModulePtr module)
{
    SubExprElim subExpr = SubExprElim();
    auto &funList = module->getFunList();
    for (auto &fun : funList)
    {
        auto Doms = CFGUtils::computeDoms(fun);
        subExpr.ExperElimPass(fun, Doms);
    }
}