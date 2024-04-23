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
#include <cassert>

/// @brief 整个AST的叶子节点
ast_node *ast_root = nullptr;

/// @brief 拷贝构造
/// @param node
ast_node::ast_node(const ast_node &node)
{
    this->parent = node.parent;
    this->sons = node.sons;
    this->node_type = node.node_type;
    this->val_type = node.val_type;
    this->literal_val = node.literal_val;
    this->vari = node.vari;
    this->CodesIr = node.CodesIr;
}

/// @brief 根据 节点值类型以及所在行号构造,若ValueType能确定顶节点类型则指定，否则按照_node_type指定
/// @param _type 节点值类型
/// @param _node_type 节点类型,若_type值类型无法确定节点类型，则由该参数指定
ast_node::ast_node(const ValueType &_type, ast_node_type _node_type)
{
    // 除以下switch情况外采用参数指定默认节点类型
    node_type = _node_type; // 默认先初始化为非法类型，需要之后赋值确定
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
    default:
        break;
    }
    parent = nullptr;
    val_type = _type;
    CodesIr = new IRBlock();
}

/// @brief 根据抽象语法树节点类型构造,若节点类型能确定节点的值类型则指定，否则默认为TYPE_NONE
/// @param _node_type AST节点类型
ast_node::ast_node(const ast_node_type &_node_type)
{
    node_type = _node_type;
    val_type = BasicValueType::TYPE_NONE; // 默认初始化为不存在类型，供之后重新赋值
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
    default:
        break;
    }
    parent = nullptr;
    CodesIr = new IRBlock();
}

/// @brief 通过字面量创建,若字面量类型能确定节点的值类型，则指定，否则默认初始化为TYPE_NONE
/// @param literal 字面量
/// @param _node_type 节点类型，默认为非法类型；若literal 无法确定节点类型，将由该参数指定
ast_node::ast_node(const Literal_Val &literal, ast_node_type _node_type)
{
    literal_val = literal;
    parent = nullptr;
    node_type = _node_type;               // 默认初始化为非法节点类型，需后继赋值
    val_type = BasicValueType::TYPE_NONE; // 默认设置为none类型，之后可能需按具体要求修改
    // 通过字面量类型 可以确定的部分节点类型
    switch (literal.type.type)
    {
    case BasicValueType::TYPE_INT32:
        node_type = ast_node_type::AST_LEAF_LITERAL_INT;
        val_type = literal.type; // 默认设置和字面量类型一样
        break;
    case BasicValueType::TYPE_UINT32:
        node_type = ast_node_type::AST_LEAF_LITERAL_UINT;
        val_type = literal.type; // 默认设置和字面量类型一样
        break;
    case BasicValueType::TYPE_FLOAT:
        node_type = ast_node_type::AST_LEAF_LITERAL_FLOAT;
        val_type = literal.type; // 默认设置和字面量类型一样
        break;
    default:
        break;
    }
    CodesIr = new IRBlock();
}

/// @brief 判断是否是叶子节点类型
/// @param _node_type AST节点类型
/// @return true：是叶子节点 false：内部节点
bool isLeafNodeType(ast_node_type _node_type)
{
    bool isleaf = false;
    switch (_node_type)
    {
    case ast_node_type::AST_LEAF_LITERAL_INT:
    case ast_node_type::AST_LEAF_LITERAL_FLOAT:
    case ast_node_type::AST_LEAF_LITERAL_UINT:
    case ast_node_type::AST_LEAF_VAR_ID:
    case ast_node_type::AST_LEAF_FUNC_FORMAL_PARAM:
    case ast_node_type::AST_LEAF_TYPE:
        isleaf = true;
        break;
    default:
        break;
    }
    return isleaf;
}

/// @brief 判断是否是叶子节点
/// @param node AST节点 指针类型
/// @return true：是叶子节点 false：内部节点
bool isLeafNode(const ast_node *node)
{
    return isLeafNodeType(node->node_type);
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
/// @param _node_type 节点类型
/// @return 创建的节点指针
ast_node *new_ast_leaf_node(const Literal_Val &literal, ast_node_type _node_type, const ValueType &_type)
{
    // 断言确保输入节点类型_node_type为叶子类型
    assert(isLeafNodeType(_node_type) && "Error:the _node_type input is not leaf type!");
    ast_node *node = new ast_node(literal, _node_type);
    node->val_type = _type;
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
/// @param ret_type 函数定义节点的值类型(返回类型) 未指定则默认为TYPE__VOID
/// @return 创建函数定义节点指针
ast_node *create_fun_def(const Literal_Val &literal, ast_node *block, ast_node *params, const ValueType &ret_type)
{
    ast_node *fun_def_node = new ast_node(literal, ast_node_type::AST_OP_FUNC_DEF);
    fun_def_node->val_type = ret_type;
    // 若没有参数，则创建参数节点
    if (params == nullptr)
    {
        params = new ast_node(ast_node_type::AST_OP_FUNC_FORMAL_PARAMS);
    }
    // 若没有函数体，则创建函数体
    if (block == nullptr)
    {
        block = new ast_node(ast_node_type::AST_OP_BLOCK);
    }
    fun_def_node->sons.push_back(params);
    params->parent = fun_def_node;

    fun_def_node->sons.push_back(block);
    block->parent = fun_def_node;

    return fun_def_node;
}

/// @brief 创建函数形参节点
/// @param literal 字面量 包含行号 形参名
/// @param _type 参数的值类型
/// @return 创建的节点指针
ast_node *create_fun_formal_param(const Literal_Val &literal, const ValueType _type)
{
    ast_node *fun_formal_parm = new ast_node(literal, ast_node_type::AST_LEAF_FUNC_FORMAL_PARAM);
    fun_formal_parm->val_type = _type;
    return fun_formal_parm;
}

/// @brief 创建函数调用节点 先初始valueType为TYPE_MAX未知类型
/// @param literal 字面量 包含行号，调用函数名
/// @param params 形参列表
/// @return 创建的节点指针
ast_node *create_fun_call(const Literal_Val &literal, ast_node *params)
{
    ast_node *fun_call = new ast_node(literal, ast_node_type::AST_OP_FUNC_CALL);
    fun_call->val_type.type = BasicValueType::TYPE_MAX;
    if (params == nullptr)
    {
        params = new ast_node(ast_node_type::AST_OP_FUNC_REAL_PARAMS);
    }
    fun_call->sons.push_back(params);
    params->parent = fun_call;
    return fun_call;
}