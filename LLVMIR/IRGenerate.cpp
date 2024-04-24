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
#include "Var.h"
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

    // 函数定义， 函数形参, return, call函数调用
    ast2ir_handers[ast_node_type::AST_OP_FUNC_DEF] = &IRGenerate::ir_func_define;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerate::ir_func_formal_params;
    ast2ir_handers[ast_node_type::AST_OP_RETURN_STATEMENT] = &IRGenerate::ir_return;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_CALL] = &IRGenerate::ir_funcall;

    // 一些变量节点 varid  int float
    ast2ir_handers[ast_node_type::AST_LEAF_LITERAL_INT] = &IRGenerate::ir_leafNode_int;
    ast2ir_handers[ast_node_type::AST_LEAF_LITERAL_FLOAT] = &IRGenerate::ir_leafNode_float;
    ast2ir_handers[ast_node_type::AST_LEAF_VAR_ID] = &IRGenerate::ir_leafNode_var;

    // AST中的block节点
    ast2ir_handers[ast_node_type::AST_OP_BLOCK] = &IRGenerate::IRGenerate::ir_block;

    // AST中的变量声明  declarationItems
    ast2ir_handers[ast_node_type::AST_OP_DECL_ITEMS] = &IRGenerate::ir_declItems;

    // AST中的赋值Assign节点
    ast2ir_handers[ast_node_type::AST_OP_ASSIGN] = &IRGenerate::ir_assign;

    // AST中的运算节点 + - *  / % 等等
    ast2ir_handers[ast_node_type::AST_OP_ADD] = &IRGenerate::ir_add;
    ast2ir_handers[ast_node_type::AST_OP_SUB] = &IRGenerate::ir_sub;
    ast2ir_handers[ast_node_type::AST_OP_MUL] = &IRGenerate::ir_mul;
    ast2ir_handers[ast_node_type::AST_OP_DIV] = &IRGenerate::ir_div;
    ast2ir_handers[ast_node_type::AST_OP_MOD] = &IRGenerate::ir_mod;
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

//****************** 下面是一些AST节点对应的操作函数 ***********

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
        if (son->node_type == ast_node_type::AST_OP_BLOCK)
            node->CodesIr->extendIRBack(*(son->CodesIr)); // 当前node节点加入子节点上传的IR
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
        string formalName = son->literal_val.digit.id;
        FunFormalParam *formalp = new FunFormalParam(formalName, son->val_type);
        scoper->curFun()->addFormalParam(formalp); // 加入当前函数的形参列表
        // 根据形参创建相应名字的变量 放入声明查询哈希表中
        scoper->curFun()->getFuncTab()->newDeclVar(formalp->Value());
        // 如果有参数，则按照C语言函数规则，应该有拷贝操作
        IRInst *alloc = new AllocaIRInst(formalp->Value());         // 声明用于存储形参拷贝的变量指令
        scoper->curFun()->getIRBlock()->irfront().push_back(alloc); // 加入该alloc指令
        IRInst *asgn = new AssignIRInst(formalp->Value(), formalp);
        scoper->curFun()->getIRBlock()->irback().push_back(asgn);
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

