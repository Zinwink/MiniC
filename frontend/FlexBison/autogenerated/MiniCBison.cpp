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
  YYSYMBOL_Array = 59,                     /* Array  */
  YYSYMBOL_Expr = 60,                      /* Expr  */
  YYSYMBOL_AddExpr = 61,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 62,                   /* MulExpr  */
  YYSYMBOL_UnaryExpr = 63,                 /* UnaryExpr  */
  YYSYMBOL_Term = 64,                      /* Term  */
  YYSYMBOL_var = 65,                       /* var  */
  YYSYMBOL_FuncRealParams = 66             /* FuncRealParams  */
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
#define YYFINAL  65
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

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
       0,    73,    73,    77,    80,    84,    90,    95,   100,   105,
     110,   115,   123,   126,   132,   137,   142,   145,   151,   155,
     162,   165,   171,   175,   179,   182,   185,   188,   191,   200,
     203,   206,   209,   212,   222,   233,   249,   260,   272,   277,
     280,   285,   288,   293,   296,   301,   304,   307,   313,   316,
     319,   322,   325,   328,   334,   339,   346,   355,   368,   373,
     378,   387,   396,   406,   412,   416,   419,   425,   428,   431,
     434,   440,   443,   449,   459,   464,   469,   472,   475,   482,
     490,   493
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
  "DeclareItems", "DeclareItem", "Array", "Expr", "AddExpr", "MulExpr",
  "UnaryExpr", "Term", "var", "FuncRealParams", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-23)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     175,   -23,   -12,   -23,     2,     7,    52,    32,    33,    41,
     219,    57,    71,    26,    79,    73,   153,   -23,   -23,   -23,
     -23,   -23,   -23,    76,    49,    91,   -23,   119,    92,   -23,
      -1,   -23,   140,    17,   -23,   -23,   117,    39,   135,    70,
     111,   -23,   108,   165,    95,   113,   143,    73,    42,   -23,
     108,   114,   -23,    73,   173,   173,   164,   -23,   -23,   119,
     -23,   197,   -23,   149,   151,   -23,   -23,   -23,   -23,    73,
      73,    26,    26,    42,    42,    42,    42,    73,   188,    42,
      42,    42,    42,    42,    73,   -23,   -23,   -22,   161,    28,
     173,   -23,    42,    55,   -23,    68,   170,   151,   -23,   171,
     163,   166,   -23,   -23,   -23,   -23,    91,   -23,    92,    92,
     -23,   -23,   -23,   -23,   169,   177,    17,    17,   -23,   -23,
     -23,   181,   -23,    42,   -23,   207,   216,   190,    -2,   -23,
     -23,   -23,   190,    14,   190,    16,   219,   219,    73,   -23,
     -23,   -23,   -23,   163,   108,   163,   108,   -23,   190,   142,
     -23,   190,   -23,   190,   210,   -23,   193,   -23,   -23,   -23,
     -23,   219,   195,   -23,   -23
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    74,    79,    75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,    24,     4,
      25,    26,    27,     0,    38,    39,    41,    44,    45,    28,
      78,    48,    63,    64,    67,    71,    76,     0,     0,    79,
       0,    56,    60,    58,    79,     0,     0,     0,     0,    23,
      78,     0,    76,     0,     0,     0,     0,    31,    32,    43,
      18,     0,    20,     0,    48,     1,     3,     5,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,    80,     0,     0,     0,
       0,    54,     0,     0,    55,     0,     0,     0,    22,     0,
      79,     0,    19,    21,    53,    77,    40,    42,    46,    47,
      49,    51,    50,    52,     0,     0,    65,    66,    69,    68,
      70,     0,    72,     0,    61,     0,     0,     0,     0,    12,
      57,    59,     0,     0,     0,     0,     0,     0,     0,    33,
      62,    30,    81,    14,    16,    15,    17,     6,     0,     0,
      10,     0,     8,     0,    34,    36,     0,     7,    13,    11,
       9,     0,     0,    35,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -23,   -23,   225,    38,    86,   -19,   -23,     8,   -23,   -23,
     -23,   -14,   -23,   174,   172,   231,    88,   -23,    -3,   155,
       0,    12,   -23,    83,    40,   -23,     3,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    16,    17,   128,   129,    18,    61,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    40,    41,
      50,    31,    32,    33,    34,    35,    52,    87
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,    63,    45,    36,    42,    42,    39,    43,    43,    77,
      30,    44,   122,    36,    30,   123,    30,    36,    56,    36,
      51,    37,    62,    38,    67,    81,    82,    64,    83,     1,
       2,     3,   148,    96,    78,   149,     1,     2,     3,    99,
     125,   126,     1,     2,     3,     1,     2,     3,   151,    86,
     153,   149,    45,   149,    42,    42,    46,    43,    43,    15,
      97,    30,   127,   114,    36,    47,    48,   125,   126,   103,
     121,    49,    48,    85,    53,    48,     1,     2,     3,    69,
     125,   126,     1,     2,     3,   110,   111,   112,   113,   132,
      42,    54,    55,    43,     7,    57,     8,     9,    10,    11,
      12,    13,   134,    89,   131,    38,    15,    13,   147,    58,
      14,    60,    15,   150,    68,   152,    73,    74,    75,    76,
      70,   118,   119,   120,   156,   144,   146,    84,    93,   157,
      38,   133,   159,   135,   160,   142,    30,    30,    88,    36,
      36,    71,    72,    78,   154,   155,    79,    80,    90,    91,
      90,    94,    98,    65,   125,   126,     1,     2,     3,   108,
     109,    30,   116,   117,    36,     4,     5,     6,     7,   163,
       8,     9,    10,    11,    12,    92,    95,   100,     1,     2,
       3,    13,   101,   104,    14,   105,    15,     4,     5,     6,
       7,   115,     8,     9,    10,    11,    12,   124,    38,   138,
       1,     2,     3,    13,   136,   137,    14,   139,    15,    54,
      55,   143,     7,   140,     8,     9,    10,    11,    12,   141,
     145,    14,     1,     2,     3,    13,   161,   162,    14,   102,
      15,    54,    55,   164,     7,   158,     8,     9,    10,    11,
      12,    66,   107,   106,    59,   130,     0,    13,     0,     0,
      14,     0,    15
};

