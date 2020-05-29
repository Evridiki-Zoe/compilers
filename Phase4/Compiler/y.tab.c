/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "syntax.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "lex.h"
#include "parsing.h"
#include "quads.h"
#include "targetCode.h"


#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

int yylex();

extern int yyerror(const char* s);

extern int yylineno;
extern char * yytext;
extern int scope;
extern int maxScope;
extern double QuadNo;
extern struct symbol_table_binding* true_expr_sym;
extern struct symbol_table_binding* false_expr_sym;
extern struct symbol_table_binding* nil_expr_sym;
extern struct symbol_table_binding* number_one;
extern char* Lex_string;
extern int tmpoffset;
extern struct quad *quads;
extern int scope_spaces[];
extern int flow_Break[50];
extern int flow_Continue[50];
int ref = 1;
int args = 0;
char *result;
int unnamedFuncs = 0;
int rvalues = 0;

int insideLoop = 0;
int insideFunc = 0;
int arrayFlag;
int exprflag=0;
char** table;

struct expr *tmpexpr;
struct symbol_table_binding *tmpnode;

int current_rvals = 0;


#line 119 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    FUNCTION = 262,
    RETURN = 263,
    BREAK = 264,
    CONTINUE = 265,
    AND = 266,
    NOT = 267,
    OR = 268,
    LOCAL = 269,
    TRUE = 270,
    FALSE = 271,
    NIL = 272,
    EQ = 273,
    PLUS = 274,
    MINUS = 275,
    MULT = 276,
    DIV = 277,
    MOD = 278,
    EQUAL = 279,
    NEQUAL = 280,
    PPLUS = 281,
    MMINUS = 282,
    GREATER = 283,
    LESS = 284,
    GREATER_EQUAL = 285,
    LESS_EQUAL = 286,
    SEMICOLON = 287,
    COMMA = 288,
    COLON = 289,
    DCOLON = 290,
    DOT = 291,
    DOTS = 292,
    L_CBRACKET = 293,
    R_CBRACKET = 294,
    L_SBRACKET = 295,
    R_SBRACKET = 296,
    L_PARENTHES = 297,
    R_PARENTHES = 298,
    INTEGER = 299,
    FLOAT = 300,
    STRING = 301,
    IDENTIFIER = 302,
    UMINUS = 303
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define NOT 267
#define OR 268
#define LOCAL 269
#define TRUE 270
#define FALSE 271
#define NIL 272
#define EQ 273
#define PLUS 274
#define MINUS 275
#define MULT 276
#define DIV 277
#define MOD 278
#define EQUAL 279
#define NEQUAL 280
#define PPLUS 281
#define MMINUS 282
#define GREATER 283
#define LESS 284
#define GREATER_EQUAL 285
#define LESS_EQUAL 286
#define SEMICOLON 287
#define COMMA 288
#define COLON 289
#define DCOLON 290
#define DOT 291
#define DOTS 292
#define L_CBRACKET 293
#define R_CBRACKET 294
#define L_SBRACKET 295
#define R_SBRACKET 296
#define L_PARENTHES 297
#define R_PARENTHES 298
#define INTEGER 299
#define FLOAT 300
#define STRING 301
#define IDENTIFIER 302
#define UMINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 108 "syntax.y" /* yacc.c:355  */

    double intValue;
    double floatValue;
    char *stringValue;
	struct expr* expression;
    struct call* callexpr;

#line 263 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 278 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   477

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  207

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   140,   140,   143,   144,   143,   145,   148,   164,   165,
     166,   167,   178,   188,   197,   198,   199,   203,   224,   228,
     229,   229,   265,   265,   302,   334,   337,   340,   352,   362,
     372,   382,   395,   411,   426,   441,   456,   474,   499,   499,
     519,   532,   558,   590,   619,   652,   655,   655,   692,   698,
     701,   705,   706,   709,   717,   722,   733,   739,   742,   750,
     768,   789,   797,   810,   818,   822,   827,   837,   846,   874,
     881,   900,   909,   949,   976,   993,  1001,  1020,  1029,  1039,
    1047,  1054,  1054,  1084,  1084,  1087,  1087,  1087,  1103,  1106,
    1115,  1128,  1129,  1137,  1138,  1139,  1142,  1154,  1167,  1167,
    1168,  1171,  1171,  1172,  1175,  1175,  1189,  1197,  1216,  1224,
    1227,  1227,  1227,  1251,  1251,  1251,  1266,  1267,  1271,  1290,
    1296,  1315
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE",
  "FALSE", "NIL", "EQ", "PLUS", "MINUS", "MULT", "DIV", "MOD", "EQUAL",
  "NEQUAL", "PPLUS", "MMINUS", "GREATER", "LESS", "GREATER_EQUAL",
  "LESS_EQUAL", "SEMICOLON", "COMMA", "COLON", "DCOLON", "DOT", "DOTS",
  "L_CBRACKET", "R_CBRACKET", "L_SBRACKET", "R_SBRACKET", "L_PARENTHES",
  "R_PARENTHES", "INTEGER", "FLOAT", "STRING", "IDENTIFIER", "UMINUS",
  "$accept", "program", "multi_stmts", "$@1", "$@2", "stmt", "expr", "$@3",
  "$@4", "epsilon", "arexpr", "boolResexpr", "term", "$@5", "assignmexpr",
  "$@6", "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "multi_exprs", "objectdef", "elist_for_table",
  "multi_exprs_for_table", "indexed", "multi_indexedelem", "indexedelem",
  "$@7", "block", "$@8", "funcdef", "$@9", "$@10", "funcstart", "funcname",
  "const", "number", "idlist", "$@11", "multi_id", "$@12", "ifstmt",
  "$@13", "if_start", "whilestmt", "whilestart", "whilecond", "$@14",
  "$@15", "forstmt", "$@16", "$@17", "for_elist", "for_cond", "for_end",
  "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -138

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-138)))

