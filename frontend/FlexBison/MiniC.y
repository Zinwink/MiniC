%{
#include <cstdio>
#include <cstring>
#include <vector>
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
%token <literal> T_BREAK "break" T_CONTINUE "continue"
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
%type <node> Array
%type <node> var
%type <node> Expr
%type <node> AddExpr
%type <node> MulExpr
%type <node> UnaryExpr
%type <node> Term


%%
/* 编译单元 */
CompileUnit : FuncDef{
    $$= new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,{$1});  // 创建一个节点compileUnit，该节点包含Funcdef子节点
    ast_root=$$;
}
| CompileUnit FuncDef{
    $$=insert_ast_node($1,$2);  // 插入节点
}
| Statement{
    $$=new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,{$1});
    ast_root=$$;
}
| CompileUnit Statement{
    $$=insert_ast_node($1,$2);
}
;

/* 函数定义 */
FuncDef : "int" DIGIT_ID "(" ")" Block{
    Type* funType=FunctionType::get(Type::getIntNType(32));
    $$=create_fun_def(*$2,funType,nullptr,$5);
    delete $2; //释放内存
    $2=nullptr;
}
| "int" DIGIT_ID "(" FuncFormalParams ")" Block{
    std::vector<Type*> argsTy;
    for(auto& son:$4->sons){
        argsTy.push_back(Type::copy(son->attr));
    }
    Type* funType=FunctionType::get(Type::getIntNType(32),argsTy);
    $$=create_fun_def(*$2,funType,$4,$6);
    delete $2; //释放内存
    $2=nullptr;
}
| "void" DIGIT_ID "(" ")" Block{
    Type* funType=FunctionType::get(Type::getVoidType());
    $$=create_fun_def(*$2,funType,nullptr,$5);
    delete $2; //释放内存
    $2=nullptr;
}
| "void" DIGIT_ID "(" FuncFormalParams ")" Block{
    std::vector<Type*> argsTy;
    for(auto& son:$4->sons){
        argsTy.push_back(Type::copy(son->attr));
    }
    Type* funType=FunctionType::get(Type::getVoidType(),argsTy);
    $$=create_fun_def(*$2,funType,$4,$6);
    delete $2; //释放内存
    $2=nullptr;
}
| "float" DIGIT_ID "(" ")" Block{
    Type* funType=FunctionType::get(Type::getFloatType());
    $$=create_fun_def(*$2,funType,nullptr,$5);
    delete $2; //释放内存
    $2=nullptr;
}
| "float" DIGIT_ID "(" FuncFormalParams ")" Block{
    std::vector<Type*> argsTy;
    for(auto& son:$4->sons){
        argsTy.push_back(Type::copy(son->attr));
    }
    Type* funType=FunctionType::get(Type::getFloatType(),argsTy);
    $$=create_fun_def(*$2,funType,$4,$6);
    delete $2; //释放内存
    $2=nullptr;
}
;

/* 函数参数 */
FuncFormalParams : FuncFormalParam {
    $$ = new_ast_node(ast_node_type::AST_OP_FUNC_FORMAL_PARAMS,{$1});
}
| FuncFormalParams "," FuncFormalParam {
    $$ =insert_ast_node($1,$3);
}
;

/* 函数参数 */
FuncFormalParam : "int" DIGIT_ID{
    $$=create_fun_formal_param(*$2,Type::getIntNType(32));
    delete $2; //释放内存
    $2=nullptr;
}
| "float" DIGIT_ID{
    $$=create_fun_formal_param(*$2,Type::getFloatType());
    delete $2; //释放内存
    $2=nullptr;
}
| "int" Array{
    $2->node_type=ast_node_type::AST_LEAF_FUNC_FORMAL_PARAM;
    std::vector<int> dims=getArrayDimOrd($2);
    ArrayType* temp=ArrayType::get(dims,Type::getIntNType(32));
    Type* containedTy=temp->getContainedTy();
    temp->getContainedTy()=nullptr;
    delete temp;
    PointerType* ptr=PointerType::get(containedTy);  //指针类型
    $2->attr=ptr;
    $$=$2;
}
| "float" Array{
    $2->node_type=ast_node_type::AST_LEAF_FUNC_FORMAL_PARAM;
    std::vector<int> dims=getArrayDimOrd($2);
    ArrayType* temp=ArrayType::get(dims,Type::getFloatType());
    Type* containedTy=temp->getContainedTy();
    temp->getContainedTy()=nullptr;
    delete temp;
    PointerType* ptr=PointerType::get(containedTy);  //指针类型
    $2->attr=ptr;
    $$=$2;
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
    $$ = new_ast_node(ast_node_type::AST_OP_BLOCK,{$1});
}
| BlockItemList Statement {
    $$ = insert_ast_node($1,$2);
}
;