static const yytype_int16 yycheck[] =
{
       0,    15,     5,     0,     4,     5,     4,     4,     5,    10,
      10,     4,    34,    10,    14,    37,    16,    14,    10,    16,
       8,    33,    14,    35,    16,     8,     9,    15,    11,     3,
       4,     5,    34,    47,    35,    37,     3,     4,     5,    53,
      12,    13,     3,     4,     5,     3,     4,     5,    34,    37,
      34,    37,    55,    37,    54,    55,     4,    54,    55,    33,
      48,    61,    34,    77,    61,    33,    33,    12,    13,    61,
      84,    38,    33,    34,    33,    33,     3,     4,     5,    30,
      12,    13,     3,     4,     5,    73,    74,    75,    76,    34,
      90,    12,    13,    90,    15,    38,    17,    18,    19,    20,
      21,    28,    34,    33,    92,    35,    33,    28,   127,    38,
      31,    32,    33,   132,    38,   134,    24,    25,    26,    27,
      29,    81,    82,    83,   138,   125,   126,    10,    33,   148,
      35,    93,   151,    95,   153,   123,   136,   137,     3,   136,
     137,    22,    23,    35,   136,   137,     6,     7,    37,    38,
      37,    38,    38,     0,    12,    13,     3,     4,     5,    71,
      72,   161,    79,    80,   161,    12,    13,    14,    15,   161,
      17,    18,    19,    20,    21,    10,    33,     4,     3,     4,
       5,    28,    18,    34,    31,    34,    33,    12,    13,    14,
      15,     3,    17,    18,    19,    20,    21,    36,    35,    33,
       3,     4,     5,    28,    34,    34,    31,    38,    33,    12,
      13,     4,    15,    36,    17,    18,    19,    20,    21,    38,
       4,    31,     3,     4,     5,    28,    16,    34,    31,    32,
      33,    12,    13,    38,    15,   149,    17,    18,    19,    20,
      21,    16,    70,    69,    13,    90,    -1,    28,    -1,    -1,
      31,    -1,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    12,    13,    14,    15,    17,    18,
      19,    20,    21,    28,    31,    33,    40,    41,    44,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      59,    60,    61,    62,    63,    64,    65,    33,    35,     4,
      57,    58,    59,    65,     4,    57,     4,    33,    33,    38,
      59,    60,    65,    33,    12,    13,    46,    38,    38,    54,
      32,    45,    46,    50,    60,     0,    41,    46,    38,    30,
      29,    22,    23,    24,    25,    26,    27,    10,    35,     6,
       7,     8,     9,    11,    10,    34,    60,    66,     3,    33,
      37,    38,    10,    33,    38,    33,    50,    60,    38,    50,
       4,    18,    32,    46,    34,    34,    52,    53,    55,    55,
      60,    60,    60,    60,    50,     3,    62,    62,    63,    63,
      63,    50,    34,    37,    36,    12,    13,    34,    42,    43,
      58,    60,    34,    42,    34,    42,    34,    34,    33,    38,
      36,    38,    60,     4,    59,     4,    59,    44,    34,    37,
      44,    34,    44,    34,    46,    46,    50,    44,    43,    44,
      44,    16,    34,    46,    38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    40,    40,    41,    41,    41,    41,
      41,    41,    42,    42,    43,    43,    43,    43,    44,    44,
      45,    45,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    47,    47,    48,    49,    50,    51,
      51,    52,    52,    53,    53,    54,    54,    54,    55,    55,
      55,    55,    55,    55,    56,    56,    57,    57,    58,    58,
      58,    59,    59,    60,    61,    61,    61,    62,    62,    62,
      62,    63,    63,    63,    64,    64,    64,    64,    64,    65,
      66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     5,     6,     5,     6,
       5,     6,     1,     3,     2,     2,     2,     2,     2,     3,
       1,     2,     3,     2,     1,     1,     1,     1,     1,     2,
       4,     2,     2,     4,     5,     7,     5,     7,     1,     1,
       3,     1,     3,     2,     1,     1,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     3,
       1,     4,     4,     1,     1,     3,     3,     1,     3,     3,
       3,     1,     4,     3,     1,     1,     1,     3,     1,     1,
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
#line 73 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                     {
    (yyval.node)= new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,1,(yyvsp[0].node));  // 创建一个节点compileUnit，该节点包含Funcdef子节点
    ast_root=(yyval.node);
}
#line 1267 "MiniCBison.cpp"
    break;

  case 3: /* CompileUnit: CompileUnit FuncDef  */