#define YYTABLE_NINF -47

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-47)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       9,    17,  -138,   161,  -138,   -20,  -138,   -19,  -138,     4,
      -7,    -5,   197,   -14,  -138,  -138,  -138,   197,    12,    12,
    -138,   -12,  -138,    80,    30,  -138,  -138,  -138,  -138,  -138,
     361,  -138,  -138,  -138,  -138,  -138,   116,  -138,    16,  -138,
    -138,  -138,    -4,  -138,  -138,  -138,     2,  -138,    11,  -138,
    -138,   197,  -138,  -138,   383,  -138,  -138,  -138,  -138,  -138,
      30,    -8,    16,    -8,  -138,    22,   197,   319,    14,    25,
      47,   197,    38,     1,  -138,  -138,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   197,   197,  -138,  -138,  -138,
      39,    40,   197,   197,    67,  -138,  -138,  -138,    41,   197,
     197,  -138,    51,   161,  -138,   161,   405,   197,  -138,    56,
      50,   405,   197,  -138,  -138,  -138,    63,  -138,   227,    62,
    -138,  -138,  -138,   -10,   -10,  -138,  -138,  -138,   433,   433,
     199,   199,   199,   199,  -138,    66,   252,   340,    59,   197,
    -138,   275,    68,  -138,   105,   197,  -138,   340,  -138,    62,
    -138,    76,   319,    47,  -138,   197,   197,   197,   197,  -138,
     197,  -138,  -138,   405,  -138,  -138,    65,  -138,   405,  -138,
      81,   197,  -138,  -138,    71,   446,   420,    73,   340,  -138,
      74,   161,    78,   197,   298,  -138,  -138,  -138,    86,  -138,
    -138,  -138,   405,    91,  -138,    82,  -138,    90,   197,  -138,
    -138,  -138,    88,    86,   161,  -138,  -138
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     0,     1,     0,   109,     0,    88,     0,
       0,     0,     0,     0,    94,    95,    93,     0,     0,     0,
      16,     0,    83,    75,    38,    96,    97,    92,    53,     4,
       0,    19,    18,    25,    17,    45,    48,    56,    49,    50,
      14,    15,    90,    52,    91,     8,     0,     9,     0,    10,
      11,     0,   113,   121,     0,    12,    13,    24,    54,    40,
       0,    41,     0,    43,    55,     3,     0,    77,     0,     0,
      80,     0,     0,     3,    20,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,    42,    44,
       0,     0,     0,    69,     0,    62,    64,    65,     0,     0,
      69,    89,     0,     0,   110,     0,   107,   117,   120,     0,
       0,    81,     0,    74,    72,    73,     0,    78,     0,    51,
       5,    26,    26,    27,    28,    29,    30,    31,    36,    37,
      32,    34,    33,    35,    57,     0,     0,    71,     0,     0,
      59,     0,     0,    85,   106,     0,   108,    71,   114,     0,
      84,     0,    77,    80,    39,    69,     0,     0,    69,    58,
       0,    68,    66,    47,    60,    61,   100,   104,   111,   116,
       0,     0,    76,    79,     0,    21,    23,     0,    71,    98,
       0,     0,     0,     0,     0,    63,    67,    70,   103,    86,
     105,   112,   118,     0,    82,     0,    99,     0,   117,   101,
      87,   119,     0,   103,     0,   102,   115
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,   -58,  -138,  -138,   -99,    -9,  -138,  -138,    10,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,    46,  -138,    60,
    -138,  -138,  -138,   -95,  -137,  -138,  -138,   -17,  -138,   -16,
      23,  -138,   -64,  -138,   -22,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,   -65,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,   -57,  -138,  -138,  -138
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    73,    29,    30,   121,   122,   156,
      31,    32,    33,    71,    34,    94,    35,    36,    37,    38,
      95,    96,    97,   138,   161,    39,    68,   113,    69,   117,
      70,   151,    40,    65,    41,   166,   197,    42,   102,    43,
      44,   180,   188,   196,   203,    45,   181,    46,    47,    48,
     105,   145,   182,    49,   107,   170,   148,   193,   202,    50
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,    -6,    72,    57,   144,   142,   146,   110,    59,    -6,
     169,    78,    79,    80,    67,   120,    12,     4,    13,    14,
      15,    16,    51,    52,    17,    55,    13,    56,    90,    91,
      18,    19,    92,    58,    93,    64,    53,     8,   109,    21,
      -6,   187,   106,   101,    23,   103,    24,    21,    25,    26,
      27,    28,    98,   104,    60,   114,    99,   111,   100,    28,
     174,    -6,   118,   177,    61,    63,   115,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,    62,    62,
     116,   119,   190,   136,   137,   139,   134,   135,   140,   150,
     141,   137,    12,   143,    13,    14,    15,    16,   147,   149,
      17,    66,   162,   152,   155,   206,    18,    19,   158,   167,
     171,   165,   179,   183,   185,    21,   186,   189,    66,   195,
      23,   191,    24,   198,    25,    26,    27,    28,    22,   199,
     163,   204,   157,   200,   -46,   172,   168,   173,   205,   153,
       0,   201,    88,    89,     0,     0,   137,   175,   176,   137,
       0,   178,    90,    91,     0,     0,    92,     0,    93,     0,
       0,     0,   184,     0,     5,     0,     6,     7,     8,     9,
      10,    11,     0,    12,   192,    13,    14,    15,    16,     0,
       0,    17,     0,     0,     0,     0,     0,    18,    19,   147,
       0,     0,     0,    20,     0,     0,    21,     0,     0,    22,
       0,    23,     0,    24,     0,    25,    26,    27,    28,    12,
       0,    13,    14,    15,    16,     0,     0,    17,    76,    77,
      78,    79,    80,    18,    19,     0,     0,   -47,   -47,   -47,
     -47,     0,    21,     0,     0,     0,     0,    23,    74,    24,
      75,    25,    26,    27,    28,     0,    76,    77,    78,    79,
      80,    81,    82,     0,     0,    83,    84,    85,    86,     0,
       0,     0,     0,    74,     0,    75,     0,     0,     0,     0,
     154,    76,    77,    78,    79,    80,    81,    82,     0,     0,
      83,    84,    85,    86,     0,     0,    74,     0,    75,     0,
       0,     0,     0,   159,    76,    77,    78,    79,    80,    81,
      82,     0,     0,    83,    84,    85,    86,     0,     0,    74,
       0,    75,     0,     0,     0,     0,   164,    76,    77,    78,
      79,    80,    81,    82,     0,     0,    83,    84,    85,    86,
      74,     0,    75,     0,     0,     0,     0,   194,    76,    77,
      78,    79,    80,    81,    82,     0,     0,    83,    84,    85,
      86,    74,   112,    75,     0,     0,     0,     0,     0,    76,
      77,    78,    79,    80,    81,    82,     0,     0,    83,    84,
      85,    86,    74,   160,    75,     0,     0,     0,     0,     0,
      76,    77,    78,    79,    80,    81,    82,     0,     0,    83,
      84,    85,    86,    87,    74,     0,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    83,    84,    85,    86,   108,    74,     0,    75,     0,
       0,     0,     0,     0,    76,    77,    78,    79,    80,    81,
      82,    74,     0,    83,    84,    85,    86,     0,     0,    76,
      77,    78,    79,    80,    81,    82,     0,     0,    83,    84,
      85,    86,    76,    77,    78,    79,    80,   -47,   -47,     0,
       0,    83,    84,    85,    86,    76,    77,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86
};

