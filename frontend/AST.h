/**
 * @file AST.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 抽象语法树管理文件 包含AST节点类型描述，AST节点类，以及各类AST节点的创建
 * @version 1.0
 * @date 2024-03-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "ValueType.h"
#include "Literal_Val.h"

/// @brief AST节点类型 枚举
enum class ast_node_type : int
{
    /*AST的叶子节点*/
    ///@brief 无符号整数字面量叶子节点
    AST_LEAF_LITERAL_UINT,

    /// @brief 有符号整数字面量节点
    AST_LEAF_LITERAL_INT,

    /// @brief 浮点数字面量节点
    AST_LEAF_LITERAL_FLOAT,

    ///@brief 标识符变量叶子节点
    AST_LEAF_VAR_ID,

    /// @brief 单个函数形参运算符节点 属性包含名字与类型
    AST_LEAF_FUNC_FORMAL_PARAM,

    /// @brief 笼统叶子节点（具体状态应该如上所示）
    AST_LEAF_TYPE,

    /*以下为AST内部节点 以及根节点*/
    /// @brief 文件编译单元运算符， 可包含函数定义，语句块，表达式等
    AST_OP_COMPILE_UNIT,

    ///@brief 二元运算符 +
    AST_OP_ADD,

    /// @brief 二元运算符-
    AST_OP_SUB,

    /// @brief 二元运算符*
    AST_OP_MUL,

    /// @brief 二元运算符/
    AST_OP_DIV,

    /// @brief 赋值语句运算符 =
    AST_OP_ASSIGN,

    /// @brief 多个语句组成的块运算符
    AST_OP_BLOCK,

    /// @brief 表达式语句运算符，不显示表达式的值
    AST_OP_EXPER,

    /// @brief 表达式显示语句运算符，显示表达式的值
    AST_OP_EXPER_SHOW,

    /// @brief return 语句运算符
    AST_OP_RETURN_STATEMENT,

    /// @brief 函数定义运算符，节点属性包括函数名，返回值类型，其孩子节点：函数形式参数列表运算符节点，代码块运算符
    AST_OP_FUNC_DEF,

    /// @brief 函数形式参数列表运算符，包含多个形参  AST_LEAF_FUNC_FORMAL_PARAM
    AST_OP_FUNC_FORMAL_PARAMS,

    /// @brief 函数调用运算符，属性包含函数名，孩子包含实参列表 AST_OP_FUNC_REAL_PARAMS
    AST_OP_FUNC_CALL,

    /// @brief 实参列表运算符， 可包含AST_OP_EXPR,字面量，标识符变量等
    AST_OP_FUNC_REAL_PARAMS,

    /// @brief 非法运算符
    AST_OP_ILLEGAL,

};

/// @brief 抽象语法树AST节点描述类
class ast_node
{
public: // 属性
    /// @brief 父节点
    ast_node *parent;

    /// @brief 孩子节点
    std::vector<ast_node *> sons;

    /// @brief 节点类型
    ast_node_type node_type;

    /// @brief 节点值类型
    ValueType val_type;

    /// @brief 节点的字面量值  包含,(标识符名，uint，int,float等字面量)以及所在的行号line_no
    Literal_Val literal_val;

public: // 构造函数
    /// @brief 根据 节点值类型以及所在行号构造  叶子节点
    /// @param _type 节点值类型
    ast_node(const ValueType &_type);

    /// @brief 根据抽象语法树节点类型以及行号构造  中间节点
    /// @param _node_type AST节点类型
    ast_node(const ast_node_type &_node_type);

    /// @brief 通过字面量创建
    /// @param literal 字面量
    ast_node(const Literal_Val &literal);
};
