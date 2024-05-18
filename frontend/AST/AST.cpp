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
#include "Type.h"
#include "DerivedTypes.h"
#include "AST_Graph.h"
#include <iostream>
#include <stdexcept>

/// @brief 整个AST的叶子节点
ast_node *ast_root = nullptr;

/// @brief 根据抽象语法树节点类型构造,若节点类型能确定节点的值类型则指定，否则默认为TYPE_NONE
/// @param _node_type AST节点类型
ast_node::ast_node(ast_node_type _node_type)
{
    node_type = _node_type;
}

/// @brief 通过字面量创建,若字面量类型能确定节点的值类型，则指定，否则默认初始化为TYPE_NONE
/// @param literal 字面量
/// @param _node_type 节点类型，默认为非法类型；若literal 无法确定节点类型，将由该参数指定
ast_node::ast_node(Literal_Val &literal, ast_node_type _node_type)
{
    literal_val = literal;
    parent = nullptr;
    node_type = _node_type; // 默认初始化为非法节点类型，需后继赋值
}

/// @brief 释放内存
/// @param root
void free_ast(ast_node *root)
{
    if (root != nullptr)
    {
        for (auto &son : root->sons)
        {
            free_ast(son);
        }
        delete root;
        root = nullptr;
    }
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
    case ast_node_type::AST_LEAF_CONST_VAR_ID:
    // case ast_node_type::AST_LEAF_FUNC_FORMAL_PARAM:
    case ast_node_type::AST_LEAF_TYPE:
    case ast_node_type::AST_OP_BREAK:
    case ast_node_type::AST_OP_CONTINUE:
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
bool isLeafNode(ast_node *node)
{
    return isLeafNodeType(node->node_type);
}

/// @brief 创建指定节点类型的节点
/// @param type 节点类型
/// @param _sons  孩子节点指针列表
/// @return 创建节点的指针
ast_node *new_ast_node(ast_node_type type, std::initializer_list<ast_node *> _sons)
{
    ast_node *parent_node = new ast_node(type);
    for (auto &son : _sons)
    {
        parent_node->sons.push_back(son);
        son->parent = parent_node;
    }
    return parent_node;
}

/// @brief 创建指定节点类型的节点
/// @param type 节点类型
/// @param _sons  孩子节点指针列表
/// @return 创建节点的指针
ast_node *new_ast_node(Literal_Val &literal, ast_node_type type, std::initializer_list<ast_node *> _sons)
{
    ast_node *parent_node = new ast_node(literal, type);
    for (auto &son : _sons)
    {
        parent_node->sons.push_back(son);
        son->parent = parent_node;
    }
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
ast_node *new_ast_leaf_node(Literal_Val &literal, ast_node_type _node_type)
{
    // 断言确保输入节点类型_node_type为叶子类型
    ast_node *node = new ast_node(literal, _node_type);
    return node;
}

/// @brief 创建函数定义节点  中间节点
/// @param literal 字面量 包含行号,函数名信息
/// @param params 函数形参列表节点,可以为空
/// @param block 函数体
/// @param ret_type 函数定义节点的值类型(返回类型) 未指定则默认为TYPE__VOID
/// @return 创建函数定义节点指针
ast_node *create_fun_def(Literal_Val &literal, Type *ret_type, ast_node *params, ast_node *block)
{
    ast_node *fun_def_node = new ast_node(literal, ast_node_type::AST_OP_FUNC_DEF);
    fun_def_node->attr = ret_type;
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

/// @brief 创建函数声明
/// @param literal
/// @param ret_type
/// @param params
/// @return
ast_node *create_fun_declare(Literal_Val &literal, Type *ret_type, ast_node *params)
{
    ast_node *fun_declare = new ast_node(literal, ast_node_type::AST_OP_FUNC_DECLARE);
    fun_declare->attr = ret_type;
    // 若没有参数，则创建参数节点
    if (params == nullptr)
    {
        params = new ast_node(ast_node_type::AST_OP_FUNC_FORMAL_PARAMS);
    }
    fun_declare->sons.push_back(params);
    params->parent = fun_declare;

    return fun_declare;
}

/// @brief 创建函数形参节点
/// @param literal 字面量 包含行号 形参名
/// @param _type 参数的值类型
/// @return 创建的节点指针
ast_node *create_fun_formal_param(Literal_Val &literal, Type *_type)
{
    ast_node *fun_formal_parm = new ast_node(literal, ast_node_type::AST_LEAF_FUNC_FORMAL_PARAM);
    fun_formal_parm->attr = _type;
    return fun_formal_parm;
}

/// @brief 创建函数调用节点 先初始valueType为TYPE_MAX未知类型
/// @param literal 字面量 包含行号，调用函数名
/// @param params 形参列表
/// @return 创建的节点指针
ast_node *create_fun_call(Literal_Val &literal, ast_node *params)
{
    ast_node *fun_call = new ast_node(literal, ast_node_type::AST_OP_FUNC_CALL);
    if (params == nullptr)
    {
        params = new ast_node(ast_node_type::AST_OP_FUNC_REAL_PARAMS);
    }
    fun_call->sons.push_back(params);
    params->parent = fun_call;
    return fun_call;
}

/// @brief 更新子节点类型   Bison采用规约的形式，如此可以更新子节点类型
/// @param parent
void updateDeclTypes(ast_node *parent)
{
    // 这里主要针对  int declareItems使用 对于数组类型特殊处理，其余在MiniC.y顺带处理
    ast_node_type paretTy = parent->node_type;
    assert((paretTy == ast_node_type::AST_OP_DECL_ITEMS || paretTy == ast_node_type::AST_OP_CONST_DECL_ITEMS) && "Error! file:AST.cpp");
    for (auto &son : parent->sons)
    {
        //  DECL_ITEMS CONST_DECL_IEMS 的子节点有 DEF节点(有初赋值)，有val 节点(没有初赋值)
        ast_node_type sonTy = son->node_type;
        if (sonTy == ast_node_type::AST_OP_ARRAY) // 子节点为数组类型较为特殊
        {
            Type *ty = Type::copy(parent->attr);
            son->attr = ty;
        }
        else if (sonTy == ast_node_type::AST_LEAF_VAR_ID)
        {
            Type *ty = Type::copy(parent->attr);
            son->attr = ty;
        }
        else if (sonTy == ast_node_type::AST_LEAF_CONST_VAR_ID)
        {
            Type *ty = Type::copy(parent->attr);
            son->attr = ty;
        }
        else if (sonTy == ast_node_type::AST_OP_VAR_DEF)
        {
            Type *ty = Type::copy(parent->attr);
            son->sons[0]->attr = ty;
        }
        else if (sonTy == ast_node_type::AST_OP_CONST_VAR_DEF)
        {
            Type *ty = Type::copy(parent->attr);
            son->sons[0]->attr = ty;
        }
        else {
            Type *ty = Type::copy(parent->attr);
            son->attr = ty;
        }
    }
}

// /// @brief 获取数组名
// /// @param arr
// /// @return
// std::string getNameofArray(ast_node *arr)
// {
//     assert(arr->node_type == ast_node_type::AST_OP_ARRAY && "Error, not array type");
//     string name = arr->literal_val.digit.id;
//     if (arr->parent->node_type == ast_node_type::AST_OP_DECL_ITEMS)
//     {
//         name += ": " + arr->attr->TypeStr();
//     }
//     else
//     {
//         name += ": Array";
//     }
//     return name;
// }

/// @brief 获取数组的维度数据(如果该维度为空节点，则赋值为-1， 一般这种情况出现在函数形参中)
/// @param arr 数组类型AST节点
/// @return
// std::vector<int> getArrayDimOrd(ast_node *arr)
// {
//     // 先获取 数组节点声明的各个维度数值
//     std::vector<int> dims;
//     for (auto &son : arr->sons)
//     {
//         int num;
//         if (son->node_type == ast_node_type::AST_NULL)
//         {
//             num = -1;
//         }
//         else if (son->node_type == ast_node_type::AST_LEAF_LITERAL_INT)
//         {
//             num = son->literal_val.digit.int32_digit;
//         }
//         else if (son->node_type == ast_node_type::AST_LEAF_LITERAL_UINT)
//         {
//             num = son->literal_val.digit.int32_digit;
//         }
//         else
//         {
//             // 声明时数组的各维度一定要为整数 有符号 或无符号
//             int lino = arr->literal_val.line_no;
//             std::string errormsg = ">>>Error!: the array declare size must be const int! line: " + std::to_string(lino);
//             throw std::invalid_argument(errormsg);
//         }

//         dims.push_back(num);
//     }
//     return dims;
// }