static const yytype_int16 yycheck[] =
{
       9,     0,    24,    12,   103,   100,   105,    65,    17,     0,
     147,    21,    22,    23,    23,    73,    12,     0,    14,    15,
      16,    17,    42,    42,    20,    32,    14,    32,    36,    37,
      26,    27,    40,    47,    42,    47,    32,     7,    60,    35,
      39,   178,    51,    47,    40,    43,    42,    35,    44,    45,
      46,    47,    36,    42,    42,    41,    40,    66,    42,    47,
     155,    39,    71,   158,    18,    19,    41,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    18,    19,
      33,    43,   181,    92,    93,    18,    47,    47,    47,    39,
      99,   100,    12,    42,    14,    15,    16,    17,   107,    43,
      20,    38,    43,   112,    42,   204,    26,    27,    42,     4,
      34,    43,    47,    32,    43,    35,    43,    43,    38,    33,
      40,    43,    42,    32,    44,    45,    46,    47,    38,    47,
     139,    43,   122,   197,    18,   152,   145,   153,   203,   116,
      -1,   198,    26,    27,    -1,    -1,   155,   156,   157,   158,
      -1,   160,    36,    37,    -1,    -1,    40,    -1,    42,    -1,
      -1,    -1,   171,    -1,     3,    -1,     5,     6,     7,     8,
       9,    10,    -1,    12,   183,    14,    15,    16,    17,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,   198,
      -1,    -1,    -1,    32,    -1,    -1,    35,    -1,    -1,    38,
      -1,    40,    -1,    42,    -1,    44,    45,    46,    47,    12,
      -1,    14,    15,    16,    17,    -1,    -1,    20,    19,    20,
      21,    22,    23,    26,    27,    -1,    -1,    28,    29,    30,
      31,    -1,    35,    -1,    -1,    -1,    -1,    40,    11,    42,
      13,    44,    45,    46,    47,    -1,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,
      43,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    -1,    -1,    11,    -1,    13,    -1,
      -1,    -1,    -1,    41,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    -1,    11,
      -1,    13,    -1,    -1,    -1,    -1,    41,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      11,    -1,    13,    -1,    -1,    -1,    -1,    39,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    11,    33,    13,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    11,    33,    13,    -1,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    32,    11,    -1,    13,    -1,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    32,    11,    -1,    13,    -1,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    11,    -1,    28,    29,    30,    31,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    51,    52,     0,     3,     5,     6,     7,     8,
       9,    10,    12,    14,    15,    16,    17,    20,    26,    27,
      32,    35,    38,    40,    42,    44,    45,    46,    47,    54,
      55,    59,    60,    61,    63,    65,    66,    67,    68,    74,
      81,    83,    86,    88,    89,    94,    96,    97,    98,   102,
     108,    42,    42,    32,    55,    32,    32,    55,    47,    55,
      42,    66,    68,    66,    47,    82,    38,    55,    75,    77,
      79,    62,    83,    53,    11,    13,    19,    20,    21,    22,
      23,    24,    25,    28,    29,    30,    31,    32,    26,    27,
      36,    37,    40,    42,    64,    69,    70,    71,    36,    40,
      42,    47,    87,    43,    42,    99,    55,   103,    32,    83,
      51,    55,    33,    76,    41,    41,    33,    78,    55,    43,
      51,    56,    57,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    47,    47,    55,    55,    72,    18,
      47,    55,    72,    42,    54,   100,    54,    55,   105,    43,
      39,    80,    55,    79,    43,    42,    58,    58,    42,    41,
      33,    73,    43,    55,    41,    43,    84,     4,    55,    73,
     104,    34,    76,    78,    72,    55,    55,    72,    55,    47,
      90,    95,   101,    32,    55,    43,    43,    73,    91,    43,
      54,    43,    55,   106,    39,    33,    92,    85,    32,    47,
      81,   105,   107,    93,    43,    92,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    52,    53,    51,    51,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    55,
      56,    55,    57,    55,    55,    55,    58,    59,    59,    59,
      59,    59,    60,    60,    60,    60,    60,    60,    62,    61,
      61,    61,    61,    61,    61,    61,    64,    63,    65,    65,
      65,    65,    65,    66,    66,    66,    66,    67,    67,    67,
      67,    68,    68,    68,    69,    69,    70,    71,    72,    72,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    78,
      78,    80,    79,    82,    81,    84,    85,    83,    86,    87,
      87,    88,    88,    88,    88,    88,    89,    89,    91,    90,
      90,    93,    92,    92,    95,    94,    94,    96,    97,    98,
     100,   101,    99,   103,   104,   102,   105,   105,   106,   107,
     108,   108
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     0,     4,     0,     2,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       0,     5,     0,     5,     2,     1,     0,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       2,     2,     2,     2,     2,     1,     0,     4,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     3,     4,     3,
       4,     4,     2,     6,     1,     1,     3,     5,     2,     0,
       3,     0,     3,     3,     2,     0,     3,     0,     2,     3,
       0,     0,     6,     0,     4,     0,     0,     8,     1,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     0,     3,
       0,     0,     4,     0,     0,     6,     3,     3,     3,     1,
       0,     0,     5,     0,     0,    11,     2,     0,     1,     1,
       3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 3:
#line 143 "syntax.y" /* yacc.c:1646  */
    {current_rvals = 0;
		}
#line 1568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 144 "syntax.y" /* yacc.c:1646  */
    {rvalues = current_rvals;}
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 144 "syntax.y" /* yacc.c:1646  */
    { printf(RED "stmt multi_stmt\n" RESET);}
#line 1580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 145 "syntax.y" /* yacc.c:1646  */
    {printf(RED "multi_stmts empty\n" RESET);}
#line 1586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 148 "syntax.y" /* yacc.c:1646  */
    { printf(RED "expression \n" RESET);
					if (exprflag) {

						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						emit(assign,true_expr,NULL,(yyvsp[-1].expression),yylineno,0);
						emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						emit(assign,false_expr,NULL,(yyvsp[-1].expression),yylineno,0);
						exprflag=0;

						patchLists(((yyvsp[-1].expression)),(int)QuadNo-2,(int)QuadNo);
					}


      }
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 164 "syntax.y" /* yacc.c:1646  */
    { printf(RED "if stmt \n" RESET); }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 165 "syntax.y" /* yacc.c:1646  */
    { printf(RED "while stmt \n" RESET); }
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 166 "syntax.y" /* yacc.c:1646  */
    { printf(RED "for stmt \n" RESET); }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 167 "syntax.y" /* yacc.c:1646  */
    {

		  printf(RED "return stmt \n" RESET);
		  if( insideFunc > 0){ push_R((int)QuadNo-1); }
		  else {
				printf("Error: RETURN STMT outside of function in line %d\n",yylineno);
				exit(EXIT_FAILURE);
			}


	  }
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 178 "syntax.y" /* yacc.c:1646  */
    {
                        printf(RED "break \n" RESET);
	                  if( insideLoop > 0) {
	                      	emit(jump,NULL,NULL,NULL,yylineno,999);
					push_B((int)QuadNo-1);
	                  } else {
	                        printf("Error: BREAK STMT outside of loop in line %d\n",yylineno);
	                        exit(EXIT_FAILURE);
	                  }
	}
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 188 "syntax.y" /* yacc.c:1646  */
    {  printf(RED "continue \n" RESET);
                              if( insideLoop > 0) {
                              	emit(jump,NULL,NULL,NULL,yylineno,999);
						push_C((int)QuadNo-1);
                              } else {
                                    printf("Error: CONTINUE STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              }
      }
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 197 "syntax.y" /* yacc.c:1646  */
    { printf(RED "block \n" RESET);}
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 198 "syntax.y" /* yacc.c:1646  */
    { printf(RED "funcdef \n" RESET);}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 199 "syntax.y" /* yacc.c:1646  */
    { printf(RED "semicolon \n" RESET);}
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 203 "syntax.y" /* yacc.c:1646  */
    {


	 result =malloc(5*sizeof(char));
	 sprintf(result,"_%d",rvalues++);
	 struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);




	 if((yyvsp[0].expression)->type == tableitem_e){
		 struct expr* tempexp = new_expr(tableitem_e,newnode,NULL,0,"",'\0',NULL);
		 emit(tablegetelem,(yyvsp[0].expression),(yyvsp[0].expression)->index,tempexp,yylineno,0);

	 }else{
		 (yyval.expression) = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL); //TODO mporei na mhn thelei arithmeticexp edw

		 emit(assign,(yyvsp[0].expression),NULL,(yyval.expression),yylineno,0);
	 }
	 printf("assignment exprsession\n" );
 }
#line 1714 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 224 "syntax.y" /* yacc.c:1646  */
    { (yyval.expression)=(yyvsp[0].expression); exprflag=1; (yyval.expression)->apotimimeno=1;
		addTruelist(((yyval.expression)),(int)QuadNo-2);
		addFalselist(((yyval.expression)),(int)QuadNo-1);
	}
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 228 "syntax.y" /* yacc.c:1646  */
    { (yyval.expression)=(yyvsp[0].expression); }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 229 "syntax.y" /* yacc.c:1646  */
    {

		 struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );


		if (!(yyvsp[-1].expression)->apotimimeno) {
			emit(if_eq,(yyvsp[-1].expression),true_expr,NULL,yylineno,999);//QuadNo +4 mallon
			emit(jump,NULL,NULL,NULL,yylineno,999); // jump assign false
			addTruelist(((yyvsp[-1].expression)),(int)QuadNo-2);
			addFalselist(((yyvsp[-1].expression)),(int)QuadNo-1);

		}


	 }
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 244 "syntax.y" /* yacc.c:1646  */
    {

		  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

		  if (!(yyvsp[0].expression)->apotimimeno) {
			 emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
 			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false

			 addTruelist(((yyvsp[0].expression)),(int)QuadNo-2);
	 		 addFalselist(((yyvsp[0].expression)),(int)QuadNo-1);
		  }
		  (yyval.expression) = smallFunc(boolexp_e);
		   backpatchList((yyvsp[-4].expression)->truelist,(yyvsp[-1].intValue)+1);
		 andLists((yyval.expression),(yyvsp[-4].expression),(yyvsp[0].expression));
		 (yyval.expression)->apotimimeno=1;



			exprflag=1;
	}
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 265 "syntax.y" /* yacc.c:1646  */
    {

			struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		 	struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			if (!(yyvsp[-1].expression)->apotimimeno) {

				emit(if_eq,(yyvsp[-1].expression),true_expr,NULL,yylineno,999);//epomeno expr an true
				emit(jump,NULL,NULL,NULL,yylineno,999); // jump assign false
				addTruelist(((yyvsp[-1].expression)),(int)QuadNo-2);
				addFalselist(((yyvsp[-1].expression)),(int)QuadNo-1);

			}


			}
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 280 "syntax.y" /* yacc.c:1646  */
    {



		  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

		  if (!(yyvsp[0].expression)->apotimimeno) {
				 emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
	 			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false
				 addTruelist(((yyvsp[0].expression)),(int)QuadNo-2);
	 			 addFalselist(((yyvsp[0].expression)),(int)QuadNo-1);
		  }

			    (yyval.expression) = smallFunc(boolexp_e);
				(yyval.expression)->apotimimeno=1;
				backpatchList((yyvsp[-4].expression)->falselist,(yyvsp[-1].intValue)+1);
				orLists((yyval.expression),(yyvsp[-4].expression),(yyvsp[0].expression));


	 exprflag=1;
	}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 302 "syntax.y" /* yacc.c:1646  */
    {
			printf(RED "NOT expression\n" RESET);

			struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			if (!(yyvsp[0].expression)->apotimimeno) {
  			  emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
   			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false
			 addTruelist(((yyvsp[0].expression)),(int)QuadNo-2);
			 addFalselist(((yyvsp[0].expression)),(int)QuadNo-1);
       		exprflag = 1;
  		  }

		   (yyval.expression) = smallFunc(boolexp_e);
		   notLists((yyvsp[0].expression),(yyval.expression));

		  (yyval.expression)->apotimimeno=1;
		if (exprflag) {

			emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
			emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
			emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);
			exprflag=0;
			patchLists(((yyval.expression)),(int)QuadNo-2,(int)QuadNo);

		}else exprflag = 1;

