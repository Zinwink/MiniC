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
#line 1 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"

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
  YYSYMBOL_T_EQUAL = 20,                   /* "=="  */
  YYSYMBOL_T_NOT_EQU = 21,                 /* "!="  */
  YYSYMBOL_T_LESS = 22,                    /* "<"  */
  YYSYMBOL_T_GREATER = 23,                 /* ">"  */
  YYSYMBOL_T_LESS_EQU = 24,                /* "<="  */
  YYSYMBOL_T_GREATER_EQU = 25,             /* ">="  */
  YYSYMBOL_T_NOT = 26,                     /* "!"  */
  YYSYMBOL_T_AND = 27,                     /* "&&"  */
  YYSYMBOL_T_OR = 28,                      /* "||"  */
  YYSYMBOL_T_LBRACE = 29,                  /* "{"  */
  YYSYMBOL_T_RBRACE = 30,                  /* "}"  */
  YYSYMBOL_T_LPAREN = 31,                  /* "("  */
  YYSYMBOL_T_RPAREN = 32,                  /* ")"  */
  YYSYMBOL_T_LSQU = 33,                    /* "["  */
  YYSYMBOL_T_RSQU = 34,                    /* "]"  */
  YYSYMBOL_T_COMMA = 35,                   /* ","  */
  YYSYMBOL_T_SEMICOLON = 36,               /* ";"  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_CompileUnit = 38,               /* CompileUnit  */
  YYSYMBOL_FuncDef = 39,                   /* FuncDef  */
  YYSYMBOL_FuncFormalParams = 40,          /* FuncFormalParams  */
  YYSYMBOL_FuncFormalParam = 41,           /* FuncFormalParam  */
  YYSYMBOL_Block = 42,                     /* Block  */
  YYSYMBOL_BlockItemList = 43,             /* BlockItemList  */
  YYSYMBOL_Statement = 44,                 /* Statement  */
  YYSYMBOL_IfStmt = 45,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 46,                 /* WhileStmt  */
  YYSYMBOL_DowhileStmt = 47,               /* DowhileStmt  */
  YYSYMBOL_Condition = 48,                 /* Condition  */
  YYSYMBOL_OrCond = 49,                    /* OrCond  */
  YYSYMBOL_AndCond = 50,                   /* AndCond  */
  YYSYMBOL_NotCond = 51,                   /* NotCond  */
  YYSYMBOL_EquCondTerm = 52,               /* EquCondTerm  */
  YYSYMBOL_LessCondTerm = 53,              /* LessCondTerm  */
  YYSYMBOL_Declare = 54,                   /* Declare  */
  YYSYMBOL_DeclareItems = 55,              /* DeclareItems  */
  YYSYMBOL_DeclareItem = 56,               /* DeclareItem  */
  YYSYMBOL_Expr = 57,                      /* Expr  */
  YYSYMBOL_AddExpr = 58,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 59,                   /* MulExpr  */
  YYSYMBOL_UnaryExpr = 60,                 /* UnaryExpr  */
  YYSYMBOL_Term = 61,                      /* Term  */
  YYSYMBOL_var = 62,                       /* var  */
  YYSYMBOL_FuncRealParams = 63             /* FuncRealParams  */
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
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


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
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    75,    78,    82,    88,    93,    98,   103,
     108,   113,   121,   124,   130,   135,   143,   146,   153,   156,
     162,   166,   169,   172,   175,   178,   181,   184,   190,   193,
     199,   205,   212,   217,   220,   225,   228,   233,   236,   241,
     244,   247,   253,   256,   259,   262,   265,   268,   274,   279,
     286,   289,   294,   298,   308,   314,   318,   321,   327,   330,
     333,   336,   342,   345,   351,   361,   366,   371,   374,   380,
     388,   391
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
  "\"return\"", "\"while\"", "\"do\"", "\"==\"", "\"!=\"", "\"<\"",
  "\">\"", "\"<=\"", "\">=\"", "\"!\"", "\"&&\"", "\"||\"", "\"{\"",
  "\"}\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\",\"", "\";\"", "$accept",
  "CompileUnit", "FuncDef", "FuncFormalParams", "FuncFormalParam", "Block",
  "BlockItemList", "Statement", "IfStmt", "WhileStmt", "DowhileStmt",
  "Condition", "OrCond", "AndCond", "NotCond", "EquCondTerm",
  "LessCondTerm", "Declare", "DeclareItems", "DeclareItem", "Expr",
  "AddExpr", "MulExpr", "UnaryExpr", "Term", "var", "FuncRealParams", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-73)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     126,   -73,   -28,   -73,    12,    19,    38,     5,    41,    30,
     186,   146,    41,    70,   -73,   -73,   -73,   -73,   -73,   -73,
     -73,    29,    22,    83,   -73,   -73,    40,     3,    69,    74,
     -73,    92,    85,    76,    87,    28,    91,   -73,    28,   143,
     143,   130,   -73,   166,   -73,   121,   -73,   -73,   -73,   -73,
      41,    41,    41,    41,    41,    41,   -73,   -73,   -23,     6,
     143,   -73,    41,    54,   -73,    66,    59,    28,   122,   124,
     129,   -73,    94,    33,   -73,   -73,   128,   -73,   131,   -73,
     -73,   -73,    83,    83,   -73,   -73,   -73,   132,   -73,    41,
     162,   163,   144,   -11,   -73,   -73,   -73,   144,    36,   144,
      61,    94,   140,   121,   186,    28,    28,    59,    59,    41,
      41,    41,    41,   186,    28,   -73,   -73,   -73,   -73,   -73,
     144,   120,   -73,   144,   -73,   144,   -73,   158,   129,   -73,
      33,    33,   -73,   -73,   -73,   -73,   -73,   148,   -73,   -73,
     -73,   -73,   186,   150,   -73,   -73
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    65,    69,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,    21,     4,    22,    23,    24,
      25,     0,    54,    55,    58,    62,    67,     0,    69,     0,
      50,    52,    69,     0,     0,     0,     0,    67,     0,     0,
       0,     0,    16,     0,    18,     0,     1,     3,     5,    27,
       0,     0,     0,     0,     0,     0,    64,    70,     0,     0,
       0,    48,     0,     0,    49,     0,     0,     0,     0,    32,
      33,    35,    38,    39,    42,    20,     0,    69,     0,    17,
      19,    68,    56,    57,    60,    59,    61,     0,    63,     0,
       0,     0,     0,     0,    12,    51,    53,     0,     0,     0,
       0,    37,     0,    42,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,    71,    14,    15,     6,
       0,     0,    10,     0,     8,     0,    47,    28,    34,    36,
      40,    41,    43,    45,    44,    46,    30,     0,     7,    13,
      11,     9,     0,     0,    29,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   169,    32,    67,   -72,   -73,     4,   -73,   -73,
     -73,   -37,   -73,    82,    88,   127,    27,   -73,    -3,   142,
      14,   -73,    86,    53,   -73,     0,   -73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    13,    14,    93,    94,    15,    43,    16,    17,    18,
      19,    68,    69,    70,    71,    72,    73,    20,    29,    30,
      21,    22,    23,    24,    25,    37,    58
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      26,    76,    33,    27,    31,    31,     1,     2,     3,    88,
      26,    26,    89,    26,    41,    44,    28,    48,    90,    91,
     119,   120,    36,    32,   121,   122,    45,   124,    50,    51,
     102,     1,     2,     3,    12,    56,    35,    33,    92,    31,
      31,    57,    34,    26,     1,     2,     3,    80,   138,    74,
      55,   140,    74,   141,    66,   109,   110,   111,   112,    67,
      31,    38,     1,     2,     3,    49,    90,    91,   123,    87,
      46,   121,    12,     1,     2,     3,    96,   137,    90,    91,
      74,   103,     4,     5,     6,     7,    97,     8,     9,    10,
      67,    52,    53,   125,    54,    98,   121,   100,    99,    11,
      59,    12,    62,   116,    26,    84,    85,    86,   127,    60,
      61,    60,    64,    26,   107,   108,    63,   136,    65,    74,
      74,    74,    74,   132,   133,   134,   135,    75,    74,     1,
       2,     3,    90,    91,   130,   131,    82,    83,     4,     5,
       6,     7,    26,     8,     9,    10,   144,    77,    78,     1,
       2,     3,   105,    81,   104,    11,   106,    12,    39,    40,
     113,     7,   114,     8,     9,    10,   117,   118,   115,     1,
       2,     3,   126,    11,   142,    11,    42,    12,    39,    40,
     143,     7,    47,     8,     9,    10,   145,   128,   139,     1,
       2,     3,     0,   101,   129,    11,    79,    12,    39,    40,
       0,     7,    95,     8,     9,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    11,     0,    12
};

