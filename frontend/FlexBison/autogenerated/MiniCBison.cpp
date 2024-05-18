/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"

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


#line 83 "MiniCBison.cpp"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "MiniCBison.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_DIGIT_INT = 3,                  /* DIGIT_INT  */
  YYSYMBOL_DIGIT_ID = 4,                   /* DIGIT_ID  */
  YYSYMBOL_DIGIT_FLOAT = 5,                /* DIGIT_FLOAT  */
  YYSYMBOL_T_ADD = 6,                      /* "+"  */
  YYSYMBOL_T_SUB = 7,                      /* "-"  */
  YYSYMBOL_T_DIV = 8,                      /* "/"  */
  YYSYMBOL_T_MUL = 9,                      /* "*"  */
  YYSYMBOL_T_ASSIGN = 10,                  /* "="  */
  YYSYMBOL_T_MOD = 11,                     /* "%"  */
  YYSYMBOL_T_INT = 12,                     /* "int"  */
  YYSYMBOL_T_FLOAT = 13,                   /* "float"  */
  YYSYMBOL_T_VOID = 14,                    /* "void"  */
  YYSYMBOL_T_IF = 15,                      /* "if"  */
  YYSYMBOL_T_ELSE = 16,                    /* "else"  */
  YYSYMBOL_T_RETURN = 17,                  /* "return"  */
  YYSYMBOL_T_WHILE = 18,                   /* "while"  */
  YYSYMBOL_T_DO = 19,                      /* "do"  */
  YYSYMBOL_T_CONST = 20,                   /* "const"  */
  YYSYMBOL_T_BREAK = 21,                   /* "break"  */
  YYSYMBOL_T_CONTINUE = 22,                /* "continue"  */
  YYSYMBOL_T_EQUAL = 23,                   /* "=="  */
  YYSYMBOL_T_NOT_EQU = 24,                 /* "!="  */
  YYSYMBOL_T_LESS = 25,                    /* "<"  */
  YYSYMBOL_T_GREATER = 26,                 /* ">"  */
  YYSYMBOL_T_LESS_EQU = 27,                /* "<="  */
  YYSYMBOL_T_GREATER_EQU = 28,             /* ">="  */
  YYSYMBOL_T_NOT = 29,                     /* "!"  */
  YYSYMBOL_T_AND = 30,                     /* "&&"  */
  YYSYMBOL_T_OR = 31,                      /* "||"  */
  YYSYMBOL_T_LBRACE = 32,                  /* "{"  */
  YYSYMBOL_T_RBRACE = 33,                  /* "}"  */
  YYSYMBOL_T_LPAREN = 34,                  /* "("  */
  YYSYMBOL_T_RPAREN = 35,                  /* ")"  */
  YYSYMBOL_T_LSQU = 36,                    /* "["  */
  YYSYMBOL_T_RSQU = 37,                    /* "]"  */
  YYSYMBOL_T_COMMA = 38,                   /* ","  */
  YYSYMBOL_T_SEMICOLON = 39,               /* ";"  */
  YYSYMBOL_THEN = 40,                      /* THEN  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_CompileUnit = 42,               /* CompileUnit  */
  YYSYMBOL_FuncDef = 43,                   /* FuncDef  */
  YYSYMBOL_FuncDeclare = 44,               /* FuncDeclare  */
  YYSYMBOL_FuncFormalParams = 45,          /* FuncFormalParams  */
  YYSYMBOL_FuncFormalParam = 46,           /* FuncFormalParam  */
  YYSYMBOL_Block = 47,                     /* Block  */
  YYSYMBOL_BlockItemList = 48,             /* BlockItemList  */
  YYSYMBOL_Statement = 49,                 /* Statement  */
  YYSYMBOL_AssignStmt = 50,                /* AssignStmt  */
  YYSYMBOL_DeclStmt = 51,                  /* DeclStmt  */
  YYSYMBOL_VarlDecl = 52,                  /* VarlDecl  */
  YYSYMBOL_VarDefList = 53,                /* VarDefList  */
  YYSYMBOL_VarDef = 54,                    /* VarDef  */
  YYSYMBOL_VarInitVal = 55,                /* VarInitVal  */
  YYSYMBOL_VarInitValList = 56,            /* VarInitValList  */
  YYSYMBOL_ConstDecl = 57,                 /* ConstDecl  */
  YYSYMBOL_ConstDefList = 58,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 59,                  /* ConstDef  */
  YYSYMBOL_ConstInitVal = 60,              /* ConstInitVal  */
  YYSYMBOL_ConstInitvalList = 61,          /* ConstInitvalList  */
  YYSYMBOL_IfStmt = 62,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 63,                 /* WhileStmt  */
  YYSYMBOL_DowhileStmt = 64,               /* DowhileStmt  */
  YYSYMBOL_ArrayIndexs = 65,               /* ArrayIndexs  */
  YYSYMBOL_Expr = 66,                      /* Expr  */
  YYSYMBOL_ConstExp = 67,                  /* ConstExp  */
  YYSYMBOL_AddExpr = 68,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 69,                   /* MulExpr  */
  YYSYMBOL_Condition = 70,                 /* Condition  */
  YYSYMBOL_OrCond = 71,                    /* OrCond  */
  YYSYMBOL_AndCond = 72,                   /* AndCond  */
  YYSYMBOL_EquCondTerm = 73,               /* EquCondTerm  */
  YYSYMBOL_LessCondTerm = 74,              /* LessCondTerm  */
  YYSYMBOL_UnaryExpr = 75,                 /* UnaryExpr  */
  YYSYMBOL_PrimaryExp = 76,                /* PrimaryExp  */
  YYSYMBOL_Lval = 77,                      /* Lval  */
  YYSYMBOL_FuncRealParams = 78             /* FuncRealParams  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  70
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   443

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  208

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,    99,   102,   106,   109,   113,   119,   125,
     135,   141,   151,   157,   169,   175,   185,   191,   201,   207,
     220,   223,   229,   234,   239,   249,   255,   264,   268,   275,
     282,   290,   294,   298,   301,   304,   307,   310,   315,   320,
     323,   326,   329,   333,   339,   342,   347,   354,   361,   364,
     369,   374,   380,   385,   390,   393,   396,   401,   404,   409,
     414,   421,   424,   429,   436,   441,   444,   447,   452,   455,
     461,   472,   488,   499,   511,   514,   521,   527,   533,   537,
     540,   546,   549,   552,   555,   563,   568,   571,   576,   579,
     586,   589,   592,   598,   601,   604,   607,   610,   616,   619,
     622,   625,   630,   633,   636,   641,   646,   652,   660,   665,
     673,   676
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "DIGIT_INT",
  "DIGIT_ID", "DIGIT_FLOAT", "\"+\"", "\"-\"", "\"/\"", "\"*\"", "\"=\"",
  "\"%\"", "\"int\"", "\"float\"", "\"void\"", "\"if\"", "\"else\"",
  "\"return\"", "\"while\"", "\"do\"", "\"const\"", "\"break\"",
  "\"continue\"", "\"==\"", "\"!=\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"",
  "\"!\"", "\"&&\"", "\"||\"", "\"{\"", "\"}\"", "\"(\"", "\")\"", "\"[\"",
  "\"]\"", "\",\"", "\";\"", "THEN", "$accept", "CompileUnit", "FuncDef",
  "FuncDeclare", "FuncFormalParams", "FuncFormalParam", "Block",
  "BlockItemList", "Statement", "AssignStmt", "DeclStmt", "VarlDecl",
  "VarDefList", "VarDef", "VarInitVal", "VarInitValList", "ConstDecl",
  "ConstDefList", "ConstDef", "ConstInitVal", "ConstInitvalList", "IfStmt",
  "WhileStmt", "DowhileStmt", "ArrayIndexs", "Expr", "ConstExp", "AddExpr",
  "MulExpr", "Condition", "OrCond", "AndCond", "EquCondTerm",
  "LessCondTerm", "UnaryExpr", "PrimaryExp", "Lval", "FuncRealParams", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-155)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     197,  -155,    60,  -155,   409,   409,    21,    73,    80,    99,
      32,   114,   308,   100,   -22,    78,   409,   234,   409,  -155,
     132,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,
    -155,  -155,   103,   121,   147,  -155,  -155,   153,   328,   409,
     131,  -155,  -155,  -155,    38,   135,  -155,    57,   137,   149,
     409,  -155,   146,   409,   190,   190,   178,   193,   193,  -155,
    -155,  -155,  -155,   271,  -155,  -155,    79,   168,   156,    97,
    -155,  -155,  -155,  -155,  -155,   409,   409,   409,   409,   409,
     409,  -155,  -155,    12,   169,   409,   377,    45,     6,   190,
    -155,    96,  -155,   108,   170,   177,  -155,   172,    19,   179,
      20,   143,  -155,   148,  -155,  -155,   409,  -155,   409,   409,
     409,   409,   409,   409,   409,   147,   147,  -155,  -155,  -155,
     181,  -155,   409,  -155,   184,   345,  -155,  -155,   218,   219,
     -17,   122,  -155,   377,  -155,     2,   127,    13,   134,   308,
     308,   409,   393,    39,   193,  -155,  -155,   168,   156,    97,
      97,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,  -155,
      -5,   188,  -155,  -155,  -155,    31,   176,  -155,  -155,  -155,
      37,  -155,  -155,    58,   209,  -155,   192,   361,  -155,  -155,
     121,   393,  -155,  -155,   377,    82,   131,  -155,  -155,  -155,
    -155,  -155,  -155,  -155,   308,   189,  -155,  -155,    62,  -155,
    -155,   194,  -155,  -155,  -155,   393,   131,  -155
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,   104,   108,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,     2,     6,    33,     4,    39,    40,    45,    44,    34,
      35,    36,     0,    76,    78,    81,    98,   102,     0,     0,
     109,    99,   102,   100,    50,     0,    48,    50,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,    37,
      38,   101,    27,     0,    29,    93,     0,    86,    88,    90,
       1,     3,     7,     5,    41,     0,     0,     0,     0,     0,
       0,   107,   110,     0,     0,     0,     0,     0,    52,     0,
      46,     0,    47,     0,     0,    85,    31,     0,    50,     0,
       0,     0,    61,     0,    28,    30,     0,   103,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    83,    82,    84,
       0,   106,     0,    74,     0,     0,    51,    54,     0,     0,
       0,     0,    20,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    59,    60,    87,    89,    91,
      92,    94,    96,    95,    97,    43,   111,    75,    55,    57,
       0,    22,    23,    14,     8,     0,     0,    53,    18,    12,
       0,    16,    10,     0,    70,    72,     0,     0,    63,    65,
      77,     0,    62,    56,     0,     0,    25,    15,     9,    21,
      19,    13,    17,    11,     0,     0,    66,    68,     0,    64,
      58,    24,    71,    73,    67,     0,    26,    69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,   212,   213,    77,    68,  -111,  -155,   -10,  -155,
    -155,  -155,     5,   154,  -119,  -155,  -155,   186,    91,  -154,
    -155,  -155,  -155,  -155,    -2,    -7,  -155,  -137,   115,   -49,
     224,   139,   140,    83,     4,  -155,     1,  -155
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    20,    21,    22,   131,   132,    23,    63,    24,    25,
      26,    27,    45,    46,   126,   160,    28,   101,   102,   178,
     198,    29,    30,    31,    88,    32,   179,    33,    34,    94,
      95,    67,    68,    69,    35,    36,    42,    83
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    37,    56,    52,    97,   180,   159,    64,    41,    43,
      73,    65,    48,    37,   167,    17,   133,    59,    37,   164,
      61,    37,   163,   197,   169,    44,   172,   199,   183,    86,
     142,    82,    84,   184,    17,     1,     2,     3,     4,     5,
     180,   168,    85,    65,   180,    17,    65,   121,    86,   181,
     122,   207,   171,   105,   188,    39,    39,   128,   129,   191,
      48,    16,   193,    17,    37,   200,    18,    86,   180,    17,
     187,    51,    87,   120,    39,    85,   190,    47,   124,   127,
     130,   117,   118,   119,    49,     1,     2,     3,     4,     5,
      17,    91,   176,    39,    38,   204,    39,   192,   143,    65,
     205,    65,    65,    65,   151,   152,   153,   154,   128,   129,
     106,    16,    57,    58,   107,   156,    18,    60,   127,   201,
     128,   129,   111,   112,   113,   114,   127,    75,    76,   174,
     175,   135,    70,    50,    65,     1,     2,     3,     4,     5,
      37,    37,    74,   137,     6,     7,     8,     9,    53,    10,
      11,    12,    13,    14,    15,    77,    78,   165,    79,   186,
     166,    16,   170,    80,    17,   166,    18,    85,   136,   173,
     138,    19,   166,    89,    90,    89,    92,   127,    84,   109,
     110,   144,   145,    93,   202,    96,   144,   146,   128,   129,
     115,   116,   149,   150,    98,    37,    99,   100,   108,   206,
       1,     2,     3,     4,     5,   139,   123,   140,   106,     6,
       7,     8,     9,   141,    10,    11,    12,    13,    14,    15,
     155,   157,   161,   162,   185,   194,    16,   195,   203,    17,
      39,    18,    71,    72,   189,   182,    19,     1,     2,     3,
       4,     5,    66,   134,   103,   147,    54,    55,   148,     9,
       0,    10,    11,    12,    13,    14,    15,     0,     0,     0,
       0,     0,     0,    16,     0,     0,    17,    62,    18,     0,
       0,     0,     0,    19,     1,     2,     3,     4,     5,     0,
       0,     0,     0,    54,    55,     0,     9,     0,    10,    11,
      12,    13,    14,    15,     0,     0,     0,     0,     0,     0,
      16,     0,     0,    17,   104,    18,     0,     0,     0,     0,
      19,     1,     2,     3,     4,     5,     0,     0,     0,     0,
      54,    55,     0,     9,     0,    10,    11,    12,    13,    14,
      15,     1,     2,     3,     4,     5,     0,    16,     0,     0,
      17,     0,    18,     0,     0,     0,     0,    19,     1,     2,
       3,     4,     5,     0,     0,     0,     0,    16,     0,     0,
       0,     0,    18,    81,     1,     2,     3,     4,     5,     0,
       0,     0,     0,     0,    16,     0,     0,   125,   158,    18,
       1,     2,     3,     4,     5,     0,     0,     0,     0,     0,
      16,     0,     0,   177,   196,    18,     1,     2,     3,     4,
       5,     0,     0,     0,     0,     0,    16,     0,     0,   125,
       0,    18,     1,     2,     3,     4,     5,     0,     0,     0,
       0,     0,    16,     0,     0,   177,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
       2,     0,    12,    10,    53,   142,   125,    17,     4,     5,
      20,    18,     7,    12,   133,    32,    10,    39,    17,   130,
      16,    20,    39,   177,   135,     4,   137,   181,    33,    10,
      10,    38,    39,    38,    32,     3,     4,     5,     6,     7,
     177,    39,    36,    50,   181,    32,    53,    35,    10,    10,
      38,   205,    39,    63,   165,    36,    36,    12,    13,   170,
      55,    29,   173,    32,    63,   184,    34,    10,   205,    32,
      39,    39,    34,    80,    36,    36,    39,     4,    85,    86,
      35,    77,    78,    79,     4,     3,     4,     5,     6,     7,
      32,    34,   141,    36,    34,    33,    36,    39,   100,   106,
      38,   108,   109,   110,   111,   112,   113,   114,    12,    13,
      31,    29,    12,    13,    35,   122,    34,    39,   125,    37,
      12,    13,    25,    26,    27,    28,   133,     6,     7,   139,
     140,    35,     0,    34,   141,     3,     4,     5,     6,     7,
     139,   140,    39,    35,    12,    13,    14,    15,    34,    17,
      18,    19,    20,    21,    22,     8,     9,    35,    11,   161,
      38,    29,    35,    10,    32,    38,    34,    36,    91,    35,
      93,    39,    38,    38,    39,    38,    39,   184,   185,    23,
      24,    38,    39,    34,   194,    39,    38,    39,    12,    13,
      75,    76,   109,   110,     4,   194,    18,     4,    30,   201,
       3,     4,     5,     6,     7,    35,    37,    35,    31,    12,
      13,    14,    15,    34,    17,    18,    19,    20,    21,    22,
      39,    37,     4,     4,    36,    16,    29,    35,    39,    32,
      36,    34,    20,    20,   166,   144,    39,     3,     4,     5,
       6,     7,    18,    89,    58,   106,    12,    13,   108,    15,
      -1,    17,    18,    19,    20,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    12,    13,    -1,    15,    -1,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      12,    13,    -1,    15,    -1,    17,    18,    19,    20,    21,
      22,     3,     4,     5,     6,     7,    -1,    29,    -1,    -1,
      32,    -1,    34,    -1,    -1,    -1,    -1,    39,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    34,    35,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,    32,    33,    34,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    32,    33,    34,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    32,
      -1,    34,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    32,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    12,    13,    14,    15,
      17,    18,    19,    20,    21,    22,    29,    32,    34,    39,
      42,    43,    44,    47,    49,    50,    51,    52,    57,    62,
      63,    64,    66,    68,    69,    75,    76,    77,    34,    36,
      65,    75,    77,    75,     4,    53,    54,     4,    53,     4,
      34,    39,    66,    34,    12,    13,    49,    12,    13,    39,
      39,    75,    33,    48,    49,    66,    71,    72,    73,    74,
       0,    43,    44,    49,    39,     6,     7,     8,     9,    11,
      10,    35,    66,    78,    66,    36,    10,    34,    65,    38,
      39,    34,    39,    34,    70,    71,    39,    70,     4,    18,
       4,    58,    59,    58,    33,    49,    31,    35,    30,    23,
      24,    25,    26,    27,    28,    69,    69,    75,    75,    75,
      66,    35,    38,    37,    66,    32,    55,    66,    12,    13,
      35,    45,    46,    10,    54,    35,    45,    35,    45,    35,
      35,    34,    10,    65,    38,    39,    39,    72,    73,    74,
      74,    66,    66,    66,    66,    39,    66,    37,    33,    55,
      56,     4,     4,    39,    47,    35,    38,    55,    39,    47,
      35,    39,    47,    35,    49,    49,    70,    32,    60,    67,
      68,    10,    59,    33,    38,    36,    65,    39,    47,    46,
      39,    47,    39,    47,    16,    35,    33,    60,    61,    60,
      55,    37,    49,    39,    33,    38,    65,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    42,    42,    42,    42,    42,    43,    43,
      43,    43,    43,    43,    44,    44,    44,    44,    44,    44,
      45,    45,    46,    46,    46,    46,    46,    47,    47,    48,
      48,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    50,    51,    51,    52,    52,    53,    53,
      54,    54,    54,    54,    55,    55,    55,    56,    56,    57,
      57,    58,    58,    59,    59,    60,    60,    60,    61,    61,
      62,    62,    63,    64,    65,    65,    66,    67,    68,    68,
      68,    69,    69,    69,    69,    70,    71,    71,    72,    72,
      73,    73,    73,    74,    74,    74,    74,    74,    75,    75,
      75,    75,    76,    76,    76,    76,    76,    76,    77,    77,
      78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     2,     5,     6,
       5,     6,     5,     6,     5,     6,     5,     6,     5,     6,
       1,     3,     2,     2,     4,     3,     5,     2,     3,     1,
       2,     3,     2,     1,     1,     1,     1,     2,     2,     1,
       1,     2,     1,     4,     1,     1,     3,     3,     1,     3,
       1,     3,     2,     4,     1,     2,     3,     1,     3,     4,
       4,     1,     3,     3,     4,     1,     2,     3,     1,     3,
       5,     7,     5,     7,     3,     4,     1,     1,     1,     3,
       3,     1,     3,     3,     3,     1,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     2,
       2,     2,     1,     3,     1,     1,     4,     3,     1,     2,
       1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* CompileUnit: FuncDef  */