#line 77 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                     {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));  // 插入节点
}
#line 1275 "MiniCBison.cpp"
    break;

  case 4: /* CompileUnit: Statement  */
#line 80 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
           {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COMPILE_UNIT,1,(yyvsp[0].node));
    ast_root=(yyval.node);
}
#line 1284 "MiniCBison.cpp"
    break;

  case 5: /* CompileUnit: CompileUnit Statement  */
#line 84 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
    (yyval.node)=insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
}
#line 1292 "MiniCBison.cpp"
    break;

  case 6: /* FuncDef: "int" DIGIT_ID "(" ")" Block  */
#line 90 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                      {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_INT32);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1302 "MiniCBison.cpp"
    break;

  case 7: /* FuncDef: "int" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 95 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                               {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_INT32);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1312 "MiniCBison.cpp"
    break;

  case 8: /* FuncDef: "void" DIGIT_ID "(" ")" Block  */
#line 100 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                               {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_VOID);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1322 "MiniCBison.cpp"
    break;

  case 9: /* FuncDef: "void" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 105 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_VOID);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1332 "MiniCBison.cpp"
    break;

  case 10: /* FuncDef: "float" DIGIT_ID "(" ")" Block  */
#line 110 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    (yyval.node)=create_fun_def(*(yyvsp[-3].literal),(yyvsp[0].node),nullptr,BasicValueType::TYPE_FLOAT);
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1342 "MiniCBison.cpp"
    break;

  case 11: /* FuncDef: "float" DIGIT_ID "(" FuncFormalParams ")" Block  */