/// @brief AST函数调用节点对应的操作
/// @param node
/// @return
bool IRGenerate::ir_funcall(ast_node *node)
{
    // 先从全局符号表中查找该函数
    string funname = node->literal_val.digit.id; // 函数名
    Function *fun = scoper->globalTab()->findDeclFun(funname);
    if (fun == nullptr)
    { // 未找到该函数
        std::cout << funname << "undeclared in this scope, line number:" << node->literal_val.line_no << std::endl;
        return false;
    }
    else // 找到了该函数
    {
        ast_node *realparams = node->sons[0];                                // 实参列表节点
        std::vector<FunFormalParam *> &formalparms = fun->getFormalParams(); // 形参列表
        if (formalparms.size() != realparams->sons.size())
        {
            // 形参列表长度和实参列表长度不等  失败
            std::cout << "the arguments' num is not equal to function:" << funname << ", line number:" << node->literal_val.line_no << std::endl;
            return false;
        }
        // 下面进行遍历参数，目前只完成int 不考虑转型
        std::vector<Var *> srcVars;
        for (uint32_t i = 0; i < realparams->sons.size(); i++)
        {
            ast_node *result = ir_visit_astnode(realparams->sons[i]);
            if (result == nullptr)
                return false;
            if (result->vari->getValType() != formalparms[i]->getValType()) // 形参类型和实参类型不同
            {
                std::cout << "warning: the real param is not match the formal param type, line number:" << node->literal_val.line_no << std::endl;
                return false;
            }
            srcVars.push_back(result->vari);
            node->CodesIr->extendIRBack(*(result->CodesIr)); // 上传形参节点的IR指令
        }
        if (fun->getRetType().type == BasicValueType::TYPE_VOID)
        {
            IRInst *inst = new CallIRInst(fun, nullptr, srcVars);
            node->CodesIr->irback().push_back(inst);
        }
        else
        {
            Var *tmp = newTempVar(fun->getRetType()); // 调用函数后得到的结果变量
            node->vari = tmp;                         // 该节点的产生的临时结果
            IRInst *inst = new CallIRInst(fun, tmp, srcVars);
            node->CodesIr->irback().push_back(inst);
        }
    }
    return true;
}

/// @brief AST中 return 节点对应的函数操作
/// @param node
/// @return
bool IRGenerate::ir_return(ast_node *node)
{
    // 检查返回类型是否和当前函数匹配
    if (node->sons.size() == 0)
    {
        // 无孩子  void类型
        if (scoper->curFun()->getRetType().type != BasicValueType::TYPE_VOID)
        {
            std::cout << "the return type void doesn't match the function: '"
                      << scoper->curFun()->getName() << "' return type:" << scoper->curFun()->getRetType().toString() << std::endl;
            return false;
        }
        IRInst *ret = new ReturnIRInst(nullptr);
        node->CodesIr->irback().push_back(ret); // 加入指令
        return true;
    }
    else
    { // 有孩子 有返回值
        ast_node *sonNode = node->sons[0];
        ast_node *result = ir_visit_astnode(sonNode);
        if (result == nullptr)
        {
            return false;
        }

        node->CodesIr->extendIRBack(*(sonNode->CodesIr)); // 加入子节点的IR
        IRInst *ret = new ReturnIRInst(sonNode->vari);    // 子节点对应的 ret指令
        node->CodesIr->irback().push_back(ret);           // 加入ret 指令
    }
    return true;
}

/// @brief AST   DeclarationItems节点对应的操作函数
/// @param node
/// @return
bool IRGenerate::ir_declItems(ast_node *node)
{
    for (auto &son : node->sons)
    {
        ast_node *result = ir_visit_astnode(son);
        if (result == nullptr)
        {
            return false;
        }
        if (result->node_type == ast_node_type::AST_LEAF_VAR_ID)
        {
            // 变量节点
            if (result->vari->getIsGloabl())
            { // 是全局变量的声明
                IRInst *inst = new GlobalVarIRInst(result->vari);
                scoper->globalTab()->varInsts().push_back(inst);
            }
            else
            { // 函数中的局部变量
                IRInst *inst = new AllocaIRInst(result->vari);
                scoper->curFun()->getIRBlock()->irfront().push_back(inst);
            }
        }
        else
        {
            // 赋值节点  将子节点IR上传
            node->CodesIr->extendIRBack(*(result->CodesIr));
        }
    }
    return true;
}

