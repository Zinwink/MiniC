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
#include "DerivedInst.h"
#include "BlockTempTab.h"
#include "FuncTab.h"
#include "Function.h"
#include <iostream>
#include "DerivedTypes.h"
#include "InitValueList.h"

/// @brief 析构函数
IRGen::~IRGen()
{
    module.reset();
    delete scoper;
    scoper = nullptr;
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
    ast2ir_handers[ast_node_type::AST_OP_FUNC_DECLARE] = &IRGen::ir_func_declare;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_DEF] = &IRGen::ir_func_define;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGen::ir_func_formal_params;
    ast2ir_handers[ast_node_type::AST_OP_RETURN_STATEMENT] = &IRGen::ir_return;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_CALL] = &IRGen::ir_funcall;

    // 一些变量节点 varid  int float
    ast2ir_handers[ast_node_type::AST_LEAF_LITERAL_INT] = &IRGen::ir_leafNode_int;
    ast2ir_handers[ast_node_type::AST_LEAF_LITERAL_FLOAT] = &IRGen::ir_leafNode_float;
    ast2ir_handers[ast_node_type::AST_LEAF_VAR_ID] = &IRGen::ir_leafNode_var;
    ast2ir_handers[ast_node_type::AST_OP_ARRAY] = &IRGen::ir_leafNode_array;
    ast2ir_handers[ast_node_type::AST_NULL] = &IRGen::ir_leafNode_NULL;

    // AST中的block节点
    ast2ir_handers[ast_node_type::AST_OP_BLOCK] = &IRGen::IRGen::ir_block;

    // AST中的变量声明  declarationItems
    ast2ir_handers[ast_node_type::AST_OP_DECL_ITEMS] = &IRGen::ir_declItems;
    ast2ir_handers[ast_node_type::AST_OP_VAR_DEF] = &IRGen::ir_declVarDef;
    ast2ir_handers[ast_node_type::AST_ARRAY_DEF] = &IRGen::ir_array_def; // 带有数组初始化的节点

    // AST const 修饰
    ast2ir_handers[ast_node_type::AST_OP_CONST_DECL_ITEMS] = &IRGen::ir_const_declItems;
    ast2ir_handers[ast_node_type::AST_OP_CONST_VAR_DEF] = &IRGen::ir_const_declVarDef;
    ast2ir_handers[ast_node_type::AST_CONST_ARRAY_DEF] = &IRGen::ir_const_array_def; // 带有数组初始化的节点

    // AST 初始化列表 只做容器使用
    ast2ir_handers[ast_node_type::AST_ARRAY_INITLIST] = &IRGen::ir_initValueList;
    ast2ir_handers[ast_node_type::AST_CONST_ARRAY_INITLIST] = &IRGen::ir_initValueList;

    // AST中的赋值Assign节点
    ast2ir_handers[ast_node_type::AST_OP_ASSIGN] = &IRGen::ir_assign;

    // AST中的运算节点 + - *  / % 等等
    ast2ir_handers[ast_node_type::AST_OP_NEG] = &IRGen::ir_Negative;
    ast2ir_handers[ast_node_type::AST_OP_ADD] = &IRGen::ir_add;
    ast2ir_handers[ast_node_type::AST_OP_SUB] = &IRGen::ir_sub;
    ast2ir_handers[ast_node_type::AST_OP_MUL] = &IRGen::ir_mul;
    ast2ir_handers[ast_node_type::AST_OP_DIV] = &IRGen::ir_div;
    ast2ir_handers[ast_node_type::AST_OP_MOD] = &IRGen::ir_mod;

    // 条件相关的节点 if  while do while break continue
    ast2ir_handers[ast_node_type::AST_OP_IFSTMT] = &IRGen::ir_if_Stmt;
    ast2ir_handers[ast_node_type::AST_OP_WHILESTMT] = &IRGen::ir_while_Stmt;
    ast2ir_handers[ast_node_type::AST_OP_BREAK] = &IRGen::ir_break;
    ast2ir_handers[ast_node_type::AST_OP_CONTINUE] = &IRGen::ir_continue;
    ast2ir_handers[ast_node_type::AST_OP_DOWHILESTMT] = &IRGen::ir_Dowhile_Stmt;
    ast2ir_handers[ast_node_type::AST_OP_COND_NOT] = &IRGen::ir_Cond_NOT;
    ast2ir_handers[ast_node_type::AST_OP_COND_OR] = &IRGen::ir_Cond_OR;   //  ||
    ast2ir_handers[ast_node_type::AST_OP_COND_AND] = &IRGen::ir_Cond_AND; // &&
    ast2ir_handers[ast_node_type::AST_OP_COND_LESS] = &IRGen::ir_cmp_less;
    ast2ir_handers[ast_node_type::AST_OP_COND_GREATER] = &IRGen::ir_cmp_greater;
    ast2ir_handers[ast_node_type::AST_OP_COND_EQU] = &IRGen::ir_cmp_equal;
    ast2ir_handers[ast_node_type::AST_OP_COND_LESSEQU] = &IRGen::ir_cmp_lessEqual;
    ast2ir_handers[ast_node_type::AST_OP_COND_NOTEQU] = &IRGen::ir_cmp_notEqual;
    ast2ir_handers[ast_node_type::AST_OP_COND_GREATEREQU] = &IRGen::ir_cmp_greaterEqual;
}

/// @brief 创建IRGen对象
/// @param root
/// @param _module
/// @return
IRGenPtr IRGen::get(ast_node *root, ModulePtr _module)
{
    IRGenPtr gen = std::make_shared<IRGen>(root, _module);
    return gen;
}

// ***************** 从基本快流中获取当前基本块 ******************
/// @brief 获取基本块流中的当前基本块
/// @return
BasicBlockPtr &IRGen::getCurBlock()
{
    assert(transmitBlocks.size() != 0 && "the transmitBlocks has no element!");
    return transmitBlocks.front();
}

/// @brief 在当前block后面插入blocks,并在函数中对应的当前block后插入基本块
/// @param block
void IRGen::insertAtCurBlockBack(FuncPtr fun, LabelParams blocks)
{
    assert(transmitBlocks.size() != 0 && "Error! the function has ended"); // 表示队列为空
    bblockIter transmitpos = std::next(transmitBlocks.begin());
    transmitBlocks.insert(transmitpos, blocks.begin(), blocks.end()); // 插入
    bblockIter funcBBlockpos = std::next(curUsedBlockIter);           // 插入位置为当前的下一个位置
    fun->insertBBlock(blocks, funcBBlockpos);
    blocks.clear();
    blocks.shrink_to_fit();
}

/// @brief 根据AST节点的类型查找相应的函数操作并执行
/// @return nullptr表示运行失败，否则返回node指针
ast_node *IRGen::ir_visit_astnode(ast_node *node, LabelParams blocks)
{
    if (node == nullptr)
        return nullptr;
    if (node->node_type == ast_node_type::AST_OP_NULL_STMT)
        return node;
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
    scoper->popTab(); // 弹出全局表
    return true;
}

/// @brief AST  function define节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_func_define(ast_node *node, LabelParams blocks)
{
    string funcname = node->literal_val.digit.id; // 函数名
    uint64_t lineno = node->literal_val.line_no;  // 行号
    // 先查找符号表中有没有对应的函数声明
    ValPtr vfun = scoper->globalTab()->findDeclVar(funcname);
    FuncPtr fun = nullptr;
    if (vfun == nullptr)
    { // 未找到  则创建
        fun = Function::get(node->attr, funcname);
        node->attr = nullptr;                 // 防止反复释放
        scoper->globalTab()->newDeclVar(fun); // 将声明定义的函数加入到全局符号表中，供后继查找
        module->addFunction(fun);             // 加入到module函数列表中
    }
    else // 找到了
    {
        fun = std::static_pointer_cast<Function>(vfun);
        if (fun->getBasicBlocks().size() != 0)
        {
            // 已经定义 报错 退出
            std::cout << ">>>Error: the function: " << funcname << " is redifined! line: " << lineno << std::endl;
            return false;
        }
    }
    // 创建entry函数入口基本块
    BasicBlockPtr Entry = BasicBlock::get(fun, "entry"); // 每个function一定有一个entry基本快
    BasicBlockPtr Exit = BasicBlock::get(fun, "exit");   // 创建函数的出口
    fun->AddBBlockBack(Entry);                           // 加入函数内
    fun->AddBBlockBack(Exit);
    // 根据函数返回值类型创建 函数返回值临时变量
    if (fun->getReturnTy()->isVoidType())
    {
        RetInstPtr ret = RetInst::get();
        Exit->AddInstBack(ret); // 出口处加入ret指令
        ret->setBBlockParent(Exit);
    }
    else
    {
        InstPtr allocaRet = AllocaInst::get("", Type::copy(fun->getReturnTy())); // 非void
        fun->insertAllocaInst(allocaRet);                                        // 加入创建的返回值临时变量
        allocaRet->setBBlockParent(fun->getEntryBlock());
        InstPtr load = LoadInst::get(allocaRet);
        Exit->AddInstBack(load);
        load->setBBlockParent(Exit);
        RetInst::create(load, Exit); // 在Exit出口中加入ret 语句
    }
    transmitBlocks.push_back(Entry); // 加入基本块流 不加函数出口
    // transmitBlocks.push_back(Exit);
    // fun->AllocaIter() = Entry->begin(); // 设置函数的AllocaInst的插入点
    scoper->curFun() = fun;                           // 标记当前记录函数
    scoper->pushTab(FuncTab::get());                  // 创建函数的符号表并加入到管理器scoper中
    curUsedBlockIter = fun->getBasicBlocks().begin(); // 记录当前函数基本块的迭代器
    for (auto &son : node->sons)
    {
        ast_node *result = ir_visit_astnode(son, {}); // 将函数基本块传参至下游节点
        if (result == nullptr)
        {
            scoper->curFun() = nullptr;
            return false;
        }
    }
    // 判断最后一个基本块(即当前基本快)
    if (transmitBlocks.size() != 0)
    {
        assert(transmitBlocks.size() == 1 && ">>>Error!Basic block not aligned with corresponding program during program execution! file: IRGen.cpp; this may be caused by the .c file having the usage not supported currently!");
        // 基本块流中还存在基本块
        // 函数无返回值  加入跳转至Exit指令
        BranchInstPtr br = BranchInst::get(Exit);
        getCurBlock()->AddInstBack(br);
        br->setBBlockParent(getCurBlock());
    }
    // 结束翻译函数时curFun赋值为nullptr,函数符号表弹出栈
    scoper->curFun() = nullptr;
    scoper->popTab(); // 弹栈

    transmitBlocks.clear(); // 弹出函数中剩余的最后一个基本块   流队列的方式
    fun->mergeAllocaToEntry();
    return true;
}

