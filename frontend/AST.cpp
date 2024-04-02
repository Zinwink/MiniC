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

/// @brief 整个AST的叶子节点
ast_node *ast_root = nullptr;

/// @brief 根据ast_node节点值类型以及节点所在行号进行构造
/// @param _type 节点值类型
ast_node::ast_node(const ValueType &_type)
{
    node_type = ast_node_type::AST_LEAF_TYPE;
    parent = nullptr;
    val_type = _type;
}

/// @brief  根据抽象语法树节点类型以及行号构造
/// @param _node_type AST节点类型
ast_node::ast_node(const ast_node_type &_node_type)
{
    node_type = _node_type;
    val_type = BasicValueType::TYPE_MAX;
    parent = nullptr;
}

/// @brief 通过字面量创建
/// @param literal 字面量
ast_node::ast_node(const Literal_Val &literal)
{
    literal_val = literal;
    parent = nullptr;
    node_type = ast_node_type::AST_LEAF_TYPE;
    val_type = BasicValueType::TYPE_MAX;
}