#line 115 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                 {
    (yyval.node)=create_fun_def(*(yyvsp[-4].literal),(yyvsp[0].node),(yyvsp[-2].node),BasicValueType::TYPE_FLOAT);
    delete (yyvsp[-4].literal); //释放内存
    (yyvsp[-4].literal)=nullptr;
}
#line 1352 "MiniCBison.cpp"
    break;

  case 12: /* FuncFormalParams: FuncFormalParam  */
#line 123 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                   {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_FUNC_FORMAL_PARAMS,1,(yyvsp[0].node));
}
#line 1360 "MiniCBison.cpp"
    break;

  case 13: /* FuncFormalParams: FuncFormalParams "," FuncFormalParam  */
#line 126 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                       {
    (yyval.node) =insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1368 "MiniCBison.cpp"
    break;

  case 14: /* FuncFormalParam: "int" DIGIT_ID  */
#line 132 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    (yyval.node)=create_fun_formal_param(*(yyvsp[0].literal),BasicValueType::TYPE_INT32);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1378 "MiniCBison.cpp"
    break;

  case 15: /* FuncFormalParam: "float" DIGIT_ID  */
#line 137 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                  {
    (yyval.node)=create_fun_formal_param(*(yyvsp[0].literal),BasicValueType::TYPE_FLOAT);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1388 "MiniCBison.cpp"
    break;

  case 16: /* FuncFormalParam: "int" Array  */
#line 142 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
             {
    
}
#line 1396 "MiniCBison.cpp"
    break;

  case 17: /* FuncFormalParam: "float" Array  */
#line 145 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {

}
#line 1404 "MiniCBison.cpp"
    break;

  case 18: /* Block: "{" "}"  */
#line 151 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)= new ast_node(ast_node_type::AST_OP_BLOCK);
    // 无操作
}
#line 1413 "MiniCBison.cpp"
    break;

  case 19: /* Block: "{" BlockItemList "}"  */
#line 155 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    // 语句块中的语句列表 语句块指针指向语句列表
    (yyval.node) = (yyvsp[-1].node);
}
#line 1422 "MiniCBison.cpp"
    break;

  case 20: /* BlockItemList: Statement  */
#line 162 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_BLOCK,1,(yyvsp[0].node));
}
#line 1430 "MiniCBison.cpp"
    break;

  case 21: /* BlockItemList: BlockItemList Statement  */
#line 165 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node) = insert_ast_node((yyvsp[-1].node),(yyvsp[0].node));
}
#line 1438 "MiniCBison.cpp"
    break;

  case 22: /* Statement: "return" Expr ";"  */
#line 171 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                              {
    //返回语句
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_RETURN_STATEMENT,1,(yyvsp[-1].node));
}
#line 1447 "MiniCBison.cpp"
    break;

  case 23: /* Statement: "return" ";"  */
#line 175 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    //无返回值
    (yyval.node)=new ast_node(ast_node_type::AST_OP_RETURN_STATEMENT);
}
#line 1456 "MiniCBison.cpp"
    break;

  case 24: /* Statement: Block  */
#line 179 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
        {
    (yyval.node)=(yyvsp[0].node);
}
#line 1464 "MiniCBison.cpp"
    break;

  case 25: /* Statement: IfStmt  */