/* 语句 *****************************************************/
Statement : "return" Expr ";" {
    //返回语句
    $$ = new_ast_node(ast_node_type::AST_OP_RETURN_STATEMENT,{$2});
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
/* | var "=" Expr ";" {
    $$ = new_ast_node(ast_node_type::AST_OP_ASSIGN,2,$1,$3);
} */
/* | Expr ";"{
    ; // 仅仅有一个表达式(可能是一个函数调用，也可能是a+b表达式)  目前先设定无动作
} */
| Condition ";"{
    // 无动作
}
| var "=" Condition ";"{
    $$ = new_ast_node(ast_node_type::AST_OP_ASSIGN,{$1,$3});
}
| "break" ";" {
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_OP_BREAK);
    delete $1; //释放内存
    $1=nullptr;
}
| "continue" ";" {
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_OP_CONTINUE);  //continue语句
    delete $1; //释放内存
    $1=nullptr;
}
| Array "=" Condition ";"{
    $$=new_ast_node(ast_node_type::AST_OP_ASSIGN,{$1,$3});
}
;

/* 条件if else *************** */
IfStmt : "if" "(" Condition ")" Statement {
    // statement 可以是block,也可以是单条语句，为了方便处理，这里需要进行判断，在AST抽象语法树上统一显示block
    if($5->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{$5});
        $$=new_ast_node(ast_node_type::AST_OP_IFSTMT,{$3,block});
    }
    else{
        $$=new_ast_node(ast_node_type::AST_OP_IFSTMT,{$3,$5});
    }
}
| "if" "(" Condition ")" Statement "else" Statement {
    if($5->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{$5});
        $5=block;
    }
    if($7->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{$7});
        $7=block;
    }
    $$=new_ast_node(ast_node_type::AST_OP_IFSTMT,{$3,$5,$7});
}
;

/* 循环 while */
WhileStmt : "while" "(" Condition ")" Statement {
    if($5->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{$5});
        $5=block;
    }
    $$=new_ast_node(ast_node_type::AST_OP_WHILESTMT,{$3,$5});
}
;

/* do-while循环 */
DowhileStmt : "do" Statement "while" "(" Condition ")" ";" {
     if($2->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{$2});
        $2=block;
    }
    $$=new_ast_node(ast_node_type::AST_OP_DOWHILESTMT,{$2,$5});
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
   $$=new_ast_node(ast_node_type::AST_OP_COND_OR,{$1,$3});
}
;

AndCond : NotCond {
  $$=$1;
}
| AndCond "&&" NotCond {
   $$=new_ast_node(ast_node_type::AST_OP_COND_AND,{$1,$3});
}
;

NotCond : "!" EquCondTerm {
  $$=new_ast_node(ast_node_type::AST_OP_COND_NOT,{$2});
}
| EquCondTerm {
  $$=$1;
}
;

EquCondTerm : LessCondTerm {
   $$=$1;
}
| EquCondTerm "==" LessCondTerm {
   $$=new_ast_node(ast_node_type::AST_OP_COND_EQU,{$1,$3});
}
| EquCondTerm "!=" LessCondTerm {
    $$=new_ast_node(ast_node_type::AST_OP_COND_NOTEQU,{$1,$3});
}
;

// < > >= 等比较  最底层的条件 表达式的值也做条件之一
LessCondTerm : Expr {
   $$=$1;
}
| LessCondTerm "<" Expr {
   $$=new_ast_node(ast_node_type::AST_OP_COND_LESS,{$1,$3});
}
| LessCondTerm "<=" Expr {
   $$=new_ast_node(ast_node_type::AST_OP_COND_LESSEQU,{$1,$3});
}
| LessCondTerm ">" Expr {
  $$=new_ast_node(ast_node_type::AST_OP_COND_GREATER,{$1,$3});
} 
| LessCondTerm ">=" Expr {
  $$=new_ast_node(ast_node_type::AST_OP_COND_GREATEREQU,{$1,$3});
}
| "(" Condition ")" {
  $$=$2;
}
;

/* 变量声明定义******************************* */
Declare : "int" DeclareItems ";"{
    // 先指明DeclareItems下的值类型 ValueType  
    $2->attr=Type::getIntNType(32);
    $$=$2;
    updateDeclTypes($2); //更新神名的变量 数组类型

}
| "float" DeclareItems ";"{
    $2->attr=Type::getFloatType();
    $$=$2;
    updateDeclTypes($2); 
}
;

