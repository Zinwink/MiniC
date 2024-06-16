/**
 * @file CommSubExprElim.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  公共子表达式删除 （应在 进行活跃变量分析消减load store alloca 后做(类似于Mem2reg效果)）
 * @version 1.0
 * @date 2024-06-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "BasicBlock.h"
#include "CFGUtils.h"
#include "Value.h"
#include "DerivedInst.h"
#include "Constant.h"
#include "Module.h"

struct equalCmp
{

    /// @brief 哈希比较函数
    /// @param left
    /// @param right
    /// @return
    bool operator()(const InstPtr &left, const InstPtr &right) const;
};

struct instHash
{
    std::size_t operator()(const InstPtr &inst) const
    {
        // 根据指令类型和属性计算哈希值 当 指令类型以及操作数都相同时相等
        // 为了简便 对于Add Mul指令满足交换律的 在创建时会根据操作数指针地址从小到达置入
        std::size_t h = std::hash<int>{}((int)inst->getOpcode());
        if (inst->isGetelemPtrInst())
        {
            // gaimDim 也需要判断
            getelemInstPtr gep = std::static_pointer_cast<getelementptrInst>(inst);
            int gainDim = gep->getgainDim();
            h ^= std::hash<int>{}(gainDim);
        }
        ValPtr op1 = inst->getOperand(0);
        ValPtr op2 = inst->getOperand(1);
        if (op1->isConstantInt())
        {
            ConstantIntPtr op1C = std::static_pointer_cast<ConstantInt>(op1);
            h ^= std::hash<int>{}(op1C->getValue());
        }
        else
        {
            h ^= std::hash<ValPtr>{}(op1);
        }

        if (op2->isConstantInt())
        {
            ConstantIntPtr op2C = std::static_pointer_cast<ConstantInt>(op2);
            h ^= std::hash<int>{}(op2C->getValue());
        }
        else
        {
            h ^= std::hash<ValPtr>{}(op2);
        }
        return h;
    }
};

/// @brief 判断两个二元运算指令的结果是否相同
/// @param left
/// @param right
/// @return
bool equalBianaryInst(const InstPtr &left, const InstPtr &right);

/// @brief 用于比较 加法和乘法(加法和乘法满足交换律)
/// @param left
/// @param right
/// @return
bool equalAddInst(const InstPtr &left, const InstPtr &right);

/// @brief 用于比较 减法 除法 取余 以及移位运算
/// @param left
/// @param right
/// @return
bool equalSubInst(const InstPtr &left, const InstPtr &right);

/// @brief 判断两个数组地址计算指令的结果是否相同
/// @param left
/// @param right
/// @return
bool equalGetelementInst(const InstPtr &left, const InstPtr &right);

/// @brief 判断两个常数相同
/// @param left
/// @param right
/// @return
bool equalConstInt(const ConstantIntPtr &left, const ConstantIntPtr &right);

/// @brief 判断左右操作数是否相等(综合了constant)
/// @param left
/// @param right
/// @return
bool equalOperand(const ValPtr &left, const ValPtr &right);

/// @brief 公共子表达式删除(对于必经节点的公共表达式也可复用)
class SubExprElim
{
private:
    /// @brief 存放各个块的表达式(不会重复记录局部的公共表达式)
    std::unordered_map<BasicBlockPtr, std::unordered_set<InstPtr, instHash, equalCmp>> blk_insts;

    /// @brief 查找记录中是否有可用的公共子表达式(会结合必经节点查找)
    /// @param Doms 支配节点记录
    /// @param inst 当前指令
    /// @return 没有公共表达式记录则 返回nullptr
    InstPtr searchRecord(InstPtr inst, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms);

public:
    /// @brief 重置清空当前函数的blk_insts记录
    void reset()
    {
        blk_insts.clear();
    }

    /// @brief 对fun函数处理 以删除公共子表达式
    /// @param fun
    /// @param Doms 必经节点记录
    void ExperElimPass(FuncPtr fun, std::unordered_map<BasicBlockPtr, std::set<BasicBlockPtr>> &Doms);
};

/// @brief 公共子表达式优化
/// @param module
void CommSubExprElim(ModulePtr module);