static const yytype_int16 yycheck[] =
{
       0,    38,     5,    31,     4,     5,     3,     4,     5,    32,
      10,    11,    35,    13,    10,    11,     4,    13,    12,    13,
      92,    32,     8,     4,    35,    97,    12,    99,     6,     7,
      67,     3,     4,     5,    31,    32,    31,    40,    32,    39,
      40,    27,     4,    43,     3,     4,     5,    43,   120,    35,
      10,   123,    38,   125,    26,    22,    23,    24,    25,    31,
      60,    31,     3,     4,     5,    36,    12,    13,    32,    55,
       0,    35,    31,     3,     4,     5,    62,   114,    12,    13,
      66,    67,    12,    13,    14,    15,    32,    17,    18,    19,
      31,     8,     9,    32,    11,    63,    35,    65,    32,    29,
      31,    31,    10,    89,   104,    52,    53,    54,   104,    35,
      36,    35,    36,   113,    20,    21,    31,   113,    31,   105,
     106,   107,   108,   109,   110,   111,   112,    36,   114,     3,
       4,     5,    12,    13,   107,   108,    50,    51,    12,    13,
      14,    15,   142,    17,    18,    19,   142,     4,    18,     3,
       4,     5,    28,    32,    32,    29,    27,    31,    12,    13,
      32,    15,    31,    17,    18,    19,     4,     4,    36,     3,
       4,     5,    32,    29,    16,    29,    30,    31,    12,    13,
      32,    15,    13,    17,    18,    19,    36,   105,   121,     3,
       4,     5,    -1,    66,   106,    29,    30,    31,    12,    13,
      -1,    15,    60,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    12,    13,    14,    15,    17,    18,
      19,    29,    31,    38,    39,    42,    44,    45,    46,    47,
      54,    57,    58,    59,    60,    61,    62,    31,     4,    55,
      56,    62,     4,    55,     4,    31,    57,    62,    31,    12,
      13,    44,    30,    43,    44,    57,     0,    39,    44,    36,
       6,     7,     8,     9,    11,    10,    32,    57,    63,    31,
      35,    36,    10,    31,    36,    31,    26,    31,    48,    49,
      50,    51,    52,    53,    57,    36,    48,     4,    18,    30,
      44,    32,    59,    59,    60,    60,    60,    57,    32,    35,
      12,    13,    32,    40,    41,    56,    57,    32,    40,    32,
      40,    52,    48,    57,    32,    28,    27,    20,    21,    22,
      23,    24,    25,    32,    31,    36,    57,     4,     4,    42,
      32,    35,    42,    32,    42,    32,    32,    44,    50,    51,
      53,    53,    57,    57,    57,    57,    44,    48,    42,    41,
      42,    42,    16,    32,    44,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    38,    38,    38,    39,    39,    39,    39,
      39,    39,    40,    40,    41,    41,    42,    42,    43,    43,
      44,    44,    44,    44,    44,    44,    44,    44,    45,    45,
      46,    47,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    52,    53,    53,    53,    53,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    58,    58,    58,    59,    59,
      59,    59,    60,    60,    60,    61,    61,    61,    61,    62,
      63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     5,     6,     5,     6,
       5,     6,     1,     3,     2,     2,     2,     3,     1,     2,
       3,     1,     1,     1,     1,     1,     4,     2,     5,     7,
       5,     7,     1,     1,     3,     1,     3,     2,     1,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     1,     3,     1,     1,     3,     3,     1,     3,
       3,     3,     1,     4,     3,     1,     1,     1,     3,     1,
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
#line 71 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                     {
    (yyval.node)= new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,1,(yyvsp[0].node));  // 创建一个节点compileUnit，该节点包含Funcdef子节点
    ast_root=(yyval.node);
}
#line 1246 "MiniCBison.cpp"
    break;

  case 3: /* CompileUnit: CompileUnit FuncDef  */