#line 95 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                     {
    (yyval.node)= new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,{(yyvsp[0].node)});  // 创建一个节点compileUnit，该节点包含Funcdef子节点
    ast_root=(yyval.node);
}
#line 1343 "MiniCBison.cpp"
    break;

  case 3: /* CompileUnit: CompileUnit FuncDef  */
#line 99 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                     {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));  // 插入节点
}
#line 1351 "MiniCBison.cpp"
    break;

  case 4: /* CompileUnit: Statement  */
#line 102 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
           {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,{(yyvsp[0].node)});
    ast_root=(yyval.node);
}
#line 1360 "MiniCBison.cpp"
    break;

  case 5: /* CompileUnit: CompileUnit Statement  */
#line 106 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
}
#line 1368 "MiniCBison.cpp"
    break;

  case 6: /* CompileUnit: FuncDeclare  */
#line 109 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
             {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,{(yyvsp[0].node)});
    ast_root=(yyval.node);
}
#line 1377 "MiniCBison.cpp"
    break;

  case 7: /* CompileUnit: CompileUnit FuncDeclare  */
#line 113 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
}
#line 1385 "MiniCBison.cpp"
    break;

  case 8: /* FuncDef: "int" DIGIT_ID "(" ")" Block  */
#line 119 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                      {
    Type* funType=FunctionType::get(Type::getIntNType(32));
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),funType,nullptr,(yyvsp[0].node));
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1396 "MiniCBison.cpp"
    break;

  case 9: /* FuncDef: "int" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 125 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                               {
    // std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getIntNType(32));
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),funType,(yyvsp[-2].node),(yyvsp[0].node));
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1411 "MiniCBison.cpp"
    break;

  case 10: /* FuncDef: "void" DIGIT_ID "(" ")" Block  */
