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
#include "Var.h"

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

    /// @brief 二元运算 %
    AST_OP_MOD,

    /// @brief 赋值语句运算符 =
    AST_OP_ASSIGN,

    /// @brief 条件与 &&
    AST_OP_COND_AND,

    /// @brief 条件或 ||
    AST_OP_COND_OR,

    /// @brief 条件非 ！
    AST_OP_COND_NOT,

    /// @brief 条件相等 ==
    AST_OP_COND_EQU,

    /// @brief 条件不等 !=
    AST_OP_COND_NOTEQU,

    /// @brief 条件小于 <
    AST_OP_COND_LESS,

    /// @brief 条件大于 >
    AST_OP_COND_GREATER,

    /// @brief 小于等于 <=
    AST_OP_COND_LESSEQU,

    /// @brief 大于等于 >=
    AST_OP_COND_GREATEREQU,

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

    /// @brief 多个声明
    AST_OP_DECL_ITEMS,

    /// @brief 单项声明节点
    AST_OP_DECL_ITEM,

    /// @brief if语句 ifstatement
    AST_OP_IFSTMT,

    /// @brief while循环
    AST_OP_WHILESTMT,

    /// @brief do_while循环
    AST_OP_DOWHILESTMT,

    /// @brief 非法运算符
    AST_ILLEGAL,

    /// @brief 未知类型
    AST_UNKONN,

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

    /// @brief 节点的字面量值  包含,(标识符名,函数名,参数名，uint，int,float等字面量之一)以及所在的行号line_no
    Literal_Val literal_val;

    /// @brief 对应的变量
    Var *vari;

public: // 构造函数
    /// @brief 根据 节点值类型以及所在行号构造,若ValueType能确定顶节点类型则指定，否则按照_node_type指定
    /// @param _type 节点值类型
    /// @param _node_type 节点类型,若_type值类型无法确定节点类型，则由该参数指定
    ast_node(const ValueType &_type, ast_node_type _node_type = ast_node_type::AST_ILLEGAL);

    /// @brief 根据抽象语法树节点类型构造,若节点类型能确定节点的值类型则指定，否则默认为TYPE_NONE
    /// @param _node_type AST节点类型
    ast_node(const ast_node_type &_node_type);

    /// @brief 通过字面量创建,若字面量类型能确定节点的值类型，则指定，否则默认初始化为TYPE_NONE
    /// @param literal 字面量
    /// @param _node_type 节点类型，默认为非法类型；若literal 无法确定节点类型，将由该参数指定
    ast_node(const Literal_Val &literal, ast_node_type _node_type = ast_node_type::AST_ILLEGAL);
};

// 下面是一些工具函数**************************************

/// @brief 抽象语法树根节点
extern ast_node *ast_root;

/// @brief 判断是否是叶子节点类型
/// @param _node_type AST节点类型
/// @return true：是叶子节点 false：内部节点
bool isLeafNodeType(ast_node_type _node_type);

/// @brief 判断是否是叶子节点
/// @param node AST节点 指针类型
/// @return true：是叶子节点 false：内部节点
bool isLeafNode(const ast_node *node);

/// @brief 创建指定节点类型的节点
/// @param type 节点类型
/// @param sons_num 子节点的数目
/// @param  可变参数，支持插入若干孩子节点,
/// @return 创建节点的指针
ast_node *new_ast_node(ast_node_type type, int sons_num, ...);

/// @brief 向父节点插入一个节点
/// @param parent 父节点
/// @param node 插入节点
/// @return 父节点指针
ast_node *insert_ast_node(ast_node *parent, ast_node *node);

/// @brief 根据字面量(将在bison语法分析中读取数据)创建叶子节点(字面量：如uint,int,float等)
/// @param literal 字面量
/// @param _node_type 节点类型,默认为AST_LEAF_TYPE
/// @param _type 节点值类型,默认为非法类型
/// @return 创建的节点指针
ast_node *new_ast_leaf_node(const Literal_Val &literal, ast_node_type _node_type = ast_node_type::AST_LEAF_TYPE, const ValueType &_type = BasicValueType::TYPE_MAX);

/// @brief 清理抽象语法树节点 node为root时清楚整个AST
/// @param node 抽象语法树节点
void free_ast_node(ast_node *node);

/// @brief 创建函数定义节点  中间节点
/// @param literal 字面量 包含行号,函数名信息
/// @param block 函数体语句块节点
/// @param params 函数形参列表节点,可以为空(未指定则默认参数为nullptr)
/// @param ret_type 函数定义节点的值类型(返回类型) 未指定则默认为TYPE__VOID
/// @return 创建函数定义节点指针
ast_node *create_fun_def(const Literal_Val &literal, ast_node *block, ast_node *params = nullptr, const ValueType &ret_type = BasicValueType::TYPE_VOID);

/// @brief 创建函数形参节点
/// @param literal 字面量 包含行号 形参名
/// @param _type 参数的值类型
/// @return 创建的节点指针
ast_node *create_fun_formal_param(const Literal_Val &literal, const ValueType _type);

/// @brief 创建函数调用节点
/// @param literal 字面量 包含行号，函数名
/// @param params 形参列表
/// @return 创建的节点指针
ast_node *create_fun_call(const Literal_Val &literal, ast_node *params);
