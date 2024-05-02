/**
 * @file BasicBlock.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 基本块
 * @version 1.0
 * @date 2024-04-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "Value.h"

class Function;
class BasicBlock;
using BasicBlockPtr = std::shared_ptr<BasicBlock>;
using FunctionPtr = std::shared_ptr<Function>;

class BasicBlock : public Value
{
private:

};