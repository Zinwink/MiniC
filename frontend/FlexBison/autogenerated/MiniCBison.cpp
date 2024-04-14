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




/* First part of user prologue.  */
#line 1 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"

#include <cstdio>
#include <cstring>
// 词法分析文件
#include "FlexLexer.h"
// 语法分析头文件
#include "BisonParser.h"
#include "AST.h"

// LR语法分析失败时调用
void yyerror(const char* msg); 


#line 85 "MiniCBison.cpp"

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
  YYSYMBOL_T_BREAK = 20,                   /* "break"  */
  YYSYMBOL_T_CONTINUE = 21,                /* "continue"  */
  YYSYMBOL_T_EQUAL = 22,                   /* "=="  */
  YYSYMBOL_T_NOT_EQU = 23,                 /* "!="  */
  YYSYMBOL_T_LESS = 24,                    /* "<"  */
  YYSYMBOL_T_GREATER = 25,                 /* ">"  */
  YYSYMBOL_T_LESS_EQU = 26,                /* "<="  */
  YYSYMBOL_T_GREATER_EQU = 27,             /* ">="  */
  YYSYMBOL_T_NOT = 28,                     /* "!"  */
  YYSYMBOL_T_AND = 29,                     /* "&&"  */
  YYSYMBOL_T_OR = 30,                      /* "||"  */
  YYSYMBOL_T_LBRACE = 31,                  /* "{"  */
  YYSYMBOL_T_RBRACE = 32,                  /* "}"  */
  YYSYMBOL_T_LPAREN = 33,                  /* "("  */
  YYSYMBOL_T_RPAREN = 34,                  /* ")"  */
  YYSYMBOL_T_LSQU = 35,                    /* "["  */
  YYSYMBOL_T_RSQU = 36,                    /* "]"  */
  YYSYMBOL_T_COMMA = 37,                   /* ","  */
  YYSYMBOL_T_SEMICOLON = 38,               /* ";"  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_CompileUnit = 40,               /* CompileUnit  */
  YYSYMBOL_FuncDef = 41,                   /* FuncDef  */
  YYSYMBOL_FuncFormalParams = 42,          /* FuncFormalParams  */
  YYSYMBOL_FuncFormalParam = 43,           /* FuncFormalParam  */
  YYSYMBOL_Block = 44,                     /* Block  */
  YYSYMBOL_BlockItemList = 45,             /* BlockItemList  */
  YYSYMBOL_Statement = 46,                 /* Statement  */
  YYSYMBOL_IfStmt = 47,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 48,                 /* WhileStmt  */
  YYSYMBOL_DowhileStmt = 49,               /* DowhileStmt  */
  YYSYMBOL_Condition = 50,                 /* Condition  */
  YYSYMBOL_OrCond = 51,                    /* OrCond  */
  YYSYMBOL_AndCond = 52,                   /* AndCond  */
  YYSYMBOL_NotCond = 53,                   /* NotCond  */
  YYSYMBOL_EquCondTerm = 54,               /* EquCondTerm  */
  YYSYMBOL_LessCondTerm = 55,              /* LessCondTerm  */
  YYSYMBOL_Declare = 56,                   /* Declare  */
  YYSYMBOL_DeclareItems = 57,              /* DeclareItems  */
  YYSYMBOL_DeclareItem = 58,               /* DeclareItem  */
  YYSYMBOL_Expr = 59,                      /* Expr  */
  YYSYMBOL_AddExpr = 60,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 61,                   /* MulExpr  */
  YYSYMBOL_UnaryExpr = 62,                 /* UnaryExpr  */
  YYSYMBOL_Term = 63,                      /* Term  */
  YYSYMBOL_var = 64,                       /* var  */
  YYSYMBOL_FuncRealParams = 65             /* FuncRealParams  */
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
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  150

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    72,    72,    76,    79,    83,    89,    94,    99,   104,
     109,   114,   122,   125,   131,   136,   144,   147,   154,   157,
     163,   167,   170,   173,   176,   179,   182,   185,   188,   191,
     197,   200,   206,   212,   219,   224,   227,   232,   235,   240,
     243,   248,   251,   254,   260,   263,   266,   269,   272,   275,
     281,   286,   293,   296,   301,   305,   315,   321,   325,   328,
     334,   337,   340,   343,   349,   352,   358,   368,   373,   378,
     381,   387,   395,   398
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
  "\"return\"", "\"while\"", "\"do\"", "\"break\"", "\"continue\"",
  "\"==\"", "\"!=\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"!\"",
  "\"&&\"", "\"||\"", "\"{\"", "\"}\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\",\"", "\";\"", "$accept", "CompileUnit", "FuncDef",
  "FuncFormalParams", "FuncFormalParam", "Block", "BlockItemList",
  "Statement", "IfStmt", "WhileStmt", "DowhileStmt", "Condition", "OrCond",
  "AndCond", "NotCond", "EquCondTerm", "LessCondTerm", "Declare",
  "DeclareItems", "DeclareItem", "Expr", "AddExpr", "MulExpr", "UnaryExpr",
  "Term", "var", "FuncRealParams", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     152,   -77,   -32,   -77,    12,    18,    20,     1,    32,    17,
     218,   -12,    14,   174,    32,   130,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,    62,    38,    10,   -77,   -77,    79,    25,
      74,    35,   -77,    99,    78,    45,    80,    28,    76,   -77,
      28,   108,   108,    97,   -77,   -77,   -77,   196,   -77,    82,
     -77,   -77,   -77,   -77,    32,    32,    32,    32,    32,    32,
     -77,   -77,   -23,    42,   108,   -77,    32,    50,   -77,    54,
      66,    28,    92,    98,   100,   -77,    73,    67,   -77,   -77,
     102,   -77,   104,   -77,   -77,   -77,    10,    10,   -77,   -77,
     -77,    93,   -77,    32,   128,   134,   109,    23,   -77,   -77,
     -77,   109,    40,   109,    44,    73,   107,    82,   218,    28,
      28,    66,    66,    32,    32,    32,    32,   218,    28,   -77,
     -77,   -77,   -77,   -77,   109,    85,   -77,   109,   -77,   109,
     -77,   136,   100,   -77,    67,    67,   -77,   -77,   -77,   -77,
     -77,   119,   -77,   -77,   -77,   -77,   218,   116,   -77,   -77
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    67,    71,    68,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,    21,     4,    22,
      23,    24,    25,     0,    56,    57,    60,    64,    69,     0,
      71,     0,    52,    54,    71,     0,     0,     0,     0,    69,
       0,     0,     0,     0,    28,    29,    16,     0,    18,     0,
       1,     3,     5,    27,     0,     0,     0,     0,     0,     0,
      66,    72,     0,     0,     0,    50,     0,     0,    51,     0,
       0,     0,     0,    34,    35,    37,    40,    41,    44,    20,
       0,    71,     0,    17,    19,    70,    58,    59,    62,    61,
      63,     0,    65,     0,     0,     0,     0,     0,    12,    53,
      55,     0,     0,     0,     0,    39,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      73,    14,    15,     6,     0,     0,    10,     0,     8,     0,
      49,    30,    36,    38,    42,    43,    45,    47,    46,    48,
      32,     0,     7,    13,    11,     9,     0,     0,    31,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -77,   -77,   143,   -60,    34,   -76,   -77,    -7,   -77,   -77,
     -77,   -28,   -77,    53,    58,    90,    -8,   -77,    -3,   110,
       9,   -77,    51,    29,   -77,     0,   -77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    15,    16,    97,    98,    17,    47,    18,    19,    20,
      21,    72,    73,    74,    75,    76,    77,    22,    31,    32,
      23,    24,    25,    26,    27,    39,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      28,    29,    35,    43,    33,    33,    48,   102,    52,   104,
      28,    92,    80,    28,    93,    28,    30,    38,    56,    57,
     123,    58,    34,    49,    36,   126,    44,   128,     1,     2,
       3,     1,     2,     3,    37,     1,     2,     3,    61,    35,
      84,    33,    33,   106,    54,    55,    78,    28,   142,    78,
      40,   144,    45,   145,    94,    95,    70,   124,    14,    60,
     125,    71,    94,    95,    33,    14,    94,    95,    91,     1,
       2,     3,    64,    65,   127,   100,    96,   125,   129,    78,
     107,   125,    64,    68,   101,    88,    89,    90,   103,    59,
     141,   113,   114,   115,   116,   111,   112,    94,    95,    71,
      53,   131,   120,   134,   135,    86,    87,    63,    28,    66,
     140,    67,    81,    69,    79,    82,    85,    28,    78,    78,
      78,    78,   136,   137,   138,   139,   108,    78,   109,   110,
      50,   119,   121,     1,     2,     3,   117,   118,   122,   148,
      13,   130,     4,     5,     6,     7,    28,     8,     9,    10,
      11,    12,   146,   147,   149,     1,     2,     3,    51,   143,
     105,    13,   132,    14,     4,     5,     6,     7,   133,     8,
       9,    10,    11,    12,    99,     0,     0,     1,     2,     3,
       0,     0,     0,    13,     0,    14,    41,    42,     0,     7,
       0,     8,     9,    10,    11,    12,     0,     0,     0,     1,
       2,     3,     0,     0,     0,    13,    46,    14,    41,    42,
       0,     7,     0,     8,     9,    10,    11,    12,     0,     0,
       0,     1,     2,     3,     0,     0,     0,    13,    83,    14,
      41,    42,     0,     7,     0,     8,     9,    10,    11,    12,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,    14
};

