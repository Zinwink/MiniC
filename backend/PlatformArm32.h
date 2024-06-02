/**
 * @file PlatformArm32.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 存放一些工具函数 后端 前端都可使用
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

    /// @brief 判断是否是合法偏移
    /// @param offset
    /// @return
    bool isLegalDisp(int offset);

    /// @brief 判断是否是2的幂次方 以及幂的次数
    /// @param n 数值
    /// @return
    int isPowerOfTwo(int n);
}
