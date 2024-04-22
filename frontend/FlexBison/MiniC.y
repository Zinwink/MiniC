%{
#include <cstdio>
#include <cstring>
// 词法分析文件
#include "FlexLexer.h"
// 语法分析头文件
#include "BisonParser.h"
#include "AST.h"

// LR语法分析失败时调用
void yyerror(const char* msg); 

%}
// 联合体声明 接待你类型  字面量读取
%union{
    class ast_node * node;
    class Literal_Val* literal;
};

// 文法开始符号
%start CompileUnit

// 指定文法终结符号 字面量
%token <literal> DIGIT_INT  DIGIT_ID   DIGIT_FLOAT
// 运算符
%token T_ADD "+" T_SUB "-" T_DIV "/" T_MUL "*" T_ASSIGN "=" T_MOD "%"
// 关键字
%token T_INT "int" T_FLOAT "float" T_VOID "void" T_IF "if" T_ELSE "else" T_RETURN "return" T_WHILE "while" T_DO "do"
%token T_BREAK "break" T_CONTINUE "continue"
// 条件运算
%token T_EQUAL "==" T_NOT_EQU "!=" T_LESS "<" T_GREATER ">" T_LESS_EQU "<=" T_GREATER_EQU ">=" T_NOT "!" T_AND "&&" T_OR "||"
// 括弧
%token T_LBRACE "{" T_RBRACE "}" T_LPAREN "(" T_RPAREN ")" T_LSQU "[" T_RSQU "]"
// 标点
%token T_COMMA "," T_SEMICOLON ";"
// 结合性与优先级
%left T_ADD T_SUB 
%left T_MUL T_DIV T_MOD
%left T_EQUAL T_NOT_EQU T_LESS T_LESS_EQU T_GREATER T_GREATER_EQU T_AND T_OR
%right T_NOT

%type <node> CompileUnit
%type <node> FuncDef
%type <node> FuncFormalParams
%type <node> FuncFormalParam
%type <node> FuncRealParams
%type <node> Block
%type <node> BlockItemList
%type <node> Statement
%type <node> IfStmt
%type <node> WhileStmt
%type <node> DowhileStmt
%type <node> Condition
%type <node> OrCond
%type <node> AndCond
%type <node> NotCond
%type <node> EquCondTerm
%type <node> LessCondTerm
%type <node> Declare
%type <node> DeclareItems
%type <node> DeclareItem
%type <node> var
%type <node> Expr
%type <node> AddExpr
%type <node> MulExpr
%type <node> UnaryExpr
%type <node> Term


%%
/* 编译单元 */
CompileUnit : FuncDef{
    $$= new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,1,$1);  // 创建一个节点compileUnit，该节点包含Funcdef子节点
    ast_root=$$;
}
| CompileUnit FuncDef{
    $$=insert_ast_node($1,$2);  // 插入节点
}
| Statement{
    $$=new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,1,$1);
    ast_root=$$;
}
| CompileUnit Statement{
    $$=insert_ast_node($1,$2);
}
;

/* 函数定义 */
FuncDef : "int" DIGIT_ID "(" ")" Block{
    $$=create_fun_def(*$2,$5,nullptr,BasicValueType::TYPE_INT32);
    delete $2; //释放内存
    $2=nullptr;
}
| "int" DIGIT_ID "(" FuncFormalParams ")" Block{
    $$=create_fun_def(*$2,$6,$4,BasicValueType::TYPE_INT32);
    delete $2; //释放内存
    $2=nullptr;
}
| "void" DIGIT_ID "(" ")" Block{
    $$=create_fun_def(*$2,$5,nullptr,BasicValueType::TYPE_VOID);
    delete $2; //释放内存
    $2=nullptr;
}
| "void" DIGIT_ID "(" FuncFormalParams ")" Block{
    $$=create_fun_def(*$2,$6,$4,BasicValueType::TYPE_VOID);
    delete $2; //释放内存
    $2=nullptr;
}
| "float" DIGIT_ID "(" ")" Block{
    $$=create_fun_def(*$2,$5,nullptr,BasicValueType::TYPE_FLOAT);
    delete $2; //释放内存
    $2=nullptr;
}
| "float" DIGIT_ID "(" FuncFormalParams ")" Block{
    $$=create_fun_def(*$2,$6,$4,BasicValueType::TYPE_FLOAT);
    delete $2; //释放内存
    $2=nullptr;
}
;