#line 75 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                     {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));  // 插入节点
}
#line 1254 "MiniCBison.cpp"
    break;

  case 4: /* CompileUnit: Statement  */
#line 78 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
           {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,1,(yyvsp[0].node));
    ast_root=(yyval.node);
}
#line 1263 "MiniCBison.cpp"
    break;

  case 5: /* CompileUnit: CompileUnit Statement  */
#line 82 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                       {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
}
#line 1271 "MiniCBison.cpp"
    break;

  case 6: /* FuncDef: "int" DIGIT_ID "(" ")" Block  */
#line 88 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                      {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_INT32);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1281 "MiniCBison.cpp"
    break;

  case 7: /* FuncDef: "int" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 93 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                               {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_INT32);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1291 "MiniCBison.cpp"
    break;

  case 8: /* FuncDef: "void" DIGIT_ID "(" ")" Block  */
#line 98 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                               {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_VOID);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1301 "MiniCBison.cpp"
    break;

  case 9: /* FuncDef: "void" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 103 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                                {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_VOID);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1311 "MiniCBison.cpp"
    break;

  case 10: /* FuncDef: "float" DIGIT_ID "(" ")" Block  */
#line 108 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_FLOAT);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1321 "MiniCBison.cpp"
    break;

  case 11: /* FuncDef: "float" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 113 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                                 {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_FLOAT);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1331 "MiniCBison.cpp"
    break;

  case 12: /* FuncFormalParams: FuncFormalParam  */