static const yytype_int16 yycheck[] =
{
       0,    33,     5,    10,     4,     5,    13,    67,    15,    69,
      10,    34,    40,    13,    37,    15,     4,     8,     8,     9,
      96,    11,     4,    14,     4,   101,    38,   103,     3,     4,
       5,     3,     4,     5,    33,     3,     4,     5,    29,    42,
      47,    41,    42,    71,     6,     7,    37,    47,   124,    40,
      33,   127,    38,   129,    12,    13,    28,    34,    33,    34,
      37,    33,    12,    13,    64,    33,    12,    13,    59,     3,
       4,     5,    37,    38,    34,    66,    34,    37,    34,    70,
      71,    37,    37,    38,    34,    56,    57,    58,    34,    10,
     118,    24,    25,    26,    27,    22,    23,    12,    13,    33,
      38,   108,    93,   111,   112,    54,    55,    33,   108,    10,
     117,    33,     4,    33,    38,    18,    34,   117,   109,   110,
     111,   112,   113,   114,   115,   116,    34,   118,    30,    29,
       0,    38,     4,     3,     4,     5,    34,    33,     4,   146,
      31,    34,    12,    13,    14,    15,   146,    17,    18,    19,
      20,    21,    16,    34,    38,     3,     4,     5,    15,   125,
      70,    31,   109,    33,    12,    13,    14,    15,   110,    17,
      18,    19,    20,    21,    64,    -1,    -1,     3,     4,     5,
      -1,    -1,    -1,    31,    -1,    33,    12,    13,    -1,    15,
      -1,    17,    18,    19,    20,    21,    -1,    -1,    -1,     3,
       4,     5,    -1,    -1,    -1,    31,    32,    33,    12,    13,
      -1,    15,    -1,    17,    18,    19,    20,    21,    -1,    -1,
      -1,     3,     4,     5,    -1,    -1,    -1,    31,    32,    33,
      12,    13,    -1,    15,    -1,    17,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    12,    13,    14,    15,    17,    18,
      19,    20,    21,    31,    33,    40,    41,    44,    46,    47,
      48,    49,    56,    59,    60,    61,    62,    63,    64,    33,
       4,    57,    58,    64,     4,    57,     4,    33,    59,    64,
      33,    12,    13,    46,    38,    38,    32,    45,    46,    59,
       0,    41,    46,    38,     6,     7,     8,     9,    11,    10,
      34,    59,    65,    33,    37,    38,    10,    33,    38,    33,
      28,    33,    50,    51,    52,    53,    54,    55,    59,    38,
      50,     4,    18,    32,    46,    34,    61,    61,    62,    62,
      62,    59,    34,    37,    12,    13,    34,    42,    43,    58,
      59,    34,    42,    34,    42,    54,    50,    59,    34,    30,
      29,    22,    23,    24,    25,    26,    27,    34,    33,    38,
      59,     4,     4,    44,    34,    37,    44,    34,    44,    34,
      34,    46,    52,    53,    55,    55,    59,    59,    59,    59,
      46,    50,    44,    43,    44,    44,    16,    34,    46,    38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    40,    40,    41,    41,    41,    41,
      41,    41,    42,    42,    43,    43,    44,    44,    45,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    48,    49,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    54,    55,    55,    55,    55,    55,    55,
      56,    56,    57,    57,    58,    58,    59,    60,    60,    60,
      61,    61,    61,    61,    62,    62,    62,    63,    63,    63,
      63,    64,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     5,     6,     5,     6,
       5,     6,     1,     3,     2,     2,     2,     3,     1,     2,
       3,     1,     1,     1,     1,     1,     4,     2,     2,     2,
       5,     7,     5,     7,     1,     1,     3,     1,     3,     2,
       1,     1,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     1,     3,     1,     1,     3,     3,
       1,     3,     3,     3,     1,     4,     3,     1,     1,     1,
       3,     1,     1,     3
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
#line 72 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                     {
    (yyval.node)= new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,1,(yyvsp[0].node));  // 创建一个节点compileUnit，该节点包含Funcdef子节点
    ast_root=(yyval.node);
}
#line 1257 "MiniCBison.cpp"
    break;

  case 3: /* CompileUnit: CompileUnit FuncDef  */
