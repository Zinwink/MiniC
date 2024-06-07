%code top{
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

}


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
%token T_CONST "const"
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

%precedence THEN
%precedence "else"
 



%type <node> CompileUnit
%type <node> FuncDef
%type <node> FuncDeclare
%type <node> FuncFormalParams
%type <node> FuncFormalParam
%type <node> FuncRealParams
%type <node> Block
%type <node> BlockItemList
%type <node> Statement
%type <node> DeclStmt
%type <node> ConstDecl
%type <node> VarlDecl
%type <node> VarDefList
%type <node> VarDef
%type <node> VarInitVal
%type <node> VarInitValList
%type <node> ConstInitvalList
%type <node> ConstExp
%type <node> ConstDefList
%type <node> ConstDef
%type <node> ConstInitVal

%type <node> IfStmt
%type <node> WhileStmt
%type <node> DowhileStmt
%type <node> AssignStmt
%type <node> Condition
%type <node> OrCond
%type <node> AndCond
%type <node> EquCondTerm
%type <node> LessCondTerm

%type <node> ArrayIndexs
%type <node> Lval

%type <node> Expr
%type <node> AddExpr
%type <node> MulExpr
%type <node> UnaryExpr
%type <node> PrimaryExp

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
| FuncDeclare{
    $$=new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,{$1});
    ast_root=$$;
}
| CompileUnit FuncDeclare{
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
    // std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getIntNType(32));
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
    // std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getVoidType());
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
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getFloatType());
    $$=create_fun_def(*$2,funType,$4,$6);
    delete $2; //释放内存
    $2=nullptr;
}
;

FuncDeclare: "int" DIGIT_ID "(" ")" ";"{
    Type* funType=FunctionType::get(Type::getIntNType(32));
    $$=create_fun_declare(*$2,funType,nullptr);
    delete $2; //释放内存
    $2=nullptr;
}
| "int" DIGIT_ID "(" FuncFormalParams ")" ";"{
    std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getIntNType(32));
    $$=create_fun_declare(*$2,funType,$4);
    delete $2; //释放内存
    $2=nullptr;
}
| "void" DIGIT_ID "(" ")" ";"{
    Type* funType=FunctionType::get(Type::getVoidType());
    $$=create_fun_declare(*$2,funType,nullptr);
    delete $2; //释放内存
    $2=nullptr;
}
| "void" DIGIT_ID "(" FuncFormalParams ")" ";"{
    std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getVoidType());
    $$=create_fun_declare(*$2,funType,$4);
    delete $2; //释放内存
    $2=nullptr;
}
| "float" DIGIT_ID "(" ")" ";"{
    Type* funType=FunctionType::get(Type::getFloatType());
    $$=create_fun_declare(*$2,funType,nullptr);
    delete $2; //释放内存
    $2=nullptr;
}
| "float" DIGIT_ID "(" FuncFormalParams ")" ";"{
    // std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getFloatType());
    $$=create_fun_declare(*$2,funType,$4);
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
| "int" DIGIT_ID "[""]"{
    $$=create_fun_formal_param(*$2,Type::getIntNType(32));
    ast_node* nullNode=new_ast_node(ast_node_type::AST_NULL,{});
    ast_node* arraydims=new_ast_node(ast_node_type:: AST_OP_ARRAY_INDEX,{nullNode});
    insert_ast_node($$,arraydims);

    delete $2; //释放内存
    $2=nullptr;

}
| "int" DIGIT_ID ArrayIndexs{
    $$=create_fun_formal_param(*$2,Type::getIntNType(32));
    insert_ast_node($$,$3);
    delete $2; //释放内存
    $2=nullptr;
}
| "int" DIGIT_ID "[""]" ArrayIndexs{
    ast_node* nullNode=new_ast_node(ast_node_type::AST_NULL,{});
    $5->sons.push_front(nullNode);
    $$=create_fun_formal_param(*$2,Type::getIntNType(32));
    insert_ast_node($$,$5);
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
    if($1!=nullptr){
        $$ = new_ast_node(ast_node_type::AST_OP_BLOCK,{$1});
    }else{
        $$ = new_ast_node(ast_node_type::AST_OP_BLOCK,{});
    }
}
| BlockItemList Statement {
    if($2!=nullptr){
      $$ = insert_ast_node($1,$2);
    }  
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
| AssignStmt {
    $$=$1;
}
| DeclStmt{
   $$=$1;
}
| Expr ";" {
    $$=$1;
}
| ";" {
    $$= new_ast_node(ast_node_type::AST_OP_NULL_STMT,{});
}

AssignStmt: Lval "=" Expr ";"{
    $$ = new_ast_node(ast_node_type::AST_OP_ASSIGN,{$1,$3});
}
;


DeclStmt: ConstDecl{
    $$=$1;
}
| VarlDecl {
    $$=$1;
}
;

VarlDecl: "int" VarDefList ";" {
    $$=$2;
    $$->attr=Type::getIntNType(32);
    // 下面更新 下游节点的类型
    updateDeclTypes($$);

}
| "float" VarDefList ";"{
    $$=$2;
    $$->attr=Type::getFloatType();
    updateDeclTypes($$);
}
;

VarDefList: VarDef {
    $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,{$1});
}
| VarDefList "," VarDef{
    $$=insert_ast_node($1,$3);
}
;

VarDef: DIGIT_ID {
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_VAR_ID);
    delete $1; //释放内存
    $1=nullptr;
}
| DIGIT_ID "=" VarInitVal {
    ast_node* var=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_VAR_ID);
    $$=new_ast_node(ast_node_type::AST_OP_VAR_DEF,{var,$3});
    delete $1; //释放内存
    $1=nullptr;
}
| DIGIT_ID ArrayIndexs {
    $$=new_ast_node(*$1,ast_node_type::AST_OP_ARRAY,{$2});
    delete $1; //释放内存
    $1=nullptr;
}
| DIGIT_ID ArrayIndexs "=" VarInitVal {
    //  暂时未实现
}
;