#line 121 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                   {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_FUNC_FORMAL_PARAMS,1,(yyvsp[0].node));
}
#line 1339 "MiniCBison.cpp"
    break;

  case 13: /* FuncFormalParams: FuncFormalParams "," FuncFormalParam  */
#line 124 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                       {
    (yyval.node) =insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1347 "MiniCBison.cpp"
    break;

  case 14: /* FuncFormalParam: "int" DIGIT_ID  */
#line 130 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                {
    (yyval.node)=create_fun_formal_param(*(yyvsp[0].literal),BasicValueType::TYPE_INT32);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1357 "MiniCBison.cpp"
    break;

  case 15: /* FuncFormalParam: "float" DIGIT_ID  */
#line 135 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                  {
    (yyval.node)=create_fun_formal_param(*(yyvsp[0].literal),BasicValueType::TYPE_FLOAT);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1367 "MiniCBison.cpp"
    break;

  case 16: /* Block: "{" "}"  */
#line 143 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
               {
    (yyval.node)=nullptr; //无语句
}
#line 1375 "MiniCBison.cpp"
    break;

  case 17: /* Block: "{" BlockItemList "}"  */
#line 146 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                        {
    // 语句块中的语句列表 语句块指针指向语句列表
    (yyval.node) = (yyvsp[-1].node);
}
#line 1384 "MiniCBison.cpp"
    break;

  case 18: /* BlockItemList: Statement  */
#line 153 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                          {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_BLOCK,1,(yyvsp[0].node));
}
#line 1392 "MiniCBison.cpp"
    break;

  case 19: /* BlockItemList: BlockItemList Statement  */
#line 156 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                          {
    (yyval.node) = insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
}
#line 1400 "MiniCBison.cpp"
    break;

  case 20: /* Statement: "return" Expr ";"  */
#line 162 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                              {
    //返回语句
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_RETURN_STATEMENT,1,(yyvsp[-1].node));
}
#line 1409 "MiniCBison.cpp"
    break;

  case 21: /* Statement: Block  */
#line 166 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
        {
    (yyval.node)=(yyvsp[0].node);
}
#line 1417 "MiniCBison.cpp"
    break;

  case 22: /* Statement: IfStmt  */
#line 169 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
         {
    (yyval.node)=(yyvsp[0].node);
}
#line 1425 "MiniCBison.cpp"
    break;

  case 23: /* Statement: WhileStmt  */
#line 172 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
            {
    (yyval.node)=(yyvsp[0].node);
}
#line 1433 "MiniCBison.cpp"
    break;

  case 24: /* Statement: DowhileStmt  */
#line 175 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
              {
    (yyval.node)=(yyvsp[0].node);
}
#line 1441 "MiniCBison.cpp"
    break;

  case 25: /* Statement: Declare  */
#line 178 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
          {
    (yyval.node)=(yyvsp[0].node);
}
#line 1449 "MiniCBison.cpp"
    break;

  case 26: /* Statement: var "=" Expr ";"  */
#line 181 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                   {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_ASSIGN,2,(yyvsp[-3].node),(yyvsp[-1].node));
}
#line 1457 "MiniCBison.cpp"
    break;

  case 27: /* Statement: Expr ";"  */
#line 184 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
          {
    ; // 仅仅有一个表达式(可能是一个函数调用，也可能是a+b表达式)  目前先设定无动作
}
#line 1465 "MiniCBison.cpp"
    break;

  case 28: /* IfStmt: "if" "(" Condition ")" Statement  */
#line 190 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                          {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1473 "MiniCBison.cpp"
    break;

  case 29: /* IfStmt: "if" "(" Condition ")" Statement "else" Statement  */