#line 76 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                     {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));  // 插入节点
}
#line 1265 "MiniCBison.cpp"
    break;

  case 4: /* CompileUnit: Statement  */
#line 79 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
           {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,1,(yyvsp[0].node));
    ast_root=(yyval.node);
}
#line 1274 "MiniCBison.cpp"
    break;

  case 5: /* CompileUnit: CompileUnit Statement  */
#line 83 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
}
#line 1282 "MiniCBison.cpp"
    break;

  case 6: /* FuncDef: "int" DIGIT_ID "(" ")" Block  */
#line 89 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                      {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_INT32);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1292 "MiniCBison.cpp"
    break;

  case 7: /* FuncDef: "int" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 94 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                               {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_INT32);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1302 "MiniCBison.cpp"
    break;

  case 8: /* FuncDef: "void" DIGIT_ID "(" ")" Block  */
#line 99 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                               {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_VOID);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1312 "MiniCBison.cpp"
    break;

  case 9: /* FuncDef: "void" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 104 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_VOID);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1322 "MiniCBison.cpp"
    break;

  case 10: /* FuncDef: "float" DIGIT_ID "(" ")" Block  */
#line 109 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_FLOAT);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1332 "MiniCBison.cpp"
    break;

  case 11: /* FuncDef: "float" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 114 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                 {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_FLOAT);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1342 "MiniCBison.cpp"
    break;

  case 12: /* FuncFormalParams: FuncFormalParam  */
