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

/// @brief 将所有使用本对象的User的本对象指针替换(可能用于优化时)
/// @param _self 本对象
/// @param newVal
void Value::replaceAllUsesWith(ValPtr _self, ValPtr newVal)
{
    for (auto &user : _self->UserList)
    {
        user->replaceUseWith(_self, newVal);
    }
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
            str = string("%") + std::to_string(ord);
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
        int64_t ord = cnt->getCount(val);
        str = string("%") + std::to_string(ord);
    }
    return str;
}