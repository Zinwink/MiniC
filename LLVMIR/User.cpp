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

    for (size_t i = 0; i < operands.size(); i++)
    {
        if (operands[i] == from)
        {
            operands[i] = to;
        }
    }
    to->insertUser(shared_from_this());

    // auto it = std::find(operands.begin(), operands.end(), from);
    // assert(it != operands.end() && "can find from!");
    // *it = to;
    // // 将本user 加入到to的UseList中
    // to->insertUser(shared_from_this());
    return true;
}