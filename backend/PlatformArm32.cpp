/**
 * @file PlatformArm32.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "PlatformArm32.h"

/// @brief 判断无符号 val 是否可以作为立即数
/// @param val
/// @return
bool Arm32::canBeImmOperand(unsigned val)
{
    int i = 0;
    while (i < 32)
    {
        unsigned shift_val = ((val) >> i) | ((val) << (32 - i)); // 循环右移偶数位
        if ((shift_val & 0xFFFFFF00) == 0x00000000)
            return true;
        i = i + 2;
    }
    return false;
}

/// @brief 判断有符号整数是否可以作为立即数
/// @param val
/// @return
bool Arm32::canBeImmOperand(int val)
{
    if (val >= 0)
    {
        unsigned us = (unsigned)val;
        return Arm32::canBeImmOperand(us);
    }
    else
    {
        unsigned us = (unsigned)val;
        us = ~us + 1;
        return Arm32::canBeImmOperand(us);
    }
}

/// @brief 判断是否是合法偏移
/// @param offset
/// @return
bool Arm32::isLegalDisp(int offset)
{
    return offset < 4096 && offset > -4096;
}

/// @brief 判断是否是2的幂次方 以及幂的次数
/// @param n 数值
/// @return
int Arm32::isPowerOfTwo(int n)
{
    if (n <= 0)
    {
        return -1; // 不是2的幂次方
    }
    if ((n & (n - 1)) == 0)
    {
        // 使用n & (n - 1)可以消除最低位的1，如果结果为0，说明只有一个1
        int count = 0;
        while (n > 1)
        {
            n >>= 1;
            count++;
        }
        return count;
    }
    else
    {
        return -1; // 不是2的幂次方
    }
}