#line 135 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                               {
    Type* funType=FunctionType::get(Type::getVoidType());
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),funType,nullptr,(yyvsp[0].node));
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1422 "MiniCBison.cpp"
    break;

  case 11: /* FuncDef: "void" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 141 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                {
    // std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getVoidType());
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),funType,(yyvsp[-2].node),(yyvsp[0].node));
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1437 "MiniCBison.cpp"
    break;

  case 12: /* FuncDef: "float" DIGIT_ID "(" ")" Block  */
#line 151 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    Type* funType=FunctionType::get(Type::getFloatType());
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),funType,nullptr,(yyvsp[0].node));
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1448 "MiniCBison.cpp"
    break;

  case 13: /* FuncDef: "float" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 157 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                 {
    std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getFloatType());
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),funType,(yyvsp[-2].node),(yyvsp[0].node));
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1463 "MiniCBison.cpp"
    break;

  case 14: /* FuncDeclare: "int" DIGIT_ID "(" ")" ";"  */
#line 169 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                       {
    Type* funType=FunctionType::get(Type::getIntNType(32));
    (yyval.node)=create_fun_declare(*(yyvsp[-3].literal),funType,nullptr);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1474 "MiniCBison.cpp"
    break;

  case 15: /* FuncDeclare: "int" DIGIT_ID "(" FuncFormalParams ")" ";"  */