/// @brief AST  ASSIGN赋值节点对应的函数操作
/// @param node
/// @return
bool IRGenerate::ir_assign(ast_node *node)
{
    ast_node *left = ir_visit_astnode(node->sons[0]);
    if (left == nullptr)
        return false;
    ast_node *right = ir_visit_astnode(node->sons[1]);
    if (right == nullptr)
        return false;
    if (!scoper->curTab()->isGlobalTab())
    {
        if (node->sons[1]->node_type != ast_node_type::AST_LEAF_VAR_ID)
        {
            IRInst *inst = new AssignIRInst(left->vari, right->vari);
            node->CodesIr->extendIRBack(*(right->CodesIr));
            node->CodesIr->irback().push_back(inst);
        }
        else
        {
            ValueType tmpType(right->vari->getValType());
            Var *tmp = newTempVar(tmpType);
            IRInst *load = new LoadIRInst(right->vari, tmp);
            IRInst *assign = new AssignIRInst(left->vari, tmp);
            node->CodesIr->extendIRBack(*(right->CodesIr));
            node->CodesIr->irback().push_back(load);
            node->CodesIr->irback().push_back(assign);
        }
    }
    else
    {
        int32_t value = right->vari->int32Value();
        left->vari->int32Value() = value;
    }

    return true;
}

/// @brief AST 加法操作节点对应的函数操作
/// @param node
/// @return
bool IRGenerate::ir_add(ast_node *node)
{
    ast_node *left = ir_visit_astnode(node->sons[0]);
    if (left == nullptr)
        return false;
    ast_node *right = ir_visit_astnode(node->sons[1]);
    if (left == nullptr)
        return false;
    if (!scoper->curTab()->isGlobalTab())
    {
        // 产生的临时变量结果暂时设置为int，存放地址暂时为MEMORY 还未实现类型转换 @todo
        ValueType temp_valType(BasicValueType::TYPE_INT32);
        Var *tmp = newTempVar(temp_valType);
        node->vari = tmp;
        node->CodesIr->extendIRBack(*(left->CodesIr));
        node->CodesIr->extendIRBack(*(right->CodesIr));
        // 暂时为 int 加法，后继类型未实现 @todo
        IRInst *add = new BinaryIRInst(IROperator::IR_ADD_INT, tmp, left->vari, right->vari);
        node->CodesIr->irback().push_back(add); // 加入指令
    }
    else
    {
        // 是全局符号表
        int32_t leftval = left->vari->int32Value();
        int32_t rightval = right->vari->int32Value();
        Var *tmp = new Var((leftval + rightval));
        node->vari = tmp;
    }
    return true;
}

/// @brief AST 减法节点对应的操作
/// @param node
/// @return
bool IRGenerate::ir_sub(ast_node *node)
{ //  TODO
    ast_node *left = ir_visit_astnode(node->sons[0]);
    if (left == nullptr)
        return false;
    ast_node *right = ir_visit_astnode(node->sons[1]);
    if (left == nullptr)
        return false;
    if (!scoper->curTab()->isGlobalTab())
    {
        // 产生的临时变量结果暂时设置为int，存放地址暂时为MEMORY 还未实现类型转换 @todo
        ValueType temp_valType(BasicValueType::TYPE_INT32);
        Var *tmp = newTempVar(temp_valType);
        node->vari = tmp;
        node->CodesIr->extendIRBack(*(left->CodesIr));
        node->CodesIr->extendIRBack(*(right->CodesIr));
        // 暂时为 int 加法，后继类型未实现 @todo
        IRInst *sub = new BinaryIRInst(IROperator::IR_SUB_INT, tmp, left->vari, right->vari);
        node->CodesIr->irback().push_back(sub); // 加入指令
    }
    else
    {
        // 是全局符号表
        int32_t leftval = left->vari->int32Value();
        int32_t rightval = right->vari->int32Value();
        Var *tmp = new Var((leftval - rightval));
        node->vari = tmp;
    }

    return true;
}