/// @brief AST 函数声明节点
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_func_declare(ast_node *node, LabelParams blocks)
{
    string funcname = node->literal_val.digit.id; // 函数名
    uint64_t lineno = node->literal_val.line_no;  // 行号
    // 先查找符号表中有没有对应的函数声明
    ValPtr vfun = scoper->globalTab()->findDeclVar(funcname);
    if (vfun == nullptr)
    {
        // 未查找到 则创建
        FuncPtr funp = Function::get(node->attr, funcname);
        node->attr = nullptr;
        scoper->globalTab()->newDeclVar(funp); // 加入到表中
        // 遍历形参列表
        ast_node *res = ir_visit_astnode(node->sons[0], {});
        if (res == nullptr)
            return false;

        // 添加到 Extern表中 默认是外部
        module->addExternFunction(funp);
    }
    else
    {
        FuncPtr fun = std::static_pointer_cast<Function>(vfun);
        if (fun->isBuildIn())
        {
            // 是内建函数
            // 添加到 Extern表中 默认是外部
            module->addExternFunction(fun);
        }
        else
        {
            // 查找到  重复声明 报错
            std::cout << ">>>>Error!: not supported function redeclared! function:" << funcname << " line: " << lineno << std::endl;
            return false;
        }
    }
    return true;
}

/// @brief AST  函数形参列表节点对应的操作函数
/// @param node
/// @return
bool IRGen::ir_func_formal_params(ast_node *node, LabelParams blocks)
{
    // 先查找父节点对应的函数
    ast_node *parent = node->parent;
    string funname = parent->literal_val.digit.id;          // 形参对应的函数名
    ValPtr fun = scoper->globalTab()->findDeclVar(funname); // 查找对应的函数
    FuncPtr fun_f = std::static_pointer_cast<Function>(fun);
    uint32_t argNo = 0;
    for (auto &son : node->sons)
    {
        string argName = son->literal_val.digit.id; // 形参名

        // 先获取形参类型
        ArgPtr arg;
        if (son->sons.size() == 0)
        {
            // 非数组
            arg = Argument::get(son->attr, argName); // 形参对象
            son->attr = nullptr;
        }
        else
        {
            // 是数组
            ast_node *arrIndex = son->sons[0];
            std::vector<int> arrDims;
            for (auto &index : arrIndex->sons)
            {
                ast_node *res = ir_visit_astnode(index, {});
                if (res == nullptr)
                {
                    return false;
                }
                // 函数形参数组维度一定是常量
                ConstantIntPtr c = std::static_pointer_cast<ConstantInt>(res->value);
                arrDims.push_back(c->getValue());
            }
            ArrayType *arrFUll = ArrayType::get(arrDims, son->attr);
            son->attr = nullptr;
            Type *arrL = PointerType::get(arrFUll->getContainedTy());
            arrFUll = nullptr;
            arg = Argument::get(arrL, argName); // 形参对象
        }

        /// 设置形参编号
        arg->setArgNo(argNo);
        argNo++;
        fun_f->addArg(arg);

        // 如果父节点是define类型的，则将形参变量加入到函数符号表中   对于形参列表节点 其父节点有可能是decalre function(只声明无定义)
        if (parent->node_type == ast_node_type::AST_OP_FUNC_DEF)
        {
            ValPtr argFind = scoper->curTab()->findDeclVarOfCurTab(argName);
            if (argFind != nullptr)
            {
                // 找到了该参数名 报错
                int64_t lino = son->literal_val.line_no;
                std::cout << ">>>Error! redefinition of parameter:" << argName << " line: " << lino << std::endl;
                return false;
            }
            AllocaInstPtr alloca = AllocaInst::get(argName, Type::copy(arg->getType())); // 创建 Alloca
            StoreInstPtr store = StoreInst::get(arg, alloca);
            alloca->setAllocaArg(arg);       // 设置对应的形参
            fun_f->insertAllocaInst(alloca); // 加入AllocaInst
            alloca->setBBlockParent(fun_f->getEntryBlock());
            fun_f->getEntryBlock()->AddInstBack(store); // 加入store指令
            store->setBBlockParent(fun_f->getEntryBlock());
            scoper->curTab()->newDeclVar(alloca);
        }
    }
    return true;
}

/// @brief if 语句
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_if_Stmt(ast_node *node, LabelParams blocks)
{
    int blocksNum = node->sons.size(); // 创建的基本块数目
    LabelParams jumps;                 // 创建基本块
    for (int i = 0; i < blocksNum; i++)
    {
        jumps.push_back(BasicBlock::get(scoper->curFun()));
    }
    insertAtCurBlockBack(scoper->curFun(), jumps); // 加入基本块
    // 遍历子节点
    ast_node *cond = ir_visit_astnode(node->sons[0], {jumps[0], jumps[1]});
    if (cond == nullptr)
        return false;
    ast_node *ifTrue = ir_visit_astnode(node->sons[1], {jumps.back()});
    if (ifTrue == nullptr)
        return false;
    if (blocksNum == 3)
    {
        // 有假语句体
        ast_node *ifFalse = ir_visit_astnode(node->sons[2], {jumps[2]});
        if (ifFalse == nullptr)
            return false;
    }

    return true;
}

/// @brief while语句
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_while_Stmt(ast_node *node, LabelParams blocks)
{
    LabelParams jumps;
    // 创建三个口 循环入口 循环体入口 循环出口
    BasicBlockPtr whileEntry = BasicBlock::get(scoper->curFun());
    BasicBlockPtr blockEntry = BasicBlock::get(scoper->curFun());
    BasicBlockPtr whileExit = BasicBlock::get(scoper->curFun());
    jumps.push_back(whileEntry);
    jumps.push_back(blockEntry);
    jumps.push_back(whileExit);
    insertAtCurBlockBack(scoper->curFun(), jumps); // 创建的基本快插入

    // 维护两个循环栈 供break,continue 使用
    loopEntrys.push(whileEntry);
    loopExits.push(whileExit);

    // 进入翻译循环前需弹出前一个block, 因为循环在新的一个块开始
    BranchInstPtr br = BranchInst::get(whileEntry);
    getCurBlock()->AddInstBack(br);
    br->setBBlockParent(getCurBlock());
    transmitBlocks.pop_front();
    curUsedBlockIter = std::next(curUsedBlockIter);

    // 下面正式翻译循环
    ast_node *cond = ir_visit_astnode(node->sons[0], {blockEntry, whileExit}); // 传入 循环体口，循环出口
    if (cond == nullptr)
        return false;
    ast_node *whileBody = ir_visit_astnode(node->sons[1], {whileEntry}); // 传入循环入口
    if (whileBody == nullptr)
        return false;
    // 循环结束后 弹出 loopEntrys, loopExits 栈流(嵌套循环时重要)
    loopEntrys.pop();
    loopExits.pop();

    return true;
}

/// @brief do while语句
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_Dowhile_Stmt(ast_node *node, LabelParams blocks)
{
    LabelParams jumps;
    // 创建三个口 循环体循环入口(函数体) 条件与语句的基本块   循环出口
    BasicBlockPtr whileEntry = BasicBlock::get(scoper->curFun());
    // BasicBlockPtr condBlock = BasicBlock::get(scoper->curFun());
    BasicBlockPtr whileExit = BasicBlock::get(scoper->curFun());
    jumps.push_back(whileEntry);
    // jumps.push_back(condBlock);
    jumps.push_back(whileExit);
    insertAtCurBlockBack(scoper->curFun(), jumps); // 创建的基本快插入

    // 维护两个循环栈 供break,continue 使用
    loopEntrys.push(whileEntry);
    loopExits.push(whileExit);

    // 进入翻译循环前需弹出前一个block, 因为循环在新的一个块开始
    BranchInstPtr br = BranchInst::get(whileEntry);
    getCurBlock()->AddInstBack(br);
    br->setBBlockParent(getCurBlock());
    transmitBlocks.pop_front();
    curUsedBlockIter = std::next(curUsedBlockIter);

    // 下面正式翻译循环
    ast_node *whileBody = ir_visit_astnode(node->sons[0], {}); // 传入循环入口
    if (whileBody == nullptr)
        return false;
    ast_node *cond = ir_visit_astnode(node->sons[1], {whileEntry, whileExit}); // 传入 循环体口，循环出口
    if (cond == nullptr)
        return false;

    // 循环结束后 弹出 loopEntrys, loopExits 栈流(嵌套循环时重要)
    loopEntrys.pop();
    loopExits.pop();

    return true;
}