#line 175 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                             {
    std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getIntNType(32));
    (yyval.node)=create_fun_declare(*(yyvsp[-4].literal),funType,(yyvsp[-2].node));
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1489 "MiniCBison.cpp"
    break;

  case 16: /* FuncDeclare: "void" DIGIT_ID "(" ")" ";"  */
#line 185 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                             {
    Type* funType=FunctionType::get(Type::getVoidType());
    (yyval.node)=create_fun_declare(*(yyvsp[-3].literal),funType,nullptr);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1500 "MiniCBison.cpp"
    break;

  case 17: /* FuncDeclare: "void" DIGIT_ID "(" FuncFormalParams ")" ";"  */
#line 191 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                              {
    std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getVoidType());
    (yyval.node)=create_fun_declare(*(yyvsp[-4].literal),funType,(yyvsp[-2].node));
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1515 "MiniCBison.cpp"
    break;

  case 18: /* FuncDeclare: "float" DIGIT_ID "(" ")" ";"  */
#line 201 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                              {
    Type* funType=FunctionType::get(Type::getFloatType());
    (yyval.node)=create_fun_declare(*(yyvsp[-3].literal),funType,nullptr);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1526 "MiniCBison.cpp"
    break;

  case 19: /* FuncDeclare: "float" DIGIT_ID "(" FuncFormalParams ")" ";"  */
