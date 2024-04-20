/**
 * @file IRGenerate.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "IRGenerate.h"

/// @brief 构造函数
/// @param _scop 作用域符号表管理
/// @param _root 抽象语法树指针
IRGenerate::IRGenerate(ScopeMg *_scop, ast_node *_root)
{
    scoper = _scop;
    root = _root;
}