/// @brief 循环中 break语句的翻译
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_break(ast_node *node, LabelParams blocks)
{
    // break 跳转到循环出口  使用 break 将判断是否在循环内 否则报错输出行号
    // 判断是否在循环内 采用loopExits判断
    int lino = node->literal_val.line_no; // 行号
    if (loopExits.empty())
    {
        // 为空 说明不在循环中
        std::cout << ">>>Error!: break statement not within loop or switch! line: " << lino << std::endl;
        return false;
    }
    else
    {
        // 跳转
        BasicBlockPtr jumpExit = loopExits.top();
        BranchInstPtr br = BranchInst::get(jumpExit);
        getCurBlock()->AddInstBack(br); // 加入跳转指令到基本快
        br->setBBlockParent(getCurBlock());
        // 当前基本块已经完毕 （末尾为跳转语句）
        // 创建一个新的基本块(主要用于对齐transmitBlocks状态，虽然这样会将break后无用语句加入，但可后期删除无用基本快)
        BasicBlockPtr block = BasicBlock::get(scoper->curFun());
        // 将创建的块加入流中 以及函数基本快列表中
        insertAtCurBlockBack(scoper->curFun(), {block});
        // 弹出当前基本快  当前块已结束
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    return true;
}

/// @brief 循环中 continue语句的翻译
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_continue(ast_node *node, LabelParams blocks)
{
    // continue 跳转到循环入口  使用 continue 将判断是否在循环内 否则报错输出行号
    // 判断是否在循环内 采用loopEntrys判断
    int lino = node->literal_val.line_no; // 行号
    if (loopEntrys.empty())
    {
        // 为空 说明不在循环中
        std::cout << ">>>Error!: continue statement not within loop or switch! line: " << lino << std::endl;
        return false;
    }
    else
    {
        // 跳转
        BasicBlockPtr jumpEntry = loopEntrys.top();
        BranchInstPtr br = BranchInst::get(jumpEntry);
        getCurBlock()->AddInstBack(br); // 加入跳转指令到基本快
        br->setBBlockParent(getCurBlock());
        // 当前基本块已经完毕 （末尾为跳转语句）
        // 创建一个新的基本块(主要用于对齐transmitBlocks状态，虽然这样会将continue后无用语句加入，但可后期删除无用基本快)
        BasicBlockPtr block = BasicBlock::get(scoper->curFun());
        // 将创建的块加入流中 以及函数基本快列表中
        insertAtCurBlockBack(scoper->curFun(), {block});
        // 弹出当前基本快  当前块已结束
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    return true;
}

/// @brief AST中block节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_block(ast_node *node, LabelParams blocks)
{
    ast_node_type parentNodeTy = node->parent->node_type;
    if (parentNodeTy == ast_node_type::AST_OP_COMPILE_UNIT)
    {
        // 全局中不能只出现 block，智能出现在function定义下
        std::cout << ">>>Error! expected identifier or '(' before '{' token" << std::endl;
        return false;
    }
    else if (parentNodeTy == ast_node_type::AST_OP_FUNC_DEF)
    {
        // 说明是函数定义的函数体block
        // 无需操作  在ir_func_define中已经完成
    }
    else
    {
        // 说明是 函数体下的子block 压栈block
        scoper->pushTab(BlockTempTab::get());
    }
    for (auto &son : node->sons)
    {
        ast_node *result = ir_visit_astnode(son, {}); // block的跳转块不传入子节点
        if (result == nullptr)
            return false;
    }
    if (blocks.size() == 1)
    {
        // block ast节点一般只有一个跳转   条件语句通常两个跳转块
        // 有一个跳转块  goto无条件跳转
        BranchInstPtr br = BranchInst::get(blocks[0]);
        getCurBlock()->AddInstBack(br);
        br->setBBlockParent(getCurBlock());
        transmitBlocks.pop_front(); // 当前基本块已完成  弹出 (使用的跳转基本快创建时会加入transmitBlocks队列流中)
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    if (parentNodeTy != ast_node_type::AST_OP_FUNC_DEF)
    {
        scoper->popTab(); // 是blocktemp表 则从此弹出
    }

    return true;
}

/// @brief AST中 return 节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_return(ast_node *node, LabelParams blocks)
{
    if (node->sons.size() == 0)
    {
        // 无返回值
        if (!scoper->curFun()->getReturnTy()->isVoidType())
        {
            std::cout << ">>>Error! the function: " << scoper->curFun()->getName() << " has no return value!" << std::endl;
            return false;
        }
    }
    else
    {
        if (scoper->curFun()->getReturnTy()->isVoidType())
        {
            std::cout << ">>>Error! the function: " << scoper->curFun()->getName() << " is void type has no return value! " << std::endl;
            return false;
        }
        ast_node *result = ir_visit_astnode(node->sons[0], {});
        if (result == nullptr)
        {
            return false;
        }
        StoreInst::create(result->value, scoper->curFun()->getAllocaLists().front(), getCurBlock()); // 保存返回值
    }
    BranchInstPtr br = BranchInst::get(scoper->curFun()->getExitBlock());
    getCurBlock()->AddInstBack(br);
    br->setBBlockParent(getCurBlock());
    // 创建一个基本块 防止后面还有代码，使transmitBlocks无法对齐情况
    BasicBlockPtr blcok = BasicBlock::get(scoper->curFun());
    insertAtCurBlockBack(scoper->curFun(), {blcok});
    transmitBlocks.pop_front();                     // 弹出当前基本块
    curUsedBlockIter = std::next(curUsedBlockIter); // 伴随pop 需要向后移动一次

    return true;
}

/// @brief AST函数调用节点对应的操作
/// @param node
/// @return
bool IRGen::ir_funcall(ast_node *node, LabelParams blocks)
{
    string funcname = node->literal_val.digit.id;            // 调用的函数名
    int lineno = node->literal_val.line_no;                  // 行号
    ValPtr fun = scoper->globalTab()->findDeclVar(funcname); // 查找该函数
    if (fun == nullptr)
    {
        // 未找到 报错  退出
        std::cout << ">>>Error: no such function:" << funcname << " line: " << lineno << std::endl;
        return false;
    }
    else
    {
        // 找到了 如果是std中的函数加入到 ExternFunction表中
        FuncPtr funCast = std::static_pointer_cast<Function>(fun);
        if (funCast->isBuildIn())
        {
            module->addExternFunction(funCast);
        }
    }
    ast_node *realParams = node->sons[0]; // 实参列表
    std::vector<ValPtr> realArgs;         // 记录实参值
    for (auto &son : realParams->sons)
    { // son为实参
        ast_node *result = ir_visit_astnode(son, {});
        if (result == nullptr)
            return false;
        realArgs.push_back(result->value); // 记录实参值Value
    }
    CallInstPtr call = CallInst::create(fun, realArgs, getCurBlock());
    node->value = call; // 记录 value(对于有返回值的函数有作用)
    if (blocks.size() != 0)
    {
        assert(blocks.size() == 2 && !call->getType()->isVoidType());
        // 函数调用有跳转块  说明父亲节点传入了跳转 需要使用函数返回值作为跳转条件
        ConstantIntPtr zero = ConstantInt::get(32);
        zero->setValue(0); // 和0比较
        ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, call, zero, getCurBlock());
        // 再创建条件跳转语句
        BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br);
        br->setBBlockParent(getCurBlock());
        // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }

    // 更新当前函数调用函数的最大参数数目
    scoper->curFun()->updateMaxCallFunArgsNum(realArgs.size());

    return true;
}

/// @brief AST  ASSIGN赋值节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_assign(ast_node *node, LabelParams blocks)
{
    // 先进行右边 后进行左边
    ast_node *right = ir_visit_astnode(node->sons[1], blocks);
    if (right == nullptr)
        return false;
    ast_node *left = ir_visit_astnode(node->sons[0], blocks);
    if (left == nullptr)
    {
        return false;
    }

    if (scoper->curTab()->isGlobalTab())
    { // 全局中的变量初始化
        assert(left->value->isGlobalVariable() && "it's not global value");
        if (!right->value->isConstant())
        {
            std::cout << "globalvariable " << left->value->getName() << " must use constant to define! line: " << left->literal_val.line_no << std::endl;
            return false;
        }
        GlobalVariPtr g = std::static_pointer_cast<GlobalVariable>(left->value);
        ConstantPtr initer = std::static_pointer_cast<Constant>(right->value);
        g->setInitilizer(std::move(initer)); // 设置初始化值
    }
    else
    {
        // 在局部作用域下的赋值指令
        StoreInst::create(right->value, left->value, getCurBlock());
    }

    return true;
}

/// @brief AST   DeclarationItems节点对应的操作函数
/// @param node
/// @return
bool IRGen::ir_declItems(ast_node *node, LabelParams blocks)
{
    for (auto &son : node->sons)
    {
        ast_node *result = ir_visit_astnode(son, {});
        if (result == nullptr)
        {
            return false;
        }
    }
    return true;
}

/// @brief AST  const DeclarationItems
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_const_declItems(ast_node *node, LabelParams blocks)
{
    for (auto &son : node->sons)
    {
        ast_node *result = ir_visit_astnode(son, {});
        if (result == nullptr)
        {
            return false;
        }
    }
    return true;
}

/// @brief declitems 下的 def定义节点
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_declVarDef(ast_node *node, LabelParams blocks)
{
    // 定义的变量名
    ast_node *left = node->sons[0];
    ast_node *right = node->sons[1];
    string name = left->literal_val.digit.id;
    ValPtr val = scoper->curTab()->findDeclVarOfCurTab(name);
    if (val != nullptr)
    {
        // 找到该value 重复声明！
        std::cout << ">>>Error:the variable " << name << " is redifined! line:" << left->literal_val.line_no << std::endl;
        return false;
    }
    if (scoper->curTab()->isGlobalTab())
    {
        // 全局变量 声明+ 定义
        if (left->sons.size() == 0)
        { // 说明是变量的声明定义
            GlobalVariPtr g = GlobalVariable::get(left->attr, name);
            left->attr = nullptr;
            module->addGlobalVar(g);
            scoper->curTab()->newDeclVar(g);
            // 进行初始化
            ast_node *res = ir_visit_astnode(right, {});
            if (res == nullptr)
            {
                return false;
            }
            if (!res->value->isConstant())
            {
                std::cout << "globalvariable " << name << " must use constant to define! line: " << left->literal_val.line_no << std::endl;
                return false;
            }
            ConstantPtr initer = std::static_pointer_cast<Constant>(right->value);
            g->setInitilizer(std::move(initer));
        }
        else
        {
            // 说明是数组的声明+定义
            // 数组的初始化暂未实现
        }
    }
    else
    {
        // 非全局变量的声明+ 定义
        if (left->sons.size() == 0)
        {
            // 变量 非数组
            AllocaInstPtr alloca = AllocaInst::get(name, left->attr);
            left->attr = nullptr;
            scoper->curTab()->newDeclVar(alloca);
            scoper->curFun()->insertAllocaInst(alloca);
            alloca->setBBlockParent(scoper->curFun()->getEntryBlock());
            // 访问右边
            ast_node *res = ir_visit_astnode(right, {});
            if (res == nullptr)
                return false;
            StoreInst::create(right->value, alloca, getCurBlock());
        }
    }

    return true;
}

/// @brief const 变量声明定义
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_const_declVarDef(ast_node *node, LabelParams blocks)
{
    // 简单处理 既然 const 修饰 就当常量 constantint 处理吧
    ast_node *left = node->sons[0];
    ast_node *right = node->sons[1];
    right = ir_visit_astnode(right, {});
    int linno = left->literal_val.line_no;
    string name = left->literal_val.digit.id;
    if (right == nullptr)
    {
        return false;
    }
    if (!right->value->isConstant())
    {
        std::cout << ">>>Error! the const var: " << name
                  << " must be initilized with constant! line: " << linno << std::endl;
        return false;
    }
    else
    {
        // 将创建的 const 变量 加入到 当前作用域表中
        // 先查找 当前作用域表 防止重复 声明
        ValPtr res = scoper->curTab()->findDeclVarOfCurTab(name);
        if (res != nullptr)
        {
            std::cout << ">>>Error! the var: " << name << " is redifined! line: " << linno << std::endl;
            return false;
        }
        else
        {
            ConstantIntPtr rgval = std::static_pointer_cast<ConstantInt>(right->value);
            int rightval = rgval->getValue();
            ConstantIntPtr leftconst = ConstantInt::get(32);
            leftconst->setValue(rightval);
            left->value = std::move(leftconst);
            left->value->setName(name);
            // 没找到
            scoper->curTab()->newDeclVar(left->value);
        }
    }

    return true;
}

/// @brief 取负号
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_Negative(ast_node *node, LabelParams blocks)
{
    // 翻译时对 neg进行初步优化 如 - - - - a  变为 a
    ast_node *son = node->sons[0];
    bool isneg = true;
    while (son->node_type == ast_node_type::AST_OP_NEG)
    {
        son = son->sons[0];
        isneg = !isneg;
    }
    ast_node *res = ir_visit_astnode(son, {});
    if (res == nullptr)
        return false;

    if (res->value->isConstant())
    {
        // 目前只有 int 故直接转int
        ConstantIntPtr intCOnst = std::static_pointer_cast<ConstantInt>(res->value);
        int num = intCOnst->getValue();
        ConstantIntPtr resConst = ConstantInt::get(32);
        if (isneg)
        {
            resConst->setValue(-num);
        }
        else
        {
            resConst->setValue(num);
        }
        node->value = std::move(resConst);
    }
    else
    {
        // 不是常数  则使用 sub 二元操作  左操作数为0
        if (isneg)
        {
            ConstantIntPtr leftConst = ConstantInt::get(32);
            leftConst->setValue(0);
            BinaryOperatorPtr negValue = BinaryOperator::create(Opcode::SubInteger, leftConst, res->value, getCurBlock());
            node->value = negValue;
        }
        else
        {
            node->value = son->value;
        }
    }
    if (blocks.size() == 2)
    {
        // if while do-while 条件下
        ConstantIntPtr zero = ConstantInt::get(32);
        zero->setValue(0);
        ICmpInstPtr icmp = ICmpInst::create(Opcode::NotEqInteger, node->value, zero, getCurBlock());
        BranchInstPtr br = BranchInst::get(icmp, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br);
        br->setBBlockParent(getCurBlock());
        // 当前基本块结束
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    return true;
}

/// @brief AST 加法操作节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_add(ast_node *node, LabelParams blocks)
{
    // 遍历Ast  时进行初步的优化
    ast_node *left = ir_visit_astnode(node->sons[0], {});
    if (left == nullptr)
    {
        return false;
    }
    ast_node *right = ir_visit_astnode(node->sons[1], {});
    if (right == nullptr)
        return false;

    // 编写一个下面可能都用到的 Lamda函数
    // 当加法值作为条件值 使用时如 if(a+b)
    auto whenTheResIsCond = [&]()
    {
        if (blocks.size() != 0)
        {
            assert(blocks.size() == 2 && !node->value->getType()->isVoidType());
            // 函数调用有跳转块  说明父亲节点传入了跳转 需要使用函数返回值作为跳转条件
            ConstantIntPtr zero = ConstantInt::get(32);
            zero->setValue(0); // 和0比较
            ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, node->value, zero, getCurBlock());
            // 再创建条件跳转语句
            BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
            getCurBlock()->AddInstBack(br);
            br->setBBlockParent(getCurBlock());
            // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
            transmitBlocks.pop_front();
            curUsedBlockIter = std::next(curUsedBlockIter);
        }
    };

    assert(left->value != nullptr && right->value != nullptr);

    if (left->value->isConstant() && right->value->isConstant())
    {
        // 如果加法的两者均为常数 则直接相加运算 (目前默认只实现整数的加法运算)
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        int res = left_const->getValue() + right_const->getValue();
        ConstantIntPtr resPtr = ConstantInt::get(32);
        resPtr->setValue(res); // 设置常数值
        node->value = resPtr;
        whenTheResIsCond();
        return true;
    }
    else if (left->value->isConstant())
    {
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        if (left_const->getValue() == 0)
        {
            node->value = right->value;
            whenTheResIsCond();
            return true;
        }
    }
    else if (right->value->isConstant())
    {
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        if (right_const->getValue() == 0)
        {
            node->value = left->value;
            whenTheResIsCond();
            return true;
        }
    }
    // 不都是常数
    BinaryOperatorPtr binaryOp = BinaryOperator::create(Opcode::AddInteger, left->value, right->value, getCurBlock());
    node->value = binaryOp;
    whenTheResIsCond();
    return true;
}

/// @brief AST 减法节点对应的操作
/// @param node
/// @return
bool IRGen::ir_sub(ast_node *node, LabelParams blocks)
{
    // 遍历Ast  时进行初步的优化
    ast_node *left = ir_visit_astnode(node->sons[0], {});
    if (left == nullptr)
    {
        return false;
    }
    ast_node *right = ir_visit_astnode(node->sons[1], {});
    if (right == nullptr)
        return false;

    // 编写一个下面可能都用到的 Lamda函数
    // 当加法值作为条件值 使用时如 if(a+b)
    auto whenTheResIsCond = [&]()
    {
        if (blocks.size() != 0)
        {
            assert(blocks.size() == 2 && !node->value->getType()->isVoidType());
            // 函数调用有跳转块  说明父亲节点传入了跳转 需要使用函数返回值作为跳转条件
            ConstantIntPtr zero = ConstantInt::get(32);
            zero->setValue(0); // 和0比较
            ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, node->value, zero, getCurBlock());
            // 再创建条件跳转语句
            BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
            getCurBlock()->AddInstBack(br);
            br->setBBlockParent(getCurBlock());
            // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
            transmitBlocks.pop_front();
            curUsedBlockIter = std::next(curUsedBlockIter);
        }
    };

    if (left->value->isConstant() && right->value->isConstant())
    {
        // 如果加法的两者均为常数 则直接相加运算 (目前默认只实现整数的加法运算)
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        int res = left_const->getValue() - right_const->getValue();
        ConstantIntPtr resPtr = ConstantInt::get(32);
        resPtr->setValue(res); // 设置常数值
        node->value = std::move(resPtr);
        whenTheResIsCond();
        return true;
    }
    else if (right->value->isConstant())
    {
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        if (right_const->getValue() == 0)
        {
            node->value = left->value;
            whenTheResIsCond();
            return true;
        }
    }
    // 不都是常数
    BinaryOperatorPtr binaryOp = BinaryOperator::create(Opcode::SubInteger, left->value, right->value, getCurBlock());
    node->value = binaryOp;
    whenTheResIsCond();

    return true;
}

/// @brief AST 乘法节点对应的操作
/// @param node
/// @return
bool IRGen::ir_mul(ast_node *node, LabelParams blocks)
{
    // 遍历Ast  时进行初步的优化
    ast_node *left = ir_visit_astnode(node->sons[0], {});
    if (left == nullptr)
    {
        return false;
    }
    ast_node *right = ir_visit_astnode(node->sons[1], {});
    if (right == nullptr)
        return false;

    // 编写一个下面可能都用到的 Lamda函数
    // 当加法值作为条件值 使用时如 if(a+b)
    auto whenTheResIsCond = [&]()
    {
        if (blocks.size() != 0)
        {
            assert(blocks.size() == 2 && !node->value->getType()->isVoidType());
            // 函数调用有跳转块  说明父亲节点传入了跳转 需要使用函数返回值作为跳转条件
            ConstantIntPtr zero = ConstantInt::get(32);
            zero->setValue(0); // 和0比较
            ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, node->value, zero, getCurBlock());
            // 再创建条件跳转语句
            BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
            getCurBlock()->AddInstBack(br);
            br->setBBlockParent(getCurBlock());
            // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
            transmitBlocks.pop_front();
            curUsedBlockIter = std::next(curUsedBlockIter);
        }
    };

    if (left->value->isConstant() && right->value->isConstant())
    {
        // 如果加法的两者均为常数 则直接相加运算 (目前默认只实现整数的加法运算)
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        int res = left_const->getValue() * right_const->getValue();
        ConstantIntPtr resPtr = ConstantInt::get(32);
        resPtr->setValue(res); // 设置常数值
        node->value = resPtr;
        whenTheResIsCond();
        return true;
    }
    else if (left->value->isConstant())
    {
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        if (left_const->getValue() == 0)
        {
            ConstantIntPtr resPtr = ConstantInt::get(32);
            resPtr->setValue(0); // 设置常数值
            node->value = resPtr;
            whenTheResIsCond();
            return true;
        }
        else if (left_const->getValue() == 1)
        {
            node->value = right->value;
            whenTheResIsCond();
            return true;
        }
    }
    else if (right->value->isConstant())
    {
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        if (right_const->getValue() == 1)
        {
            node->value = left->value;
            whenTheResIsCond();
            return true;
        }
        else if (right_const->getValue() == 0)
        {
            ConstantIntPtr resPtr = ConstantInt::get(32);
            resPtr->setValue(0); // 设置常数值
            node->value = resPtr;
            whenTheResIsCond();
            return true;
        }
    }

    // 不都是常数
    BinaryOperatorPtr binaryOp = BinaryOperator::create(Opcode::MulInteger, left->value, right->value, getCurBlock());
    node->value = binaryOp;
    whenTheResIsCond();

    return true;
}