#line 207 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                               {
    // std::vector<Type*> argsTy;
    // for(auto& son:$4->sons){
    //     argsTy.push_back(Type::copy(son->attr));
    // }
    Type* funType=FunctionType::get(Type::getFloatType());
    (yyval.node)=create_fun_declare(*(yyvsp[-4].literal),funType,(yyvsp[-2].node));
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1541 "MiniCBison.cpp"
    break;

  case 20: /* FuncFormalParams: FuncFormalParam  */
#line 220 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                   {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_FUNC_FORMAL_PARAMS,{(yyvsp[0].node)});
}
#line 1549 "MiniCBison.cpp"
    break;

  case 21: /* FuncFormalParams: FuncFormalParams "," FuncFormalParam  */
#line 223 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                       {
    (yyval.node) =insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1557 "MiniCBison.cpp"
    break;

  case 22: /* FuncFormalParam: "int" DIGIT_ID  */
#line 229 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    (yyval.node)=create_fun_formal_param(*(yyvsp[0].literal),Type::getIntNType(32));
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1567 "MiniCBison.cpp"
    break;

  case 23: /* FuncFormalParam: "float" DIGIT_ID  */
#line 234 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                  {
    (yyval.node)=create_fun_formal_param(*(yyvsp[0].literal),Type::getFloatType());
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1577 "MiniCBison.cpp"
    break;

  case 24: /* FuncFormalParam: "int" DIGIT_ID "[" "]"  */
#line 239 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
    (yyval.node)=create_fun_formal_param(*(yyvsp[-2].literal),Type::getIntNType(32));
    ast_node* nullNode=new_ast_node(ast_node_type::AST_NULL,{});
    ast_node* arraydims=new_ast_node(ast_node_type:: AST_OP_ARRAY_INDEX,{nullNode});
    insert_ast_node((yyval.node),arraydims);

    delete (yyvsp[-2].literal); //释放内存
    (yyvsp[-2].literal)=nullptr;

}
#line 1592 "MiniCBison.cpp"
    break;

  case 25: /* FuncFormalParam: "int" DIGIT_ID ArrayIndexs  */
#line 249 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                            {
    (yyval.node)=create_fun_formal_param(*(yyvsp[-1].literal),Type::getIntNType(32));
    insert_ast_node((yyval.node),(yyvsp[0].node));
    delete (yyvsp[-1].literal); //释放内存
    (yyvsp[-1].literal)=nullptr;
}
#line 1603 "MiniCBison.cpp"
    break;

  case 26: /* FuncFormalParam: "int" DIGIT_ID "[" "]" ArrayIndexs  */
#line 255 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                   {
    ast_node* nullNode=new_ast_node(ast_node_type::AST_NULL,{});
    (yyvsp[0].node)->sons.push_front(nullNode);
    (yyval.node)=create_fun_formal_param(*(yyvsp[-3].literal),Type::getIntNType(32));
    insert_ast_node((yyval.node),(yyvsp[0].node));
}
#line 1614 "MiniCBison.cpp"
    break;

  case 27: /* Block: "{" "}"  */
#line 264 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)= new ast_node(ast_node_type::AST_OP_BLOCK);
    // 无操作
}
#line 1623 "MiniCBison.cpp"
    break;

  case 28: /* Block: "{" BlockItemList "}"  */
#line 268 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    // 语句块中的语句列表 语句块指针指向语句列表
    (yyval.node) = (yyvsp[-1].node);
}
#line 1632 "MiniCBison.cpp"
    break;

  case 29: /* BlockItemList: Statement  */
#line 275 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    if((yyvsp[0].node)!=nullptr){
        (yyval.node) = new_ast_node(ast_node_type::AST_OP_BLOCK,{(yyvsp[0].node)});
    }else{
        (yyval.node) = new_ast_node(ast_node_type::AST_OP_BLOCK,{});
    }
}
#line 1644 "MiniCBison.cpp"
    break;

  case 30: /* BlockItemList: BlockItemList Statement  */
#line 282 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    if((yyvsp[0].node)!=nullptr){
      (yyval.node) = insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
    }  
}
#line 1654 "MiniCBison.cpp"
    break;

  case 31: /* Statement: "return" Expr ";"  */
#line 290 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                              {
    //返回语句
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_RETURN_STATEMENT,{(yyvsp[-1].node)});
}
#line 1663 "MiniCBison.cpp"
    break;

  case 32: /* Statement: "return" ";"  */
