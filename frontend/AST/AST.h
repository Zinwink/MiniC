/**
 * @file AST.h
 * @author ZhengWenJie-mole (2732356616@qq.com)
 * @brief 抽象语法树管理文件 包含AST节点类型描述，AST节点类，以及各类AST节点的创建
 * @version 1.0
 * @date 2024-03-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <vector>
#include <deque>
#include <string>
#include <cstdint>
#include "Literal_Val.h"
#include "Type.h"
#include "Value.h"
#include "DerivedTypes.h"

/// @brief AST节点类型 枚举
enum class ast_node_type : int
{
    /*AST的叶子节点*/
    ///@brief 无符号整数字面量叶子节点
    AST_LEAF_LITERAL_UINT,

    /// @brief 有符号整数字面量节点
    AST_LEAF_LITERAL_INT,

    /// @brief 浮点数字面量节点
    AST_LEAF_LITERAL_FLOAT,

    ///@brief 标识符变量叶子节点
    AST_LEAF_VAR_ID,

    /// @brief 常量节点 const 修饰的
    AST_LEAF_CONST_VAR_ID,

    /// @brief 变量声明时定义的定义 如 int a=100
    AST_OP_VAR_DEF,

    /// @brief const 修饰的常量初始定义
    AST_OP_CONST_VAR_DEF,

    /// @brief 数组节点,可能是声明处，也可能是取址处，也可能是函数形参
    AST_OP_ARRAY,

    /// @brief const 修饰的数组
    AST_OP_CONST_ARRAY,

    /// @brief 数组初赋值 定义节点
    AST_ARRAY_DEF,

    /// @brief const修饰的数组初赋值节点
    AST_CONST_ARRAY_DEF,

    /// @brief 单个函数形参运算符节点 属性包含名字与类型
    AST_LEAF_FUNC_FORMAL_PARAM,

    /// @brief 笼统叶子节点（具体状态应该如上所示）
    AST_LEAF_TYPE,

    /*以下为AST内部节点 以及根节点*/
    /// @brief 文件编译单元运算符， 可包含函数定义，语句块，表达式等
    AST_OP_COMPILE_UNIT,

    /// @brief 左自减
    AST_OP_LEFT_SELF_SUB,

    /// @brief 右自减
    AST_OP_RIGHT_SELF_SUB,

    /// @brief 左自增
    AST_OP_LEFT_SELF_ADD,

    /// @brief 右自增
    AST_OP_RIGHT_SELF_ADD,

    /// @brief 一元运算符  负数
    AST_OP_NEG,

    ///@brief 二元运算符 +
    AST_OP_ADD,

    /// @brief 二元运算符-
    AST_OP_SUB,

    /// @brief 二元运算符*
    AST_OP_MUL,

    /// @brief 二元运算符/
    AST_OP_DIV,

    /// @brief 二元运算 %
    AST_OP_MOD,

    /// @brief 赋值语句运算符 =
    AST_OP_ASSIGN,

    /// @brief 条件与 &&
    AST_OP_COND_AND,

    /// @brief 条件或 ||
    AST_OP_COND_OR,

    /// @brief 条件非 ！
    AST_OP_COND_NOT,

    /// @brief 条件相等 ==
    AST_OP_COND_EQU,

    /// @brief 条件不等 !=
    AST_OP_COND_NOTEQU,

    /// @brief 条件小于 <
    AST_OP_COND_LESS,

    /// @brief 条件大于 >
    AST_OP_COND_GREATER,

    /// @brief 小于等于 <=
    AST_OP_COND_LESSEQU,

    /// @brief 大于等于 >=
    AST_OP_COND_GREATEREQU,

    /// @brief 多个语句组成的块运算符
    AST_OP_BLOCK,

    /// @brief 表达式语句运算符，不显示表达式的值
    AST_OP_EXPER,

    /// @brief 表达式显示语句运算符，显示表达式的值
    AST_OP_EXPER_SHOW,

    /// @brief return 语句运算符
    AST_OP_RETURN_STATEMENT,

    /// @brief 函数声明 （用于）
    AST_OP_FUNC_DECLARE,

    /// @brief 函数定义运算符，节点属性包括函数名，返回值类型，其孩子节点：函数形式参数列表运算符节点，代码块运算符
    AST_OP_FUNC_DEF,

    /// @brief 函数形式参数列表运算符，包含多个形参  AST_LEAF_FUNC_FORMAL_PARAM
    AST_OP_FUNC_FORMAL_PARAMS,

    /// @brief 函数调用运算符，属性包含函数名，孩子包含实参列表 AST_OP_FUNC_REAL_PARAMS
    AST_OP_FUNC_CALL,

    /// @brief 实参列表运算符， 可包含AST_OP_EXPR,字面量，标识符变量等
    AST_OP_FUNC_REAL_PARAMS,

    /// @brief 多个声明
    AST_OP_DECL_ITEMS,

    /// @brief 多个 const 声明
    AST_OP_CONST_DECL_ITEMS,

    /// @brief 单项声明节点
    AST_OP_DECL_ITEM,

    /// @brief if语句 ifstatement
    AST_OP_IFSTMT,

    /// @brief while循环
    AST_OP_WHILESTMT,

    /// @brief do_while循环
    AST_OP_DOWHILESTMT,

    /// @brief  空语句
    AST_OP_NULL_STMT,

    /// @brief break;
    AST_OP_BREAK,

    /// @brief continue
    AST_OP_CONTINUE,

    /// @brief 数组索引
    AST_OP_ARRAY_INDEX,

    /// @brief 非法运算符
    AST_ILLEGAL,

    /// @brief 未知类型
    AST_UNKONN,

    /// @brief 空节点类型
    AST_NULL,

};

