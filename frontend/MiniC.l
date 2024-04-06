%{
/*包含头文件*/
#include <cstdio>
#include <cstdint>
#include <cstring>
#include "BisonParser.h"
#include "Literal_Val.h"
%}

/* 不添加默认规则, 当给定规则无法匹配时，抛出错误 */
%option nodefault
/* 不使用yywrap */
%option noyywrap
/* yylineno维护当前行编号 */
%option yylineno
/* 区分大小写 */
%option case-sensitive
/* 不进行命令行交互 只能分析文件 */
%option never-interactive
/* yytext为指针类型，提高运行效率 */
%option pointer
/* 用于进入多行注释状态 */
%x COMMENT
/* 一些辅助定义式 */

/* 整数 */
int_digit       (-?[1-9][0-9]*)|0
/* 标识符 */
identifer       [a-zA-Z_][0-9a-zA-Z_]* 
/* 小数 */
decimal         -?([0-9]+"."[0-9])*|-?("."[0-9]+)
/* 空白 */
white           [\t\040]
/* 空白行 */
white_line  [\r\n]

%%

"/*"            {    // 进入注释有限自动机
                    BEGIN(COMMENT);
                } 
<COMMENT>"*/"   {
            // 结束注释子优先自动机
            BEGIN(INITIAL);
}
<COMMENT>([^*]|\n)+|.   {
       ;  //忽略注释中所有字符 包括换行符
}
<COMMENT><<EOF>> {
    //处于注释有限自动机中，没遇到 */ 文件结束
    printf("Line %d: Unterminated comment\n",yylineno);
    return 1190;  //词法识别错误
}
"//".*\n    {
    ;   //忽略行注释
}


"int"       {return T_INT;}
"float"     {return T_FLOAT;}
"void"      {return T_VOID;}

"if"        {return T_IF;}
"else"      {return T_ELSE;}
"return"    {return T_RETURN;}

"while"     {return T_WHILE;}
"do"        {return T_DO;}

"+"         {return T_ADD;}
"/"         {return T_DIV;}
"*"         {return T_MUL;}
"-"         {return T_SUB;}
"="         {return T_ASSIGN;}
"%"         {return T_MOD;}

"=="        {return T_EQUAL;}
"!="        {return T_NOT_EQU;}
"<"         {return T_LESS;}
">"         {return T_GREATER;}
"<="        {return T_LESS_EQU;}
">="        {return T_GREATER_EQU;}
"!"         {return T_NOT;}
"&&"        {return T_AND;}
"||"        {return T_OR;}

"{"         {return T_LBRACE;}
"}"         {return T_RBRACE;}
"("         {return T_LPAREN;}
")"         {return T_RPAREN;}
"["         {return T_LSQU;}
"]"         {return T_RSQU;}

","         {return T_COMMA;}
";"         {return T_SEMICOLON;}

{int_digit} {
    //识别整数
    yylval.literal=new Literal_Val(std::stoi(yytext),yylineno);
    return DIGIT_INT;
}

{identifer}   {
    // 识别标识符
    yylval.literal=new Literal_Val(strdup(yytext),yylineno);
    return DIGIT_ID;
}

{decimal}  {
    //识别小数
    yylval.literal=new Literal_Val(std::stof(yytext),yylineno);
    return DIGIT_FLOAT;
}

{white}+  ;
{white_line}+ ;

.    {  //其余未识别的符号 错误
        printf("Line %d:unknown token %s\n",yylineno,yytext);
        return 8909;
}


%%


