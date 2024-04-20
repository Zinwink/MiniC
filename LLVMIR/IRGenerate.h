/**
 * @file IRGenerate.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief  IR指令产生管理
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "ScopeMg.h"
#include "AST.h"

class IRGenerate
{
private:
    /// @brief 作用域管理
    ScopeMg *scoper;

    /// @brief 抽象语法树根节点
    ast_node *root;

    /// @brief AST的节点操作函数指针
    typedef bool (IRGenerate::*ast2ir_handler_t)(ast_node *);

    /// @brief 节点类型--函数操作的对应哈希表
    std::unordered_map<ast_node_type, ast2ir_handler_t> ast2ir_hander;

private: // 一些抽象语法树节点对应的操作函数
    /// @brief 对AST compileUnit的翻译函数
    /// @param node 抽象书节点
    /// @return 成功 true  失败false
    bool ir_CompileUnit(ast_node *node);

    /// @brief AST  function define节点对应的函数操作
    /// @param node
    /// @return
    bool ir_func_define(ast_node *node);

    /// @brief AST  函数形参列表节点对应的操作函数
    /// @param node
    /// @return
    bool ir_func_formal_params(ast_node *node);

    /// @brief AST中block节点对应的函数操作
    /// @param node
    /// @return
    bool ir_block(ast_node *node);

    /// @brief AST中 return 节点对应的函数操作
    /// @param node
    /// @return
    bool ir_return(ast_node *node);

    /// @brief AST   DeclarationItems节点对应的操作函数
    /// @param node
    /// @return
    bool ir_declItems(ast_node *node);

    /// @brief AST  ASSIGN赋值节点对应的函数操作
    /// @param node
    /// @return
    bool ir_assign(ast_node *node);

    /// @brief AST 加法操作节点对应的函数操作
    /// @param node
    /// @return
    bool ir_add(ast_node *node);

public:
    /// @brief 构造函数
    /// @param _scop 作用域符号表管理
    /// @param _root 抽象语法树指针
    IRGenerate(ScopeMg *_scop, ast_node *_root);

    /// @brief 析构函数
    ~IRGenerate() = default;

    /// @brief 运行产生线性IR指令
    /// @return 产生成功true,产生失败false
    bool run();

    /// @brief 将IR指令对象转化为字符串输出到文件中
    /// @param irpath 文件路径
    void IR2Str(const std::string &irpath);
};