#line 294 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    //无返回值
    (yyval.node)=new ast_node(ast_node_type::AST_OP_RETURN_STATEMENT);
}
#line 1672 "MiniCBison.cpp"
    break;

  case 33: /* Statement: Block  */
#line 298 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
        {
    (yyval.node)=(yyvsp[0].node);
}
#line 1680 "MiniCBison.cpp"
    break;

  case 34: /* Statement: IfStmt  */
#line 301 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
         {
    (yyval.node)=(yyvsp[0].node);
}
#line 1688 "MiniCBison.cpp"
    break;

  case 35: /* Statement: WhileStmt  */
#line 304 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
            {
    (yyval.node)=(yyvsp[0].node);
}
#line 1696 "MiniCBison.cpp"
    break;

  case 36: /* Statement: DowhileStmt  */
#line 307 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    (yyval.node)=(yyvsp[0].node);
}
#line 1704 "MiniCBison.cpp"
    break;

  case 37: /* Statement: "break" ";"  */
#line 310 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[-1].literal),ast_node_type::AST_OP_BREAK);
    delete (yyvsp[-1].literal); //释放内存
    (yyvsp[-1].literal)=nullptr;
}
#line 1714 "MiniCBison.cpp"
    break;

  case 38: /* Statement: "continue" ";"  */
#line 315 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[-1].literal),ast_node_type::AST_OP_CONTINUE);  //continue语句
    delete (yyvsp[-1].literal); //释放内存
    (yyvsp[-1].literal)=nullptr;
}
#line 1724 "MiniCBison.cpp"
    break;

  case 39: /* Statement: AssignStmt  */
#line 320 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
             {
    (yyval.node)=(yyvsp[0].node);
}
#line 1732 "MiniCBison.cpp"
    break;

  case 40: /* Statement: DeclStmt  */
#line 323 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
          {
   (yyval.node)=(yyvsp[0].node);
}
#line 1740 "MiniCBison.cpp"
    break;

  case 41: /* Statement: Expr ";"  */
#line 326 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
           {
    (yyval.node)=(yyvsp[-1].node);
}
#line 1748 "MiniCBison.cpp"
    break;

  case 42: /* Statement: ";"  */
#line 329 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
      {
    (yyval.node)=nullptr;
}
#line 1756 "MiniCBison.cpp"
    break;

  case 43: /* AssignStmt: Lval "=" Expr ";"  */
#line 333 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                             {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_ASSIGN,{(yyvsp[-3].node),(yyvsp[-1].node)});
}
#line 1764 "MiniCBison.cpp"
    break;

  case 44: /* DeclStmt: ConstDecl  */
#line 339 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    (yyval.node)=(yyvsp[0].node);
}
#line 1772 "MiniCBison.cpp"
    break;

  case 45: /* DeclStmt: VarlDecl  */
#line 342 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
           {
    (yyval.node)=(yyvsp[0].node);
}
#line 1780 "MiniCBison.cpp"
    break;

  case 46: /* VarlDecl: "int" VarDefList ";"  */
#line 347 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                               {
    (yyval.node)=(yyvsp[-1].node);
    (yyval.node)->attr=Type::getIntNType(32);
    // 下面更新 下游节点的类型
    updateDeclTypes((yyval.node));

}
#line 1792 "MiniCBison.cpp"
    break;

  case 47: /* VarlDecl: "float" VarDefList ";"  */
#line 354 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=(yyvsp[-1].node);
    (yyval.node)->attr=Type::getFloatType();
    updateDeclTypes((yyval.node));
}
#line 1802 "MiniCBison.cpp"
    break;

  case 48: /* VarDefList: VarDef  */
#line 361 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,{(yyvsp[0].node)});
}
#line 1810 "MiniCBison.cpp"
    break;

  case 49: /* VarDefList: VarDefList "," VarDef  */
#line 364 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
    (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1818 "MiniCBison.cpp"
    break;

  case 50: /* VarDef: DIGIT_ID  */
#line 369 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_VAR_ID);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1828 "MiniCBison.cpp"
    break;

  case 51: /* VarDef: DIGIT_ID "=" VarInitVal  */
#line 374 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    ast_node* var=new_ast_leaf_node(*(yyvsp[-2].literal),ast_node_type::AST_LEAF_VAR_ID);
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_VAR_DEF,{var,(yyvsp[0].node)});
    delete (yyvsp[-2].literal); //释放内存
    (yyvsp[-2].literal)=nullptr;
}
#line 1839 "MiniCBison.cpp"
    break;

  case 52: /* VarDef: DIGIT_ID ArrayIndexs  */
#line 380 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
    (yyval.node)=new_ast_node(*(yyvsp[-1].literal),ast_node_type::AST_OP_ARRAY,{(yyvsp[0].node)});
    delete (yyvsp[-1].literal); //释放内存
    (yyvsp[-1].literal)=nullptr;
}
#line 1849 "MiniCBison.cpp"
    break;

  case 53: /* VarDef: DIGIT_ID ArrayIndexs "=" VarInitVal  */
#line 385 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                      {
    //  暂时未实现
}
#line 1857 "MiniCBison.cpp"
    break;

  case 54: /* VarInitVal: Expr  */
#line 390 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                {
    (yyval.node)=(yyvsp[0].node);
}
#line 1865 "MiniCBison.cpp"
    break;

  case 55: /* VarInitVal: "{" "}"  */
#line 393 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
          {
    // 数组初赋值  暂时未实现
}
#line 1873 "MiniCBison.cpp"
    break;

  case 56: /* VarInitVal: "{" VarInitValList "}"  */
#line 396 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    // 数组初赋值 暂时未实现
}
#line 1881 "MiniCBison.cpp"
    break;

  case 57: /* VarInitValList: VarInitVal  */
#line 401 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {

}
#line 1889 "MiniCBison.cpp"
    break;

  case 58: /* VarInitValList: VarInitValList "," VarInitVal  */