/// @brief AST 乘法节点对应的操作
/// @param node
/// @return
bool IRGenerate::ir_mul(ast_node *node)
{
    ast_node *left = ir_visit_astnode(node->sons[0]);
    if (left == nullptr)
        return false;
    ast_node *right = ir_visit_astnode(node->sons[1]);
    if (left == nullptr)
        return false;
    if (!scoper->curTab()->isGlobalTab())
    {
        // 产生的临时变量结果暂时设置为int，存放地址暂时为MEMORY 还未实现类型转换 @todo
        ValueType temp_valType(BasicValueType::TYPE_INT32);
        Var *tmp = newTempVar(temp_valType);
        node->vari = tmp;
        node->CodesIr->extendIRBack(*(left->CodesIr));
        node->CodesIr->extendIRBack(*(right->CodesIr));
        // 暂时为 int 加法，后继类型未实现 @todo
        IRInst *mul = new BinaryIRInst(IROperator::IR_MUL_INT, tmp, left->vari, right->vari);
        node->CodesIr->irback().push_back(mul); // 加入指令
    }
    else
    {
        // 是全局符号表
        int32_t leftval = left->vari->int32Value();
        int32_t rightval = right->vari->int32Value();
        Var *tmp = new Var((leftval * rightval));
        node->vari = tmp;
    }
    return true;
}

/// @brief AST 除法节点对应的操作
/// @param node
/// @return
bool IRGenerate::ir_div(ast_node *node)
{
    ast_node *left = ir_visit_astnode(node->sons[0]);
    if (left == nullptr)
        return false;
    ast_node *right = ir_visit_astnode(node->sons[1]);
    if (left == nullptr)
        return false;
    if (!scoper->curTab()->isGlobalTab())
    {
        // 产生的临时变量结果暂时设置为int，存放地址暂时为MEMORY 还未实现类型转换 @todo
        ValueType temp_valType(BasicValueType::TYPE_INT32);
        Var *tmp = newTempVar(temp_valType);
        node->vari = tmp;
        node->CodesIr->extendIRBack(*(left->CodesIr));
        node->CodesIr->extendIRBack(*(right->CodesIr));
        // 暂时为 int 加法，后继类型未实现 @todo
        IRInst *div = new BinaryIRInst(IROperator::IR_DIV_INT, tmp, left->vari, right->vari);
        node->CodesIr->irback().push_back(div); // 加入指令
    }
    else
    {
        // 是全局符号表
        int32_t leftval = left->vari->int32Value();
        int32_t rightval = right->vari->int32Value();
        Var *tmp = new Var((leftval / rightval));
        node->vari = tmp;
    }
    return true;
}

/// @brief AST 取余节点对应的操作
/// @param node
/// @return
bool IRGenerate::ir_mod(ast_node *node)
{
    ast_node *left = ir_visit_astnode(node->sons[0]);
    if (left == nullptr)
        return false;
    ast_node *right = ir_visit_astnode(node->sons[1]);
    if (left == nullptr)
        return false;
    if (!scoper->curTab()->isGlobalTab())
    { // 当前不是全局符号表
        // 产生的临时变量结果暂时设置为int，存放地址暂时为MEMORY 还未实现类型转换 @todo
        ValueType temp_valType(BasicValueType::TYPE_INT32);
        Var *tmp = newTempVar(temp_valType);
        node->vari = tmp;
        node->CodesIr->extendIRBack(*(left->CodesIr));
        node->CodesIr->extendIRBack(*(right->CodesIr));
        // 暂时为 int 加法，后继类型未实现 @todo
        IRInst *mod = new BinaryIRInst(IROperator::IR_MOD_INT, tmp, left->vari, right->vari);
        node->CodesIr->irback().push_back(mod); // 加入指令
    }
    else
    { // 是全局符号表
        int32_t leftval = left->vari->int32Value();
        int32_t rightval = right->vari->int32Value();
        Var *tmp = new Var((leftval % rightval));
        node->vari = tmp;
    }

    return true;
}