#line 193 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                                    {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,3,(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1481 "MiniCBison.cpp"
    break;

  case 30: /* WhileStmt: "while" "(" Condition ")" Statement  */
#line 199 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                                {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_WHILESTMT,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1489 "MiniCBison.cpp"
    break;

  case 31: /* DowhileStmt: "do" Statement "while" "(" Condition ")" ";"  */
#line 205 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                                           {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DOWHILESTMT,2,(yyvsp[-5].node),(yyvsp[-2].node));
}
#line 1497 "MiniCBison.cpp"
    break;

  case 32: /* Condition: OrCond  */
#line 212 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                   {
    (yyval.node)=(yyvsp[0].node);
}
#line 1505 "MiniCBison.cpp"
    break;

  case 33: /* OrCond: AndCond  */
#line 217 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                 {
    (yyval.node)=(yyvsp[0].node);
}
#line 1513 "MiniCBison.cpp"
    break;

  case 34: /* OrCond: OrCond "||" AndCond  */
#line 220 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                      {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_OR,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1521 "MiniCBison.cpp"
    break;

  case 35: /* AndCond: NotCond  */
#line 225 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                  {
  (yyval.node)=(yyvsp[0].node);
}
#line 1529 "MiniCBison.cpp"
    break;

  case 36: /* AndCond: AndCond "&&" NotCond  */
#line 228 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                       {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_AND,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1537 "MiniCBison.cpp"
    break;

  case 37: /* NotCond: "!" EquCondTerm  */
#line 233 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                          {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_NOT,1,(yyvsp[0].node));
}
#line 1545 "MiniCBison.cpp"
    break;

  case 38: /* NotCond: EquCondTerm  */
#line 236 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
              {
  (yyval.node)=(yyvsp[0].node);
}
#line 1553 "MiniCBison.cpp"
    break;

  case 39: /* EquCondTerm: LessCondTerm  */
#line 241 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                           {
   (yyval.node)=(yyvsp[0].node);
}
#line 1561 "MiniCBison.cpp"
    break;

  case 40: /* EquCondTerm: EquCondTerm "==" LessCondTerm  */
#line 244 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_EQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1569 "MiniCBison.cpp"
    break;

  case 41: /* EquCondTerm: EquCondTerm "!=" LessCondTerm  */
#line 247 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_NOTEQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1577 "MiniCBison.cpp"
    break;

  case 42: /* LessCondTerm: Expr  */
#line 253 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                    {
   (yyval.node)=(yyvsp[0].node);
}
#line 1585 "MiniCBison.cpp"
    break;

  case 43: /* LessCondTerm: LessCondTerm "<" Expr  */
#line 256 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                        {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_LESS,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1593 "MiniCBison.cpp"
    break;

  case 44: /* LessCondTerm: LessCondTerm "<=" Expr  */
#line 259 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                         {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_LESSEQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1601 "MiniCBison.cpp"
    break;

  case 45: /* LessCondTerm: LessCondTerm ">" Expr  */
#line 262 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                        {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_GREATER,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1609 "MiniCBison.cpp"
    break;

  case 46: /* LessCondTerm: LessCondTerm ">=" Expr  */
#line 265 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                         {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_GREATEREQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1617 "MiniCBison.cpp"
    break;

  case 47: /* LessCondTerm: "(" Condition ")"  */
#line 268 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                    {
  (yyval.node)=(yyvsp[-1].node);
}
#line 1625 "MiniCBison.cpp"
    break;

  case 48: /* Declare: "int" DeclareItems ";"  */
#line 274 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                {
    // 先指明DeclareItems下的值类型 ValueType  
    (yyvsp[-1].node)->val_type=BasicValueType::TYPE_INT32;
    (yyval.node)=(yyvsp[-1].node);
}
#line 1635 "MiniCBison.cpp"
    break;

  case 49: /* Declare: "float" DeclareItems ";"  */
#line 279 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                          {
    (yyvsp[-1].node)->val_type=BasicValueType::TYPE_FLOAT;
    (yyval.node)=(yyvsp[-1].node);
}
#line 1644 "MiniCBison.cpp"
    break;

  case 50: /* DeclareItems: DeclareItem  */
#line 286 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                          {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,1,(yyvsp[0].node));
}
#line 1652 "MiniCBison.cpp"
    break;

  case 51: /* DeclareItems: DeclareItems "," DeclareItem  */
