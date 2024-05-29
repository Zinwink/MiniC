/**
 * @file MachineFunc.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineFunc.h"

/// @brief 构造函数
/// @param p 属于的module
/// @param _funcNo 函数编号
MachineFunc::MachineFunc(MModulePtr p)
{
    parent = p;
    addSaveReg(11); // fp
    addSaveReg(14); // lr
}

/// @brief 创建智能指针类型
/// @param p
/// @return
MFuncPtr MachineFunc::get(MModulePtr p)
{
    MFuncPtr fun = std::make_shared<MachineFunc>(p);
    return fun;
}

/// @brief 手动打破环 使智能指针自动释放
void MachineFunc::clear()
{
    parent.reset();
    for (auto &b : blockList)
    {
        b->clear();
    }
    blockList.clear();
}

/// @brief 析构函数
MachineFunc::~MachineFunc()
{
    MachineFunc::clear();
}

/// @brief 修正InstToAdjust中的指令
void MachineFunc::AdjustInsts()
{
    // 目前没有浮点寄存器
    for (auto &minst : InstToAdjust)
    {
        if (minst->isPOP())
        {
            // 获取savedRegs
            std::vector<MOperaPtr> savedRegsVect;
            for (auto &regNo : regsSave)
            {
                // 先创建一下寄存器操作数
                MOperaPtr regOPerator = MachineOperand::get(MachineOperand::REG, regNo);
                // 加入到列表中
                savedRegsVect.push_back(std::move(regOPerator));
            }
            MStackInstPtr stk = std::static_pointer_cast<MStackInst>(minst);
            stk->setRegs(savedRegsVect); // 设置pop的寄存器  pop {r4, r5, r6, fp,lr}
        }
        if (minst->isLoad())
        {
            // 用于矫正 函数后4形参的偏移  其偏移为高地址
            MLoadInstPtr ldr = std::static_pointer_cast<MLoadInst>(minst);
            int bias = 4 * (regsSave.size() - 2);
            ldr->AddOffsetBias(bias); // 新增偏置
        }
        if (minst->isStore())
        { // 用于矫正 函数后4形参的偏移  其偏移为高地址
            MStorePtr str = std::static_pointer_cast<MStore>(minst);
            int bias = 4 * (regsSave.size() - 2);
            str->AddOffsetBias(bias); // 新增偏置
        }
    }
}