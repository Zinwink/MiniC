/**
 * @file Value.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief Value基类(是包括  Instruct,Constant,Function,Argument的父类)
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "Type.h"
#include <list>

using ValPtr = std::shared_ptr<Value>;

/// @brief Value类，是所有包括Instruction,等的基类
class Value
{
private:
    TypePtr ty;                 // 类型
    std::list<ValPtr> UserList; // 该Value被其他Value使用的记录列表
public:
    enum SubClassID
    {
        InstructionVal, // 指令类型
        BasicBlockVal,  // 基本快
        ArgumentVal,    // 函数参数
        FunctionVal,   // 函数子类
        
    };
};