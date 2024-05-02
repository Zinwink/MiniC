/**
 * @file User.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "User.h"
#include <algorithm>

/// @brief 将操作数替换为指定的Value
/// @param from 旧值
/// @param to 替换值
/// @return
bool User::replaceUseWith(ValPtr from, ValPtr to)
{
    auto it = std::find(operands.begin(), operands.end(), from);
    assert(it != operands.end() && "can find from!");
    *it = to;
    return true;
}