#line 122 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                   {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_FUNC_FORMAL_PARAMS,1,(yyvsp[0].node));
}
#line 1350 "MiniCBison.cpp"
    break;

  case 13: /* FuncFormalParams: FuncFormalParams "," FuncFormalParam  */
#line 125 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                       {
    (yyval.node) =insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1358 "MiniCBison.cpp"
    break;

  case 14: /* FuncFormalParam: "int" DIGIT_ID  */
#line 131 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    (yyval.node)=create_fun_formal_param(*(yyvsp[0].literal),BasicValueType::TYPE_INT32);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1368 "MiniCBison.cpp"
    break;

  case 15: /* FuncFormalParam: "float" DIGIT_ID  */
#line 136 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                  {
    (yyval.node)=create_fun_formal_param(*(yyvsp[0].literal),BasicValueType::TYPE_FLOAT);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1378 "MiniCBison.cpp"
    break;

  case 16: /* Block: "{" "}"  */
#line 144 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=nullptr; //无语句
}
#line 1386 "MiniCBison.cpp"
    break;

  case 17: /* Block: "{" BlockItemList "}"  */
#line 147 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    // 语句块中的语句列表 语句块指针指向语句列表
    (yyval.node) = (yyvsp[-1].node);
}
#line 1395 "MiniCBison.cpp"
    break;

  case 18: /* BlockItemList: Statement  */