#line 182 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
         {
    (yyval.node)=(yyvsp[0].node);
}
#line 1472 "MiniCBison.cpp"
    break;

  case 26: /* Statement: WhileStmt  */
#line 185 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
            {
    (yyval.node)=(yyvsp[0].node);
}
#line 1480 "MiniCBison.cpp"
    break;

  case 27: /* Statement: DowhileStmt  */
#line 188 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    (yyval.node)=(yyvsp[0].node);
}
#line 1488 "MiniCBison.cpp"
    break;

  case 28: /* Statement: Declare  */
#line 191 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
          {
    (yyval.node)=(yyvsp[0].node);
}
#line 1496 "MiniCBison.cpp"
    break;

  case 29: /* Statement: Condition ";"  */
#line 200 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    // 无动作
}
#line 1504 "MiniCBison.cpp"
    break;

  case 30: /* Statement: var "=" Condition ";"  */
#line 203 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
    (yyval.node) = new_ast_node(ast_node_type::AST_OP_ASSIGN,2,(yyvsp[-3].node),(yyvsp[-1].node));
}
#line 1512 "MiniCBison.cpp"
    break;

  case 31: /* Statement: "break" ";"  */
#line 206 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    ; // break语句
}
#line 1520 "MiniCBison.cpp"
    break;

  case 32: /* Statement: "continue" ";"  */
#line 209 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    ;  //continue语句
}
#line 1528 "MiniCBison.cpp"
    break;

  case 33: /* Statement: Array "=" Condition ";"  */
#line 212 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
    (yyvsp[-3].node)->ArrayDim.clear();
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_ASSIGN,2,(yyvsp[-3].node),(yyvsp[-1].node));
}
#line 1537 "MiniCBison.cpp"
    break;

  case 34: /* IfStmt: "if" "(" Condition ")" Statement  */
#line 222 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                          {
    // statement 可以是block,也可以是单条语句，为了方便处理，这里需要进行判断，在AST抽象语法树上统一显示block
    if((yyvsp[0].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,1,(yyvsp[0].node));
        (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,2,(yyvsp[-2].node),block);
    }
    else{
        (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,2,(yyvsp[-2].node),(yyvsp[0].node));
    }
}
#line 1553 "MiniCBison.cpp"
    break;

  case 35: /* IfStmt: "if" "(" Condition ")" Statement "else" Statement  */
#line 233 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                    {
    if((yyvsp[-2].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,1,(yyvsp[-2].node));
        (yyvsp[-2].node)=block;
    }
    if((yyvsp[0].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,1,(yyvsp[0].node));
        (yyvsp[0].node)=block;
    }
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_IFSTMT,3,(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1571 "MiniCBison.cpp"
    break;

  case 36: /* WhileStmt: "while" "(" Condition ")" Statement  */
#line 249 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                {
    if((yyvsp[0].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,1,(yyvsp[0].node));
        (yyvsp[0].node)=block;
    }
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_WHILESTMT,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1584 "MiniCBison.cpp"
    break;

  case 37: /* DowhileStmt: "do" Statement "while" "(" Condition ")" ";"  */
#line 260 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                                           {
     if((yyvsp[-5].node)->node_type!=ast_node_type::AST_OP_BLOCK){
        // statement不是  Block类型，为了统一翻译  套上一层block
        ast_node* block=new_ast_node(ast_node_type::AST_OP_BLOCK,1,(yyvsp[-5].node));
        (yyvsp[-5].node)=block;
    }
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DOWHILESTMT,2,(yyvsp[-5].node),(yyvsp[-2].node));
}
#line 1597 "MiniCBison.cpp"
    break;

  case 38: /* Condition: OrCond  */
#line 272 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    (yyval.node)=(yyvsp[0].node);
}
#line 1605 "MiniCBison.cpp"
    break;

  case 39: /* OrCond: AndCond  */
