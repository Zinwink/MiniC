/**
 * @file MachineModule.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "MachineModule.h"

/// @brief 手动清理
void MachineModule::clear()
{
    counter.reset();
    for (auto &Mfun : funcList)
    {
        Mfun->clear();
    }
    funcList.clear();
    funcList.shrink_to_fit();
    globalVaris.clear();
    globalVaris.shrink_to_fit();
}

/// @brief  析构函数
MachineModule::~MachineModule()
{
    clear();
}

/// @brief 获取编号 全局变脸 常量标签地址  临时变量的虚拟寄存器编号
/// @param val
/// @return
uint32_t MachineModule::getNo(ValPtr val) { return counter->getNo(val); }

/// @brief 不插入记录 获取相应的
/// @return
uint32_t MachineModule::getRegNo()
{
    return counter->getRegNo();
}

//************************************* MCount ******************************************

/// @brief 获取编号 当记录中存在时 取出 不存在时放入 并增加计数
/// @param val
/// @return
uint32_t MCount::getNo(ValPtr val)
{
    uint32_t res = -1;
    auto iter = record.find(val);
    if (iter != record.end())
    {
        // 找到了
        return iter->second;
    }
    else
    {
        // 没找到 根据val 类型进行判断
        if (val->isBasicBlockVal())
        {
            res = MachineBlockNo;
            record.emplace(val, MachineBlockNo);
            MachineBlockNo++; // 自增
        }
        else if (val->isGlobalVariable())
        { // 全局变量 或者 常量池 使用标签地址
            res = LabelAddr;
            record.emplace(val, LabelAddr);
            LabelAddr++;
        }
        else if (val->isTemporary())
        {
            // 需要寄存器编号 虚拟寄存器(物理寄存器已经确定)
            res = RegNo;
            record.emplace(val, RegNo);
            RegNo++;
        }
    }
    return res;
}
