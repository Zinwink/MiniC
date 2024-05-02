/**
 * @file Function.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  函数类
 * @version 1.0
 * @date 2024-05-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "Value.h"
#include "BasicBlock.h"
#include "Argument.h"

class BasicBlock;
class Function;
using FunctionPtr = std::shared_ptr<Function>;

class Function : public Value
{
private:
    string funcName;                     // 函数名
    std::vector<ArgPtr> args;            // 形参列表
    std::list<BasicBlockPtr> BlocksList; // 基本块列表

public:
    /// @brief 构造函数
    /// @param _ty
    /// @param _name
    Function(FunctionTyPtr _ty, string _name);

    /// @brief 析构函数
    ~Function()
    {
        args.clear();
        args.shrink_to_fit();
        BlocksList.clear();
    }
};
