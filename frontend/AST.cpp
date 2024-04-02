/**
 * @file AST.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 抽象语法树管理文件 包含AST节点类型描述，AST节点类，以及各类AST节点的创建
 * @version 1.0
 * @date 2024-03-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "AST.h"
#include <stdarg.h>

/// @brief 整个AST的叶子节点
ast_node *ast_root = nullptr;

/// @brief 根据ast_node节点值类型以及节点所在行号进行构造
/// @param _type 节点值类型
ast_node::ast_node(const ValueType &_type)
{
    // 已经能确定的节点类型
    switch (_type.type)
    {
    case BasicValueType::TYPE_INT32:
        node_type = ast_node_type::AST_LEAF_LITERAL_INT;
        break;
    case BasicValueType::TYPE_UINT32:
        node_type = ast_node_type::AST_LEAF_LITERAL_UINT;
        break;
    case BasicValueType::TYPE_FLOAT:
        node_type = ast_node_type::AST_LEAF_LITERAL_FLOAT;
        break;
    }
    node_type = ast_node_type::AST_ILLEGAL; // 默认先初始化为非法类型，需要之后赋值确定
    parent = nullptr;
    val_type = _type;
}

/// @brief  根据抽象语法树节点类型以及行号构造
/// @param _node_type AST节点类型
ast_node::ast_node(const ast_node_type &_node_type)
{
    node_type = _node_type;
    // 可通过条件确定一些Value_type取值
    switch (_node_type)
    {
    case ast_node_type::AST_LEAF_LITERAL_INT:
        val_type = BasicValueType::TYPE_INT32;
        break;
    case ast_node_type::AST_LEAF_LITERAL_FLOAT:
        val_type = BasicValueType::TYPE_FLOAT;
        break;
    case ast_node_type::AST_LEAF_LITERAL_UINT:
        val_type = BasicValueType::TYPE_UINT32;
        break;
    case ast_node_type::AST_LEAF_VAR_ID:
        val_type = BasicValueType::TYPE_STR;
        break;
    }
    val_type = BasicValueType::TYPE_NONE; // 默认初始化为不存在类型，供之后重新赋值
    parent = nullptr;
}

/// @brief 通过字面量创建
/// @param literal 字面量
ast_node::ast_node(const Literal_Val &literal)
{
    literal_val = literal;
    parent = nullptr;
    // 通过字面量类型 可以确定的部分节点类型
    switch (literal.type.type)
    {
    case BasicValueType::TYPE_INT32:
        node_type = ast_node_type::AST_LEAF_LITERAL_INT;
        break;
    case BasicValueType::TYPE_UINT32:
        node_type = ast_node_type::AST_LEAF_LITERAL_UINT;
        break;
    case BasicValueType::TYPE_FLOAT:
        node_type = ast_node_type::AST_LEAF_LITERAL_FLOAT;
        break;
    }
    node_type = ast_node_type::AST_ILLEGAL; // 默认初始化为非法节点类型，需后继赋值
    val_type = literal.type;
}

/// @brief 判断是否是叶子节点
/// @param node AST节点 指针类型
/// @return true：是叶子节点 false：内部节点
bool isLeafNode(const ast_node *node)
{
    bool isleaf = false;
    switch (node->node_type)
    {
    case ast_node_type::AST_LEAF_LITERAL_INT:
    case ast_node_type::AST_LEAF_LITERAL_FLOAT:
    case ast_node_type::AST_LEAF_LITERAL_UINT:
    case ast_node_type::AST_LEAF_VAR_ID:
    case ast_node_type::AST_LEAF_FUNC_FORMAL_PARAM:
    case ast_node_type::AST_LEAF_TYPE:
        isleaf = true;
        break;
    }
    return isleaf;
}

/// @brief 创建指定节点类型的节点
/// @param type 节点类型
/// @param sons_num 子节点的数目
/// @param  可变参数，支持插入若干孩子节点,
/// @return 创建节点的指针
ast_node *new_ast_node(ast_node_type type, int sons_num, ...)
{
    ast_node *parent_node = new ast_node(type);
    va_list sons_args; // 参数列表
    va_start(sons_args, sons_num);
    for (int i = 0; i < sons_num; i++)
    {
        ast_node *node = va_arg(sons_args, ast_node *);
        parent_node->sons.push_back(node);
        node->parent = parent_node;
    }
    va_end(sons_args); // 清理sons_args
    return parent_node;
}

/// @brief 向父节点插入一个节点
/// @param parent 父节点
/// @param node 插入节点
/// @return 父节点指针
ast_node *insert_ast_node(ast_node *parent, ast_node *node)
{
    node->parent = parent;
    parent->sons.push_back(node);
    return parent;
}

/// @brief 根据字面量(将在bison语法分析中读取数据)创建叶子节点(字面量：如uint,int,float等)
/// @param literal 字面量 包含行号以及字面量
/// @return 创建的节点指针
ast_node *new_ast_leaf_node(const Literal_Val &literal)
{
    ast_node *node = new ast_node(literal);
    return node;
}

/// @brief 清理抽象语法树节点 node为root时清楚整个AST
/// @param node 抽象语法树节点
void free_ast_node(ast_node *node)
{
    if (node != nullptr)
    {
        for (ast_node *son : node->sons)
        {
            free_ast_node(son);
        }
        delete node;
        node = nullptr;
    }
}

/// @brief 创建函数定义节点  中间节点
/// @param literal 字面量 包含行号,函数名信息
/// @param block 函数体语句块节点
/// @param params 函数形参列表节点,可以为空
/// @return 创建函数定义节点指针
ast_node *create_fun_def(const Literal_Val &literal, ast_node *block, ast_node *params)
{
    ast_node *fun_def_node = new ast_node(literal);
    fun_def_node->node_type = ast_node_type::AST_OP_FUNC_DEF;
}