/* 函数参数 */
FuncFormalParams : FuncFormalParam {
    $$ = new_ast_node(ast_node_type::AST_OP_FUNC_FORMAL_PARAMS,1,$1);
}
| FuncFormalParams "," FuncFormalParam {
    $$ =insert_ast_node($1,$3);
}
;

/* 函数参数 */
FuncFormalParam : "int" DIGIT_ID{
    $$=create_fun_formal_param(*$2,BasicValueType::TYPE_INT32);
    delete $2; //释放内存
    $2=nullptr;
}
| "float" DIGIT_ID{
    $$=create_fun_formal_param(*$2,BasicValueType::TYPE_FLOAT);
    delete $2; //释放内存
    $2=nullptr;
}
;

/* 语句块 */
Block : "{" "}"{
    $$= new ast_node(ast_node_type::AST_OP_BLOCK);
    // 无操作
}
| "{" BlockItemList "}" {
    // 语句块中的语句列表 语句块指针指向语句列表
    $$ = $2;
}
;

/* 语句块内语句列表 */
BlockItemList : Statement {
    $$ = new_ast_node(ast_node_type::AST_OP_BLOCK,1,$1);
}
| BlockItemList Statement {
    $$ = insert_ast_node($1,$2);
}
;

/* 语句 *****************************************************/
Statement : "return" Expr ";" {
    //返回语句
    $$ = new_ast_node(ast_node_type::AST_OP_RETURN_STATEMENT,1,$2);
}
| "return" ";"{
    //无返回值
    $$=new ast_node(ast_node_type::AST_OP_RETURN_STATEMENT);
}
| Block {
    $$=$1;
}
| IfStmt {
    $$=$1;
}
| WhileStmt {
    $$=$1;
}
| DowhileStmt {
    $$=$1;
}
| Declare {
    $$=$1;
}
| var "=" Expr ";" {
    $$ = new_ast_node(ast_node_type::AST_OP_ASSIGN,2,$1,$3);
}
| Expr ";"{
    ; // 仅仅有一个表达式(可能是一个函数调用，也可能是a+b表达式)  目前先设定无动作
}
| "break" ";" {
    ; // break语句
}
| "continue" ";" {
    ;  //continue语句
}
;

/* 条件if else *************** */
IfStmt : "if" "(" Condition ")" Statement {
    $$=new_ast_node(ast_node_type::AST_OP_IFSTMT,2,$3,$5);
}
| "if" "(" Condition ")" Statement "else" Statement {
    $$=new_ast_node(ast_node_type::AST_OP_IFSTMT,3,$3,$5,$7);
}
;

/* 循环 while */
WhileStmt : "while" "(" Condition ")" Statement {
    $$=new_ast_node(ast_node_type::AST_OP_WHILESTMT,2,$3,$5);
}
;

/* do-while循环 */
DowhileStmt : "do" Statement "while" "(" Condition ")" ";" {
    $$=new_ast_node(ast_node_type::AST_OP_DOWHILESTMT,2,$2,$5);
}
;


/* 复合条件 */
Condition : OrCond {
    $$=$1;
}
;

OrCond : AndCond {
    $$=$1;
}
| OrCond "||" AndCond {
   $$=new_ast_node(ast_node_type::AST_OP_COND_OR,2,$1,$3);
}
;

AndCond : NotCond {
  $$=$1;
}
| AndCond "&&" NotCond {
   $$=new_ast_node(ast_node_type::AST_OP_COND_AND,2,$1,$3);
}
;

NotCond : "!" EquCondTerm {
  $$=new_ast_node(ast_node_type::AST_OP_COND_NOT,1,$2);
}
| EquCondTerm {
  $$=$1;
}
;

EquCondTerm : LessCondTerm {
   $$=$1;
}
| EquCondTerm "==" LessCondTerm {
   $$=new_ast_node(ast_node_type::AST_OP_COND_EQU,2,$1,$3);
}
| EquCondTerm "!=" LessCondTerm {
    $$=new_ast_node(ast_node_type::AST_OP_COND_NOTEQU,2,$1,$3);
}
;

// < > >= 等比较  最底层的条件 表达式的值也做条件之一
LessCondTerm : Expr {
   $$=$1;
}
| LessCondTerm "<" Expr {
   $$=new_ast_node(ast_node_type::AST_OP_COND_LESS,2,$1,$3);
}
| LessCondTerm "<=" Expr {
   $$=new_ast_node(ast_node_type::AST_OP_COND_LESSEQU,2,$1,$3);
}
| LessCondTerm ">" Expr {
  $$=new_ast_node(ast_node_type::AST_OP_COND_GREATER,2,$1,$3);
} 
| LessCondTerm ">=" Expr {
  $$=new_ast_node(ast_node_type::AST_OP_COND_GREATEREQU,2,$1,$3);
}
| "(" Condition ")" {
  $$=$2;
}
;