VarInitVal: Expr{
    $$=$1;
}
| "{" "}" {
    // 数组初赋值  暂时未实现
}
| "{" VarInitValList "}"{
    // 数组初赋值 暂时未实现
}
;

VarInitValList: VarInitVal{

}
| VarInitValList "," VarInitVal{

}
;

ConstDecl: "const" "int" ConstDefList ";"{
    $$=$3;
    $$->attr=Type::getIntNType(32);
    updateDeclTypes($$);
}
| "const" "float" ConstDefList ";"{
    $$=$3;
    $$->attr=Type::getFloatType();
    updateDeclTypes($$);
}
;

ConstDefList: ConstDef {
    $$=new_ast_node(ast_node_type::AST_OP_CONST_DECL_ITEMS,{$1});
}
| ConstDefList "," ConstDef{
    $$=insert_ast_node($1,$3);
}
;

ConstDef: DIGIT_ID "=" ConstInitVal {
    ast_node* constval=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_CONST_VAR_ID);
    $$=new_ast_node(ast_node_type::AST_OP_CONST_VAR_DEF,{constval,$3});
    delete $1; //释放内存
    $1=nullptr;

}
| DIGIT_ID ArrayIndexs "=" ConstInitVal{

}
;

ConstInitVal: ConstExp{
    $$=$1;
}
| "{" "}" {

}
| "{" ConstInitvalList "}"{

}
;

ConstInitvalList: ConstInitVal{

}
| ConstInitvalList "," ConstInitVal{

}
;

/* 条件if else *************** */
IfStmt : "if" "(" Condition ")" Statement %prec THEN {
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


/* ArrayIndex */
ArrayIndexs : "[" Expr "]"{
    $$=new_ast_node(ast_node_type::AST_OP_ARRAY_INDEX,{$2});
}
| ArrayIndexs "[" Expr "]"{
    $$=insert_ast_node($1,$3);
}
;


/* 表达式 *********************************************************/
Expr : AddExpr {
    $$=$1;
}
;

/* 常量表达式 */
ConstExp: AddExpr{
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

AndCond : EquCondTerm {
  $$=$1;
}
| AndCond "&&" EquCondTerm {
   $$=new_ast_node(ast_node_type::AST_OP_COND_AND,{$1,$3});
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
;


UnaryExpr: PrimaryExp {
    $$=$1;
}
| "+" UnaryExpr{
    $$=$2;
}
| "-" UnaryExpr{
    $$=new_ast_node(ast_node_type::AST_OP_NEG,{$2});
}
| "!" UnaryExpr{
    $$=new_ast_node(ast_node_type::AST_OP_COND_NOT,{$2});
}


PrimaryExp: Lval{
    $$=$1;
}
| "(" OrCond ")" {
    $$=$2;
}
| DIGIT_INT {
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_LITERAL_INT);
    delete $1; //释放内存
    $1=nullptr;
}
| DIGIT_FLOAT {
    $$=new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_LITERAL_FLOAT);
    delete $1; //释放内存
    $1=nullptr;
}
|  DIGIT_ID "(" FuncRealParams ")" {
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
/* 左值 */
Lval: DIGIT_ID{
    $$ = new_ast_leaf_node(*$1,ast_node_type::AST_LEAF_VAR_ID);
    delete $1; //释放内存
    $1=nullptr;
}
| DIGIT_ID ArrayIndexs{
    $$=new_ast_node(*$1,ast_node_type::AST_OP_ARRAY,{$2});
}




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