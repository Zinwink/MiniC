/**
 * @file BasicBlockPass.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  对基本块的局部优化 并获取相关数据流信息
 * @version 1.0
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "BasicBlock.h"

/// @brief 对基本块的局部优化
class BBlockPass
{
private:
    // 到达定值分析 获取基本块的 gen kill，同时对当前基本块进行一定的局部优化 删除，替换指令
    //  如 store 10, a  store 20,a  可删除 store 10,a指令 ,store 10,a定义后被使用的load  将进行替换为 10
    //  暂时不考虑调用函数的副作用(全局变量更改赋值 传参数组的更改赋值)  后继可加入相关调用函数的分析

    
};