#line 277 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=(yyvsp[0].node);
}
#line 1613 "MiniCBison.cpp"
    break;

  case 40: /* OrCond: OrCond "||" AndCond  */
#line 280 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_OR,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1621 "MiniCBison.cpp"
    break;

  case 41: /* AndCond: NotCond  */
#line 285 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                  {
  (yyval.node)=(yyvsp[0].node);
}
#line 1629 "MiniCBison.cpp"
    break;

  case 42: /* AndCond: AndCond "&&" NotCond  */
#line 288 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                       {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_AND,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1637 "MiniCBison.cpp"
    break;

  case 43: /* NotCond: "!" EquCondTerm  */
#line 293 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_NOT,1,(yyvsp[0].node));
}
#line 1645 "MiniCBison.cpp"
    break;

  case 44: /* NotCond: EquCondTerm  */
#line 296 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
  (yyval.node)=(yyvsp[0].node);
}
#line 1653 "MiniCBison.cpp"
    break;

  case 45: /* EquCondTerm: LessCondTerm  */
#line 301 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                           {
   (yyval.node)=(yyvsp[0].node);
}
#line 1661 "MiniCBison.cpp"
    break;

  case 46: /* EquCondTerm: EquCondTerm "==" LessCondTerm  */
#line 304 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_EQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1669 "MiniCBison.cpp"
    break;

  case 47: /* EquCondTerm: EquCondTerm "!=" LessCondTerm  */
#line 307 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_NOTEQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1677 "MiniCBison.cpp"
    break;

  case 48: /* LessCondTerm: Expr  */
#line 313 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                    {
   (yyval.node)=(yyvsp[0].node);
}
#line 1685 "MiniCBison.cpp"
    break;

  case 49: /* LessCondTerm: LessCondTerm "<" Expr  */
#line 316 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_LESS,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1693 "MiniCBison.cpp"
    break;

  case 50: /* LessCondTerm: LessCondTerm "<=" Expr  */
#line 319 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
   (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_LESSEQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1701 "MiniCBison.cpp"
    break;

  case 51: /* LessCondTerm: LessCondTerm ">" Expr  */
#line 322 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_GREATER,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1709 "MiniCBison.cpp"
    break;

  case 52: /* LessCondTerm: LessCondTerm ">=" Expr  */
#line 325 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
  (yyval.node)=new_ast_node(ast_node_type::AST_OP_COND_GREATEREQU,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1717 "MiniCBison.cpp"
    break;

  case 53: /* LessCondTerm: "(" Condition ")"  */
#line 328 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                    {
  (yyval.node)=(yyvsp[-1].node);
}
#line 1725 "MiniCBison.cpp"
    break;

  case 54: /* Declare: "int" DeclareItems ";"  */
#line 334 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                {
    // 先指明DeclareItems下的值类型 ValueType  
    (yyvsp[-1].node)->val_type=BasicValueType::TYPE_INT32;
    (yyval.node)=(yyvsp[-1].node);
}
#line 1735 "MiniCBison.cpp"
    break;

  case 55: /* Declare: "float" DeclareItems ";"  */
#line 339 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyvsp[-1].node)->val_type=BasicValueType::TYPE_FLOAT;
    (yyval.node)=(yyvsp[-1].node);
}
#line 1744 "MiniCBison.cpp"
    break;

  case 56: /* DeclareItems: DeclareItem  */
#line 346 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    if((yyvsp[0].node)->node_type==ast_node_type::AST_LEAF_VAR_ID){
        (yyval.node)=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,1,(yyvsp[0].node));
    }else{
        // 是assign赋值形式,为了后继方便翻译这里将声明和赋值区分
        ast_node* left=new ast_node(*((yyvsp[0].node)->sons[0]));  //左边的声明变量(拷贝构造产生新的节点)
        (yyval.node)=new_ast_node(ast_node_type::AST_OP_DECL_ITEMS,2,left,(yyvsp[0].node));
    }
}
#line 1758 "MiniCBison.cpp"
    break;

  case 57: /* DeclareItems: DeclareItems "," DeclareItem  */