#line 154 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_BLOCK,1,(yyvsp[0].node));
}
#line 1403 "MiniCBison.cpp"
    break;

  case 19: /* BlockItemList: BlockItemList Statement  */
#line 157 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node) = insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
}
#line 1411 "MiniCBison.cpp"
    break;

  case 20: /* Statement: "return" Expr ";"  */
#line 163 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                              {
    //返回语句
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_RETURN_STATEMENT,1,(yyvsp[-1].node));
}
#line 1420 "MiniCBison.cpp"
    break;

  case 21: /* Statement: Block  */
#line 167 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
        {
    (yyval.node)=(yyvsp[0].node);
}
#line 1428 "MiniCBison.cpp"
    break;

  case 22: /* Statement: IfStmt  */
#line 170 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
         {
    (yyval.node)=(yyvsp[0].node);
}
#line 1436 "MiniCBison.cpp"
    break;

  case 23: /* Statement: WhileStmt  */
#line 173 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
            {
    (yyval.node)=(yyvsp[0].node);
}
#line 1444 "MiniCBison.cpp"
    break;

  case 24: /* Statement: DowhileStmt  */
#line 176 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    (yyval.node)=(yyvsp[0].node);
}
#line 1452 "MiniCBison.cpp"
    break;

  case 25: /* Statement: Declare  */
#line 179 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
          {
    (yyval.node)=(yyvsp[0].node);
}
#line 1460 "MiniCBison.cpp"
    break;

  case 26: /* Statement: var "=" Expr ";"  */
#line 182 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_ASSIGN,2,(yyvsp[-3].node),(yyvsp[-1].node));
}
#line 1468 "MiniCBison.cpp"
    break;

  case 27: /* Statement: Expr ";"  */
#line 185 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
          {
    ; // 仅仅有一个表达式(可能是一个函数调用，也可能是a+b表达式)  目前先设定无动作
}
#line 1476 "MiniCBison.cpp"
    break;

  case 28: /* Statement: "break" ";"  */
#line 188 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    ; // break语句
}
#line 1484 "MiniCBison.cpp"
    break;

  case 29: /* Statement: "continue" ";"  */
#line 191 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    ;  //continue语句
}
#line 1492 "MiniCBison.cpp"
    break;

  case 30: /* IfStmt: "if" "(" Condition ")" Statement  */
#line 197 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                          {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1500 "MiniCBison.cpp"
    break;

  case 31: /* IfStmt: "if" "(" Condition ")" Statement "else" Statement  */
#line 200 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                    {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,3,(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1508 "MiniCBison.cpp"
    break;

  case 32: /* WhileStmt: "while" "(" Condition ")" Statement  */
#line 206 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_WHILESTMT,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1516 "MiniCBison.cpp"
    break;

  case 33: /* DowhileStmt: "do" Statement "while" "(" Condition ")" ";"  */
#line 212 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                           {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DOWHILESTMT,2,(yyvsp[-5].node),(yyvsp[-2].node));
}
#line 1524 "MiniCBison.cpp"
    break;

  case 34: /* Condition: OrCond  */