#line 404 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                               {

}
#line 1897 "MiniCBison.cpp"
    break;

  case 59: /* ConstDecl: "const" "int" ConstDefList ";"  */
#line 409 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                         {
    (yyval.node)=(yyvsp[-1].node);
    (yyval.node)->attr=Type::getIntNType(32);
    updateDeclTypes((yyval.node));
}
#line 1907 "MiniCBison.cpp"
    break;

  case 60: /* ConstDecl: "const" "float" ConstDefList ";"  */
#line 414 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                  {
    (yyval.node)=(yyvsp[-1].node);
    (yyval.node)->attr=Type::getFloatType();
    updateDeclTypes((yyval.node));
}
#line 1917 "MiniCBison.cpp"
    break;

  case 61: /* ConstDefList: ConstDef  */
#line 421 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_CONST_DECL_ITEMS,{(yyvsp[0].node)});
}
#line 1925 "MiniCBison.cpp"
    break;

  case 62: /* ConstDefList: ConstDefList "," ConstDef  */
#line 424 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                           {
    (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1933 "MiniCBison.cpp"
    break;

  case 63: /* ConstDef: DIGIT_ID "=" ConstInitVal  */
#line 429 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                    {
    ast_node* constval=new_ast_leaf_node(*(yyvsp[-2].literal),ast_node_type::AST_LEAF_CONST_VAR_ID);
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_CONST_VAR_DEF,{constval,(yyvsp[0].node)});
    delete (yyvsp[-2].literal); //释放内存
    (yyvsp[-2].literal)=nullptr;

}
#line 1945 "MiniCBison.cpp"
    break;

  case 64: /* ConstDef: DIGIT_ID ArrayIndexs "=" ConstInitVal  */
#line 436 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                       {

}
#line 1953 "MiniCBison.cpp"
    break;

  case 65: /* ConstInitVal: ConstExp  */
#line 441 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=(yyvsp[0].node);
}
#line 1961 "MiniCBison.cpp"
    break;

  case 66: /* ConstInitVal: "{" "}"  */
#line 444 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
          {

}
#line 1969 "MiniCBison.cpp"
    break;

  case 67: /* ConstInitVal: "{" ConstInitvalList "}"  */
#line 447 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {

}
#line 1977 "MiniCBison.cpp"
    break;

  case 68: /* ConstInitvalList: ConstInitVal  */
#line 452 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                              {

}
#line 1985 "MiniCBison.cpp"
    break;

  case 69: /* ConstInitvalList: ConstInitvalList "," ConstInitVal  */
#line 455 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                   {

}
#line 1993 "MiniCBison.cpp"
    break;

  case 70: /* IfStmt: "if" "(" Condition ")" Statement  */
#line 461 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                     {
    // statement 可以是block,也可以是单条语句，为了方便处理，这里需要进行判断，在AST抽象语法树上统一显示block
    if((yyvsp[0].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{(yyvsp[0].node)});
        (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,{(yyvsp[-2].node),block});
    }
    else{
        (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,{(yyvsp[-2].node),(yyvsp[0].node)});
    }
}
#line 2009 "MiniCBison.cpp"
    break;

  case 71: /* IfStmt: "if" "(" Condition ")" Statement "else" Statement  */
#line 472 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                    {
    if((yyvsp[-2].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{(yyvsp[-2].node)});
        (yyvsp[-2].node)=block;
    }
    if((yyvsp[0].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{(yyvsp[0].node)});
        (yyvsp[0].node)=block;
    }
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,{(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2027 "MiniCBison.cpp"
    break;

  case 72: /* WhileStmt: "while" "(" Condition ")" Statement  */
#line 488 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                {
    if((yyvsp[0].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{(yyvsp[0].node)});
        (yyvsp[0].node)=block;
    }
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_WHILESTMT,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2040 "MiniCBison.cpp"
    break;

  case 73: /* DowhileStmt: "do" Statement "while" "(" Condition ")" ";"  */
#line 499 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                           {
     if((yyvsp[-5].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,{(yyvsp[-5].node)});
        (yyvsp[-5].node)=block;
    }
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DOWHILESTMT,{(yyvsp[-5].node),(yyvsp[-2].node)});
}
#line 2053 "MiniCBison.cpp"
    break;

  case 74: /* ArrayIndexs: "[" Expr "]"  */
#line 511 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_ARRAY_INDEX,{(yyvsp[-1].node)});
}
#line 2061 "MiniCBison.cpp"
    break;

  case 75: /* ArrayIndexs: ArrayIndexs "[" Expr "]"  */
#line 514 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node)=insert_ast_node((yyvsp[-3].node),(yyvsp[-1].node));
}
#line 2069 "MiniCBison.cpp"
    break;

  case 76: /* Expr: AddExpr  */
#line 521 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=(yyvsp[0].node);
}
#line 2077 "MiniCBison.cpp"
    break;

  case 77: /* ConstExp: AddExpr  */
#line 527 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=(yyvsp[0].node);
}
#line 2085 "MiniCBison.cpp"
    break;

  case 78: /* AddExpr: MulExpr  */
#line 533 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    // MulExpr可以推导得到UnaryExpr  这样写保证乘除取余的优先级
    (yyval.node)=(yyvsp[0].node);
}
#line 2094 "MiniCBison.cpp"
    break;

  case 79: /* AddExpr: AddExpr "+" MulExpr  */
#line 537 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_ADD,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2102 "MiniCBison.cpp"
    break;

  case 80: /* AddExpr: AddExpr "-" MulExpr  */
#line 540 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_SUB,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2110 "MiniCBison.cpp"
    break;

  case 81: /* MulExpr: UnaryExpr  */
#line 546 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                    {
    (yyval.node)=(yyvsp[0].node);
}
#line 2118 "MiniCBison.cpp"
    break;

  case 82: /* MulExpr: MulExpr "*" UnaryExpr  */