#line 355 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                              {
    if((yyvsp[0].node)->node_type==ast_node_type::AST_LEAF_VAR_ID){
        (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));  // DeclareItem是变量类型
    }else{
        // DeclareItem是赋值类型
        ast_node* left=new ast_node(*((yyvsp[0].node)->sons[0])); //左边的声明变量
        (yyval.node)=insert_ast_node((yyvsp[-2].node),left);  //插入left 声明变量
        (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));  //插入 后继操作:赋值节点
    }
    
}
#line 1774 "MiniCBison.cpp"
    break;

  case 58: /* DeclareItem: var  */
#line 368 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    // 无动作
    // $$=new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,$1);
    (yyval.node)=(yyvsp[0].node);
}
#line 1784 "MiniCBison.cpp"
    break;

  case 59: /* DeclareItem: var "=" Expr  */
#line 373 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    ast_node* node=new_ast_node(ast_node_type::AST_OP_ASSIGN,2,(yyvsp[-2].node),(yyvsp[0].node));
    (yyval.node)=node;
    // $$ = new_ast_node(ast_node_type::AST_OP_DECL_ITEM,1,node);
}
#line 1794 "MiniCBison.cpp"
    break;

  case 60: /* DeclareItem: Array  */
#line 378 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
       {
    (yyvsp[0].node)->node_type=ast_node_type::AST_DECL_ARRAY;
    (yyvsp[0].node)->ArrayIndexs.clear();
    (yyval.node)=(yyvsp[0].node);
}
#line 1804 "MiniCBison.cpp"
    break;

  case 61: /* Array: DIGIT_ID "[" DIGIT_INT "]"  */
#line 387 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                 {
    // 对于数组维度，在这里设计为 最右边的维度在AST树节点的顶部，最左边的维度在AST节点的底部
    (yyval.node)=new_ast_leaf_node(*(yyvsp[-3].literal),ast_node_type::AST_USE_ARRAY);
    int num=(yyvsp[-1].literal)->digit.int32_digit;
    (yyval.node)->ArrayDim.push_back(num);  //目前还不知道节点类型，所以都加入数值
    (yyval.node)->ArrayIndexs.push_back(num);
    delete (yyvsp[-1].literal);
    (yyvsp[-1].literal)=nullptr;
}
#line 1818 "MiniCBison.cpp"
    break;

  case 62: /* Array: Array "[" DIGIT_INT "]"  */
#line 396 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                         {
    int num=(yyvsp[-1].literal)->digit.int32_digit;
    (yyval.node)->ArrayDim.push_back(num);  //目前还不知道节点类型，所以都加入数值
    (yyval.node)->ArrayIndexs.push_back(num);
    delete (yyvsp[-1].literal);
    (yyvsp[-1].literal)=nullptr;
}
#line 1830 "MiniCBison.cpp"
    break;

  case 63: /* Expr: AddExpr  */
#line 406 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=(yyvsp[0].node);
}
#line 1838 "MiniCBison.cpp"
    break;

  case 64: /* AddExpr: MulExpr  */
#line 412 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    // MulExpr可以推导得到UnaryExpr  这样写保证乘除取余的优先级
    (yyval.node)=(yyvsp[0].node);
}
#line 1847 "MiniCBison.cpp"
    break;

  case 65: /* AddExpr: AddExpr "+" MulExpr  */
#line 416 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_ADD,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1855 "MiniCBison.cpp"
    break;

  case 66: /* AddExpr: AddExpr "-" MulExpr  */
#line 419 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_SUB,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1863 "MiniCBison.cpp"
    break;

  case 67: /* MulExpr: UnaryExpr  */