//			patchLists(($$),(int)QuadNo-2,(int)QuadNo);


}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 334 "syntax.y" /* yacc.c:1646  */
    { (yyval.expression)=(yyvsp[0].expression); printf(RED"term (%s)\n"RESET, (yyvsp[0].expression)->sym->value.var->name); }
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 337 "syntax.y" /* yacc.c:1646  */
    {(yyval.intValue)=QuadNo;}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 340 "syntax.y" /* yacc.c:1646  */
    {
				/*compile time type check*/
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(arithmeticexp_e);
                  emit(add, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
            }
            else{
              printf("Compile time error: cannot ADD 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
              exit(EXIT_FAILURE);
            }

      }
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 352 "syntax.y" /* yacc.c:1646  */
    {
		    if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
		          (yyval.expression) = smallFunc(arithmeticexp_e);
		          emit(sub, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
		    }
		    else{
		          printf("Compile time error: cannot sub 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 362 "syntax.y" /* yacc.c:1646  */
    {
		    if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
		          (yyval.expression) = smallFunc(arithmeticexp_e);
		          emit(mul, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
		    }
		    else{
		          printf("Compile time error: cannot multiple 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 372 "syntax.y" /* yacc.c:1646  */
    {
		    if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
		          (yyval.expression) = smallFunc(arithmeticexp_e);
		          emit(Div, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
		    }
		    else {
		          printf("Compile time error: cannot div 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 382 "syntax.y" /* yacc.c:1646  */
    {
		    if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
		          (yyval.expression) = smallFunc(arithmeticexp_e);
		          emit(mod, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
		    }
		    else {
		      printf("Compile time error: cannot mod 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
		      exit(EXIT_FAILURE);
		    }
		}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 395 "syntax.y" /* yacc.c:1646  */
    {

	  if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
			(yyval.expression) = smallFunc(boolexp_e);
	  } else {
			printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
			exit(EXIT_FAILURE);
	  }

	  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
	  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

	  emit(if_greater,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,999);
	  emit(jump,NULL,NULL,NULL,yylineno,999);

	}
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 411 "syntax.y" /* yacc.c:1646  */
    {
			  if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
					(yyval.expression) = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_greatereq,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 426 "syntax.y" /* yacc.c:1646  */
    {
			  if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
					(yyval.expression) = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_less,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 441 "syntax.y" /* yacc.c:1646  */
    {
			  if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
					(yyval.expression) = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_lesseq,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
#line 2031 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 456 "syntax.y" /* yacc.c:1646  */
    {

			  //compile time type check
			  if( ((yyvsp[-2].expression))->type == 1 && ((yyvsp[0].expression))->type == 11 ){ //table and nil ok
			  }
			  else if(oneIsVar((yyvsp[-2].expression), (yyvsp[0].expression))) {
					//ok
			  }

			  (yyval.expression) = smallFunc(boolexp_e);

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_eq,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 474 "syntax.y" /* yacc.c:1646  */
    {
			  if( ((yyvsp[-2].expression))->type ==1 && ((yyvsp[0].expression))->type ==11 ){
					//table and nil ok
			  }
			  else if(oneIsVar((yyvsp[-2].expression), (yyvsp[0].expression))) {
					//ok
			  }


			  (yyval.expression) = smallFunc(boolexp_e);

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_not_eq,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,999);//THELEI SWSTO LABEL
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 499 "syntax.y" /* yacc.c:1646  */
    {
	push_E(exprflag); exprflag=0;
}
#line 2085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 501 "syntax.y" /* yacc.c:1646  */
    { printf(RED " (expression) \n" RESET);

          (yyval.expression) = (yyvsp[-1].expression);
		  if (exprflag == 1) {
			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

  			emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
  			emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
  			emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);
			exprflag=0;
  			patchLists(((yyval.expression)),(int)QuadNo-2,(int)QuadNo);
  		}


		 exprflag=pop_E();

      }
#line 2108 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 519 "syntax.y" /* yacc.c:1646  */
    {

            printf(RED " - expression \n" RESET);
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            tmpnode = malloc(sizeof(struct symbol_table_binding));
            tmpnode =insertVar(result,yylineno,scope);
            tmpexpr=malloc(sizeof(struct expr));
            tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
            emit(uminus,(yyvsp[0].expression),NULL,tmpexpr,yylineno,0);
            (yyval.expression) = tmpexpr;
   	}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 532 "syntax.y" /* yacc.c:1646  */
    {
	      printf(RED "++lvalue\n" RESET);
            check_for_funcname((yyvsp[0].expression)->sym->value.var->name);

            if((yyvsp[0].expression)->type == 1){
			  	(yyval.expression)= member_item((yyvsp[0].expression), (yyvsp[0].expression)->sym->value.var->name);
			  	//new expr for number 1
			  	struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

				emit(add,(yyval.expression),tmp_one,(yyval.expression),yylineno,0);
        		emit(table_setelem,(yyvsp[0].expression)->index,(yyval.expression),(yyvsp[0].expression),yylineno,0);
        } else{
                  result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
    			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
    			   	tmpnode =insertVar(result,yylineno,scope);
    			   	tmpexpr=malloc(sizeof(struct expr));
    			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
      				//new expr for number 1
              struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(add,(yyvsp[0].expression),tmp_one,(yyvsp[0].expression),yylineno,0);
      			emit(assign,(yyvsp[0].expression),NULL,tmpexpr,yylineno,0);
              (yyval.expression) = tmpexpr;
              }
	}
#line 2156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 558 "syntax.y" /* yacc.c:1646  */
    {
	      check_for_funcname((yyvsp[-1].expression)->sym->value.var->name);
            result =malloc(5*sizeof(char));
  			sprintf(result,"_%d",rvalues++);

          		  if((yyvsp[-1].expression)->type == 1){
                   struct expr* temp_expr;
          			   temp_expr= member_item((yyvsp[-1].expression), (yyvsp[-1].expression)->sym->value.var->name);

          			   tmpnode =insertVar(result,yylineno,scope);
             			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
             			 //new expr for number 1
                   struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

             			 emit(assign,temp_expr,NULL,tmpexpr,yylineno,0);
          				 emit(add,temp_expr,tmp_one,temp_expr,yylineno,0);
          				 emit(table_setelem,(yyvsp[-1].expression)->index,temp_expr,(yyvsp[-1].expression),yylineno,0);

                   (yyval.expression) = tmpexpr;
          		  } else {
          			  tmpnode =insertVar(result,yylineno,scope);
          			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
          			   //new expr for number 1
          			 struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

          			emit(assign,(yyvsp[-1].expression),NULL,tmpexpr,yylineno,0);
          			emit(add,(yyvsp[-1].expression),tmp_one,(yyvsp[-1].expression),yylineno,0);
          	   			(yyval.expression) = tmpexpr;
          		  }


	}
#line 2193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 590 "syntax.y" /* yacc.c:1646  */
    {
          check_for_funcname((yyvsp[0].expression)->sym->value.var->name);
  				printf(RED "--lvalue\n" RESET);

				if((yyvsp[0].expression)->type == 1){
	  			  (yyval.expression)= member_item((yyvsp[0].expression), (yyvsp[0].expression)->sym->value.var->name);
	  			  //new expr for number 1
	  			  struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

	  			  emit(sub,(yyval.expression),tmp_one,(yyval.expression),yylineno,0);
	  			  emit(table_setelem,(yyvsp[0].expression)->index,(yyval.expression),(yyvsp[0].expression),yylineno,0);
	  	  } else{
      				result =malloc(5*sizeof(char));
      			  sprintf(result,"_%d",rvalues++);

    			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
    			   	tmpnode =insertVar(result,yylineno,scope);
    			   	tmpexpr=malloc(sizeof(struct expr));
    			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
    				  //new expr for number 1
              struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(sub,(yyvsp[0].expression),tmp_one,(yyvsp[0].expression),yylineno,0);
    			emit(assign,(yyvsp[0].expression),NULL,tmpexpr,yylineno,0);

              (yyval.expression) = tmpexpr;
          }

  	}
#line 2227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 619 "syntax.y" /* yacc.c:1646  */
    {
            check_for_funcname((yyvsp[-1].expression)->sym->value.var->name);
            printf(RED "lvalue--\n" RESET);

            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);

      		  if((yyvsp[-1].expression)->type == 1){
               struct expr* temp_expr;
      			   temp_expr= member_item((yyvsp[-1].expression), (yyvsp[-1].expression)->sym->value.var->name);

      			   tmpnode =insertVar(result,yylineno,scope);
         			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
         			 //new expr for number 1
               struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

         			 emit(assign,temp_expr,NULL,tmpexpr,yylineno,0);
      				 emit(sub,temp_expr,tmp_one,temp_expr,yylineno,0);
      				 emit(table_setelem,(yyvsp[-1].expression)->index,temp_expr,(yyvsp[-1].expression),yylineno,0);

               (yyval.expression) = tmpexpr;
      		  }else{
      			  tmpnode =insertVar(result,yylineno,scope);
      			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
      			   //new expr for number 1
      			 struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(assign,(yyvsp[-1].expression),NULL,tmpexpr,yylineno,0);
      			emit(sub,(yyvsp[-1].expression),tmp_one,(yyvsp[-1].expression),yylineno,0);
      	   			(yyval.expression) = tmpexpr;
      		  }

			}
#line 2265 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 652 "syntax.y" /* yacc.c:1646  */
    { printf(RED "primary\n" RESET); (yyval.expression)=(yyvsp[0].expression);  }
#line 2271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 655 "syntax.y" /* yacc.c:1646  */
    { if(!arrayFlag && ref)   check_for_funcname((yyvsp[0].expression)->sym->value.var->name); push_E(exprflag); exprflag=0; }
#line 2277 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 655 "syntax.y" /* yacc.c:1646  */
    {
							     arrayFlag = 0;
                   				 ref = 1;

								 if (exprflag) {
					 				struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					 				struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					 				emit(assign,true_expr,NULL,(yyvsp[0].expression),yylineno,0);
					 				emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					 				emit(assign,false_expr,NULL,(yyvsp[0].expression),yylineno,0);
									exprflag=0;

									patchLists(((yyvsp[0].expression)),(int)QuadNo-2,(int)QuadNo);

					 			}

                   if((yyvsp[-3].expression)->type == tableitem_e){

                        emit(table_setelem,(yyvsp[-3].expression)->index,(yyvsp[0].expression),(yyvsp[-3].expression),yylineno,0);

                        struct symbol_table_binding *tmp_index = malloc(sizeof(struct symbol_table_binding));
                        tmp_index->value.var = malloc(sizeof(struct variable));
                        tmp_index->value.var->name = malloc((strlen((yyvsp[-3].expression)->index->sym->value.var->name) + 1) * sizeof(char));
                        strcpy(tmp_index->value.var->name, (yyvsp[-3].expression)->index->sym->value.var->name);
                        tmp_index->next = NULL;

                        struct expr*  returned_exp = new_expr(tableitem_e,tmp_index,(yyvsp[-3].expression),0,"",'\0',NULL);
                        (yyval.expression) = (yyvsp[-3].expression);
                   }else{
							            emit(assign,(yyvsp[0].expression),NULL,(yyvsp[-3].expression),yylineno,0);
										printf("assign kanoniko\n" );
                   }
				   exprflag=pop_E();
						  }
#line 2317 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 692 "syntax.y" /* yacc.c:1646  */
    { printf(RED "primary:: lvalue \n" RESET); (yyval.expression)=(yyvsp[0].expression);
            if((yyvsp[0].expression)->type == 1 ){
                  (yyvsp[0].expression) = member_item((yyvsp[0].expression), (yyvsp[0].expression)->sym->value.var->name);
            }
            (yyval.expression)=(yyvsp[0].expression);
         }
#line 2328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 698 "syntax.y" /* yacc.c:1646  */
    {printf(RED "primary:: call %s \n" RESET,(yyvsp[0].expression)->sym->value.var->name);

         }
#line 2336 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 701 "syntax.y" /* yacc.c:1646  */
    { printf(RED "primary:: objectdef\n" RESET);

                (yyval.expression) = (yyvsp[0].expression);
         }
#line 2345 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 705 "syntax.y" /* yacc.c:1646  */
    { printf(RED "primary:: (funcdef)\n" RESET); (yyval.expression) = (yyvsp[-1].expression); exprflag=pop_E(); }
#line 2351 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 706 "syntax.y" /* yacc.c:1646  */
    { printf(RED "primary:: const\n" RESET);  (yyval.expression)=(yyvsp[0].expression); }
#line 2357 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 709 "syntax.y" /* yacc.c:1646  */
    {
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode= insertVar( yylval.stringValue, yylineno, scope);
            if(tmpnode->symbol_type == 3) (yyval.expression)=new_expr(2,tmpnode,NULL,0,"",'\0',NULL);
						else if(tmpnode->symbol_type == 4) (yyval.expression)=new_expr(3,tmpnode,NULL,0,"",'\0',NULL);
            else (yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);

            }
#line 2370 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 717 "syntax.y" /* yacc.c:1646  */
    {
						printf(RED "lvalue:: local identifier\n" RESET);
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode = localVar( yylval.stringValue, yylineno, scope);
						(yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);}
#line 2380 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 722 "syntax.y" /* yacc.c:1646  */
    {
            tmpnode=malloc(sizeof(struct symbol_table_binding));
            if((tmpnode=global_exists((yyvsp[0].stringValue))) == NULL) {
                  printf("\"%s\" undeclared, (first use here), line: %d\n", (yyvsp[0].stringValue), yylineno);
                  exit(EXIT_FAILURE);
            }
			if (tmpnode->symbol_type==user) (yyval.expression)=new_expr(programfunc_e,tmpnode,NULL,0,"",'\0',NULL);
			else if (tmpnode->symbol_type==library) (yyval.expression)=new_expr(libfunc_e,tmpnode,NULL,0,"",'\0',NULL);
		    else   (yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);

            printf( RED "lvalue:: doublecolon\n" RESET);}
#line 2396 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 733 "syntax.y" /* yacc.c:1646  */
    { printf(RED "lvalue:: member %s type %d\n" RESET, (yyvsp[0].expression)->sym->value.var->name, (yyvsp[0].expression)->type);
            (yyval.expression) = (yyvsp[0].expression);

         }
#line 2405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 739 "syntax.y" /* yacc.c:1646  */
    {
            (yyval.expression) = member_item((yyvsp[-2].expression), (yyvsp[0].stringValue));
         }
#line 2413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 742 "syntax.y" /* yacc.c:1646  */
    {
                arrayFlag = 1;
                printf(RED"member:: lvalue[expression]\n"RESET);

				(yyvsp[-3].expression) = emit_iftable_item((yyvsp[-3].expression));
				(yyval.expression) = new_expr(tableitem_e,(yyvsp[-3].expression)->sym,(yyvsp[-1].expression),0,"",'\0',NULL);

         }
#line 2426 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 750 "syntax.y" /* yacc.c:1646  */
    {

              struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
              tmp_symbol_id->value.var = malloc(sizeof(struct variable));
              tmp_symbol_id->value.var->name = malloc((strlen((yyvsp[0].stringValue)) + 1) * sizeof(char));
              strcpy(tmp_symbol_id->value.var->name, (yyvsp[0].stringValue));
              tmp_symbol_id->next = NULL;
              //adespoto symbol pou den prepei na mpei sto hash!

              struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);

              (yyvsp[-2].expression)->index = tmpexpr_id;

              struct expr* tmp_exression = member_item((yyvsp[-2].expression), (yyvsp[0].stringValue)); //prepei to $1 na einai table item
              (yyval.expression) = tmp_exression;


         }
#line 2449 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 768 "syntax.y" /* yacc.c:1646  */
    { \
            arrayFlag = 1;

            printf(RED "member:: call[expression]\n" RESET);
            struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
            tmp_symbol_id->value.var = malloc(sizeof(struct variable));
            tmp_symbol_id->value.var->name = malloc((strlen((yyvsp[-1].expression)->sym->value.var->name) + 1) * sizeof(char));
            strcpy(tmp_symbol_id->value.var->name, (yyvsp[-1].expression)->sym->value.var->name);
            tmp_symbol_id->next = NULL;
            //adespoto symbol pou den prepei na mpei sto hash!

            struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);

            (yyvsp[-3].expression)->index = tmpexpr_id;

            struct expr* tmp_exression = member_item((yyvsp[-3].expression), (yyvsp[-1].expression)->sym->value.var->name); //prepei to $1 na einai table item
            (yyval.expression) = tmp_exression;

         }
#line 2473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 789 "syntax.y" /* yacc.c:1646  */
    {

				printf(RED "call:: call (elist)\n" RESET);

        //printf("1) make call type %d\n", $3->type);
        (yyval.expression) = make_call((yyvsp[-3].expression), (yyvsp[-1].expression));

 			}
#line 2486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 797 "syntax.y" /* yacc.c:1646  */
    {

          (yyvsp[-1].expression) = emit_iftable_item((yyvsp[-1].expression));
          if ((yyvsp[0].callexpr)->method ){
                struct expr* t = (yyvsp[-1].expression);
                t->next = (yyvsp[0].callexpr)->elist;
                (yyvsp[-1].expression) = emit_iftable_item(member_item(t, (yyvsp[0].callexpr)->name));
                (yyvsp[0].callexpr)->elist = t ;

          }
       //   printf("2) make call type %d\n", $2->elist->type);
          (yyval.expression) = make_call((yyvsp[-1].expression), (yyvsp[0].callexpr)->elist);
				}
#line 2504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 810 "syntax.y" /* yacc.c:1646  */
    {
		   			printf(RED "call:: (funcdef)(elist)\n" RESET);
//            printf("3) make call type %d\n", $3->type);
          (yyval.expression) = make_call((yyvsp[-4].expression), (yyvsp[-1].expression));

  			}
#line 2515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 818 "syntax.y" /* yacc.c:1646  */
    { printf(RED"callsuffix:: (elist)\n"RESET);

                (yyval.callexpr) = (yyvsp[0].callexpr);
           }
#line 2524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 822 "syntax.y" /* yacc.c:1646  */
    { printf(RED "callsuffix:: ..id(elist)\n" RESET);
                (yyval.callexpr) = (yyvsp[0].callexpr);
           }
#line 2532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 827 "syntax.y" /* yacc.c:1646  */
    {
              (yyval.callexpr) = malloc(sizeof(struct call));
              (yyval.callexpr)->elist = (yyvsp[-1].expression);
//              $$->elist->type = $2->type;
              (yyval.callexpr)->method = 0;
              (yyval.callexpr)->name = NULL;

         }
#line 2545 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 837 "syntax.y" /* yacc.c:1646  */
    { printf(RED "methodcall\n" RESET);
                (yyval.callexpr) = malloc(sizeof(struct call));
                (yyval.callexpr)->elist = (yyvsp[-1].expression);
//              $$->elist->type = $2->type;
                (yyval.callexpr)->method = 1;
                (yyval.callexpr)->name = (yyvsp[-3].stringValue);
           }
#line 2557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 846 "syntax.y" /* yacc.c:1646  */
    {
	 				args++;

          struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
          newnode->value.var = malloc(sizeof(struct variable));
          newnode->value.var->name = malloc((strlen((yyvsp[-1].expression)->sym->value.var->name) + 1) * sizeof(char));
          strcpy(newnode->value.var->name, (yyvsp[-1].expression)->sym->value.var->name);
          newnode->value.var->line = yylineno;
          newnode->symbol_type = 1;
          newnode->value.var->scope = scope;
          newnode->next = NULL;

          struct expr* temp_elem = new_expr(var_e,newnode,NULL,0,"",'\0',(yyvsp[0].expression));


          (yyval.expression) = (yyvsp[-1].expression);
          (yyval.expression)->next = (yyvsp[0].expression); ///edw
		  if (exprflag) {
			 struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			 emit(assign,true_expr,NULL,(yyvsp[-1].expression),yylineno,0);
			 emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
			 emit(assign,false_expr,NULL,(yyvsp[-1].expression),yylineno,0);
			 exprflag=0;
			patchLists(((yyvsp[-1].expression)),(int)QuadNo-2,(int)QuadNo);
		 }
	}
#line 2590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 874 "syntax.y" /* yacc.c:1646  */
    { printf(RED "elist:: empty\n" RESET);
                args = 0;
                struct expr* temp_elem = new_expr(var_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                (yyval.expression) = temp_elem;
      }
#line 2600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 881 "syntax.y" /* yacc.c:1646  */
    {
					args++;

          struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
          newnode->value.var = malloc(sizeof(struct variable));
          newnode->value.var->name = malloc((strlen((yyvsp[-1].expression)->sym->value.var->name) + 1) * sizeof(char));
          strcpy(newnode->value.var->name, (yyvsp[-1].expression)->sym->value.var->name);
          newnode->value.var->line = yylineno;
          newnode->symbol_type = 1;
          newnode->value.var->scope = scope;
          newnode->next = NULL;

          struct expr* temp_elem = new_expr(var_e,newnode,NULL,0,"",'\0',(yyvsp[0].expression));
          // bazw sto next to epomeno stoixeio


          (yyval.expression) = (yyvsp[-1].expression);
          (yyval.expression)->next = (yyvsp[0].expression); ///edw
	}
#line 2624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 900 "syntax.y" /* yacc.c:1646  */
    { printf(RED "multi exprsessions: empty\n" RESET);
                  args = 0; //mallon eixe ksexastei ayto
                  struct expr* temp_elem = new_expr(var_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                  (yyval.expression) = NULL;
      }
#line 2634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 909 "syntax.y" /* yacc.c:1646  */
    {
                  printf(RED "objectdef:: elist\n" RESET);

                  result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
                  struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                  struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
                  emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);

                  struct expr* tmp = (yyvsp[-1].expression);
                  double i = 0;

                  while(tmp!= NULL) {
                    if(tmp->sym ){
                        printf("table %f %s", i, tmp->sym->value.var->name);
                        char* name =malloc(5*sizeof(char));
                        sprintf(name,"%f",(double)i);
                        //to index:: ena symbol (oxi sto hash), me onoma to index tou stoixeiou
                      	struct symbol_table_binding *tmp_index = malloc(sizeof(struct symbol_table_binding));
                        tmp_index->value.var = malloc(sizeof(struct variable));
                    	tmp_index->value.var->name = malloc((strlen(name) + 1) * sizeof(char));
                        strcpy(tmp_index->value.var->name, name);
	                     tmp_index->next = NULL;
                        //adespoto symbol pou den prepei na mpei sto hash!

                        struct expr* tmp_expr_index = new_expr(conststring_e,tmp_index,NULL,0,name,'\0',NULL);

                        struct symbol_table_binding* tmp_symbol=  insertVar(result ,  yylineno , scope);


                        struct expr* temp_elem = new_expr(var_e,tmp_symbol,NULL,0,"",'\0',NULL);

                        emit(table_setelem,tmp_expr_index ,tmp , temp_elem,yylineno,0);
                      }
                        tmp = tmp->next;
                        i++;
                  }
                  rvalues++;
                  (yyval.expression) = tmp_table;// epistrefw pros ta panw olo to table
            }
#line 2679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 949 "syntax.y" /* yacc.c:1646  */
    {

                   printf(RED "objectdef:: indexed\n" RESET);
				   result =malloc(5*sizeof(char));
				   sprintf(result,"_%d",rvalues);
				   struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
				   struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
				   emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);


                   struct expr* tmp = (yyvsp[-1].expression);

                    (yyval.expression) = tmp_table;// epistrefw pros ta panw olo to table

                    int i = 0;
                    while(tmp!= NULL) {
                          printf("indexed table %d kai index(%s) val(%s)", i, tmp->index->sym->value.var->name, tmp->sym->value.var->name);
						  emit(table_setelem,tmp->index,tmp,tmp_table,yylineno,0);
                          tmp = tmp->next;
                          i++;
                    }
            }
#line 2706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 976 "syntax.y" /* yacc.c:1646  */
    {
                args++;
                // //adespoto symbol pou den prepei na mpei sto hash!
                // struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
                // newnode->value.var = malloc(sizeof(struct variable));
                // newnode->value.var->name = malloc((strlen($1->sym->value.var->name) + 1) * sizeof(char));
                // strcpy(newnode->value.var->name, $1->sym->value.var->name);
                // newnode->value.var->line = yylineno;
                // newnode->symbol_type = 1;
                // newnode->value.var->scope = scope;
                // newnode->next = NULL;
				//
                // struct expr* temp_elem = new_expr(tableitem_e,newnode,NULL,0,"",'\0',$2);
                (yyvsp[-1].expression)->next= (yyvsp[0].expression);
//new_expr(tableitem_e,$1->sym,$1->index,0,"",'\0',$2);
                (yyval.expression) = (yyvsp[-1].expression);
        }
#line 2728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 993 "syntax.y" /* yacc.c:1646  */
    {
          struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
          (yyval.expression) = temp_elem;
          printf(RED "elist:: empty\n" RESET);
          args = 0;
        }
#line 2739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1001 "syntax.y" /* yacc.c:1646  */
    {
                             args++;

                             // //adespoto symbol pou den prepei na mpei sto hash!
                             // struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
                             // newnode->value.var = malloc(sizeof(struct variable));
                             // newnode->value.var->name = malloc((strlen($2->sym->value.var->name) + 1) * sizeof(char));
                             // strcpy(newnode->value.var->name, $2->sym->value.var->name);
                             // newnode->value.var->line = yylineno;
                             // newnode->symbol_type = 1;
                             // newnode->value.var->scope = scope;
                             // newnode->next = NULL;
							 //
                             // struct expr* temp_elem = new_expr(tableitem_e,newnode,NULL,0,"",'\0',$3);
                             // // bazw sto next to epomeno stoixeio
                             (yyvsp[-1].expression)->next = (yyvsp[0].expression);
                             (yyval.expression) = (yyvsp[-1].expression); //pernaw to neo expression me to next, sto $$

                        }
#line 2763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1020 "syntax.y" /* yacc.c:1646  */
    {
                              struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                              (yyval.expression) = NULL;//temp_elem;
                      }
#line 2772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1029 "syntax.y" /* yacc.c:1646  */
    {

                printf(RED "indexed:: indexedelement multi\n" RESET);
                struct expr* expr_with_next = new_expr(tableitem_e,(yyvsp[-1].expression)->sym,(yyvsp[-1].expression)->index,0,"",'\0',(yyvsp[0].expression));
                (yyvsp[-1].expression)->next=(yyvsp[0].expression);// = expr_with_next;
				(yyval.expression)=(yyvsp[-1].expression);

                }
#line 2785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1039 "syntax.y" /* yacc.c:1646  */
    {
                         printf(RED "multi_indexedelem:: comma indelem multi\n" RESET);
						//
                        // struct expr* expr_with_next = new_expr(tableitem_e,$2->sym,$2->index,0,"",'\0',$3);
                        // $$ = expr_with_next;
						(yyvsp[-1].expression)->next=(yyvsp[0].expression);
						(yyval.expression)=(yyvsp[-1].expression);
                        }
#line 2798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1047 "syntax.y" /* yacc.c:1646  */
    {
                        printf(RED "multi_indexedelem:: empty\n" RESET);
                    //    struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                        (yyval.expression) = NULL;
                  }
#line 2808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1054 "syntax.y" /* yacc.c:1646  */
    {
	if (exprflag) {
	   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
	   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

	   emit(assign,true_expr,NULL,(yyvsp[0].expression),yylineno,0);
	   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
	   emit(assign,false_expr,NULL,(yyvsp[0].expression),yylineno,0);
	   exprflag=0;
	  patchLists(((yyvsp[0].expression)),(int)QuadNo-2,(int)QuadNo);
   }
}
#line 2825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1066 "syntax.y" /* yacc.c:1646  */
    {
					if (exprflag) {
					   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					   emit(assign,true_expr,NULL,(yyvsp[-1].expression),yylineno,0);
					   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					   emit(assign,false_expr,NULL,(yyvsp[-1].expression),yylineno,0);
					   exprflag=0;
					  patchLists(((yyvsp[-1].expression)),(int)QuadNo-2,(int)QuadNo);
				   }

				   (yyvsp[-1].expression)->index=(yyvsp[-4].expression);
				   (yyval.expression)=(yyvsp[-1].expression);

              }
#line 2846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1084 "syntax.y" /* yacc.c:1646  */
    { scope++; if(scope > maxScope) maxScope = scope; }
#line 2852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1084 "syntax.y" /* yacc.c:1646  */
    {hide_symbols(scope); scope--;  printf( RED "block:: {stmt multi stmt}\n" RESET ); }
#line 2858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1087 "syntax.y" /* yacc.c:1646  */
    {push_SP(tmpoffset); tmpoffset=0; insideFunc++;}
#line 2864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1087 "syntax.y" /* yacc.c:1646  */
    {  (yyvsp[-4].expression)->sym->value.func->totalArgs=tmpoffset; tmpoffset=0; make_not_accessible(scope+1);  push_E(exprflag); exprflag=0; }
#line 2870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1087 "syntax.y" /* yacc.c:1646  */
    {
			  make_accessible_again(scope+1);
			  insideFunc--;
			  emit(funcend,(yyvsp[-6].expression),NULL,NULL,yylineno,0);
			  (yyvsp[-6].expression)->sym->value.func->totalVars=tmpoffset;
			  (yyvsp[-6].expression)->sym->value.func->funcAddress=(yyvsp[-7].intValue)+2;//+1 gia indexing apo to 0 +1 giati to $1 einai to jump

			  (yyval.expression)=(yyvsp[-6].expression);
			  quads[(int)(yyvsp[-7].intValue)].label=QuadNo+1;
			  tmpoffset=pop_SP();

			  patchReturn((int)(yyvsp[-7].intValue),(int)QuadNo);
			  exprflag=pop_E();
		   	}
#line 2889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1103 "syntax.y" /* yacc.c:1646  */
    { emit(jump,NULL,NULL,NULL,yylineno,999); (yyval.intValue)=QuadNo-1; }
#line 2895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1106 "syntax.y" /* yacc.c:1646  */
    {
					tmpnode=malloc(sizeof(struct symbol_table_binding));
					tmpnode= newFunction( (yyvsp[0].stringValue), yylineno, scope);
					tmpexpr=malloc(sizeof(struct expr));
					tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);

					emit(funcstart,tmpexpr,NULL,NULL,yylineno,0);
					(yyval.expression)=tmpexpr;
			}
#line 2909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1115 "syntax.y" /* yacc.c:1646  */
    {
					 result = malloc(2 * sizeof(char)); sprintf(result, "^%d", unnamedFuncs++);
					 tmpnode=malloc(sizeof(struct symbol_table_binding));
					 tmpnode=newFunction(result, yylineno, scope);
					 tmpexpr=malloc(sizeof(struct expr));
					 tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);


					 emit(funcstart,tmpexpr,NULL,NULL,yylineno,0);
					 free(result);
					 (yyval.expression)=tmpexpr;
		 }
#line 2926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1128 "syntax.y" /* yacc.c:1646  */
    {		(yyval.expression)=(yyvsp[0].expression); 	}
#line 2932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1129 "syntax.y" /* yacc.c:1646  */
    {
				tmpnode=malloc(sizeof(struct symbol_table_binding));
				tmpnode->value.var = malloc(sizeof(struct variable));
				tmpnode->value.var->name = malloc((strlen(Lex_string) + 1) * sizeof(char));
				strcpy(tmpnode->value.var->name, Lex_string);
				(yyval.expression) = (struct expr *)malloc(sizeof(struct expr));
				(yyval.expression) = new_expr(conststring_e,tmpnode,NULL,0,Lex_string,'\0',NULL);
			}
#line 2945 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1137 "syntax.y" /* yacc.c:1646  */
    { (yyval.expression) = new_expr(nil_e,nil_expr_sym,NULL,0,"",'\0',NULL); }
#line 2951 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1138 "syntax.y" /* yacc.c:1646  */
    { (yyval.expression) = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );  }
#line 2957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1139 "syntax.y" /* yacc.c:1646  */
    { (yyval.expression) = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL ); }
#line 2963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1142 "syntax.y" /* yacc.c:1646  */
    {
     					result = malloc(50 * sizeof(char)); sprintf(result,"%f", ((yyvsp[0].intValue)));

    					struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
    					newnode->value.var = malloc(sizeof(struct variable));
    					newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
    					strcpy(newnode->value.var->name, result);
    					(yyval.expression) = (struct expr *)malloc(sizeof(struct expr));

    					(yyval.expression) = new_expr(const_num_e,newnode,NULL,((yyvsp[0].intValue)),"",'\0',NULL);

					}
#line 2980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1154 "syntax.y" /* yacc.c:1646  */
    {
			            result = malloc(50 * sizeof(char)); sprintf(result,"%f", ((yyvsp[0].floatValue)));
			            struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
			            newnode->value.var = malloc(sizeof(struct variable));
			            newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
			            strcpy(newnode->value.var->name, result);
			            (yyval.expression) = (struct expr *)malloc(sizeof(struct expr));
			            (yyval.expression) = new_expr(const_num_e,newnode,NULL,((yyvsp[0].floatValue)),"",'\0',NULL);


					}
#line 2996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1167 "syntax.y" /* yacc.c:1646  */
    { argumentF( (yyvsp[0].stringValue), yylineno, (scope + 1)); }
#line 3002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1168 "syntax.y" /* yacc.c:1646  */
    { printf(RED "idlist:: empty\n" RESET); }
#line 3008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1171 "syntax.y" /* yacc.c:1646  */
    { argumentF(((yyvsp[0].stringValue)), yylineno, (scope+1)); }
#line 3014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1172 "syntax.y" /* yacc.c:1646  */
    { printf(RED "multi_idlists:: empty\n" RESET); }
#line 3020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1175 "syntax.y" /* yacc.c:1646  */
    {

				emit(jump,NULL,NULL,NULL,yylineno,999); /*Sto telos tis else*/
				//Kanoume patch to jump mesa stin else se periptosi pou apotixei i if
				quads[((int)(yyvsp[-3].intValue))].label=QuadNo+1;
				//Pername stin tmp mas to quad no tis kainourgias jump ekso apo tin else
				(yyvsp[-3].intValue)=QuadNo-1;

			}
#line 3034 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1183 "syntax.y" /* yacc.c:1646  */
    {
				//Pigenoume sto quad tis jump pano apo tin else kai kanoume patch to label sto quad kato apo tin
   			 	//teleftaia entoli toy stmt tis else !!!
				printf(RED "if(exprsession) stmt else stmt\n" RESET);
				quads[((int)(yyvsp[-5].intValue))].label=QuadNo+1;
	}
#line 3045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1189 "syntax.y" /* yacc.c:1646  */
    {
			 printf(RED "if(exprsession) stmt\n" RESET);
			 //Pigenoume sto quad tis jump kai kanoume patch to label sto quad kato apo tin
		 	//teleftaia entoli toy stmt !!!
		 	quads[((int)(yyvsp[-2].intValue))].label=QuadNo+1;
	}
#line 3056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1197 "syntax.y" /* yacc.c:1646  */
    {

				if (exprflag) {
				   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
				   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

				   emit(assign,true_expr,NULL,(yyvsp[0].expression),yylineno,0);
				   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
				   emit(assign,false_expr,NULL,(yyvsp[0].expression),yylineno,0);
				   exprflag=0;
				  patchLists(((yyvsp[0].expression)),(int)QuadNo-2,(int)QuadNo);
			   }
				struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
				emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tou if
				emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis if
				//Pername sto if_start to index tou quad tis jump
				(yyval.intValue)=QuadNo-1;
			}
#line 3079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1216 "syntax.y" /* yacc.c:1646  */
    {
					insideLoop--;
					emit(jump,NULL,NULL,NULL,yylineno,(yyvsp[-2].intValue)); //$1 quadno stin arxi tou sxpr tis while
					quads[((int)(yyvsp[-1].intValue))].label=QuadNo+1;
					printf(RED "while(expr) stmt\n" RESET);
					patchFlow((yyvsp[-2].intValue),QuadNo+1);
			}
#line 3091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1224 "syntax.y" /* yacc.c:1646  */
    {(yyval.intValue)=QuadNo+1;}
#line 3097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1227 "syntax.y" /* yacc.c:1646  */
    { insideLoop++; }
#line 3103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1227 "syntax.y" /* yacc.c:1646  */
    {

						if (exprflag) {
						   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						   emit(assign,true_expr,NULL,(yyvsp[0].expression),yylineno,0);
						   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						   emit(assign,false_expr,NULL,(yyvsp[0].expression),yylineno,0);
						   exprflag=0;
						   patchLists(((yyvsp[0].expression)),(int)QuadNo-2,(int)QuadNo);
					   }


						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tis while
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis while


						}
#line 3128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1247 "syntax.y" /* yacc.c:1646  */
    {(yyval.intValue)=QuadNo-1;
            }
#line 3135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1251 "syntax.y" /* yacc.c:1646  */
    { insideLoop++; push_E(exprflag); exprflag=0; }
#line 3141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1251 "syntax.y" /* yacc.c:1646  */
    {exprflag=pop_E();}
#line 3147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1251 "syntax.y" /* yacc.c:1646  */
    {

				printf(RED "for(elist; expr;elist) stmt\n" RESET);
				insideLoop--;
				emit(jump,NULL,NULL,NULL,yylineno,(yyvsp[-4].intValue)+1); /*jump stin arxi tou 2ou elist*/
				quads[(int)(yyvsp[-4].intValue)-1].label=QuadNo+1; /*gia to jump sto telos tou for */
				quads[(int)(yyvsp[-4].intValue)-2].label=(yyvsp[-2].intValue)+1; /*if_eq jump arxi for*/
				quads[(int)(yyvsp[-2].intValue)-1].label=(yyvsp[-7].intValue)+1; /*gia jump sto cond tis for*/

				patchFlow((int)(yyvsp[-4].intValue)+1,(int)QuadNo+1);

			}
#line 3164 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1266 "syntax.y" /* yacc.c:1646  */
    {printf(RED "for_elist:: \n" RESET); (yyval.intValue)=QuadNo;  }
#line 3170 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1267 "syntax.y" /* yacc.c:1646  */
    { printf(RED "for_elist:: empty\n" RESET); }
#line 3176 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1271 "syntax.y" /* yacc.c:1646  */
    {
						if (exprflag) {
						   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						   emit(assign,true_expr,NULL,(yyvsp[0].expression),yylineno,0);
						   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						   emit(assign,false_expr,NULL,(yyvsp[0].expression),yylineno,0);
						   exprflag=0;
						  patchLists(((yyvsp[0].expression)),(int)QuadNo-2,(int)QuadNo);
					   }


						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,999); // jump stin arxi tis for
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis for
						(yyval.intValue)=QuadNo;
					}
#line 3199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1290 "syntax.y" /* yacc.c:1646  */
    {

                  emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika stin arxi tis for
                  (yyval.intValue)=QuadNo;
	      }
#line 3209 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1296 "syntax.y" /* yacc.c:1646  */
    {
				if (exprflag) {

					struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					emit(assign,true_expr,NULL,(yyvsp[-1].expression),yylineno,0);
					emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					emit(assign,false_expr,NULL,(yyvsp[-1].expression),yylineno,0);
					exprflag=0;

					patchLists(((yyvsp[-1].expression)),(int)QuadNo-2,(int)QuadNo);
				}


					printf(RED "return expression; \n" RESET);
					emit(ret,NULL,NULL,(yyvsp[-1].expression),yylineno,0);
					emit(jump,NULL,NULL,NULL,yylineno,999);//end of func
				}
#line 3233 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1315 "syntax.y" /* yacc.c:1646  */
    {
                        printf(RED "return; \n" RESET);
                        emit(ret,NULL,NULL,NULL,yylineno,0);
                        emit(jump,NULL,NULL,NULL,yylineno,999);//end of func
                  }
#line 3243 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3247 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1322 "syntax.y" /* yacc.c:1906  */