/* 变量声明定义******************************* */
Declare : "int" DeclareItems ";"{
    // 先指明DeclareItems下的值类型 ValueType  
    $2->val_type=BasicValueType::TYPE_INT32;
    $$=$2;
}
| "float" DeclareItems ";"{
    $2->val_type=BasicValueType::TYPE_FLOAT;
    $$=$2;
}
;

//包含多项声明
DeclareItems : DeclareItem{
    if($1->node_type==ast_node_type::AST_LEAF_VAR_ID){
        $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,1,$1);
    }else{
        // 是assign赋值形式,为了后继方便翻译这里将声明和赋值区分
        ast_node* left=$1->sons[0];  //左边的声明变量
        $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,2,left,$1);
    }
}
| DeclareItems "," DeclareItem{
    if($3->node_type==ast_node_type::AST_LEAF_VAR_ID){
        $$=insert_ast_node($1,$3);  // DeclareItem是变量类型
    }else{
        // DeclareItem是赋值类型
        ast_node* left=$3->sons[0]; //左边的声明变量
        $$=insert_ast_node($1,left);  //插入left 声明变量
        $$=insert_ast_node($1,$3);  //插入 后继操作:赋值节点
    }
    
}
;
// 单项声明
DeclareItem : var{
    // 无动作
    // $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,$1);
    $$=$1;
}
| var "=" Expr {
    ast_node* node=new_ast_node(ast_node_type::AST_OP_ASSIGN,2,$1,$3);
    $$=node;
    // $$ = new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,node);
}
;



/* 表达式 *********************************************************/
Expr : AddExpr {
    $$=$1;
}
;

/* 加，减运算 */
AddExpr: MulExpr {
    // MulExpr可以推导得到UnaryExpr  这样写保证乘除取余的优先级
    $$=$1;
}
| AddExpr "+" MulExpr {
    $$=new_ast_node(ast_node_type::AST_OP_ADD,2,$1,$3);
}
| AddExpr "-" MulExpr {
    $$=new_ast_node(ast_node_type::AST_OP_SUB,2,$1,$3);
}
;

/* 乘 除 取余 运算 */
MulExpr : UnaryExpr {
    $$=$1;
}
| MulExpr "*" UnaryExpr {
    $$=new_ast_node(ast_node_type::AST_OP_MUL,2,$1,$3);
}
| MulExpr "/" UnaryExpr {
    $$=new_ast_node(ast_node_type::AST_OP_DIV,2,$1,$3);
}
| MulExpr "%" UnaryExpr {
    $$=new_ast_node(ast_node_type::AST_OP_MOD,2,$1,$3);
}
;

/* 基本运算表达式 */
UnaryExpr : Term {
    $$=$1;
}
| DIGIT_ID "(" FuncRealParams ")" {
    // 有参函数调用的值
    $$=create_fun_call(*$1,$3);
    delete $1; //释放内存
    $1=nullptr;
}
| DIGIT_ID "(" ")" {
    //无参函数调用的值
    $$=create_fun_call(*$1,nullptr);
    delete $1; //释放内存
    $1=nullptr;
}
;


/* 只含单个字面量或者变量的表达式 */
Term :  DIGIT_INT{
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_LITERAL_INT,BasicValueType::TYPE_INT32);
    delete $1; //释放内存
    $1=nullptr;
}
| DIGIT_FLOAT {
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_LITERAL_FLOAT,BasicValueType::TYPE_FLOAT);
    delete $1; //释放内存
    $1=nullptr;
}
| var {
    $$=$1;
}
| "(" Expr ")" {
    $$=$2;
}
;

/* 变量 暂时无数组类型 */
var : DIGIT_ID {
    $$ = new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_VAR_ID);
    delete $1; //释放内存
    $1=nullptr;
}
;

/* 函数实参列表 */
FuncRealParams : Expr {
    $$=new_ast_node(ast_node_type::AST_OP_FUNC_REAL_PARAMS,1,$1);
}
| FuncRealParams "," Expr {
    $$=insert_ast_node($1,$3);
}
;

%%

// 语法分析时的错误信息
void yyerror(const char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}