/// @brief 对于int字面量AST节点的操作 AST_LEAF_LITERAL_INT,
/// @param node AST int字面量节点
/// @return true成功 false失败
bool IRGenerate::ir_leafNode_int(ast_node *node)
{
    int32_t intdigit = node->literal_val.digit.int32_digit;
    Var *leafint = new Var(intdigit);
    node->vari = leafint;
    if (node->vari == nullptr)
        return false;
    return true;
}

/// @brief 对于float字面量AST节点的操作 AST_LEAF_LITERAL_FLOAT
/// @param node AST float字面量节点
/// @return
bool IRGenerate::ir_leafNode_float(ast_node *node)
{
    float floatdigit = node->literal_val.digit.float_digit;
    Var *leaffloat = new Var(floatdigit);
    node->vari = leaffloat;
    if (node->vari == nullptr)
        return false;
    return true;
}

/// @brief 对于AST_LEAF_VAR_ID(变量)的函数操作
/// @param node
/// @return
bool IRGenerate::ir_leafNode_var(ast_node *node)
{
    // 对于 用户定义的变量 对于此节点的访问需要看父节点的相关性质
    // var的产生只能在DeclarationItems节点管理下产生。其他情况下只是进行查找
    ast_node_type paretType = node->parent->node_type;
    string varName = node->literal_val.digit.id; // 获取变量名
    if (paretType == ast_node_type::AST_OP_DECL_ITEMS)
    {
        Var *result = scoper->curTab()->findDeclVarOfCurTab(varName); // 查找
        // 父节点为DeclareItems声明节点
        if (result == nullptr)
        {
            // 未找到 表示可以定义
            Var *declvar = new Var(varName, node->parent->val_type); // 生成该变量
            node->vari = declvar;                                    // AST指向该变量供之后访问
            // 下面将该声明变量加入到当前作用域表中
            scoper->curTab()->newDeclVar(declvar);
        }
        else
        { // 在本作用域中找到已经声明该变量 打印错误
            std::cout << "[error] redeclaration of '" << varName
                      << "' ,line number:" << node->literal_val.line_no << std::endl;
            return false; // 失败
        }
    }
    else
    {
        // 父节点不是DeclItems节点，表示该变量被使用，只需进行查找(查找将包括当前作用域以及父作用域)即可
        Var *result = scoper->curTab()->findDeclVar(varName);
        if (result != nullptr)
        {
            // 表示找到，使用的变量已经声明
            node->vari = result; // AST节点指向该变量，供后继使用
            // 由于是被使用，除了赋值操作外，其他的运算如 +- * /以及return 等都需要使用load取出该数
            if (paretType != ast_node_type::AST_OP_ASSIGN && !scoper->curTab()->isGlobalTab())
            {
                Var *tmp = newTempVar(result->getValType()); // 创建临时变量 类型为搜索到的该变量的类型
                node->vari = tmp;                            // 更新为临时变量
                IRInst *load = new LoadIRInst(result, tmp);
                node->CodesIr->irback().push_back(load);
                return true;
            }
            if (paretType != ast_node_type::AST_OP_ASSIGN && scoper->curTab()->isGlobalTab())
            {
                // 全局符号表  出现在运算符号下的 var变量
                if (result->getVarTag() != VarTag::CONST_VAR)
                {
                    // 不是常量类型
                    std::cout << "[error] expression must have a constant value, line number:" << node->literal_val.line_no << std::endl;
                    return false;
                }
            }
        }
        else
        { // 未找到 ，未声明
            std::cout << "[error] '" << varName << "' undeclared,line number:" << node->literal_val.line_no << std::endl;
            return false;
        }
    }
    return true;
}

//****************** 下面是一运行产生线性IR的一些函数 ***********

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
        for (auto &globalvarInst : scoper->globalTab()->varInsts())
        {
            string str;
            str = globalvarInst->toString(str, nullptr);
            file << str;
            file << "\n";
        }
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