#line 549 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_MUL,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2126 "MiniCBison.cpp"
    break;

  case 83: /* MulExpr: MulExpr "/" UnaryExpr  */
#line 552 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DIV,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2134 "MiniCBison.cpp"
    break;

  case 84: /* MulExpr: MulExpr "%" UnaryExpr  */
#line 555 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_MOD,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2142 "MiniCBison.cpp"
    break;

  case 85: /* Condition: OrCond  */
#line 563 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    (yyval.node)=(yyvsp[0].node);
}
#line 2150 "MiniCBison.cpp"
    break;

  case 86: /* OrCond: AndCond  */
#line 568 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=(yyvsp[0].node);
}
#line 2158 "MiniCBison.cpp"
    break;

  case 87: /* OrCond: OrCond "||" AndCond  */
#line 571 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_OR,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2166 "MiniCBison.cpp"
    break;

  case 88: /* AndCond: EquCondTerm  */
#line 576 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
  (yyval.node)=(yyvsp[0].node);
}
#line 2174 "MiniCBison.cpp"
    break;

  case 89: /* AndCond: AndCond "&&" EquCondTerm  */
#line 579 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                           {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_AND,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2182 "MiniCBison.cpp"
    break;

  case 90: /* EquCondTerm: LessCondTerm  */
#line 586 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                           {
   (yyval.node)=(yyvsp[0].node);
}
#line 2190 "MiniCBison.cpp"
    break;

  case 91: /* EquCondTerm: EquCondTerm "==" LessCondTerm  */
#line 589 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_EQU,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2198 "MiniCBison.cpp"
    break;

  case 92: /* EquCondTerm: EquCondTerm "!=" LessCondTerm  */
#line 592 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_NOTEQU,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2206 "MiniCBison.cpp"
    break;

  case 93: /* LessCondTerm: Expr  */
#line 598 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                    {
   (yyval.node)=(yyvsp[0].node);
}
#line 2214 "MiniCBison.cpp"
    break;

  case 94: /* LessCondTerm: LessCondTerm "<" Expr  */
#line 601 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_LESS,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2222 "MiniCBison.cpp"
    break;

  case 95: /* LessCondTerm: LessCondTerm "<=" Expr  */
#line 604 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_LESSEQU,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2230 "MiniCBison.cpp"
    break;

  case 96: /* LessCondTerm: LessCondTerm ">" Expr  */
#line 607 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_GREATER,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2238 "MiniCBison.cpp"
    break;

  case 97: /* LessCondTerm: LessCondTerm ">=" Expr  */
#line 610 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_GREATEREQU,{(yyvsp[-2].node),(yyvsp[0].node)});
}
#line 2246 "MiniCBison.cpp"
    break;

  case 98: /* UnaryExpr: PrimaryExp  */
#line 616 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=(yyvsp[0].node);
}
#line 2254 "MiniCBison.cpp"
    break;

  case 99: /* UnaryExpr: "+" UnaryExpr  */
#line 619 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=(yyvsp[0].node);
}
#line 2262 "MiniCBison.cpp"
    break;

  case 100: /* UnaryExpr: "-" UnaryExpr  */
#line 622 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_NEG,{(yyvsp[0].node)});
}
#line 2270 "MiniCBison.cpp"
    break;

  case 101: /* UnaryExpr: "!" UnaryExpr  */
#line 625 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_NOT,{(yyvsp[0].node)});
}
#line 2278 "MiniCBison.cpp"
    break;

  case 102: /* PrimaryExp: Lval  */
#line 630 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                {
    (yyval.node)=(yyvsp[0].node);
}
#line 2286 "MiniCBison.cpp"
    break;

  case 103: /* PrimaryExp: "(" OrCond ")"  */
#line 633 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=(yyvsp[-1].node);
}
#line 2294 "MiniCBison.cpp"
    break;

  case 104: /* PrimaryExp: DIGIT_INT  */
#line 636 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
            {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_LITERAL_INT);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 2304 "MiniCBison.cpp"
    break;

  case 105: /* PrimaryExp: DIGIT_FLOAT  */
#line 641 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_LITERAL_FLOAT);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 2314 "MiniCBison.cpp"
    break;

  case 106: /* PrimaryExp: DIGIT_ID "(" FuncRealParams ")"  */
#line 646 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                   {
    // 有参函数调用的值
    (yyval.node)=create_fun_call(*(yyvsp[-3].literal),(yyvsp[-1].node));
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 2325 "MiniCBison.cpp"
    break;

  case 107: /* PrimaryExp: DIGIT_ID "(" ")"  */
#line 652 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    //无参函数调用的值
    (yyval.node)=create_fun_call(*(yyvsp[-2].literal),nullptr);
    delete (yyvsp[-2].literal); //释放内存
    (yyvsp[-2].literal)=nullptr;
}
#line 2336 "MiniCBison.cpp"
    break;

  case 108: /* Lval: DIGIT_ID  */
#line 660 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    (yyval.node) = new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_VAR_ID);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 2346 "MiniCBison.cpp"
    break;

  case 109: /* Lval: DIGIT_ID ArrayIndexs  */
#line 665 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(*(yyvsp[-1].literal),ast_node_type::AST_OP_ARRAY,{(yyvsp[0].node)});
}
#line 2354 "MiniCBison.cpp"
    break;

  case 110: /* FuncRealParams: Expr  */
#line 673 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_FUNC_REAL_PARAMS,{(yyvsp[0].node)});
}
#line 2362 "MiniCBison.cpp"
    break;

  case 111: /* FuncRealParams: FuncRealParams "," Expr  */
#line 676 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 2370 "MiniCBison.cpp"
    break;


#line 2374 "MiniCBison.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 681 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"


// 语法分析时的错误信息
void yyerror(const char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
