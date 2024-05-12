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
        ast_node *sonNode = ir_visit_astnode(son, {});
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
bool IRGen::ir_func_define(ast_node *node, LabelParams blocks)
{
    string funcname = node->literal_val.digit.id; // 函数名
    FuncPtr fun = Function::get(std::move(node->attr), funcname);
    // 创建entry函数入口基本块
    BasicBlockPtr block = BasicBlock::get(fun, "entry"); // 每个function一定有一个entry基本快
    fun->AddBBlockBack(block);                           // 加入函数内
    fun->AllocaIter() = block->begin();                  // 设置函数的AllocaInst的插入点
    scoper->curFun() = fun;                              // 标记当前记录函数
    scoper->pushTab(FuncTab::get());                     // 创建函数的符号表并加入到管理器scoper中
    for (auto &son : node->sons)
    {
        ast_node *result = ir_visit_astnode(node, {block}); // 将函数基本块传参至下游节点
        if (result == nullptr)
        {
            scoper->curFun() = nullptr;
            return false;
        }
    }
    // 结束翻译函数时curFun赋值为nullptr,函数符号表弹出栈
    scoper->curFun() = nullptr;
    scoper->popTab(); // 弹栈
    return true;
}

/// @brief AST  函数形参列表节点对应的操作函数
/// @param node
/// @return
bool IRGen::ir_func_formal_params(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST中block节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_block(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST中 return 节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_return(ast_node *node, LabelParams blocks)
{
    
    return true;
}

/// @brief AST函数调用节点对应的操作
/// @param node
/// @return
bool IRGen::ir_funcall(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST  ASSIGN赋值节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_assign(ast_node *node, LabelParams blocks)
{

    return true;
}

/// @brief AST   DeclarationItems节点对应的操作函数
/// @param node
/// @return
bool IRGen::ir_declItems(ast_node *node, LabelParams blocks)
{
    for (auto &son : node->sons)
    {
        ast_node *result = ir_visit_astnode(node, blocks);
        if (result == nullptr)
        {
            return false;
        }
    }
    return true;
}

/// @brief AST 加法操作节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_add(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST 减法节点对应的操作
/// @param node
/// @return
bool IRGen::ir_sub(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST 乘法节点对应的操作
/// @param node
/// @return
bool IRGen::ir_mul(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST 除法节点对应的操作
/// @param node
/// @return
bool IRGen::ir_div(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST 取余节点对应的操作
/// @param node
/// @return
bool IRGen::ir_mod(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST < 节点对应的操作
/// @param node
/// @return
bool IRGen::ir_cmp_less(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST  > 节点对应的操作
/// @param node
/// @return
bool IRGen::ir_cmp_greater(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief AST == 节点对应的操作
/// @param node
/// @return
bool IRGen::ir_cmp_equal(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief 对于AST_LEAF_VAR_ID(变量)的函数操作
/// @param node
/// @return
bool IRGen::ir_leafNode_var(ast_node *node, LabelParams blocks)
{
    string name = node->literal_val.digit.id; // 变量名
    // 判断变量 可能是声明区域下的，也可能是使用区域下的
    if (node->parent->node_type == ast_node_type::AST_OP_DECL_ITEMS)
    {                                                             // 变量的父节点是declare_items
        ValPtr val = scoper->curTab()->findDeclVarOfCurTab(name); // 查找
        if (val != nullptr)
        { // 查找到该value
            std::cout << ">>>Error:the variable " << name << " is redifined! line:" << node->literal_val.line_no << std::endl;
            return false;
        }
        if (scoper->curTab()->isGlobalTab())
        { // 全局变量声明
            GlobalVariPtr g = GlobalVariable::get(std::move(node->attr), name);
            module->addGlobalVar(g);         // 加入全局变量列表
            scoper->curTab()->newDeclVar(g); // 符号表中加入相应的声明
        }
        else
        {
            // 非全局变量声明
            AllocaInstPtr alloca = AllocaInst::get(name, std::move(node->attr));
            scoper->curTab()->newDeclVar(alloca);       //  将声明变量加入当前符号表中
            scoper->curFun()->insertAllocaInst(alloca); // 将allocaInst加入到指令基本块中
        }
    }
    else
    {
        // 不直接在declitems下的节点(被使用)
        ValPtr val = scoper->curTab()->findDeclVar(name); // 查找
        if (val == nullptr)
        {
            std::cout << ">>>Error:the variable " << name << " is not declared! line:" << node->literal_val.line_no << std::endl;
            return false;
        }
        node->value = val;
    }

    return true;
}

/// @brief 对于int字面量AST节点的操作 AST_LEAF_LITERAL_INT,
/// @param node AST int字面量节点
/// @return true成功 false失败
bool IRGen::ir_leafNode_int(ast_node *node, LabelParams blocks)
{
    int num = node->literal_val.digit.int32_digit; // 获取常数数值
    ConstantIntPtr conInt = ConstantInt::get(32, true);
    conInt->setValue(num);
    node->value = std::move(conInt);
    return true;
}

/// @brief 对于float字面量AST节点的操作 AST_LEAF_LITERAL_FLOAT
/// @param node AST float字面量节点
/// @return
bool IRGen::ir_leafNode_float(ast_node *node, LabelParams blocks)
{
    return true;
}

//***************** 运行产生线性IR ******************

/// @brief 运行产生线性IR
/// @return
bool IRGen::run()
{
    ast_node *node = ir_visit_astnode(ast_root, {});
    return node != nullptr;
}