#line 219 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    (yyval.node)=(yyvsp[0].node);
}
#line 1532 "MiniCBison.cpp"
    break;

  case 35: /* OrCond: AndCond  */
#line 224 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=(yyvsp[0].node);
}
#line 1540 "MiniCBison.cpp"
    break;

  case 36: /* OrCond: OrCond "||" AndCond  */
#line 227 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_OR,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1548 "MiniCBison.cpp"
    break;

  case 37: /* AndCond: NotCond  */
#line 232 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                  {
  (yyval.node)=(yyvsp[0].node);
}
#line 1556 "MiniCBison.cpp"
    break;

  case 38: /* AndCond: AndCond "&&" NotCond  */
#line 235 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_AND,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1564 "MiniCBison.cpp"
    break;

  case 39: /* NotCond: "!" EquCondTerm  */
#line 240 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_NOT,1,(yyvsp[0].node));
}
#line 1572 "MiniCBison.cpp"
    break;

  case 40: /* NotCond: EquCondTerm  */
#line 243 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
  (yyval.node)=(yyvsp[0].node);
}
#line 1580 "MiniCBison.cpp"
    break;

  case 41: /* EquCondTerm: LessCondTerm  */
#line 248 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                           {
   (yyval.node)=(yyvsp[0].node);
}
#line 1588 "MiniCBison.cpp"
    break;

  case 42: /* EquCondTerm: EquCondTerm "==" LessCondTerm  */
#line 251 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_EQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1596 "MiniCBison.cpp"
    break;

  case 43: /* EquCondTerm: EquCondTerm "!=" LessCondTerm  */
#line 254 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_NOTEQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1604 "MiniCBison.cpp"
    break;

  case 44: /* LessCondTerm: Expr  */
#line 260 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                    {
   (yyval.node)=(yyvsp[0].node);
}
#line 1612 "MiniCBison.cpp"
    break;

  case 45: /* LessCondTerm: LessCondTerm "<" Expr  */
#line 263 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_LESS,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1620 "MiniCBison.cpp"
    break;

  case 46: /* LessCondTerm: LessCondTerm "<=" Expr  */
#line 266 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_LESSEQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1628 "MiniCBison.cpp"
    break;

  case 47: /* LessCondTerm: LessCondTerm ">" Expr  */
#line 269 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_GREATER,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1636 "MiniCBison.cpp"
    break;

  case 48: /* LessCondTerm: LessCondTerm ">=" Expr  */
#line 272 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_GREATEREQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1644 "MiniCBison.cpp"
    break;

  case 49: /* LessCondTerm: "(" Condition ")"  */
#line 275 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                    {
  (yyval.node)=(yyvsp[-1].node);
}
#line 1652 "MiniCBison.cpp"
    break;

  case 50: /* Declare: "int" DeclareItems ";"  */
#line 281 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    // 先指明DeclareItems下的值类型 ValueType  
    (yyvsp[-1].node)->val_type=BasicValueType::TYPE_INT32;
    (yyval.node)=(yyvsp[-1].node);
}
#line 1662 "MiniCBison.cpp"
    break;

  case 51: /* Declare: "float" DeclareItems ";"  */
#line 286 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyvsp[-1].node)->val_type=BasicValueType::TYPE_FLOAT;
    (yyval.node)=(yyvsp[-1].node);
}
#line 1671 "MiniCBison.cpp"
    break;

  case 52: /* DeclareItems: DeclareItem  */
#line 293 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,1,(yyvsp[0].node));
}
#line 1679 "MiniCBison.cpp"
    break;

  case 53: /* DeclareItems: DeclareItems "," DeclareItem  */
#line 296 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                              {
    (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1687 "MiniCBison.cpp"
    break;

  case 54: /* DeclareItem: var  */
#line 301 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    // 无动作
    // $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,$1);
}
#line 1696 "MiniCBison.cpp"
    break;

  case 55: /* DeclareItem: var "=" Expr  */
