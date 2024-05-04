/**
 * @file AST_Graph.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 遍历AST 使用graphvz对抽象语法树可视化
 * @version 1.0
 * @date 2024-04-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "AST.h"
#include <string>
#include <gvc.h>

/// @brief 获取节点名字
/// @param node 节点
/// @return 字符串名
std::string getNodeName(ast_node* node);

/// @brief 生成叶子节点的图形
/// @param g Agraph_t 图形对象
/// @param astnode ast节点
/// @return Agnode_t* 节点
Agnode_t *genLeafGraphNode(Agraph_t *g, ast_node* astnode);

/// @brief 生成非叶子节点图形
/// @param g 图形对象
/// @param astnode
/// @return Agnode_t*
Agnode_t *genInternalGraphNode(Agraph_t *g, ast_node* astnode);

/// @brief 遍历AST,得到图形
/// @param g 图形对象
/// @param astnode
/// @return
Agnode_t *Traverse_AST(Agraph_t *g, ast_node* astnode);

/// @brief 可视化AST
/// @param root AST根节点
/// @param filePath AST保存的图片路径(包含图片名)
void VisualizeAST(ast_node* root, const std::string &filePath);