/// @brief 抽象语法树AST节点描述类
class ast_node
{
public: // 属性
    /// @brief 父节点
    ast_node *parent = nullptr;

    /// @brief 孩子节点
    std::deque<ast_node *> sons;

    /// @brief 节点类型
    ast_node_type node_type;

    /// @brief 节点值类型 指针
    Type *attr = nullptr;

    /// @brief 节点的字面量值  包含,(标识符名,函数名,参数名，uint，int,float等字面量之一)以及所在的行号line_no
    Literal_Val literal_val;

    /// @brief 对应的Value
    ValPtr value = nullptr;

public:
    /// @brief 析构函数
    ~ast_node()
    {
        parent = nullptr;
        delete attr; // attr不共享
        attr = nullptr;
        value.reset();
    }

    /// @brief 根据抽象语法树节点类型构造,若节点类型能确定节点的值类型则指定，否则默认为TYPE_NONE
    /// @param _node_type AST节点类型
    ast_node(ast_node_type _node_type);

    /// @brief 通过字面量创建,若字面量类型能确定节点的值类型，则指定，否则默认初始化为TYPE_NONE
    /// @param literal 字面量
    /// @param _node_type 节点类型，默认为非法类型；若literal 无法确定节点类型，将由该参数指定
    ast_node(Literal_Val &literal, ast_node_type _node_type = ast_node_type::AST_ILLEGAL);
};

// 下面是一些工具函数**************************************

/// @brief 抽象语法树根节点
extern ast_node *ast_root;

/// @brief 释放内存
/// @param root
void free_ast(ast_node *root);

/// @brief 判断是否是叶子节点类型
/// @param _node_type AST节点类型
/// @return true：是叶子节点 false：内部节点
bool isLeafNodeType(ast_node_type _node_type);

/// @brief 判断是否是叶子节点
/// @param node AST节点 指针类型
/// @return true：是叶子节点 false：内部节点
bool isLeafNode(ast_node *node);

/// @brief 创建指定节点类型的节点
/// @param type 节点类型
/// @param _sons  孩子节点指针列表
/// @return 创建节点的指针
ast_node *new_ast_node(ast_node_type type, std::initializer_list<ast_node *> _sons);

/// @brief 创建指定节点类型的节点
/// @param type 节点类型
/// @param _sons  孩子节点指针列表
/// @return 创建节点的指针
ast_node *new_ast_node(Literal_Val &literal, ast_node_type type, std::initializer_list<ast_node *> _sons);

/// @brief 向父节点插入一个节点
/// @param parent 父节点
/// @param node 插入节点
/// @return 父节点指针
ast_node *insert_ast_node(ast_node *parent, ast_node *node);

/// @brief 根据字面量(将在bison语法分析中读取数据)创建叶子节点(字面量：如uint,int,float等)
/// @param literal 字面量
/// @param _node_type 节点类型,默认为AST_LEAF_TYPE
/// @return 创建的节点指针
ast_node *new_ast_leaf_node(Literal_Val &literal, ast_node_type _node_type = ast_node_type::AST_LEAF_TYPE);

/// @brief 创建函数定义节点  中间节点
/// @param literal 字面量 包含行号,函数名信息
/// @param params 函数形参列表节点,可以为空(未指定则默认参数为nullptr)
/// @param block   block块节点 如果没有
/// @param ret_type 函数定义节点的值类型(返回类型) 未指定则默认为TYPE__VOID
/// @return 创建函数定义节点指针
ast_node *create_fun_def(Literal_Val &literal, Type *ret_type, ast_node *params = nullptr, ast_node *block = nullptr);

/// @brief 创建函数声明
/// @param literal
/// @param ret_type
/// @param params
/// @return
ast_node *create_fun_declare(Literal_Val &literal, Type *ret_type, ast_node *params = nullptr);

/// @brief 创建函数形参节点
/// @param literal 字面量 包含行号 形参名
/// @param _type 参数的值类型
/// @return 创建的节点指针
ast_node *create_fun_formal_param(Literal_Val &literal, Type *_type);

/// @brief 创建函数调用节点
/// @param literal 字面量 包含行号，函数名
/// @param params 形参列表
/// @return 创建的节点指针
ast_node *create_fun_call(Literal_Val &literal, ast_node *params);

/// @brief 更新子节点类型   Bison采用规约的形式，如此可以更新子节点类型
/// @param parent
void updateDeclTypes(ast_node *parent);

// /// @brief 获取数组名
// /// @param arr
// /// @return
// std::string getNameofArray(ast_node *arr);

// /// @brief 获取数组的维度数据(如果该维度为空节点，则赋值为-1， 一般这种情况出现在函数形参中)
// /// @param arr
// /// @return
// std::vector<int> getArrayDimOrd(ast_node *arr);

/// @brief 获取数组声明时的维度
/// @param node
/// @return
std::vector<int> getArrayDeclDims(ast_node *node);

/// @brief 获取ConstExpr节点的值(int类型)
/// @param node
/// @return
int getValueofOpNode(ast_node *node);