/// @brief AST 除法节点对应的操作
/// @param node
/// @return
bool IRGen::ir_div(ast_node *node, LabelParams blocks)
{
    // 遍历Ast  时进行初步的优化
    ast_node *left = ir_visit_astnode(node->sons[0], {});
    if (left == nullptr)
    {
        return false;
    }
    ast_node *right = ir_visit_astnode(node->sons[1], {});
    if (right == nullptr)
        return false;

    // 编写一个下面可能都用到的 Lamda函数
    // 当加法值作为条件值 使用时如 if(a+b)
    auto whenTheResIsCond = [&]()
    {
        if (blocks.size() != 0)
        {
            assert(blocks.size() == 2 && !node->value->getType()->isVoidType());
            // 函数调用有跳转块  说明父亲节点传入了跳转 需要使用函数返回值作为跳转条件
            ConstantIntPtr zero = ConstantInt::get(32);
            zero->setValue(0); // 和0比较
            ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, node->value, zero, getCurBlock());
            // 再创建条件跳转语句
            BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
            getCurBlock()->AddInstBack(br);
            br->setBBlockParent(getCurBlock());
            // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
            transmitBlocks.pop_front();
            curUsedBlockIter = std::next(curUsedBlockIter);
        }
    };
    if (left->value->isConstant() && right->value->isConstant())
    {
        // 如果加法的两者均为常数 则直接相加运算 (目前默认只实现整数的加法运算)
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        int res = left_const->getValue() / right_const->getValue();
        ConstantIntPtr resPtr = ConstantInt::get(32);
        resPtr->setValue(res); // 设置常数值
        node->value = resPtr;
        whenTheResIsCond();
        return true;
    }
    else if (right->value->isConstant())
    {
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        if (right_const->getValue() == 1)
        {
            node->value = left->value;
            whenTheResIsCond();
            return true;
        }
    }

    // 不都是常数
    BinaryOperatorPtr binaryOp = BinaryOperator::create(Opcode::DivInteger, left->value, right->value, getCurBlock());
    node->value = binaryOp;
    whenTheResIsCond();

    return true;
}

