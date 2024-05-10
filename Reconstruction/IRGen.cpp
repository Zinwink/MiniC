/**
 * @file IRGen.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-05-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "IRGen.h"
#include <iostream>

/// @brief 析构函数
IRGen::~IRGen()
{
    module.reset();
    delete scoper;
    scoper = nullptr;
    ast_root = nullptr;
}

/// @brief 构造函数
/// @param root
/// @param _module
IRGen::IRGen(ast_node *root, ModulePtr _module)
{
    ast_root = root;
    scoper = new ScopeMg();
    module = _module;

    // 初始化 AST节点 对应的处理函数哈希表
    // 编译单元
    ast2ir_handers[ast_node_type::AST_OP_COMPILE_UNIT] = &IRGen::ir_CompileUnit;

    // 函数定义， 函数形参, return, call函数调用
    ast2ir_handers[ast_node_type::AST_OP_FUNC_DEF] = &IRGen::ir_func_define;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGen::ir_func_formal_params;
    ast2ir_handers[ast_node_type::AST_OP_RETURN_STATEMENT] = &IRGen::ir_return;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_CALL] = &IRGen::ir_funcall;

    // 一些变量节点 varid  int float
    ast2ir_handers[ast_node_type::AST_LEAF_LITERAL_INT] = &IRGen::ir_leafNode_int;
    ast2ir_handers[ast_node_type::AST_LEAF_LITERAL_FLOAT] = &IRGen::ir_leafNode_float;
    ast2ir_handers[ast_node_type::AST_LEAF_VAR_ID] = &IRGen::ir_leafNode_var;

    // AST中的block节点
    ast2ir_handers[ast_node_type::AST_OP_BLOCK] = &IRGen::IRGen::ir_block;

    // AST中的变量声明  declarationItems
    ast2ir_handers[ast_node_type::AST_OP_DECL_ITEMS] = &IRGen::ir_declItems;

    // AST中的赋值Assign节点
    ast2ir_handers[ast_node_type::AST_OP_ASSIGN] = &IRGen::ir_assign;

    // AST中的运算节点 + - *  / % 等等
    ast2ir_handers[ast_node_type::AST_OP_ADD] = &IRGen::ir_add;
    ast2ir_handers[ast_node_type::AST_OP_SUB] = &IRGen::ir_sub;
    ast2ir_handers[ast_node_type::AST_OP_MUL] = &IRGen::ir_mul;
    ast2ir_handers[ast_node_type::AST_OP_DIV] = &IRGen::ir_div;
    ast2ir_handers[ast_node_type::AST_OP_MOD] = &IRGen::ir_mod;

    // 条件相关的节点
    ast2ir_handers[ast_node_type::AST_OP_COND_LESS] = &IRGen::ir_cmp_less;
    ast2ir_handers[ast_node_type::AST_OP_COND_GREATER] = &IRGen::ir_cmp_greater;
    ast2ir_handers[ast_node_type::AST_OP_COND_EQU] = &IRGen::ir_cmp_equal;
}

/// @brief 根据AST节点的类型查找相应的函数操作并执行
/// @return nullptr表示运行失败，否则返回node指针
ast_node *IRGen::ir_visit_astnode(ast_node *node, LabelParams blocks)
{
    if (node == nullptr)
        return nullptr;
    auto iter = ast2ir_handers.find(node->node_type);
    bool result;
    if (iter == ast2ir_handers.end())
    {
        // 节点类型找不到对应的操作
        std::cout << "Unkown node type:" << (int)node->node_type << std::endl;
        return nullptr;
    }
    else
    {
        // 在哈希表中能够查找到对应的操作
        result = (this->*(iter->second))(node, blocks);
    }
    if (!result)
        node = nullptr;
    return node;
}

//***************** AST节点对应的翻译操作 **********************

/// @brief 对AST compileUnit的翻译函数
/// @param node 抽象书节点
/// @return 成功 true  失败false
bool IRGen::ir_CompileUnit(ast_node *node, LabelParams blocks)
{
    for (ast_node *son : node->sons)
    {
        ast_node *sonNode = ir_visit_astnode(son, blocks);
        if (sonNode == nullptr)
        {
            return false;
        }
    }
    return true;
}

/// @brief AST  function define节点对应的函数操作
/// @param node
/// @return
bool ir_func_define(ast_node *node, LabelParams blocks)
{
    string funcname = node->literal_val.digit.id; // 函数名
    FuncPtr fun = Function::get(node->attr, funcname);
}

//***************** 运行产生线性IR ******************

/// @brief 运行产生线性IR
/// @return
bool IRGen::run()
{
    ast_node *node = ir_visit_astnode(ast_root, {});
    return node != nullptr;
}