#line 305 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    ast_node* node=new_ast_node(ast_node_type::AST_OP_ASSIGN,2,(yyvsp[-2].node),(yyvsp[0].node));
    (yyval.node)=node;
    // $$ = new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,node);
}
#line 1706 "MiniCBison.cpp"
    break;

  case 56: /* Expr: AddExpr  */
#line 315 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=(yyvsp[0].node);
}
#line 1714 "MiniCBison.cpp"
    break;

  case 57: /* AddExpr: MulExpr  */
#line 321 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    // MulExpr可以推导得到UnaryExpr  这样写保证乘除取余的优先级
    (yyval.node)=(yyvsp[0].node);
}
#line 1723 "MiniCBison.cpp"
    break;

  case 58: /* AddExpr: AddExpr "+" MulExpr  */
#line 325 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_ADD,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1731 "MiniCBison.cpp"
    break;

  case 59: /* AddExpr: AddExpr "-" MulExpr  */
#line 328 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_SUB,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1739 "MiniCBison.cpp"
    break;

  case 60: /* MulExpr: UnaryExpr  */
#line 334 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                    {
    (yyval.node)=(yyvsp[0].node);
}
#line 1747 "MiniCBison.cpp"
    break;

  case 61: /* MulExpr: MulExpr "*" UnaryExpr  */
#line 337 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_MUL,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1755 "MiniCBison.cpp"
    break;

  case 62: /* MulExpr: MulExpr "/" UnaryExpr  */
#line 340 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DIV,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1763 "MiniCBison.cpp"
    break;

  case 63: /* MulExpr: MulExpr "%" UnaryExpr  */
#line 343 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_MOD,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1771 "MiniCBison.cpp"
    break;

  case 64: /* UnaryExpr: Term  */
#line 349 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=(yyvsp[0].node);
}
#line 1779 "MiniCBison.cpp"
    break;

  case 65: /* UnaryExpr: DIGIT_ID "(" FuncRealParams ")"  */
#line 352 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                  {
    // 有参函数调用的值
    (yyval.node)=create_fun_call(*(yyvsp[-3].literal),(yyvsp[-1].node));
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1790 "MiniCBison.cpp"
    break;

  case 66: /* UnaryExpr: DIGIT_ID "(" ")"  */
#line 358 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    //无参函数调用的值
    (yyval.node)=create_fun_call(*(yyvsp[-2].literal),nullptr);
    delete (yyvsp[-2].literal); //释放内存
    (yyvsp[-2].literal)=nullptr;
}
#line 1801 "MiniCBison.cpp"
    break;

  case 67: /* Term: DIGIT_INT  */
#line 368 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_LITERAL_INT,BasicValueType::TYPE_INT32);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1811 "MiniCBison.cpp"
    break;

  case 68: /* Term: DIGIT_FLOAT  */
#line 373 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_LITERAL_FLOAT,BasicValueType::TYPE_FLOAT);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1821 "MiniCBison.cpp"
    break;

  case 69: /* Term: var  */
#line 378 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
      {
    (yyval.node)=(yyvsp[0].node);
}
#line 1829 "MiniCBison.cpp"
    break;

  case 70: /* Term: "(" Expr ")"  */
#line 381 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=(yyvsp[-1].node);
}
#line 1837 "MiniCBison.cpp"
    break;

  case 71: /* var: DIGIT_ID  */
#line 387 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node) = new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_VAR_ID);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1847 "MiniCBison.cpp"
    break;

  case 72: /* FuncRealParams: Expr  */
#line 395 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_FUNC_REAL_PARAMS,1,(yyvsp[0].node));
}
#line 1855 "MiniCBison.cpp"
    break;

  case 73: /* FuncRealParams: FuncRealParams "," Expr  */
#line 398 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1863 "MiniCBison.cpp"
    break;


#line 1867 "MiniCBison.cpp"

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

#line 403 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"


// 语法分析时的错误信息
void yyerror(const char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