/// @brief AST 取余节点对应的操作
/// @param node
/// @return
bool IRGen::ir_mod(ast_node *node, LabelParams blocks)
{
    // 遍历Ast  时进行初步的优化
    ast_node *left = ir_visit_astnode(node->sons[0], {});
    if (left == nullptr)
    {
        return false;
    }
    ast_node *right = ir_visit_astnode(node->sons[1], {});
    if (right == nullptr)
        return false;

    // 编写一个下面可能都用到的 Lamda函数
    // 当加法值作为条件值 使用时如 if(a+b)
    auto whenTheResIsCond = [&]()
    {
        if (blocks.size() != 0)
        {
            assert(blocks.size() == 2 && !node->value->getType()->isVoidType());
            // 函数调用有跳转块  说明父亲节点传入了跳转 需要使用函数返回值作为跳转条件
            ConstantIntPtr zero = ConstantInt::get(32);
            zero->setValue(0); // 和0比较
            ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, node->value, zero, getCurBlock());
            // 再创建条件跳转语句
            BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
            getCurBlock()->AddInstBack(br);
            br->setBBlockParent(getCurBlock());
            // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
            transmitBlocks.pop_front();
            curUsedBlockIter = std::next(curUsedBlockIter);
        }
    };

    if (left->value->isConstant() && right->value->isConstant())
    {
        // 如果加法的两者均为常数 则直接相加运算 (目前默认只实现整数的加法运算)
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        int res = left_const->getValue() % right_const->getValue();
        ConstantIntPtr resPtr = ConstantInt::get(32);
        resPtr->setValue(res); // 设置常数值
        node->value = std::move(resPtr);
        whenTheResIsCond();
        return true;
    }
    else if (left->value->isConstant())
    {
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        if (left_const->getValue() == 0)
        {
            ConstantIntPtr resPtr = ConstantInt::get(32);
            resPtr->setValue(0); // 设置常数值
            node->value = resPtr;
            whenTheResIsCond();
            return true;
        }
    }
    else if (right->value->isConstant())
    {
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        if (right_const->getValue() == 1)
        {
            ConstantIntPtr resPtr = ConstantInt::get(32);
            resPtr->setValue(0); // 设置常数值
            node->value = resPtr;
            whenTheResIsCond();
            return true;
        }
    }

    // 不都是常数
    BinaryOperatorPtr binaryOp = BinaryOperator::create(Opcode::ModInteger, left->value, right->value, getCurBlock());
    node->value = binaryOp;
    whenTheResIsCond();

    return true;
}

/// @brief AST ! 条件非对应的操作
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_Cond_NOT(ast_node *node, LabelParams blocks)
{
    // 对于 not 节点目前只支持 在 if else ,while do while条件体中或者||，&& 等条件分支使用 因此 此处的blocks一定会传递两个块
    // 不支持 a=!condition 等用于非 if,while,do while总体条件块下的该操作 目前
    // not 无实际作用 只需交换跳转快的顺序并往下传递即可；
    if (blocks.size() > 0)
    {
        assert(blocks.size() == 2 && "not support the usage currently!");
        // not 肯定只有一个子节点
        ast_node *result = ir_visit_astnode(node->sons[0], {blocks[1], blocks[0]}); // 交换真假出口
        if (result == nullptr)
            return false;
    }
    else
    {
        // 父节点没有传入 跳转 说明是一元运算模式
        // 注意目前 不支持 a=!(a||b)  这样的一元运算
        // 支持 !a   !-a  !!!-a  这样的一元运算
        // 会稍微 进行一定优化 如 !a 翻译为 a==0 !!a 翻译为 a!=0   !!!a 翻译为 !a相同 a==0
        bool isNot = true;
        ast_node *son = node->sons[0];
        while (son->node_type == ast_node_type::AST_OP_COND_NOT)
        {
            son = son->sons[0];
            isNot = !isNot;
        }
        ast_node *res = ir_visit_astnode(son, {});
        if (res == nullptr)
            return false;

        ConstantIntPtr zero = ConstantInt::get(32);
        zero->setValue(0);
        if (isNot)
        {
            // 翻译为 !a  a==0
            ICmpInstPtr eqZero = ICmpInst::create(Opcode::EqInTeger, res->value, zero, getCurBlock());
            // 创建 Zext 指令得到 i32为的一元运算值
            ZextInstPtr zext = ZextInst::get(eqZero, Type::getIntNType(32));
            // 将 zext 指令加入到当前基本块
            getCurBlock()->AddInstBack(zext);
            zext->setBBlockParent(getCurBlock());
            node->value = zext;
        }
        else
        {
            // 翻译为 a  a!=0
            ICmpInstPtr NotZero = ICmpInst::create(Opcode::NotEqInteger, res->value, zero, getCurBlock());
            // 创建 Zext 指令得到 i32为的一元运算值
            ZextInstPtr zext = ZextInst::get(NotZero, Type::getIntNType(32));
            // 将 zext 指令加入到当前基本块
            getCurBlock()->AddInstBack(zext);
            zext->setBBlockParent(getCurBlock());
            node->value = zext;
        }
    }

    return true;
}