#line 289 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                              {
    (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1660 "MiniCBison.cpp"
    break;

  case 52: /* DeclareItem: var  */
#line 294 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                 {
    // 无动作
    // $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,$1);
}
#line 1669 "MiniCBison.cpp"
    break;

  case 53: /* DeclareItem: var "=" Expr  */
#line 298 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
               {
    ast_node* node=new_ast_node(ast_node_type::AST_OP_ASSIGN,2,(yyvsp[-2].node),(yyvsp[0].node));
    (yyval.node)=node;
    // $$ = new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,node);
}
#line 1679 "MiniCBison.cpp"
    break;

  case 54: /* Expr: AddExpr  */
#line 308 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
               {
    (yyval.node)=(yyvsp[0].node);
}
#line 1687 "MiniCBison.cpp"
    break;

  case 55: /* AddExpr: MulExpr  */
#line 314 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                 {
    // MulExpr可以推导得到UnaryExpr  这样写保证乘除取余的优先级
    (yyval.node)=(yyvsp[0].node);
}
#line 1696 "MiniCBison.cpp"
    break;

  case 56: /* AddExpr: AddExpr "+" MulExpr  */
#line 318 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_ADD,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1704 "MiniCBison.cpp"
    break;

  case 57: /* AddExpr: AddExpr "-" MulExpr  */
#line 321 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_SUB,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1712 "MiniCBison.cpp"
    break;

  case 58: /* MulExpr: UnaryExpr  */
#line 327 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                    {
    (yyval.node)=(yyvsp[0].node);
}
#line 1720 "MiniCBison.cpp"
    break;

  case 59: /* MulExpr: MulExpr "*" UnaryExpr  */
#line 330 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_MUL,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1728 "MiniCBison.cpp"
    break;

  case 60: /* MulExpr: MulExpr "/" UnaryExpr  */
#line 333 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DIV,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1736 "MiniCBison.cpp"
    break;

  case 61: /* MulExpr: MulExpr "%" UnaryExpr  */
#line 336 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_MOD,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1744 "MiniCBison.cpp"
    break;

  case 62: /* UnaryExpr: Term  */
#line 342 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                 {
    (yyval.node)=(yyvsp[0].node);
}
#line 1752 "MiniCBison.cpp"
    break;

  case 63: /* UnaryExpr: DIGIT_ID "(" FuncRealParams ")"  */
#line 345 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                                  {
    // 有参函数调用的值
    (yyval.node)=create_fun_call(*(yyvsp[-3].literal),(yyvsp[-1].node));
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1763 "MiniCBison.cpp"
    break;

  case 64: /* UnaryExpr: DIGIT_ID "(" ")"  */
#line 351 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                   {
    //无参函数调用的值
    (yyval.node)=create_fun_call(*(yyvsp[-2].literal),nullptr);
    delete (yyvsp[-2].literal); //释放内存
    (yyvsp[-2].literal)=nullptr;
}
#line 1774 "MiniCBison.cpp"
    break;

  case 65: /* Term: DIGIT_INT  */
#line 361 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                 {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_LITERAL_INT,BasicValueType::TYPE_INT32);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1784 "MiniCBison.cpp"
    break;

  case 66: /* Term: DIGIT_FLOAT  */
#line 366 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
              {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_LITERAL_FLOAT,BasicValueType::TYPE_FLOAT);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1794 "MiniCBison.cpp"
    break;

  case 67: /* Term: var  */
#line 371 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
      {
    (yyval.node)=(yyvsp[0].node);
}
#line 1802 "MiniCBison.cpp"
    break;

  case 68: /* Term: "(" Expr ")"  */
#line 374 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
               {
    (yyval.node)=(yyvsp[-1].node);
}
#line 1810 "MiniCBison.cpp"
    break;

  case 69: /* var: DIGIT_ID  */
#line 380 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
               {
    (yyval.node) = new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_VAR_ID);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1820 "MiniCBison.cpp"
    break;

  case 70: /* FuncRealParams: Expr  */
#line 388 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_FUNC_REAL_PARAMS,1,(yyvsp[0].node));
}
#line 1828 "MiniCBison.cpp"
    break;

  case 71: /* FuncRealParams: FuncRealParams "," Expr  */
#line 391 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"
                          {
    (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1836 "MiniCBison.cpp"
    break;


#line 1840 "MiniCBison.cpp"

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

#line 396 "/home/mole/Program/compile_principle/MiniC/frontend/MiniC.y"


// 语法分析时的错误信息
void yyerror(const char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