#line 425 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                    {
    (yyval.node)=(yyvsp[0].node);
}
#line 1871 "MiniCBison.cpp"
    break;

  case 68: /* MulExpr: MulExpr "*" UnaryExpr  */
#line 428 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_MUL,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1879 "MiniCBison.cpp"
    break;

  case 69: /* MulExpr: MulExpr "/" UnaryExpr  */
#line 431 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_DIV,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1887 "MiniCBison.cpp"
    break;

  case 70: /* MulExpr: MulExpr "%" UnaryExpr  */
#line 434 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                        {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_MOD,2,(yyvsp[-2].node),(yyvsp[0].node));
}
#line 1895 "MiniCBison.cpp"
    break;

  case 71: /* UnaryExpr: Term  */
#line 440 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=(yyvsp[0].node);
}
#line 1903 "MiniCBison.cpp"
    break;

  case 72: /* UnaryExpr: DIGIT_ID "(" FuncRealParams ")"  */
#line 443 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                                  {
    // 有参函数调用的值
    (yyval.node)=create_fun_call(*(yyvsp[-3].literal),(yyvsp[-1].node));
    delete (yyvsp[-3].literal); //释放内存
    (yyvsp[-3].literal)=nullptr;
}
#line 1914 "MiniCBison.cpp"
    break;

  case 73: /* UnaryExpr: DIGIT_ID "(" ")"  */
#line 449 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                   {
    //无参函数调用的值
    (yyval.node)=create_fun_call(*(yyvsp[-2].literal),nullptr);
    delete (yyvsp[-2].literal); //释放内存
    (yyvsp[-2].literal)=nullptr;
}
#line 1925 "MiniCBison.cpp"
    break;

  case 74: /* Term: DIGIT_INT  */
#line 459 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                 {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_LITERAL_INT,BasicValueType::TYPE_INT32);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1935 "MiniCBison.cpp"
    break;

  case 75: /* Term: DIGIT_FLOAT  */
#line 464 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
              {
    (yyval.node)=new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_LITERAL_FLOAT,BasicValueType::TYPE_FLOAT);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1945 "MiniCBison.cpp"
    break;

  case 76: /* Term: var  */
#line 469 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
      {
    (yyval.node)=(yyvsp[0].node);
}
#line 1953 "MiniCBison.cpp"
    break;

  case 77: /* Term: "(" Expr ")"  */
#line 472 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node)=(yyvsp[-1].node);
}
#line 1961 "MiniCBison.cpp"
    break;

  case 78: /* Term: Array  */
#line 475 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
        {
    (yyvsp[0].node)->ArrayDim.clear();
    (yyval.node)=(yyvsp[0].node);
}
#line 1970 "MiniCBison.cpp"
    break;

  case 79: /* var: DIGIT_ID  */
#line 482 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
               {
    (yyval.node) = new_ast_leaf_node(*(yyvsp[0].literal),ast_node_type::AST_LEAF_VAR_ID);
    delete (yyvsp[0].literal); //释放内存
    (yyvsp[0].literal)=nullptr;
}
#line 1980 "MiniCBison.cpp"
    break;

  case 80: /* FuncRealParams: Expr  */
#line 490 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                      {
    (yyval.node)=new_ast_node(ast_node_type::AST_OP_FUNC_REAL_PARAMS,1,(yyvsp[0].node));
}
#line 1988 "MiniCBison.cpp"
    break;

  case 81: /* FuncRealParams: FuncRealParams "," Expr  */
#line 493 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"
                          {
    (yyval.node)=insert_ast_node((yyvsp[-2].node),(yyvsp[0].node));
}
#line 1996 "MiniCBison.cpp"
    break;


#line 2000 "MiniCBison.cpp"

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

#line 498 "/home/mole/Program/compile_principle/MiniC/frontend/FlexBison/MiniC.y"


// 语法分析时的错误信息
void yyerror(const char * msg)
{
    printf("Line %d: %s\n", yylineno, msg);
}