/// @brief 条件或 || 翻译
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_Cond_OR(ast_node *node, LabelParams blocks)
{
    // 目前翻译场景为 if while do-while 条件语句
    // 对于 a= b||m  形式的赋值暂时不支持
    assert(blocks.size() == 2 && "not support the usage, must be use in if,while,do-while condition statement");
    if (blocks.size() == 2)
    {
        BasicBlockPtr condFalse = BasicBlock::get(scoper->curFun()); // 如果 a&&b  中第一个 a条件为真的跳转口
        insertAtCurBlockBack(scoper->curFun(), {condFalse});         // 将创建的块 插入当前块之后 这将是后一个条件语句指令所在的块
        ast_node *cond1 = ir_visit_astnode(node->sons[0], {blocks[0], condFalse});
        if (cond1 == nullptr)
            return false;
        ast_node *cond2 = ir_visit_astnode(node->sons[1], blocks);
        if (cond2 == nullptr)
            return false;
    }
    return true;
}

/// @brief 条件 && 翻译
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_Cond_AND(ast_node *node, LabelParams blocks)
{
    // 目前翻译场景为 if while do-while 条件语句
    // 对于 a= b&&m  形式的赋值暂时不支持
    assert(blocks.size() == 2 && "not support the usage, must be use in if,while,do-while condition statement");
    if (blocks.size() == 2)
    {
        BasicBlockPtr condTrue = BasicBlock::get(scoper->curFun()); // 如果 a&&b  中第一个 a条件为真的跳转口
        insertAtCurBlockBack(scoper->curFun(), {condTrue});         // 将创建的块 插入当前块之后 这将是后一个条件语句指令所在的块
        ast_node *cond1 = ir_visit_astnode(node->sons[0], {condTrue, blocks.back()});
        if (cond1 == nullptr)
            return false;
        ast_node *cond2 = ir_visit_astnode(node->sons[1], blocks);
        if (cond2 == nullptr)
            return false;
    }
    return true;
}

/// @brief AST < 节点对应的操作
/// @param node
/// @return
bool IRGen::ir_cmp_less(ast_node *node, LabelParams blocks)
{
    // 目前 条件比较只支持 if while do-while条件语句
    // 对于其他场景 如  a=b<100;  这类赋值暂未支持  后继可扩展
    if (blocks.size() != 0)
    {
        assert(blocks.size() == 2 && "Conditional statements typically pass two jump basic blocks!");
        // 如果 < 是作为 if while 的判断条件 应该有两个跳转口
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::LtIntegr, left->value, right->value, getCurBlock());
        node->value = icmp;
        BranchInstPtr br = BranchInst::get(icmp, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br); // 跳转指令
        br->setBBlockParent(getCurBlock());
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    else
    {
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::LtIntegr, left->value, right->value, getCurBlock());
        // 创建 Zext 指令得到 i32为的一元运算值
        ZextInstPtr zext = ZextInst::get(icmp, Type::getIntNType(32));
        // 将 zext 指令加入到当前基本块
        getCurBlock()->AddInstBack(zext);
        zext->setBBlockParent(getCurBlock());
        node->value = zext;
    }
    return true;
}

/// @brief AST  > 节点对应的操作
/// @param node
/// @return
bool IRGen::ir_cmp_greater(ast_node *node, LabelParams blocks)
{
    // 目前 条件比较只支持 if while do-while条件语句
    // 对于其他场景 如  a=b>100;  这类赋值暂未支持  后继可扩展
    if (blocks.size() != 0)
    {
        assert(blocks.size() == 2 && "Conditional statements typically pass two jump basic blocks!");
        // 如果 < 是作为 if while 的判断条件 应该有两个跳转口
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::GtInteger, left->value, right->value, getCurBlock());
        node->value = icmp;
        BranchInstPtr br = BranchInst::get(icmp, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br); // 跳转指令
        br->setBBlockParent(getCurBlock());
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    else
    {
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::GtInteger, left->value, right->value, getCurBlock());
        // 创建 Zext 指令得到 i32为的一元运算值
        ZextInstPtr zext = ZextInst::get(icmp, Type::getIntNType(32));
        // 将 zext 指令加入到当前基本块
        getCurBlock()->AddInstBack(zext);
        zext->setBBlockParent(getCurBlock());
        node->value = zext;
    }
    return true;
}

/// @brief AST == 节点对应的操作
/// @param node
/// @return
bool IRGen::ir_cmp_equal(ast_node *node, LabelParams blocks)
{
    // 目前 条件比较只支持 if while do-while条件语句
    // 对于其他场景 如  a=b==100;  这类赋值暂未支持  后继可扩展
    if (blocks.size() != 0)
    {
        assert(blocks.size() == 2 && "Conditional statements typically pass two jump basic blocks!");
        // 如果 < 是作为 if while 的判断条件 应该有两个跳转口
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::EqInTeger, left->value, right->value, getCurBlock());
        node->value = icmp;
        BranchInstPtr br = BranchInst::get(icmp, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br); // 跳转指令
        br->setBBlockParent(getCurBlock());
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    else
    {
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::EqInTeger, left->value, right->value, getCurBlock());
        // 创建 Zext 指令得到 i32为的一元运算值
        ZextInstPtr zext = ZextInst::get(icmp, Type::getIntNType(32));
        // 将 zext 指令加入到当前基本块
        getCurBlock()->AddInstBack(zext);
        zext->setBBlockParent(getCurBlock());
        node->value = zext;
    }
    return true;
}

/// @brief AST  != 对应操作
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_cmp_notEqual(ast_node *node, LabelParams blocks)
{

    // 目前 条件比较只支持 if while do-while条件语句
    // 对于其他场景 如  a=b==100;  这类赋值暂未支持  后继可扩展
    if (blocks.size() != 0)
    {
        assert(blocks.size() == 2 && "Conditional statements typically pass two jump basic blocks!");
        // 如果 < 是作为 if while 的判断条件 应该有两个跳转口
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::NotEqInteger, left->value, right->value, getCurBlock());
        node->value = icmp;
        BranchInstPtr br = BranchInst::get(icmp, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br); // 跳转指令
        br->setBBlockParent(getCurBlock());
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    else
    {
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::NotEqInteger, left->value, right->value, getCurBlock());
        // 创建 Zext 指令得到 i32为的一元运算值
        ZextInstPtr zext = ZextInst::get(icmp, Type::getIntNType(32));
        // 将 zext 指令加入到当前基本块
        getCurBlock()->AddInstBack(zext);
        zext->setBBlockParent(getCurBlock());
        node->value = zext;
    }
    return true;
}

/// @brief AST <=
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_cmp_lessEqual(ast_node *node, LabelParams blocks)
{

    // 目前 条件比较只支持 if while do-while条件语句
    // 对于其他场景 如  a=b==100;  这类赋值暂未支持  后继可扩展
    if (blocks.size() != 0)
    {
        assert(blocks.size() == 2 && "Conditional statements typically pass two jump basic blocks!");
        // 如果 < 是作为 if while 的判断条件 应该有两个跳转口
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::LeInteger, left->value, right->value, getCurBlock());
        node->value = icmp;
        BranchInstPtr br = BranchInst::get(icmp, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br); // 跳转指令
        br->setBBlockParent(getCurBlock());
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    else
    {
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::LeInteger, left->value, right->value, getCurBlock());
        // 创建 Zext 指令得到 i32为的一元运算值
        ZextInstPtr zext = ZextInst::get(icmp, Type::getIntNType(32));
        // 将 zext 指令加入到当前基本块
        getCurBlock()->AddInstBack(zext);
        zext->setBBlockParent(getCurBlock());
        node->value = zext;
    }
    return true;
}

