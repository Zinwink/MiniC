/**
 * @file IRGen.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief IR的产生以及  IR的打印成字符串
 * @version 1.0
 * @date 2024-05-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "AST.h"
#include "BaseSymTab.h"
#include "ScopeMg.h"
#include "BasicBlock.h"
#include "Module.h"
#include <stack>
class IRGen;
using IRGenPtr = std::shared_ptr<IRGen>;
using LabelParams = std::vector<BasicBlockPtr>;
class IRGen
{
private:
    ast_node *ast_root;        // AST根节点
    ScopeMg *scoper = nullptr; // 作用域管理
    ModulePtr module;          // module  存放全局变量列表，函数列表
    /// @brief AST的节点操作函数指针, 第二个参数用于传递基本快(用于条件语句，分支语句的使用,传递基本快参数指针)
    typedef bool (IRGen::*ast2ir_handler_t)(ast_node *, LabelParams blocks);

    /// @brief 节点类型--函数操作的对应哈希表
    std::unordered_map<ast_node_type, ast2ir_handler_t> ast2ir_handers;

    std::list<BasicBlockPtr> transmitBlocks; // 传递基本快参数  基本快流

    bblockIter curUsedBlockIter; // 当前函数所使用的基本块指向迭代器(便于插入创建的基本块)

    // 为了不改动大量代码  在此基础上实现 break, continue的翻译 故出此下策 使用两个栈维护  循环的入口 循环的出口， 以循环先进后出的形式实现对 break,continue翻译
    std::stack<BasicBlockPtr> loopEntrys; // 循环入口 continue使用
    std::stack<BasicBlockPtr> loopExits;  // 循环出口 break使用

public:
    /// @brief 析构函数
    ~IRGen();

    /// @brief 构造函数
    /// @param root
    /// @param _module
    IRGen(ast_node *root, ModulePtr _module);

    /// @brief 创建IRGen对象
    /// @param root
    /// @param _module
    /// @return
    static IRGenPtr get(ast_node *root, ModulePtr _module);

    /// @brief 运行产生线性IR
    /// @return
    bool run();

private:
    /// @brief 获取基本块流中的当前基本块
    /// @return
    BasicBlockPtr &getCurBlock();

    /// @brief 在当前block后面插入blocks,并在函数中对应的当前block后插入基本块
    /// @param fun  基本块所需插入对应的的函数位置对象
    /// @param block
    void insertAtCurBlockBack(FuncPtr fun, LabelParams blocks);

    /// @brief 根据AST节点的类型查找相应的函数操作并执行
    /// @return nullptr表示运行失败，否则返回node指针
    ast_node *
    ir_visit_astnode(ast_node *node, LabelParams blocks);

    /// @brief 对AST compileUnit的翻译函数
    /// @param node 抽象书节点
    /// @return 成功 true  失败false
    bool ir_CompileUnit(ast_node *node, LabelParams blocks);

    /// @brief AST  function define节点对应的函数操作
    /// @param node
    /// @return
    bool ir_func_define(ast_node *node, LabelParams blocks);

    /// @brief AST  函数形参列表节点对应的操作函数
    /// @param node
    /// @return
    bool ir_func_formal_params(ast_node *node, LabelParams blocks);

    /// @brief if 语句
    /// @param node
    /// @param blocks
    /// @return
    bool ir_if_Stmt(ast_node *node, LabelParams blocks);

    /// @brief while语句
    /// @param node
    /// @param blocks
    /// @return
    bool ir_while_Stmt(ast_node *node, LabelParams blocks);

    /// @brief do while语句
    /// @param node
    /// @param blocks
    /// @return
    bool ir_Dowhile_Stmt(ast_node *node, LabelParams blocks);

    /// @brief 循环中 break语句的翻译
    /// @param node
    /// @param blocks
    /// @return
    bool ir_break(ast_node *node, LabelParams blocks);

    /// @brief 循环中 continue语句的翻译
    /// @param node
    /// @param blocks
    /// @return
    bool ir_continue(ast_node *node, LabelParams blocks);

    /// @brief AST中block节点对应的函数操作
    /// @param node
    /// @return
    bool ir_block(ast_node *node, LabelParams blocks);

    /// @brief AST中 return 节点对应的函数操作
    /// @param node
    /// @return
    bool ir_return(ast_node *node, LabelParams blocks);

    /// @brief AST函数调用节点对应的操作
    /// @param node
    /// @return
    bool ir_funcall(ast_node *node, LabelParams blocks);

    /// @brief AST   DeclarationItems节点对应的操作函数
    /// @param node
    /// @return
    bool ir_declItems(ast_node *node, LabelParams blocks);

    /// @brief AST  ASSIGN赋值节点对应的函数操作
    /// @param node
    /// @return
    bool ir_assign(ast_node *node, LabelParams blocks);

    /// @brief 取负号
    /// @param node
    /// @param blocks
    /// @return
    bool ir_Negative(ast_node *node, LabelParams blocks);

    /// @brief AST 加法操作节点对应的函数操作
    /// @param node
    /// @return
    bool ir_add(ast_node *node, LabelParams blocks);

    /// @brief AST 减法节点对应的操作
    /// @param node
    /// @return
    bool ir_sub(ast_node *node, LabelParams blocks);

    /// @brief AST 乘法节点对应的操作
    /// @param node
    /// @return
    bool ir_mul(ast_node *node, LabelParams blocks);

    /// @brief AST 除法节点对应的操作
    /// @param node
    /// @return
    bool ir_div(ast_node *node, LabelParams blocks);

    /// @brief AST 取余节点对应的操作
    /// @param node
    /// @return
    bool ir_mod(ast_node *node, LabelParams blocks);

    /// @brief 条件或 || 翻译
    /// @param node
    /// @param blocks
    /// @return
    bool ir_Cond_OR(ast_node *node, LabelParams blocks);

    /// @brief 条件 && 翻译
    /// @param node
    /// @param blocks
    /// @return
    bool ir_Cond_AND(ast_node *node, LabelParams blocks);

    /// @brief AST < 节点对应的操作
    /// @param node
    /// @return
    bool ir_cmp_less(ast_node *node, LabelParams blocks);

    /// @brief AST  > 节点对应的操作
    /// @param node
    /// @return
    bool ir_cmp_greater(ast_node *node, LabelParams blocks);

    /// @brief AST == 节点对应的操作
    /// @param node
    /// @return
    bool ir_cmp_equal(ast_node *node, LabelParams blocks);

    /// @brief AST  != 对应操作
    /// @param node
    /// @param blocks
    /// @return
    bool ir_cmp_notEqual(ast_node *node, LabelParams blocks);

    /// @brief AST <=
    /// @param node
    /// @param blocks
    /// @return
    bool ir_cmp_lessEqual(ast_node *node, LabelParams blocks);

    /// @brief AST  >=
    /// @param node
    /// @param blocks
    /// @return
    bool ir_cmp_greaterEqual(ast_node *node, LabelParams blocks);

    /// @brief 对于int字面量AST节点的操作 AST_LEAF_LITERAL_INT,
    /// @param node AST int字面量节点
    /// @return true成功 false失败
    bool ir_leafNode_int(ast_node *node, LabelParams blocks);

    /// @brief 对于float字面量AST节点的操作 AST_LEAF_LITERAL_FLOAT
    /// @param node AST float字面量节点
    /// @return
    bool ir_leafNode_float(ast_node *node, LabelParams blocks);

    /// @brief 对于AST_LEAF_VAR_ID(变量)的函数操作
    /// @param node
    /// @return
    bool ir_leafNode_var(ast_node *node, LabelParams blocks);

    /// @brief 数组节点
    /// @param node
    /// @param blocks
    /// @return
    bool ir_leafNode_array(ast_node *node, LabelParams blocks);
};