/**
 * @file GenerateAST.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 执行词法语法分析得到抽象语法树
 * @version 1.0
 * @date 2024-04-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <string>

class GenerateAST
{
private:
    /// @brief 要解析的文件路径
    std::string filepath;

public:
    /// @brief 构造函数
    /// @param _filepath 要解析的文件路径
    GenerateAST(std::string _filepath) : filepath(_filepath) {}

    /// @brief 析构函数
    ~GenerateAST() {}

    /// @brief 执行前端分析
    /// @return 执行成功 true 失败false
    bool run(bool showInfo = false);
};