/// @brief AST  >=
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_cmp_greaterEqual(ast_node *node, LabelParams blocks)
{

    // 目前 条件比较只支持 if while do-while条件语句
    // 对于其他场景 如  a=b==100;  这类赋值暂未支持  后继可扩展
    if (blocks.size() != 0)
    {
        assert(blocks.size() == 2 && "Conditional statements typically pass two jump basic blocks!");
        // 如果 < 是作为 if while 的判断条件 应该有两个跳转口
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::GeInTeger, left->value, right->value, getCurBlock());
        node->value = icmp;
        BranchInstPtr br = BranchInst::get(icmp, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br); // 跳转指令
        br->setBBlockParent(getCurBlock());
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
    else
    {
        ast_node *left = ir_visit_astnode(node->sons[0], {});
        if (left == nullptr)
            return false;
        ast_node *right = ir_visit_astnode(node->sons[1], {});
        if (right == nullptr)
            return false;
        ICmpInstPtr icmp = ICmpInst::create(Opcode::GeInTeger, left->value, right->value, getCurBlock());
        // 创建 Zext 指令得到 i32为的一元运算值
        ZextInstPtr zext = ZextInst::get(icmp, Type::getIntNType(32));
        // 将 zext 指令加入到当前基本块
        getCurBlock()->AddInstBack(zext);
        zext->setBBlockParent(getCurBlock());
        node->value = zext;
    }
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
            GlobalVariPtr g = GlobalVariable::get(node->attr, name);
            node->attr = nullptr;            // 防止反复释放
            module->addGlobalVar(g);         // 加入全局变量列表
            scoper->curTab()->newDeclVar(g); // 符号表中加入相应的声明
        }
        else
        {
            // 非全局变量声明
            AllocaInstPtr alloca = AllocaInst::get(name, node->attr);
            node->attr = nullptr;
            scoper->curTab()->newDeclVar(alloca);       //  将声明变量加入当前符号表中
            scoper->curFun()->insertAllocaInst(alloca); // 将allocaInst加入到指令基本块中
            alloca->setBBlockParent(scoper->curFun()->getEntryBlock());
            // 目前只有 int 对于只声明没有定义的变量初始赋值为0
            // ConstantIntPtr zero = ConstantInt::get(32);
            // zero->setValue(0);
            // StoreInstPtr str = StoreInst::get(zero, alloca);
            // scoper->curFun()->insertAllocaInst(str);
            // str->setBBlockParent(scoper->curFun()->getEntryBlock());
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
        // node->value = val;
        // 如果有传递的跳转块 (目前跳转块 只能是 由if  while || ! && 传递  而且一定传递两个块)
        if (blocks.size() == 0)
        {
            node->value = val;
        }
        else
        {
            assert(blocks.size() == 2 && "not support usage currently! file: IRGen.cpp line: 1184!");
            // 对于一个Value 判断语句是 !=0
            // 先创建 ！=0 的icmp 语句
            ConstantIntPtr zero = ConstantInt::get(32);
            zero->setValue(0); // 和0比较
            ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, val, zero, getCurBlock());
            // 再创建条件跳转语句
            BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
            getCurBlock()->AddInstBack(br);
            br->setBBlockParent(getCurBlock());
            // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
            transmitBlocks.pop_front();
            curUsedBlockIter = std::next(curUsedBlockIter);
        }
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

    if (blocks.size() == 0)
    {
        node->value = conInt;
    }
    else
    {
        assert(blocks.size() == 2 && "not support usage currently! file: IRGen.cpp line: 1239!");
        // 对于一个Value 判断语句是 !=0
        // 先创建 ！=0 的icmp 语句
        ConstantIntPtr zero = ConstantInt::get(32);
        zero->setValue(0); // 和0比较
        ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, conInt, zero, getCurBlock());
        // 再创建条件跳转语句
        BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
        getCurBlock()->AddInstBack(br);
        br->setBBlockParent(getCurBlock());
        // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }

    return true;
}

/// @brief 对于float字面量AST节点的操作 AST_LEAF_LITERAL_FLOAT
/// @param node AST float字面量节点
/// @return
bool IRGen::ir_leafNode_float(ast_node *node, LabelParams blocks)
{
    return true;
}

/// @brief NULL空节点
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_leafNode_NULL(ast_node *node, LabelParams blocks)
{
    ConstantIntPtr c = ConstantInt::get(32);
    c->setValue(-1);
    node->value = c;
    return true;
}

/// @brief 数组节点
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_leafNode_array(ast_node *node, LabelParams blocks)
{
    string name = node->literal_val.digit.id; // 数组名
    // 判断变量 可能是声明区域下的，也可能是使用区域下的
    if (node->parent->node_type == ast_node_type::AST_OP_DECL_ITEMS)
    {                                                             // 数组的父节点是declare_items
        ValPtr val = scoper->curTab()->findDeclVarOfCurTab(name); // 查找
        if (val != nullptr)
        { // 查找到该value
            std::cout << ">>>Error:the array variable " << name << " is redifined! line:" << node->literal_val.line_no << std::endl;
            return false;
        }
        if (scoper->curTab()->isGlobalTab())
        { // 全局变量声明

            ast_node *arrIndex = node->sons[0]; // 数组维度列表
            std::vector<int> dims;
            for (auto &id : arrIndex->sons)
            {
                ast_node *res = ir_visit_astnode(id, {});
                if (res == nullptr)
                {
                    return false;
                }
                // 声明时维度一定是常量 可能是  常量表达式
                ConstantIntPtr c = std::static_pointer_cast<ConstantInt>(res->value);
                dims.push_back(c->getValue());
            }
            ArrayType *arrty = ArrayType::get(dims, node->attr);
            node->attr = nullptr;
            GlobalVariPtr g = GlobalVariable::get(arrty, name);
            module->addGlobalVar(g);         // 加入全局变量列表
            scoper->curTab()->newDeclVar(g); // 符号表中加入相应的声明
        }
        else
        {
            // 非全局变量声明
            ast_node *arrIndex = node->sons[0]; // 数组维度列表
            std::vector<int> dims;
            for (auto &id : arrIndex->sons)
            {
                ast_node *res = ir_visit_astnode(id, {});
                if (res == nullptr)
                {
                    return false;
                }
                // 声明时维度一定是常量 可能是  常量表达式
                ConstantIntPtr c = std::static_pointer_cast<ConstantInt>(res->value);
                dims.push_back(c->getValue());
            }
            ArrayType *arrty = ArrayType::get(dims, node->attr);
            node->attr = nullptr;
            AllocaInstPtr alloca = AllocaInst::get(name, arrty);
            scoper->curTab()->newDeclVar(alloca);       //  将声明变量加入当前符号表中
            scoper->curFun()->insertAllocaInst(alloca); // 将allocaInst加入到指令基本块中
            alloca->setBBlockParent(scoper->curFun()->getEntryBlock());
        }
    }
    else
    {
        // 不直接在declitems下的节点(被使用)
        ValPtr val = scoper->curTab()->findDeclVar(name); // 查找
        if (val == nullptr)
        {
            std::cout << ">>>Error:the array variable " << name << " is not declared! line:" << node->literal_val.line_no << std::endl;
            return false;
        }
        ast_node *arrIndex = node->sons[0]; // 数组维度列表
        std::vector<ValPtr> dims;
        for (auto &id : arrIndex->sons)
        {
            ast_node *res = ir_visit_astnode(id, {});
            if (res == nullptr)
            {
                return false;
            }
            dims.push_back(res->value);
        }
        // 创建 getelementptr指令
        getelemInstPtr getelem = getelementptrInst::create(val, dims, getCurBlock());
        // node->value = getelem;
        if (blocks.size() == 0)
        {
            node->value = getelem;
        }
        else
        {
            assert(blocks.size() == 2 && "not support usage currently! file: IRGen.cpp line: 1239!");
            // 对于一个Value 判断语句是 !=0
            // 先创建 ！=0 的icmp 语句
            ConstantIntPtr zero = ConstantInt::get(32);
            zero->setValue(0); // 和0比较
            ICmpInstPtr notZero = ICmpInst::create(Opcode::NotEqInteger, getelem, zero, getCurBlock());
            // 再创建条件跳转语句
            BranchInstPtr br = BranchInst::get(notZero, blocks[0], blocks[1]);
            getCurBlock()->AddInstBack(br);
            br->setBBlockParent(getCurBlock());
            // 创建跳转语句后 当前块完毕  更新基本块队列以及当前块迭代器
            transmitBlocks.pop_front();
            curUsedBlockIter = std::next(curUsedBlockIter);
        }
    }

    return true;
}

