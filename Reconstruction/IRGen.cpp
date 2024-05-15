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
    ast2ir_handers[ast_node_type::AST_OP_FUNC_DEF] = &IRGen::ir_func_define;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGen::ir_func_formal_params;
    ast2ir_handers[ast_node_type::AST_OP_RETURN_STATEMENT] = &IRGen::ir_return;
    ast2ir_handers[ast_node_type::AST_OP_FUNC_CALL] = &IRGen::ir_funcall;

    // 一些变量节点 varid  int float
    ast2ir_handers[ast_node_type::AST_LEAF_LITERAL_INT] = &IRGen::ir_leafNode_int;
    ast2ir_handers[ast_node_type::AST_LEAF_LITERAL_FLOAT] = &IRGen::ir_leafNode_float;
    ast2ir_handers[ast_node_type::AST_LEAF_VAR_ID] = &IRGen::ir_leafNode_var;
    ast2ir_handers[ast_node_type::AST_LEAF_ARRAY] = &IRGen::ir_leafNode_array;

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

    // 条件相关的节点 if  while do while
    ast2ir_handers[ast_node_type::AST_OP_IFSTMT] = &IRGen::ir_if_Stmt;
    ast2ir_handers[ast_node_type::AST_OP_WHILESTMT] = &IRGen::ir_while_Stmt;
    ast2ir_handers[ast_node_type::AST_OP_DOWHILESTMT] = &IRGen::ir_Dowhile_Stmt;
    ast2ir_handers[ast_node_type::AST_OP_COND_OR] = &IRGen::ir_Cond_OR;   //  ||
    ast2ir_handers[ast_node_type::AST_OP_COND_AND] = &IRGen::ir_Cond_AND; // &&
    ast2ir_handers[ast_node_type::AST_OP_COND_LESS] = &IRGen::ir_cmp_less;
    ast2ir_handers[ast_node_type::AST_OP_COND_GREATER] = &IRGen::ir_cmp_greater;
    ast2ir_handers[ast_node_type::AST_OP_COND_EQU] = &IRGen::ir_cmp_equal;
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
        Exit->AddInstBack(RetInst::get()); // 出口处加入ret指令
    }
    else
    {
        InstPtr allocaRet = AllocaInst::get("", Type::copy(fun->getReturnTy())); // 非void
        fun->insertAllocaInst(allocaRet);                                        // 加入创建的返回值临时变量
        InstPtr load = LoadInst::get(allocaRet);
        Exit->AddInstBack(load);
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
        assert(transmitBlocks.size() == 1 && ">>>Error!Basic block not aligned with corresponding program during program execution! file: IRGen.cpp");
        // 基本块流中还存在基本块
        // 函数无返回值  加入跳转至Exit指令
        BranchInstPtr br = BranchInst::get(Exit);
        getCurBlock()->AddInstBack(br);
    }
    // 结束翻译函数时curFun赋值为nullptr,函数符号表弹出栈
    scoper->curFun() = nullptr;
    scoper->popTab(); // 弹栈

    transmitBlocks.clear(); // 弹出函数中剩余的最后一个基本块   流队列的方式
    fun->mergeAllocaToEntry();
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
    for (auto &son : node->sons)
    {
        string argName = son->literal_val.digit.id;     // 形参名
        ArgPtr arg = Argument::get(son->attr, argName); // 形参对象
        son->attr = nullptr;
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
            fun_f->insertAllocaInst(alloca);            // 加入AllocaInst
            fun_f->getEntryBlock()->AddInstBack(store); // 加入store指令
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

    // 进入翻译循环前需弹出前一个block, 因为循环在新的一个块开始
    BranchInstPtr br = BranchInst::get(whileEntry);
    getCurBlock()->AddInstBack(br);
    transmitBlocks.pop_front();
    curUsedBlockIter = std::next(curUsedBlockIter);

    // 下面正式翻译循环
    ast_node *cond = ir_visit_astnode(node->sons[0], {blockEntry, whileExit}); // 传入 循环体口，循环出口
    if (cond == nullptr)
        return false;
    ast_node *whileBody = ir_visit_astnode(node->sons[1], {whileEntry}); // 传入循环入口
    if (whileBody == nullptr)
        return false;
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

    // 进入翻译循环前需弹出前一个block, 因为循环在新的一个块开始
    BranchInstPtr br = BranchInst::get(whileEntry);
    getCurBlock()->AddInstBack(br);
    transmitBlocks.pop_front();
    curUsedBlockIter = std::next(curUsedBlockIter);

    // 下面正式翻译循环
    ast_node *whileBody = ir_visit_astnode(node->sons[0], {}); // 传入循环入口
    if (whileBody == nullptr)
        return false;
    ast_node *cond = ir_visit_astnode(node->sons[1], {whileEntry, whileExit}); // 传入 循环体口，循环出口
    if (cond == nullptr)
        return false;
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
        getCurBlock()->AddInstBack(BranchInst::get(blocks[0]));
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
        StoreInst::create(std::move(result->value), scoper->curFun()->getAllocaLists().front(), getCurBlock()); // 保存返回值
    }
    BranchInstPtr br = BranchInst::get(scoper->curFun()->getExitBlock());
    getCurBlock()->AddInstBack(br);
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
        std::cout << ">>>Error: no such function:" << funcname << "line: " << lineno << std::endl;
        return false;
    }
    ast_node *realParams = node->sons[0]; // 实参列表
    std::vector<ValPtr> realArgs;         // 记录实参值
    for (auto &son : realParams->sons)
    { // son为实参
        ast_node *result = ir_visit_astnode(son, {});
        if (result == nullptr)
            return false;
        realArgs.push_back(std::move(result->value)); // 记录实参值Value
    }
    CallInstPtr call = CallInst::create(fun, realArgs, getCurBlock());
    node->value = call; // 记录 value(对于有返回值的函数有作用)
    return true;
}

/// @brief AST  ASSIGN赋值节点对应的函数操作
/// @param node
/// @return
bool IRGen::ir_assign(ast_node *node, LabelParams blocks)
{
    ast_node *left = ir_visit_astnode(node->sons[0], blocks);
    if (left == nullptr)
    {
        return false;
    }
    ast_node *right = ir_visit_astnode(node->sons[1], blocks);
    if (right == nullptr)
        return false;
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
        ast_node *result = ir_visit_astnode(son, blocks);
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
    ast_node *left = ir_visit_astnode(node->sons[0], blocks);
    if (left == nullptr)
    {
        return false;
    }
    ast_node *right = ir_visit_astnode(node->sons[1], blocks);
    if (right == nullptr)
        return false;
    if (left->value->isConstant() && right->value->isConstant())
    {
        // 如果加法的两者均为常数 则直接相加运算 (目前默认只实现整数的加法运算)
        ConstantIntPtr left_const = std::static_pointer_cast<ConstantInt>(left->value);
        ConstantIntPtr right_const = std::static_pointer_cast<ConstantInt>(right->value);
        int res = left_const->getValue() + right_const->getValue();
        ConstantIntPtr resPtr = ConstantInt::get(32);
        resPtr->setValue(res); // 设置常数值
        node->value = resPtr;
    }
    else
    { // 不都是常数
        BinaryOperatorPtr binaryOp = BinaryOperator::create(Opcode::AddInteger, left->value, right->value, getCurBlock());
        node->value = binaryOp;
    }

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
        transmitBlocks.pop_front();
        curUsedBlockIter = std::next(curUsedBlockIter);
    }
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
        // node->value = val;
        // 下面获取索引对应的偏移
    }

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
