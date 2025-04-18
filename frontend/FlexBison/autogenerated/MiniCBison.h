/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MINICBISON_H_INCLUDED
# define YY_YY_MINICBISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DIGIT_INT = 258,               /* DIGIT_INT  */
    DIGIT_ID = 259,                /* DIGIT_ID  */
    DIGIT_FLOAT = 260,             /* DIGIT_FLOAT  */
    T_ADD = 261,                   /* "+"  */
    T_SUB = 262,                   /* "-"  */
    T_DIV = 263,                   /* "/"  */
    T_MUL = 264,                   /* "*"  */
    T_ASSIGN = 265,                /* "="  */
    T_MOD = 266,                   /* "%"  */
    T_INT = 267,                   /* "int"  */
    T_FLOAT = 268,                 /* "float"  */
    T_VOID = 269,                  /* "void"  */
    T_IF = 270,                    /* "if"  */
    T_ELSE = 271,                  /* "else"  */
    T_RETURN = 272,                /* "return"  */
    T_WHILE = 273,                 /* "while"  */
    T_DO = 274,                    /* "do"  */
    T_CONST = 275,                 /* "const"  */
    T_BREAK = 276,                 /* "break"  */
    T_CONTINUE = 277,              /* "continue"  */
    T_EQUAL = 278,                 /* "=="  */
    T_NOT_EQU = 279,               /* "!="  */
    T_LESS = 280,                  /* "<"  */
    T_GREATER = 281,               /* ">"  */
    T_LESS_EQU = 282,              /* "<="  */
    T_GREATER_EQU = 283,           /* ">="  */
    T_NOT = 284,                   /* "!"  */
    T_AND = 285,                   /* "&&"  */
    T_OR = 286,                    /* "||"  */
    T_LBRACE = 287,                /* "{"  */
    T_RBRACE = 288,                /* "}"  */
    T_LPAREN = 289,                /* "("  */
    T_RPAREN = 290,                /* ")"  */
    T_LSQU = 291,                  /* "["  */
    T_RSQU = 292,                  /* "]"  */
    T_COMMA = 293,                 /* ","  */
    T_SEMICOLON = 294,             /* ";"  */
    THEN = 295                     /* THEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"

    class ast_node * node;
    class Literal_Val* literal;

#line 109 "MiniCBison.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MINICBISON_H_INCLUDED  */