//包含多项声明
DeclareItems : DeclareItem{  
    if($1->node_type==ast_node_type::AST_LEAF_VAR_ID){
        // $1->attr=$$->attr;
        $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,{$1});
    }
    else if($1->node_type==ast_node_type::AST_OP_ARRAY){
        $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,{$1});
    }
    else{
        // 是assign赋值形式,为了后继方便翻译这里将声明和赋值区分
        // $1->sons[0]->attr=$$->attr;
        ast_node* left=new ast_node(*($1->sons[0]));  //左边的声明变量(拷贝构造产生新的节点)
        $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,{left,$1});
    }
}
| DeclareItems "," DeclareItem{
    if($3->node_type==ast_node_type::AST_LEAF_VAR_ID){
        // $3->attr=$$->attr;
        $$=insert_ast_node($1,$3);  // DeclareItem是变量类型
    }
    else if($3->node_type==ast_node_type::AST_OP_ARRAY){
        $$=insert_ast_node($1,$3);
    }
    else{
        // DeclareItem是赋值类型
        // $3->sons[0]->attr=$$->attr;
        ast_node* left=new ast_node(*($3->sons[0])); //左边的声明变量
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
    ast_node* node=new_ast_node(ast_node_type::AST_OP_ASSIGN,{$1,$3});
    $$=node;
    // $$ = new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,node);
}
| Array{
    $$=$1;
}
;


/* 数组******************************* */
Array: DIGIT_ID "[" Expr "]"{
    $$=new_ast_node(*$1,ast_node_type::AST_OP_ARRAY,{$3});
}
| DIGIT_ID "[" "]" {
    ast_node* nullNode=new ast_node(ast_node_type::AST_NULL); //创建一个空节点
    $$=new_ast_node(*$1,ast_node_type::AST_OP_ARRAY,{nullNode});
}
|Array "[" Expr "]" {
    $$=insert_ast_node($1,$3);
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
    $$=new_ast_node(ast_node_type::AST_OP_ADD,{$1,$3});
}
| AddExpr "-" MulExpr {
    $$=new_ast_node(ast_node_type::AST_OP_SUB,{$1,$3});
}
;

/* 乘 除 取余 运算 */
MulExpr : UnaryExpr {
    $$=$1;
}
| MulExpr "*" UnaryExpr {
    $$=new_ast_node(ast_node_type::AST_OP_MUL,{$1,$3});
}
| MulExpr "/" UnaryExpr {
    $$=new_ast_node(ast_node_type::AST_OP_DIV,{$1,$3});
}
| MulExpr "%" UnaryExpr {
    $$=new_ast_node(ast_node_type::AST_OP_MOD,{$1,$3});
}
;

/* 基本运算表达式 */
UnaryExpr : Term {
    $$=$1;
}
| "-" Term{
    $$=new_ast_node(ast_node_type::AST_OP_NEG,{$2});
}
;


/* 只含单个字面量或者变量的表达式 */
Term :  DIGIT_INT{
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_LITERAL_INT);
    delete $1; //释放内存
    $1=nullptr;
}
| DIGIT_FLOAT {
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_LITERAL_FLOAT);
    delete $1; //释放内存
    $1=nullptr;
}
/* | "-" DIGIT_FLOAT {
    float num=$2->digit.float_digit;
    $2->digit.float_digit=-num;
    $$=new_ast_leaf_node(*$2,ast_node_type::AST_LEAF_LITERAL_FLOAT);
    delete $2; //释放内存
    $2=nullptr;
}
| "-" DIGIT_INT{
    int num=$2->digit.int32_digit;
    $2->digit.int32_digit=-num;
    $$=new_ast_leaf_node(*$2,ast_node_type::AST_LEAF_LITERAL_INT);
    delete $2; //释放内存
    $2=nullptr;
} */
| var {
    $$=$1;
}
| "(" Expr ")" {
    $$=$2;
}
| Array {
    // $1->ArrayDim.clear();
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

/* 变量 暂时无数组类型 */
var : DIGIT_ID {
    $$ = new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_VAR_ID);
    delete $1; //释放内存
    $1=nullptr;
}
;

/* 函数实参列表 */
FuncRealParams : Expr {
    $$=new_ast_node(ast_node_type::AST_OP_FUNC_REAL_PARAMS,{$1});
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