/// @brief 无const修饰的数组初始化
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_array_def(ast_node *node, LabelParams blocks)
{
    ast_node *array = node->sons[0];
    ast_node *right = node->sons[1];
    string arrName = array->literal_val.digit.id; // 数组名
    int lineno = array->literal_val.line_no;      // 数组所在的行
    // 先看有没有重复声明
    ValPtr val = scoper->curTab()->findDeclVarOfCurTab(arrName); // 查找当前作用域
    if (val != nullptr)
    {
        // 查找到该 数组已经声明
        std::cout << ">>>Error:the array variable " << arrName << " is redifined! line:" << lineno << std::endl;
        return false;
    }
    // 访问一下右边的子节点 得到数组的初始化列表
    ast_node *rightRes = ir_visit_astnode(right, {});
    if (rightRes == nullptr)
        return false;
    InitListPtr initValues = std::static_pointer_cast<InitValueList>(rightRes->value); // 数组的初始化列表
    if (scoper->curTab()->isGlobalTab())
    {
        // 是全局数组
        ast_node *arrIndex = array->sons[0];
        std::vector<int> dims;
        for (auto &id : arrIndex->sons)
        {
            ast_node *res = ir_visit_astnode(id, {});
            if (res == nullptr)
                return false;
            ConstantIntPtr c = std::static_pointer_cast<ConstantInt>(res->value);
            dims.push_back(c->getValue());
        }
        ArrayType *arrty = ArrayType::get(dims, Type::copy(array->attr)); // 获取数组类型
        GlobalVariPtr g = GlobalVariable::get(arrty, arrName);
        module->addGlobalVar(g);
        scoper->curTab()->newDeclVar(g); // 加入符号表中
        // 全局数组的话 初始值一定是常数 遍历初始化列表 根据规则设置全局变量的initilizer
        globInitilizerPtr init = globInitilizer::get(Type::copy(arrty));
        ConstantIntPtr zero = ConstantInt::get(32);
        zero->setValue(0);
        globInitilizer::initElem(init, dims, zero); // 初始化值为0
        std::map<int, ValPtr> splitRes;
        splitMapInitList(dims, initValues, -1, splitRes);
        // 下面根据展平的一维结果计算替换得到相应的全局变量初始化结果
        globInitilizer::replaceValueInPos(init, dims, splitRes);
        g->setInitilizer(init); // 设置初始化列表
    }
    else
    {
        // 不是全局作用域
        ast_node *arrIndex = array->sons[0];
        std::vector<int> dims;
        for (auto &id : arrIndex->sons)
        {
            ast_node *res = ir_visit_astnode(id, {});
            if (res == nullptr)
                return false;
            ConstantIntPtr c = std::static_pointer_cast<ConstantInt>(res->value);
            dims.push_back(c->getValue());
        }
        ArrayType *arrty = ArrayType::get(dims, Type::copy(array->attr)); // 获取数组类型
        AllocaInstPtr alloca = AllocaInst::get(arrName, arrty);
        scoper->curTab()->newDeclVar(alloca);       //  将声明变量加入当前符号表中
        scoper->curFun()->insertAllocaInst(alloca); // 将allocaInst加入到指令基本块中
        alloca->setBBlockParent(scoper->curFun()->getEntryBlock());

        string memSetName = string("llvm.memset.p0i8.i64");
        ValPtr memsetV = scoper->globalTab()->findDeclVar(memSetName);
        FuncPtr memset = std::static_pointer_cast<Function>(memsetV);
        std::map<int, ValPtr> splitRes;
        splitMapInitList(dims, initValues, -1, splitRes);
        // 先创建bitcast
        BitCastPtr bitcast = BitCastInst::get(alloca, PointerType::get(Type::getIntNType(8)));
        bitcast->setBBlockParent(getCurBlock());
        getCurBlock()->AddInstBack(bitcast);

        std::vector<ValPtr> relArgs;
        relArgs.push_back(bitcast);
        ConstantIntPtr zero = ConstantInt::get(8);
        zero->setValue(0);
        relArgs.push_back(zero);

        int numBytes = 4;
        for (auto ind : dims)
        {
            numBytes *= ind;
        }
        ConstantIntPtr bytes = ConstantInt::get(64);
        bytes->setValue(numBytes);
        relArgs.push_back(bytes);
        ConstantIntPtr falseC = ConstantInt::get(1);
        falseC->setValue(0);
        relArgs.push_back(falseC);
        CallInstPtr callMem = CallInst::create(memset, relArgs, getCurBlock());
        module->addExternFunction(memset);
        // 下面遍历 splitRes 记录 使用store指令
        for (auto &pair : splitRes)
        {
            int pos = pair.first;
            auto &val = pair.second;
            if (val->isConstantInt())
            { // 存放0 则跳过
                ConstantIntPtr valc = std::static_pointer_cast<ConstantInt>(val);
                if (valc->getValue() == 0)
                {
                    continue;
                }
            }
            ConstantIntPtr offset = ConstantInt::get(32);
            offset->setValue(pos);
            getelemInstPtr gep = getelementptrInst::get(alloca, dims.size(), offset);
            gep->setBBlockParent(getCurBlock());
            getCurBlock()->AddInstBack(gep);
            // 创建store指令
            StoreInstPtr str = StoreInst::create(val, gep, getCurBlock());
        }
    }

    return true;
}

/// @brief const修饰的数组初始化
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_const_array_def(ast_node *node, LabelParams blocks)
{
    ast_node *array = node->sons[0];
    ast_node *right = node->sons[1];
    string arrName = array->literal_val.digit.id; // 数组名
    int lineno = array->literal_val.line_no;      // 数组所在的行
    // 先看有没有重复声明
    ValPtr val = scoper->curTab()->findDeclVarOfCurTab(arrName); // 查找当前作用域
    if (val != nullptr)
    {
        // 查找到该 数组已经声明
        std::cout << ">>>Error:the array variable " << arrName << " is redifined! line:" << lineno << std::endl;
        return false;
    }
    // 访问一下右边的子节点 得到数组的初始化列表
    ast_node *rightRes = ir_visit_astnode(right, {});
    if (rightRes == nullptr)
        return false;
    InitListPtr initValues = std::static_pointer_cast<InitValueList>(rightRes->value); // 数组的初始化列表
    if (scoper->curTab()->isGlobalTab())
    {
        // 是全局数组
        ast_node *arrIndex = array->sons[0];
        std::vector<int> dims;
        for (auto &id : arrIndex->sons)
        {
            ast_node *res = ir_visit_astnode(id, {});
            if (res == nullptr)
                return false;
            ConstantIntPtr c = std::static_pointer_cast<ConstantInt>(res->value);
            dims.push_back(c->getValue());
        }
        ArrayType *arrty = ArrayType::get(dims, Type::copy(array->attr)); // 获取数组类型
        GlobalVariPtr g = GlobalVariable::get(arrty, arrName);
        module->addGlobalVar(g);
        scoper->curTab()->newDeclVar(g); // 加入符号表中
        // 全局数组的话 初始值一定是常数 遍历初始化列表 根据规则设置全局变量的initilizer
        globInitilizerPtr init = globInitilizer::get(Type::copy(arrty));
        ConstantIntPtr zero = ConstantInt::get(32);
        zero->setValue(0);
        globInitilizer::initElem(init, dims, zero); // 初始化值为0
        std::map<int, ValPtr> splitRes;
        splitMapInitList(dims, initValues, -1, splitRes);
        // 下面根据展平的一维结果计算替换得到相应的全局变量初始化结果
        globInitilizer::replaceValueInPos(init, dims, splitRes);
        g->setInitilizer(init); // 设置初始化列表
    }
    else
    {
        // 不是全局作用域
        ast_node *arrIndex = array->sons[0];
        std::vector<int> dims;
        for (auto &id : arrIndex->sons)
        {
            ast_node *res = ir_visit_astnode(id, {});
            if (res == nullptr)
                return false;
            ConstantIntPtr c = std::static_pointer_cast<ConstantInt>(res->value);
            dims.push_back(c->getValue());
        }
        ArrayType *arrty = ArrayType::get(dims, Type::copy(array->attr)); // 获取数组类型
        AllocaInstPtr alloca = AllocaInst::get(arrName, arrty);
        scoper->curTab()->newDeclVar(alloca);       //  将声明变量加入当前符号表中
        scoper->curFun()->insertAllocaInst(alloca); // 将allocaInst加入到指令基本块中
        alloca->setBBlockParent(scoper->curFun()->getEntryBlock());

        string memSetName = string("llvm.memset.p0i8.i64");
        ValPtr memsetV = scoper->globalTab()->findDeclVar(memSetName);
        FuncPtr memset = std::static_pointer_cast<Function>(memsetV);
        std::map<int, ValPtr> splitRes;
        splitMapInitList(dims, initValues, -1, splitRes);
        // 先创建bitcast
        BitCastPtr bitcast = BitCastInst::get(alloca, PointerType::get(Type::getIntNType(8)));
        bitcast->setBBlockParent(getCurBlock());
        getCurBlock()->AddInstBack(bitcast);

        std::vector<ValPtr> relArgs;
        relArgs.push_back(bitcast);
        ConstantIntPtr zero = ConstantInt::get(8);
        zero->setValue(0);
        relArgs.push_back(zero);

        int numBytes = 4;
        for (auto ind : dims)
        {
            numBytes *= ind;
        }
        ConstantIntPtr bytes = ConstantInt::get(64);
        bytes->setValue(numBytes);
        relArgs.push_back(bytes);
        ConstantIntPtr falseC = ConstantInt::get(1);
        falseC->setValue(0);
        relArgs.push_back(falseC);
        CallInstPtr callMem = CallInst::create(memset, relArgs, getCurBlock());
        module->addExternFunction(memset);
        // 下面遍历 splitRes 记录 使用store指令
        for (auto &pair : splitRes)
        {
            int pos = pair.first;
            auto &val = pair.second;
            if (val->isConstantInt())
            { // 存放0 则跳过
                ConstantIntPtr valc = std::static_pointer_cast<ConstantInt>(val);
                if (valc->getValue() == 0)
                {
                    continue;
                }
            }
            ConstantIntPtr offset = ConstantInt::get(32);
            offset->setValue(pos);
            getelemInstPtr gep = getelementptrInst::get(alloca, dims.size(), offset);
            gep->setBBlockParent(getCurBlock());
            getCurBlock()->AddInstBack(gep);
            // 创建store指令
            StoreInstPtr str = StoreInst::create(val, gep, getCurBlock());
        }
    }

    return true;
}

/// @brief 翻译获取数组的初始化列表 const 初始化列表以及非const的列表处理方式相同
/// @param node
/// @param blocks
/// @return
bool IRGen::ir_initValueList(ast_node *node, LabelParams blocks)
{
    InitListPtr nodeVal = InitValueList::get();
    for (auto &son : node->sons)
    {
        ast_node *res = ir_visit_astnode(son, {});
        if (res == nullptr)
            return false;
        nodeVal->addElem(res->value);
    }
    node->value = nodeVal;
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
