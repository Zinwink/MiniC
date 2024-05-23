/**
 * @file PlatformArm32.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

namespace Arm32
{
    /// @brief 判断无符号 val 是否可以作为立即数
    /// @param val
    /// @return
    bool canBeImmOperand(unsigned val);

    /// @brief 判断有符号整数是否可以作为立即数
    /// @param val
    /// @return
    bool canBeImmOperand(int val);
}
