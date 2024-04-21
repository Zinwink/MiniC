/**
 * @file IRGenerate.cpp
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief
 * @version 1.0
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "IRGenerate.h"
#include "BlockTempTab.h"
#include <iostream>
#include <fstream>

/// @brief 构造函数
/// @param _scop 作用域符号表管理
/// @param _root 抽象语法树指针
IRGenerate::IRGenerate(ScopeMg *_scop, ast_node *_root)
{
    scoper = _scop;
    root = _root;
    // 下面初始化AST节点类型--操作函数指针的哈希映射表

    // 编译单元
    ast2ir_handers[ast_node_type::AST_OP_COMPILE_UNIT] = &IRGenerate::ir_CompileUnit;

    // 函数定义， 函数形参, return
    ast2ir_handers[ast_node_type::AST_OP_FUNC_DEF] = &IRGenerate::ir_func_define;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerate::ir_func_formal_params;
    ast2ir_handers[ast_node_type::AST_OP_RETURN_STATEMENT] = &IRGenerate::ir_return;

    // AST中的block节点
    ast2ir_handers[ast_node_type::AST_OP_BLOCK] = &IRGenerate::IRGenerate::ir_block;

    // AST中的变量声明  declarationItems
    ast2ir_handers[ast_node_type::AST_OP_DECL_ITEMS] = &IRGenerate::ir_declItems;

    // AST中的赋值Assign节点
    ast2ir_handers[ast_node_type::AST_OP_ASSIGN] = &IRGenerate::ir_assign;

    // AST中的运算节点 + - *  / % 等等
    ast2ir_handers[ast_node_type::AST_OP_ADD] = &IRGenerate::ir_add;
}

/// @brief 根据AST节点的类型查找相应的函数操作并执行
/// @return nullptr表示运行失败，否则返回node指针
ast_node *IRGenerate::ir_visit_astnode(ast_node *node)
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
        result = (this->*(iter->second))(node);
    }
    if (!result)
        node = nullptr;
    return node;
}

/// @brief 对AST compileUnit的翻译函数
/// @param node 抽象书节点
/// @return 成功 true  失败false
bool IRGenerate::ir_CompileUnit(ast_node *node)
{

    for (ast_node *son : node->sons)
    {
        ast_node *sonNode = ir_visit_astnode(son);
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
bool IRGenerate::ir_func_define(ast_node *node)
{
    string funcname = node->literal_val.digit.id;
    Function *fun = new Function(funcname, node->val_type);
    scoper->globalTab()->newDeclFun(fun); // 全局符号表添加相关函数
    scoper->setCurFun(fun);               // 设置当前函数
    // 遍历访问字节点(形参节点 block节点)
    for (auto son : node->sons)
    {
        ast_node *sonNode = ir_visit_astnode(son);
        if (sonNode == nullptr)
        {
            return false;
        }
    }
    fun->getIRBlock()->extendIRBack(*(node->CodesIr)); // 将block中的IR指令加入当前函数中
    scoper->setCurFun(nullptr);                        // 该函数定义翻译完后 设置为null
    return true;
}

/// @brief AST  函数形参列表节点对应的操作函数
/// @param node
/// @return
bool IRGenerate::ir_func_formal_params(ast_node *node)
{
    for (auto son : node->sons)
    {
        string formalName = node->literal_val.digit.id;
        FunFormalParam *formalp = new FunFormalParam(formalName, son->val_type);
        scoper->curFun()->addFormalParam(formalp); // 加入当前函数的形参列表
    }
    return true;
}

/// @brief AST中block节点对应的函数操作
/// @param node
/// @return
bool IRGenerate::ir_block(ast_node *node)
{
    // 每次遇见一个block时会向scoper管理栈中压入相关的符号表，模拟作用域
    // 根据block的父节点进行判断block是函数的全体block 还是函数内部的小型作用域
    if (node->parent->node_type == ast_node_type::AST_OP_FUNC_DEF && scoper->curFun() != nullptr)
    {
        // 是函数定义的大block
        scoper->pushTab(scoper->curFun()->getFuncTab()); // 将函数的符号表加入其中
    }
    else
    {
        // 是BlockTempTab  进行创建并压栈
        BaseSymTab *blocktemp = new BlockTempTab();
        scoper->pushTab(blocktemp);
    }
    // 下面遍历block下的子节点
    for (ast_node *son : node->sons)
    {
        ast_node *sonNode = ir_visit_astnode(son);
        if (sonNode == nullptr)
        {
            return false;
        }
        node->CodesIr->extendIRBack(*(son->CodesIr)); // block下的孩子节点IR指令上传
    }
    // block访问结束后弹出
    scoper->popTab();
    return true;
}

/// @brief AST中 return 节点对应的函数操作
/// @param node
/// @return
bool IRGenerate::ir_return(ast_node *node)
{
    // 检查返回类型是否和当前函数匹配  TODO

    if (node->sons.size() == 0)
    {
        // 无孩子  void类型
        IRInst *ret = new ReturnIRInst(nullptr);
        node->CodesIr->irback().push_back(ret); // 加入指令
        return true;
    }
    else
    { // 有孩子 有返回值
        ast_node *sonNode = node->sons[0];
        if (sonNode->node_type == ast_node_type::AST_LEAF_VAR_ID || sonNode->node_type == ast_node_type::AST_LEAF_LITERAL_INT)
        {
            // 返回值为一个变量类型
            string vname = sonNode->literal_val.digit.id;
            Var *var = scoper->curTab()->findDeclVar(vname);
            if (var == nullptr)
            {
                // 从符号表中没有找到相关声明 定义
                std::cout << "undifined variable, line:" << sonNode->literal_val.line_no << std::endl;
                return false;
            }
            else
            {
                // 能查找到
                IRInst *inst = new ReturnIRInst(var);
                node->CodesIr->irback().push_back(inst);
                return true;
            }
        }
        else if (sonNode->node_type == ast_node_type::AST_LEAF_LITERAL_INT)
        {
            // 字面常量类型
            Var *var = new Var(sonNode->literal_val.digit.int32_digit);
            IRInst *inst = new ReturnIRInst(var);
            node->CodesIr->irback().push_back(inst);
            return true;
        }
        else
        {
            // 表达式类型
            ast_node *visitN = ir_visit_astnode(sonNode);
            if (visitN == nullptr)
            {
                return false;
            }
            node->CodesIr->extendIRBack(*(sonNode->CodesIr));          // 加入表达式指令
            Var *vartmp = sonNode->CodesIr->irback().back()->getDst(); // 获取最后一条指令的目的操作数
            IRInst *inst = new ReturnIRInst(vartmp);
            node->CodesIr->irback().push_back(inst); // 加入ret指令
        }
    }
    return true;
}

/// @brief AST   DeclarationItems节点对应的操作函数
/// @param node
/// @return
bool IRGenerate::ir_declItems(ast_node *node)
{
    // 是否是全局声明
    bool isglobalDecl = node->parent->node_type == ast_node_type::AST_OP_COMPILE_UNIT;
    for (auto son : node->sons)
    {
        if (son->node_type == ast_node_type::AST_LEAF_VAR_ID)
        {
            // 子节点是变量
            string vname = son->literal_val.digit.id;
            Var *var = scoper->curTab()->findDeclVarOfCurTab(vname); // 查找本作用域表，踊跃确定是否重定义
            if (var != nullptr)
            {
                // 本作用域查找到了该变量的声明  重定义错误
                std::cout << "redefined variable,line: " << son->literal_val.line_no << std::endl;
                return false;
            }
            else
            {
                // 未找到 未重定义声明
                var = new Var(vname, son->val_type, isglobalDecl);
                if (isglobalDecl)
                    scoper->globalTab()->getVarList().push_back(var);
                else
                {
                    // 非全局 在函数中
                    scoper->curFun()->getFuncTab()->newDeclVar(var);
                    IRInst *inst = new AllocaIRInst(var);
                    scoper->curFun()->getIRBlock()->irfront().push_back(inst); // 加入到当前函数的irfront部分中
                }
            }
        }
        else
        {
            // 子节点是赋值类型
            ast_node *tmp = ir_visit_astnode(son);
            if (tmp == nullptr)
            {
                return false;
            }
            // 全局
            string vname = son->sons[0]->literal_val.digit.id;
            Var *var = scoper->curTab()->findDeclVarOfCurTab(vname); // 查找本作用域表，踊跃确定是否重定义
            if (var != nullptr)
            {
                // 本作用域查找到了该变量的声明  重定义错误
                std::cout << "redefined variable,line: " << son->literal_val.line_no << std::endl;
                return false;
            }
            else
            {
                var = new Var(vname, son->sons[0]->val_type, isglobalDecl);
                if (isglobalDecl)
                {
                    scoper->globalTab()->getVarList().push_back(var);
                }
                else
                {
                    scoper->curFun()->getFuncTab()->newDeclVar(var);
                    IRInst *inst = new AllocaIRInst(var);
                    scoper->curFun()->getIRBlock()->irfront().push_back(inst);
                }
            }
            node->CodesIr->extendIRBack(*(son->CodesIr)); // 子节点IR上传
        }
    }
    return true;
}

/// @brief AST  ASSIGN赋值节点对应的函数操作
/// @param node
/// @return
bool IRGenerate::ir_assign(ast_node *node)
{
    ast_node *left = node->sons[0];
    ast_node *right = node->sons[1];
    string leftname = left->literal_val.digit.id;
    Var *var = scoper->curTab()->findDeclVar(leftname);
    if (var == nullptr)
    { // 未找到
        std::cout << "undefined variable, line: " << left->literal_val.line_no << std::endl;
        return false;
    }
    else
    {
        // 找到
        ast_node *tmp = ir_visit_astnode(right);
        if (tmp == nullptr)
        {
            return false;
        }
        Var *dstv = right->CodesIr->irback().back()->getDst(); // 获取最后一条指令的目的操作数
        node->CodesIr->extendIRBack(*(right->CodesIr));
        IRInst *inst = new AssignIRInst(var, dstv);
        node->CodesIr->irback().push_back(inst);
    }
    return true;
}

/// @brief AST 加法操作节点对应的函数操作
/// @param node
/// @return
bool IRGenerate::ir_add(ast_node *node)
{
    return true;
}

/// @brief 运行产生线性IR指令
/// @return 产生成功true,产生失败false
bool IRGenerate ::run()
{
    ast_node *node = ir_visit_astnode(root);
    return node != nullptr;
}

/// @brief 将IR指令对象转化为字符串输出到文件中
/// @param irpath 文件路径
void IRGenerate::IR2Str(const std::string &irpath)
{
    std::ofstream file(irpath);
    if (file.is_open())
    {
        for (auto &fun : scoper->globalTab()->getFunList())
        {
            string str;
            str = fun->toString(str);
            file << str;
        }
    }
    else
    {
        // 文件打开失败
        std::cerr << "output IR instruction to" << irpath << " failed!" << std::endl;
    }
}