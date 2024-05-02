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