/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syntax.y"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "lex.h"
#include "parsing.h"
#include "quads.h"


#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

extern int yyerror(const char* s);
int yylex();
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

char** table;

struct expr *tmpexpr;
struct symbol_table_binding *tmpnode;

int current_rvals = 0;


#line 120 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
union YYSTYPE
{
#line 105 "syntax.y"

    double intValue;
    double floatValue;
    char *stringValue;
	  struct expr* expression;
    struct call* callexpr;

#line 267 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#define YYLAST   503

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  199

#define YYUNDEFTOK  2
#define YYMAXUTOK   303

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
       0,   136,   136,   139,   140,   139,   141,   144,   147,   148,
     149,   150,   158,   168,   177,   178,   179,   183,   200,   212,
     223,   234,   245,   256,   274,   291,   310,   327,   358,   382,
     398,   414,   417,   427,   438,   457,   493,   527,   564,   599,
     602,   602,   655,   661,   663,   672,   673,   676,   680,   685,
     695,   701,   705,   712,   756,   781,   797,   823,   840,   844,
     849,   858,   867,   883,   890,   907,   916,   953,   953,   983,
    1002,  1010,  1031,  1043,  1051,  1058,  1065,  1099,  1099,  1102,
    1102,  1102,  1117,  1120,  1129,  1143,  1144,  1153,  1154,  1155,
    1158,  1170,  1182,  1182,  1183,  1186,  1186,  1187,  1190,  1190,
    1204,  1212,  1221,  1229,  1232,  1232,  1232,  1257,  1257,  1273,
    1274,  1278,  1285,  1291,  1296
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
  "$accept", "program", "multi_stmts", "$@1", "$@2", "stmt", "expr",
  "term", "assignmexpr", "$@3", "primary", "lvalue", "member", "call",
  "callsuffix", "normcall", "methodcall", "elist", "multi_exprs",
  "objectdef", "$@4", "elist_for_table", "multi_exprs_for_table",
  "indexed", "multi_indexedelem", "indexedelem", "block", "$@5", "funcdef",
  "$@6", "$@7", "funcstart", "funcname", "const", "number", "idlist",
  "$@8", "multi_id", "$@9", "ifstmt", "$@10", "if_start", "whilestmt",
  "whilestart", "whilecond", "$@11", "$@12", "forstmt", "$@13",
  "for_elist", "for_cond", "for_end", "returnstmt", YY_NULLPTR
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

#define YYTABLE_NINF -71

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-71)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      13,    22,  -138,   106,  -138,   -17,  -138,   -15,  -138,   144,
      23,    26,   216,    -2,  -138,  -138,  -138,   216,    12,    12,
    -138,    27,  -138,   180,     4,  -138,  -138,  -138,  -138,  -138,
     402,  -138,  -138,  -138,    65,  -138,   -30,  -138,  -138,  -138,
      28,  -138,  -138,  -138,    17,  -138,    35,  -138,  -138,   216,
    -138,  -138,   424,  -138,  -138,  -138,  -138,  -138,    69,    -8,
     -30,    -8,  -138,    39,   360,    44,    43,   246,    42,     2,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,  -138,  -138,  -138,    41,    46,   216,   216,
      71,  -138,  -138,  -138,    48,   216,   216,  -138,    54,   106,
    -138,   106,   446,   216,  -138,    47,    58,   216,  -138,   216,
      63,    66,  -138,  -138,    64,  -138,   459,   459,    14,    14,
    -138,  -138,  -138,   472,   472,   182,   182,   182,   182,  -138,
      68,   271,   381,    74,   216,  -138,   294,    76,  -138,   104,
     216,  -138,   381,    92,    64,  -138,   360,   338,  -138,    44,
    -138,   216,   216,  -138,   216,  -138,  -138,   446,  -138,  -138,
      80,  -138,   446,  -138,   216,  -138,   216,    66,    85,    86,
     381,  -138,    87,   106,    91,   446,   103,   317,  -138,  -138,
    -138,  -138,   107,  -138,  -138,  -138,   216,  -138,    89,  -138,
      99,  -138,    96,  -138,  -138,   106,   107,  -138,  -138
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     0,     1,     0,   103,     0,    82,     0,
       0,     0,     0,     0,    88,    89,    87,     0,     0,     0,
      16,     0,    77,    67,     0,    90,    91,    86,    47,     4,
       0,    31,    17,    39,    42,    50,    43,    44,    14,    15,
      84,    46,    85,     8,     0,     9,     0,    10,    11,     0,
     107,   114,     0,    12,    13,    34,    48,    33,     0,    35,
       0,    37,    49,     3,    72,     0,     0,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,    36,    38,     0,     0,     0,    63,
       0,    56,    58,    59,     0,     0,    63,    83,     0,     0,
     104,     0,   101,   110,   113,     0,     0,     0,    69,     0,
       0,    75,    66,    32,    45,     5,    29,    30,    18,    19,
      20,    21,    22,    27,    28,    23,    25,    24,    26,    51,
       0,     0,    65,     0,     0,    53,     0,     0,    79,   100,
       0,   102,    65,     0,     0,    78,    72,     0,    68,     0,
      73,    63,    63,    52,     0,    62,    60,    41,    54,    55,
      94,    98,   105,   109,     0,    71,     0,    75,     0,     0,
      65,    92,     0,     0,     0,   111,     0,     0,    74,    57,
      61,    64,    97,    80,    99,   106,   110,    76,     0,    93,
       0,   112,     0,    95,    81,     0,    97,   108,    96
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,   -46,  -138,  -138,   -92,    -9,  -138,  -138,  -138,
    -138,    24,  -138,    34,  -138,  -138,  -138,   -95,  -137,  -138,
    -138,  -138,     1,  -138,   -18,     5,   -28,  -138,   -20,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,   -33,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,   -21,
    -138,  -138,  -138
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    69,    29,    30,    31,    32,    90,
      33,    34,    35,    36,    91,    92,    93,   133,   155,    37,
      65,    66,   108,   110,   150,   111,    38,    63,    39,   160,
     190,    40,    98,    41,    42,   172,   182,   189,   196,    43,
     173,    44,    45,    46,   101,   140,   174,    47,   103,   143,
     176,   192,    48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,   137,    -6,    55,    68,   163,    94,   139,    57,   141,
      95,     8,    96,    -6,    64,    67,    12,   106,    13,    14,
      15,    16,     4,   115,    17,    49,    13,    50,    86,    87,
      18,    19,    88,   181,    89,    74,    75,    76,   105,    21,
     102,    -6,    59,    61,    23,    56,    24,    21,    25,    26,
      27,    28,    60,    60,    58,    53,   168,   169,    54,    28,
      99,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,    62,    97,     8,   100,    -6,   131,
     132,   184,   109,   -40,   112,   114,   136,   132,   129,   134,
     144,    84,    85,   130,   142,   135,   138,   145,   146,   149,
     147,    86,    87,   197,   148,    88,   151,    89,   161,     5,
     152,     6,     7,     8,     9,    10,    11,   156,    12,   159,
      13,    14,    15,    16,   164,   157,    17,   171,   179,   180,
     183,   162,    18,    19,   185,   186,   193,    22,    20,   195,
     188,    21,   132,   132,    22,   170,    23,   165,    24,   178,
      25,    26,    27,    28,   167,   175,    12,   177,    13,    14,
      15,    16,   194,   198,    17,   191,     0,     0,     0,     0,
      18,    19,     0,     0,     0,     0,    51,   142,     0,    21,
       0,     0,     0,     0,    23,     0,    24,     0,    25,    26,
      27,    28,    12,     0,    13,    14,    15,    16,     0,     0,
      17,    72,    73,    74,    75,    76,    18,    19,     0,     0,
     -71,   -71,   -71,   -71,     0,    21,     0,     0,     0,     0,
      23,   -70,    24,     0,    25,    26,    27,    28,    12,     0,
      13,    14,    15,    16,     0,     0,    17,     0,     0,     0,
       0,     0,    18,    19,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,    23,    70,    24,    71,
      25,    26,    27,    28,     0,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,     0,     0,
       0,     0,    70,     0,    71,     0,     0,     0,     0,   113,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,    82,     0,     0,    70,     0,    71,     0,     0,
       0,     0,   153,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    79,    80,    81,    82,     0,     0,    70,     0,
      71,     0,     0,     0,     0,   158,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,    81,    82,    70,
       0,    71,     0,     0,     0,     0,   187,    72,    73,    74,
      75,    76,    77,    78,     0,     0,    79,    80,    81,    82,
       0,    70,   166,    71,     0,     0,     0,     0,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,    70,   107,    71,     0,     0,     0,     0,     0,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,    82,    70,   154,    71,     0,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      79,    80,    81,    82,    83,    70,     0,    71,     0,     0,
       0,     0,     0,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    79,    80,    81,    82,   104,    70,     0,    71,
       0,     0,     0,     0,     0,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    72,    73,    74,    75,    76,   -71,   -71,     0,     0,
      79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
       9,    96,     0,    12,    24,   142,    36,    99,    17,   101,
      40,     7,    42,     0,    23,    24,    12,    63,    14,    15,
      16,    17,     0,    69,    20,    42,    14,    42,    36,    37,
      26,    27,    40,   170,    42,    21,    22,    23,    58,    35,
      49,    39,    18,    19,    40,    47,    42,    35,    44,    45,
      46,    47,    18,    19,    42,    32,   151,   152,    32,    47,
      43,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    47,    47,     7,    42,    39,    88,
      89,   173,    38,    18,    41,    43,    95,    96,    47,    18,
      43,    26,    27,    47,   103,    47,    42,    39,   107,    33,
     109,    36,    37,   195,    41,    40,    42,    42,     4,     3,
      42,     5,     6,     7,     8,     9,    10,    43,    12,    43,
      14,    15,    16,    17,    32,   134,    20,    47,    43,    43,
      43,   140,    26,    27,    43,    32,    47,    38,    32,    43,
      33,    35,   151,   152,    38,   154,    40,   146,    42,   167,
      44,    45,    46,    47,   149,   164,    12,   166,    14,    15,
      16,    17,   190,   196,    20,   186,    -1,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    -1,    32,   186,    -1,    35,
      -1,    -1,    -1,    -1,    40,    -1,    42,    -1,    44,    45,
      46,    47,    12,    -1,    14,    15,    16,    17,    -1,    -1,
      20,    19,    20,    21,    22,    23,    26,    27,    -1,    -1,
      28,    29,    30,    31,    -1,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    45,    46,    47,    12,    -1,
      14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    40,    11,    42,    13,
      44,    45,    46,    47,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,    43,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    -1,    -1,    11,    -1,    13,    -1,    -1,
      -1,    -1,    41,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    -1,    11,    -1,
      13,    -1,    -1,    -1,    -1,    41,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    11,
      -1,    13,    -1,    -1,    -1,    -1,    39,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    11,    34,    13,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    11,    33,    13,    -1,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    11,    33,    13,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    32,    11,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    32,    11,    -1,    13,
      -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    51,    52,     0,     3,     5,     6,     7,     8,
       9,    10,    12,    14,    15,    16,    17,    20,    26,    27,
      32,    35,    38,    40,    42,    44,    45,    46,    47,    54,
      55,    56,    57,    59,    60,    61,    62,    68,    75,    77,
      80,    82,    83,    88,    90,    91,    92,    96,   101,    42,
      42,    32,    55,    32,    32,    55,    47,    55,    42,    60,
      62,    60,    47,    76,    55,    69,    70,    55,    77,    53,
      11,    13,    19,    20,    21,    22,    23,    24,    25,    28,
      29,    30,    31,    32,    26,    27,    36,    37,    40,    42,
      58,    63,    64,    65,    36,    40,    42,    47,    81,    43,
      42,    93,    55,    97,    32,    77,    51,    33,    71,    38,
      72,    74,    41,    43,    43,    51,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    47,
      47,    55,    55,    66,    18,    47,    55,    66,    42,    54,
      94,    54,    55,    98,    43,    39,    55,    55,    41,    33,
      73,    42,    42,    41,    33,    67,    43,    55,    41,    43,
      78,     4,    55,    67,    32,    71,    34,    74,    66,    66,
      55,    47,    84,    89,    95,    55,    99,    55,    73,    43,
      43,    67,    85,    43,    54,    43,    32,    39,    33,    86,
      79,    98,   100,    47,    75,    43,    87,    54,    86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    52,    53,    51,    51,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      58,    57,    59,    59,    59,    59,    59,    60,    60,    60,
      60,    61,    61,    61,    61,    62,    62,    62,    63,    63,
      64,    65,    66,    66,    67,    67,    68,    69,    68,    70,
      70,    71,    71,    72,    73,    73,    74,    76,    75,    78,
      79,    77,    80,    81,    81,    82,    82,    82,    82,    82,
      83,    83,    85,    84,    84,    87,    86,    86,    89,    88,
      88,    90,    91,    92,    94,    95,    93,    97,    96,    98,
      98,    99,   100,   101,   101
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     0,     4,     0,     2,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     2,     2,     2,     2,     2,     2,     1,
       0,     4,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     2,     6,     1,     1,
       3,     5,     2,     0,     3,     0,     3,     0,     4,     2,
       0,     3,     0,     2,     3,     0,     5,     0,     4,     0,
       0,     8,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     0,     3,     0,     0,     4,     0,     0,     6,
       3,     3,     3,     1,     0,     0,     5,     0,    10,     2,
       0,     1,     1,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

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
  case 3:
#line 139 "syntax.y"
    {current_rvals = 0;
		}
#line 1572 "y.tab.c"
    break;

  case 4:
#line 140 "syntax.y"
    {rvalues = current_rvals;}
#line 1578 "y.tab.c"
    break;

  case 5:
#line 140 "syntax.y"
    { printf(RED "stmt multi_stmt\n" RESET);}
#line 1584 "y.tab.c"
    break;

  case 6:
#line 141 "syntax.y"
    {printf(RED "multi_stmts empty\n" RESET);}
#line 1590 "y.tab.c"
    break;

  case 7:
#line 144 "syntax.y"
    { printf(RED "expression \n" RESET);

      }
#line 1598 "y.tab.c"
    break;

  case 8:
#line 147 "syntax.y"
    { printf(RED "if stmt \n" RESET); }
#line 1604 "y.tab.c"
    break;

  case 9:
#line 148 "syntax.y"
    { printf(RED "while stmt \n" RESET); }
#line 1610 "y.tab.c"
    break;

  case 10:
#line 149 "syntax.y"
    { printf(RED "for stmt \n" RESET); }
#line 1616 "y.tab.c"
    break;

  case 11:
#line 150 "syntax.y"
    {
		  	printf(RED "return stmt \n" RESET);
                  if( insideFunc > 0) push_R((int)QuadNo-1);
			else {
                        printf("Error: RETURN STMT outside of function in line %d\n",yylineno);
                        exit(EXIT_FAILURE);
                  }
		}
#line 1629 "y.tab.c"
    break;

  case 12:
#line 158 "syntax.y"
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
#line 1644 "y.tab.c"
    break;

  case 13:
#line 168 "syntax.y"
    {  printf(RED "continue \n" RESET);
                              if( insideLoop > 0) {
                              	emit(jump,NULL,NULL,NULL,yylineno,999);
						push_C((int)QuadNo-1);
                              } else {
                                    printf("Error: CONTINUE STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              }
      }
#line 1658 "y.tab.c"
    break;

  case 14:
#line 177 "syntax.y"
    { printf(RED "block \n" RESET);}
#line 1664 "y.tab.c"
    break;

  case 15:
#line 178 "syntax.y"
    { printf(RED "funcdef \n" RESET);}
#line 1670 "y.tab.c"
    break;

  case 16:
#line 179 "syntax.y"
    { printf(RED "semicolon \n" RESET);}
#line 1676 "y.tab.c"
    break;

  case 17:
#line 183 "syntax.y"
    {

           result =malloc(5*sizeof(char));
           sprintf(result,"_%d",rvalues++);
           struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);

           if((yyvsp[0].expression)->type == tableitem_e){
               struct expr* tempexp = new_expr(tableitem_e,newnode,NULL,0,"",'\0',NULL);
               emit(tablegetelem,(yyvsp[0].expression)->index,(yyvsp[0].expression),tempexp,yylineno,0);

           }else{
               (yyval.expression) = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL); //TODO mporei na mhn thelei arithmeticexp edw

               emit(assign,(yyvsp[0].expression),NULL,(yyval.expression),yylineno,0);
           }

       }
#line 1698 "y.tab.c"
    break;

  case 18:
#line 200 "syntax.y"
    {
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
//todo? edw o online den kanei to rvalues++
                  (yyval.expression) = smallFunc(arithmeticexp_e);
                  emit(add, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
            }
            else{
              printf("Compile time error: cannot ADD 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
              exit(EXIT_FAILURE);
            }

      }
#line 1715 "y.tab.c"
    break;

  case 19:
#line 212 "syntax.y"
    {
            /*compile time type check*/
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(arithmeticexp_e);
                  emit(sub, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
            }
            else{
                  printf("Compile time error: cannot sub 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
                  exit(EXIT_FAILURE);
            }
  	}
#line 1731 "y.tab.c"
    break;

  case 20:
#line 223 "syntax.y"
    {
            /*compile time type check*/
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(arithmeticexp_e);
                  emit(mul, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
            }
            else{
                  printf("Compile time error: cannot multiple 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
                  exit(EXIT_FAILURE);
            }
  	}
#line 1747 "y.tab.c"
    break;

  case 21:
#line 234 "syntax.y"
    {
            /*compile time type check*/
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(const_num_e);
                  emit(Div, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
            }
            else {
                  printf("Compile time error: cannot div 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
                  exit(EXIT_FAILURE);
            }
      }
#line 1763 "y.tab.c"
    break;

  case 22:
#line 245 "syntax.y"
    {
            /*compile time type check*/
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(const_num_e);
                  emit(mod, (yyvsp[-2].expression), (yyvsp[0].expression), (yyval.expression), yylineno, 0);
            }
            else {
              printf("Compile time error: cannot mod 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
              exit(EXIT_FAILURE);
            }
  	}
#line 1779 "y.tab.c"
    break;

  case 23:
#line 256 "syntax.y"
    {
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(boolexp_e);
            } else {
                  printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
                  exit(EXIT_FAILURE);
            }

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_greater,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,QuadNo+3);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);

      }
#line 1802 "y.tab.c"
    break;

  case 24:
#line 274 "syntax.y"
    {
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(boolexp_e);
            } else {
                  printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
                  exit(EXIT_FAILURE);
            }

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_greatereq,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);
      }
#line 1824 "y.tab.c"
    break;

  case 25:
#line 291 "syntax.y"
    {

            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(boolexp_e);
            } else {
                  printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
                  exit(EXIT_FAILURE);
            }

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_less,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);

      }
#line 1848 "y.tab.c"
    break;

  case 26:
#line 310 "syntax.y"
    {
            if(checkTypes((yyvsp[-2].expression), (yyvsp[0].expression)) == 1) {
                  (yyval.expression) = smallFunc(boolexp_e);
            } else {
                  printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
                  exit(EXIT_FAILURE);
            }

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_lesseq,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);
      }
#line 1870 "y.tab.c"
    break;

  case 27:
#line 327 "syntax.y"
    {

      //metatroph twn expr1 kai expr2 se bool expr
      // struct expr* expr1_apotimhsh_seboolean = apotimhsh_seboolean($1);
      // struct expr* expr2_apotimhsh_seboolean = apotimhsh_seboolean($3);

      // printf("to expr1 apotimatai se: %s, typou %d\n", expr1_apotimhsh_seboolean->sym->value.var->name, expr1_apotimhsh_seboolean->type);
      // printf("to expr2 apotimatai se: %s, typou %d\n", expr2_apotimhsh_seboolean->sym->value.var->name, expr2_apotimhsh_seboolean->type);

            //compile time type check
            if( ((yyvsp[-2].expression))->type == 1 && ((yyvsp[0].expression))->type == 11 ){ //table and nil ok
            }
            else if(oneIsVar((yyvsp[-2].expression), (yyvsp[0].expression))) {
                  //ok
            }
            else if( ((yyvsp[-2].expression))->type != ((yyvsp[0].expression))->type){
                printf("Compile time error: cannot compare 2 different types! expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
                exit(EXIT_FAILURE);
            }

            (yyval.expression) = smallFunc(boolexp_e);

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_eq,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,QuadNo+3);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);
      }
#line 1906 "y.tab.c"
    break;

  case 28:
#line 358 "syntax.y"
    {
            //compile time type check- MPOREI NA EINAI LATHOS
            if( ((yyvsp[-2].expression))->type ==1 && ((yyvsp[0].expression))->type ==11 ){
                  //table and nil ok
            }
            else if(oneIsVar((yyvsp[-2].expression), (yyvsp[0].expression))) {
                  //ok
            }
            else if( ((yyvsp[-2].expression))->type != ((yyvsp[0].expression))->type){
                printf("Compile time error: cannot COMPARE 2 different types! expr1 is %d and expr2 is %d, line %d\n",((yyvsp[-2].expression))->type, ((yyvsp[0].expression))->type, yylineno );
                exit(EXIT_FAILURE);
            }

            (yyval.expression) = smallFunc(boolexp_e);

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_not_eq,(yyvsp[-2].expression),(yyvsp[0].expression),NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);
      }
#line 1935 "y.tab.c"
    break;

  case 29:
#line 382 "syntax.y"
    {

            (yyval.expression) = smallFunc(boolexp_e);

            // struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
               // struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

               // emit(if_eq,$1,true_expr,NULL,yylineno,QuadNo+3);//epomeno expr an true
               // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+6); // jump assign false
               // emit(if_eq,$3,true_expr,NULL,yylineno,QuadNo+3);//ass true an true h methepomeno gia pollapla and (?)
               // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4); // jump assing false
               // emit(assign,true_expr,NULL,$$,yylineno,0); //  =true
               // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3); // jump under ass false
               // emit(assign,false_expr,NULL,$$,yylineno,0); // =false
   		emit(and,(yyvsp[-2].expression),(yyvsp[0].expression),(yyval.expression),yylineno,0);
      }
#line 1956 "y.tab.c"
    break;

  case 30:
#line 398 "syntax.y"
    {

            (yyval.expression) = smallFunc(boolexp_e);

            // struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
              // struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );
  			//
              // emit(if_eq,$1,true_expr,NULL,yylineno,QuadNo+5);//THELEI SWSTO LABEL
              // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+2);// den allazei kati alla to exo gia na einai idio me to online
              // emit(if_eq,$3,true_expr,NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
              // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
              // emit(assign,true_expr,NULL,$$,yylineno,0);
              // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
              // emit(assign,false_expr,NULL,$$,yylineno,0);
  		emit(or,(yyvsp[-2].expression),(yyvsp[0].expression),(yyval.expression),yylineno,0);
      }
#line 1977 "y.tab.c"
    break;

  case 31:
#line 414 "syntax.y"
    { (yyval.expression)=(yyvsp[0].expression); printf(RED"term(%s)\n"RESET, (yyvsp[0].expression)->sym->value.var->name); }
#line 1983 "y.tab.c"
    break;

  case 32:
#line 417 "syntax.y"
    { printf(RED " (expression) \n" RESET);
      /*    result =malloc(5*sizeof(char));
          sprintf(result,"_%d",rvalues++);
          tmpnode = malloc(sizeof(struct symbol_table_binding));
          tmpnode =insertVar(result,yylineno,scope);
          tmpexpr=malloc(sizeof(struct expr));
          tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
      */
          (yyval.expression) = (yyvsp[-1].expression);
      }
#line 1998 "y.tab.c"
    break;

  case 33:
#line 427 "syntax.y"
    {
            printf(RED " - expression \n" RESET);
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues);
            tmpnode = malloc(sizeof(struct symbol_table_binding));
            tmpnode =insertVar(result,yylineno,scope);
            tmpexpr=malloc(sizeof(struct expr));
            tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
            emit(uminus,(yyvsp[0].expression),NULL,tmpexpr,yylineno,0);
            (yyval.expression) = tmpexpr;
   	}
#line 2014 "y.tab.c"
    break;

  case 34:
#line 438 "syntax.y"
    {
                  printf(RED "NOT expression\n" RESET);
                  // result =malloc(5*sizeof(char));
                  // sprintf(result,"_%d",rvalues++);
                  // struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                  // $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

            (yyval.expression) = smallFunc(boolexp_e);

                  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
                  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",1,NULL );

                  emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,QuadNo+5);
                  emit(jump,NULL,NULL,NULL,yylineno,QuadNo+2);
                  emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
                  emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
                  emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);

      }
#line 2038 "y.tab.c"
    break;

  case 35:
#line 457 "syntax.y"
    {
      	      printf(RED "++lvalue dassa\n" RESET);
                  check_for_funcname((yyvsp[0].expression)->sym->value.var->name);

                  if((yyvsp[0].expression)->type == 1){

      			   struct expr* tmp_expr = new_expr(tableitem_e,(yyvsp[0].expression)->index->sym,NULL,0,"",'\0',NULL);

      			  (yyval.expression)= member_item((yyvsp[0].expression), (yyvsp[0].expression)->sym->value.var->name);

      			  result =malloc(5*sizeof(char));
      			  sprintf(result,"_%d",rvalues++);
      			  tmpnode =insertVar(result,yylineno,scope);
      			  tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
      			  //new expr for number 1
      			  struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
      			  // first add
      			  emit(add,(yyval.expression),tmp_one,(yyval.expression),yylineno,0);

              emit(table_setelem,tmp_expr,(yyval.expression),(yyval.expression)->index,yylineno,0);
              } else{
                        result =malloc(5*sizeof(char));
                        sprintf(result,"_%d",rvalues++);
          			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
          			   	tmpnode =insertVar(result,yylineno,scope);
          			   	tmpexpr=malloc(sizeof(struct expr));
          			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
            				//new expr for number 1
                    struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
            				// first add
            				emit(add,(yyvsp[0].expression),tmp_one,(yyvsp[0].expression),yylineno,0);
            				//then assign
            			  emit(assign,(yyvsp[0].expression),NULL,tmpexpr,yylineno,0);
                    (yyval.expression) = tmpexpr;
                    }
      	}
#line 2079 "y.tab.c"
    break;

  case 36:
#line 493 "syntax.y"
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
                   			 // first assing
                   			 emit(assign,temp_expr,NULL,tmpexpr,yylineno,0);

                				 emit(add,temp_expr,tmp_one,temp_expr,yylineno,0);

                				 emit(table_setelem,(yyvsp[-1].expression)->index,temp_expr,temp_expr->index,yylineno,0);
                         (yyval.expression) = tmpexpr;
                		  }else{
                			  tmpnode =insertVar(result,yylineno,scope);
                			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
                			   //new expr for number 1
                			 struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
                			   // first assing
                			   emit(assign,(yyvsp[-1].expression),NULL,tmpexpr,yylineno,0);
                			   //then add
                			   emit(add,(yyvsp[-1].expression),tmp_one,(yyvsp[-1].expression),yylineno,0);
                	   			(yyval.expression) = tmpexpr;
                		  }


      	}
#line 2118 "y.tab.c"
    break;

  case 37:
#line 527 "syntax.y"
    {
                check_for_funcname((yyvsp[0].expression)->sym->value.var->name);
        				printf(RED "--lvalue\n" RESET);

                if((yyvsp[0].expression)->type == 1){

                    struct expr* tmp_expr = new_expr(tableitem_e,(yyvsp[0].expression)->index->sym,NULL,0,"",'\0',NULL);
                    (yyval.expression)= member_item((yyvsp[0].expression), (yyvsp[0].expression)->sym->value.var->name);

                    result =malloc(5*sizeof(char));
                    sprintf(result,"_%d",rvalues++);
                    tmpnode =insertVar(result,yylineno,scope);
                    tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
                    //new expr for number 1
                    struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

                    emit(sub,(yyval.expression),tmp_one,(yyval.expression),yylineno,0);

                    emit(table_setelem,tmp_expr,(yyval.expression),(yyval.expression)->index,yylineno,0);
                } else{
            				result =malloc(5*sizeof(char));
            			  sprintf(result,"_%d",rvalues++);

          			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
          			   	tmpnode =insertVar(result,yylineno,scope);
          			   	tmpexpr=malloc(sizeof(struct expr));
          			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
          				  //new expr for number 1
                    struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
            				// first sub
            				emit(sub,(yyvsp[0].expression),tmp_one,(yyvsp[0].expression),yylineno,0);
            				//then assign
          			   	emit(assign,(yyvsp[0].expression),NULL,tmpexpr,yylineno,0);
                    (yyval.expression) = tmpexpr;
                }

        	}
#line 2160 "y.tab.c"
    break;

  case 38:
#line 564 "syntax.y"
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
               			 // first assing
               			 emit(assign,temp_expr,NULL,tmpexpr,yylineno,0);

            				 emit(sub,temp_expr,tmp_one,temp_expr,yylineno,0);

            				 emit(table_setelem,(yyvsp[-1].expression)->index,temp_expr,temp_expr->index,yylineno,0);
                     (yyval.expression) = tmpexpr;
            		  }else{
            			  tmpnode =insertVar(result,yylineno,scope);
            			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
            			   //new expr for number 1
            			 struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
            			   // first assing
            			   emit(assign,(yyvsp[-1].expression),NULL,tmpexpr,yylineno,0);
            			   //then add
            			   emit(add,(yyvsp[-1].expression),tmp_one,(yyvsp[-1].expression),yylineno,0);
            	   			(yyval.expression) = tmpexpr;
            		  }

      			}
#line 2200 "y.tab.c"
    break;

  case 39:
#line 599 "syntax.y"
    { printf(RED "primary\n" RESET); (yyval.expression)=(yyvsp[0].expression);  }
#line 2206 "y.tab.c"
    break;

  case 40:
#line 602 "syntax.y"
    { if(!arrayFlag && ref)   check_for_funcname((yyvsp[0].expression)->sym->value.var->name);  }
#line 2212 "y.tab.c"
    break;

  case 41:
#line 602 "syntax.y"
    {
							     arrayFlag = 0;
                   ref = 1;

                //   printf("eeeeeem egww (%s)=(%s)\n\n", $1->sym->value.var->name ,$4->sym->value.var->name);

                /*   if($1->type != tableitem_e && $4->type == tableitem_e){
                             //gia na grafetai to d apo to x=t.a.b.c.d;
                            // printf("ASSXP:: lvalue(%s) = eq(%s with index %s) \n",$1->sym->value.var->name, $4->sym->value.var->name, $4->index->sym->value.var->name);

                             result =malloc(5*sizeof(char));
                             sprintf(result,"_%d",rvalues++);
                             struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                             struct expr* tmp_table = new_expr(var_e,newnode,NULL,0,"",'\0',NULL);

                             emit(tablegetelem,$4,$4->index,tmp_table,yylineno,0);
                             emit(assign,$4,NULL,$1,yylineno,0);

                   }
                   else*/
                   if((yyvsp[-3].expression)->type == tableitem_e){
                          // printf("else if:: lvalue(%s with type %d) = eq(%s with index %s and index type %d ) \n",$1->sym->value.var->name,$1->type, $4->sym->value.var->name, $4->index->sym->value.var->name,$4->index->type);

                        /* if($4->index!= NULL && $4->index->type == conststring_e){
                                //gia na grafetai to v apo to t.a.b.c.d = x.k.v;
                                  //   printf("ektos:: lvalue(%s with type %d) = eq(%s with index %s and index type %d ) \n",$1->sym->value.var->name,$1->type, $4->sym->value.var->name, $4->index->sym->value.var->name,$4->index->type);
                                     result =malloc(5*sizeof(char));
                                     sprintf(result,"_%d",rvalues++);
                                     struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                                     struct expr* tmp_table = new_expr(tableitem_e,newnode,NULL,0,"",'\0',NULL);
                                     emit(tablegetelem,$4,$4->index,tmp_table,yylineno,0);
                                     $4 = tmp_table;

                                     //tablegetelem ^3        "v"      ^4
                           }
*/
                        emit(table_setelem,(yyvsp[-3].expression)->index,(yyvsp[0].expression),(yyvsp[-3].expression),yylineno,0);
//                                          e         x 2
                        struct symbol_table_binding *tmp_index = malloc(sizeof(struct symbol_table_binding));
                        tmp_index->value.var = malloc(sizeof(struct variable));
                        tmp_index->value.var->name = malloc((strlen((yyvsp[-3].expression)->index->sym->value.var->name) + 1) * sizeof(char));
                        strcpy(tmp_index->value.var->name, (yyvsp[-3].expression)->index->sym->value.var->name);
                        tmp_index->next = NULL;

                        struct expr*  returned_exp = new_expr(tableitem_e,tmp_index,(yyvsp[-3].expression),0,"",'\0',NULL);
                        (yyval.expression) = returned_exp;
                   }else{
							            emit(assign,(yyvsp[0].expression),NULL,(yyvsp[-3].expression),yylineno,0);

                   }
						  }
#line 2268 "y.tab.c"
    break;

  case 42:
#line 655 "syntax.y"
    { printf(RED "primary:: lvalue %s \n" RESET,(yyvsp[0].expression)->sym->value.var->name);
              if((yyvsp[0].expression)->type == 1 ){
                    (yyvsp[0].expression) = member_item((yyvsp[0].expression), (yyvsp[0].expression)->sym->value.var->name);
              }
              (yyval.expression)=(yyvsp[0].expression);
         }
#line 2279 "y.tab.c"
    break;

  case 43:
#line 661 "syntax.y"
    {printf(RED "primary:: call %s \n" RESET,(yyvsp[0].expression)->sym->value.var->name);
         }
#line 2286 "y.tab.c"
    break;

  case 44:
#line 663 "syntax.y"
    { printf(RED "primary:: objectdef\n" RESET);
/*              result =malloc(5*sizeof(char));
                sprintf(result,"_%d",rvalues++);
                struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                struct expr* tmp_table = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);
                emit(tablecreate,$1,NULL,tmp_table,yylineno,0);
*/
                (yyval.expression) = (yyvsp[0].expression);
         }
#line 2300 "y.tab.c"
    break;

  case 45:
#line 672 "syntax.y"
    { printf(RED "primary:: (funcdef)\n" RESET); (yyval.expression) = (yyvsp[-1].expression); }
#line 2306 "y.tab.c"
    break;

  case 46:
#line 673 "syntax.y"
    { printf(RED "primary:: const\n" RESET);  (yyval.expression)=(yyvsp[0].expression); }
#line 2312 "y.tab.c"
    break;

  case 47:
#line 676 "syntax.y"
    { printf( "lvalue:: id %s\n", (yyvsp[0].stringValue));
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode= insertVar( yylval.stringValue, yylineno, scope);
						(yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);   }
#line 2321 "y.tab.c"
    break;

  case 48:
#line 680 "syntax.y"
    {
						printf(RED "lvalue:: local identifier\n" RESET);
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode = localVar( yylval.stringValue, yylineno, scope);
						(yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);}
#line 2331 "y.tab.c"
    break;

  case 49:
#line 685 "syntax.y"
    {
            tmpnode=malloc(sizeof(struct symbol_table_binding));
            if((tmpnode=global_exists((yyvsp[0].stringValue))) == NULL) {
                  printf("\"%s\" undeclared, (first use here), line: %d\n", (yyvsp[0].stringValue), yylineno);
                  exit(EXIT_FAILURE);
            }

		        (yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);

            printf( RED "lvalue:: doublecolon\n" RESET);}
#line 2346 "y.tab.c"
    break;

  case 50:
#line 695 "syntax.y"
    { printf(RED "lvalue:: member %s type %d\n" RESET, (yyvsp[0].expression)->sym->value.var->name, (yyvsp[0].expression)->type);
            (yyval.expression) = (yyvsp[0].expression);

         }
#line 2355 "y.tab.c"
    break;

  case 51:
#line 701 "syntax.y"
    {
            (yyval.expression) = member_item((yyvsp[-2].expression), (yyvsp[0].stringValue));
            printf("(lvalue is %s) . (id is %s)\n",(yyvsp[-2].expression)->sym->value.var->name,(yyvsp[0].stringValue));
         }
#line 2364 "y.tab.c"
    break;

  case 52:
#line 705 "syntax.y"
    {
                arrayFlag = 1;
                printf(RED"member:: lvalue[expression]\n"RESET);
                printf("(lvalue is %s) [expr %s] \n",(yyvsp[-3].expression)->sym->value.var->name, (yyvsp[-1].expression)->sym->value.var->name);

                (yyval.expression) = member_item((yyvsp[-3].expression), (yyvsp[-1].expression)->sym->value.var->name);
         }
#line 2376 "y.tab.c"
    break;

  case 53:
#line 712 "syntax.y"
    {

              struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
              tmp_symbol_id->value.var = malloc(sizeof(struct variable));
              tmp_symbol_id->value.var->name = malloc((strlen((yyvsp[0].stringValue)) + 1) * sizeof(char));
              strcpy(tmp_symbol_id->value.var->name, (yyvsp[0].stringValue));
              tmp_symbol_id->next = NULL;
              //adespoto symbol pou den prepei na mpei sto hash!

              struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);

              (yyvsp[-2].expression)->index = tmpexpr_id;
              printf("(%s)'s index is %s\n", (yyvsp[-2].expression)->sym->value.var->name,(yyvsp[-2].expression)->index->sym->value.var->name);

              //$1 = emit_iftable_item($1);

              //ayto sketo pernaei to a().b; !!!!!!!!!!!
              struct expr* tmp_exression = member_item((yyvsp[-2].expression), (yyvsp[0].stringValue)); //prepei to $1 na einai table item
              printf("MEMBER SAYS type returned is %d\n", tmp_exression->type);
              (yyval.expression) = tmp_exression;

/*
      //      ayto kanei swsta to a().b alla oxi to a().b=8; (giati prepei n ginei prwta to setelem kai meta to getelem) !!!!!!!!!!!
      // den xreiazete to $1 na einai table item
              result =malloc(5*sizeof(char));
              sprintf(result,"_%d",rvalues++);
              tmpnode=malloc(sizeof(struct symbol_table_binding));
              tmpnode =insertVar(result,yylineno,scope);
              tmpexpr=malloc(sizeof(struct expr));
      				tmpexpr= new_expr(tableitem_e,tmpnode,NULL,0,"",'\0',NULL);


              struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
              tmp_symbol_id->value.var = malloc(sizeof(struct variable));
              tmp_symbol_id->value.var->name = malloc((strlen($3) + 1) * sizeof(char));
              strcpy(tmp_symbol_id->value.var->name, $3);
              tmp_symbol_id->next = NULL;
              //adespoto symbol pou den prepei na mpei sto hash!

              struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);
            $$ = tmpexpr_id;
              emit(tablegetelem,$1,tmpexpr_id,tmpexpr,yylineno,0);
*/
         }
#line 2425 "y.tab.c"
    break;

  case 54:
#line 756 "syntax.y"
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
            //printf("(%s)'s index is %s\n", $1->sym->value.var->name,$1->index->sym->value.var->name);

            //$1 = emit_iftable_item($1);

            //ayto sketo pernaei to a().b; !!!!!!!!!!!
            struct expr* tmp_exression = member_item((yyvsp[-3].expression), (yyvsp[-1].expression)->sym->value.var->name); //prepei to $1 na einai table item
            //printf("MEMBER SAYS type returned is %d\n", tmp_exression->type);
            (yyval.expression) = tmp_exression;
         }
#line 2453 "y.tab.c"
    break;

  case 55:
#line 781 "syntax.y"
    {

				printf(RED "call:: call (elist)\n" RESET);
/*				result =malloc(5*sizeof(char));
				sprintf(result,"_%d",rvalues++);
				tmpnode=malloc(sizeof(struct symbol_table_binding));
				tmpnode =insertVar(result,yylineno,scope);
				tmpexpr=malloc(sizeof(struct expr));
				tmpexpr= new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);
				emit(call,NULL,NULL,$1,yylineno,0);
				emit(getretval,NULL,NULL,tmpexpr,yylineno,0);
				$$=tmpexpr;
*/
        (yyval.expression) = make_call((yyvsp[-3].expression), (yyvsp[-1].expression));

 			}
#line 2474 "y.tab.c"
    break;

  case 56:
#line 797 "syntax.y"
    {
		/*   			check_if_exists( $1->sym->value.var->name, scope);
          if($1->type == 1) $1 = member_item($1, $1->index->sym->value.var->name);
					emit(call,NULL,NULL,$1,yylineno,0);
					result =malloc(5*sizeof(char));
	   			 	sprintf(result,"_%d",rvalues++);
		  			 tmpnode=malloc(sizeof(struct symbol_table_binding));
		   			 tmpnode =insertVar(result,yylineno,scope);
		  			 tmpexpr=malloc(sizeof(struct expr));
		   			 tmpexpr= new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);
		  			 emit(getretval,NULL,NULL,tmpexpr,yylineno,0);
				  // $$=tmpexpr;
*/

          //printf("lvalll %s\n", $1->sym->value.var->name);
          (yyvsp[-1].expression) = emit_iftable_item((yyvsp[-1].expression));
          if ((yyvsp[0].callexpr)->method ){
                struct expr* t = (yyvsp[-1].expression);
                t->next = (yyvsp[0].callexpr)->elist;
                (yyvsp[-1].expression) = emit_iftable_item(member_item(t, (yyvsp[0].callexpr)->name));
                (yyvsp[0].callexpr)->elist = t ;

          }

          (yyval.expression) = make_call((yyvsp[-1].expression), (yyvsp[0].callexpr)->elist);
				}
#line 2505 "y.tab.c"
    break;

  case 57:
#line 823 "syntax.y"
    {
		   			printf(RED "call:: (funcdef)(elist)\n" RESET);
/*					emit(call,NULL,NULL,$2,yylineno,0);
					result =malloc(5*sizeof(char));
	   			 	sprintf(result,"_%d",rvalues++);
		  			 tmpnode=malloc(sizeof(struct symbol_table_binding));
		   			 tmpnode =insertVar(result,yylineno,scope);
		  			 tmpexpr=malloc(sizeof(struct expr));
		   			 tmpexpr= new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);
		  			 emit(getretval,NULL,NULL,tmpexpr,yylineno,0);
					 $$=tmpexpr;
*/
          (yyval.expression) = make_call((yyvsp[-4].expression), (yyvsp[-1].expression));

  			}
#line 2525 "y.tab.c"
    break;

  case 58:
#line 840 "syntax.y"
    { printf(RED"callsuffix:: (elist)\n"RESET);

                (yyval.callexpr) = (yyvsp[0].callexpr);
           }
#line 2534 "y.tab.c"
    break;

  case 59:
#line 844 "syntax.y"
    { printf(RED "callsuffix:: ..id(elist)\n" RESET);
                (yyval.callexpr) = (yyvsp[0].callexpr);
           }
#line 2542 "y.tab.c"
    break;

  case 60:
#line 849 "syntax.y"
    { printf("normcall \n");
              (yyval.callexpr) = malloc(sizeof(struct call));
              (yyval.callexpr)->elist = (yyvsp[-1].expression);
              (yyval.callexpr)->method = 0;
              (yyval.callexpr)->name = NULL;

         }
#line 2554 "y.tab.c"
    break;

  case 61:
#line 858 "syntax.y"
    { printf(RED "methodcall\n" RESET);
                (yyval.callexpr) = malloc(sizeof(struct call));

                (yyval.callexpr)->elist = (yyvsp[-1].expression);
                (yyval.callexpr)->method = 1;
                (yyval.callexpr)->name = (yyvsp[-3].stringValue);
           }
#line 2566 "y.tab.c"
    break;

  case 62:
#line 867 "syntax.y"
    {
	 				args++;
          // printf("elist::%s \n",$1->sym->value.var->name);
//					emit(param,$1,NULL,NULL,yylineno,0);
          struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
          newnode->value.var = malloc(sizeof(struct variable));
          newnode->value.var->name = malloc((strlen((yyvsp[-1].expression)->sym->value.var->name) + 1) * sizeof(char));
          strcpy(newnode->value.var->name, (yyvsp[-1].expression)->sym->value.var->name);
          newnode->value.var->line = yylineno;
          newnode->symbol_type = 1;
          newnode->value.var->scope = scope;
          newnode->next = NULL;

          struct expr* temp_elem = new_expr(var_e,newnode,NULL,0,"",'\0',(yyvsp[0].expression));
          (yyval.expression) = temp_elem;
	}
#line 2587 "y.tab.c"
    break;

  case 63:
#line 883 "syntax.y"
    { printf(RED "elist:: empty\n" RESET);
                args = 0;
                struct expr* temp_elem = new_expr(var_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                (yyval.expression) = temp_elem;
      }
#line 2597 "y.tab.c"
    break;

  case 64:
#line 890 "syntax.y"
    {
					args++; printf("multiexpr commma expr(%s) exprs\n", (yyvsp[-1].expression)->sym->value.var->name);
//					emit(param,$2,NULL,NULL,yylineno,0);

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
          (yyval.expression) = temp_elem; //pernaw to neo expression me to next, sto $$
	}
#line 2619 "y.tab.c"
    break;

  case 65:
#line 907 "syntax.y"
    { printf(RED "multi exprsessions: empty\n" RESET);
                  struct expr* temp_elem = new_expr(var_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                  (yyval.expression) = temp_elem;
      }
#line 2628 "y.tab.c"
    break;

  case 66:
#line 916 "syntax.y"
    {
                  printf(RED "objectdef:: elist\n" RESET);

                  result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
                  struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                  struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
                  emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);

                  //edw tupwnontai ola ta stoixeia tou pinaka
                  struct expr* tmp = (yyvsp[-1].expression);
                  int i = 0;

                  while(tmp->sym!= NULL) {
                        char* name =malloc(5*sizeof(char));
                        sprintf(name,"%d",i);
                        //to index:: ena symbol (oxi sto hash), me onoma to index tou stoixeiou
                      	struct symbol_table_binding *tmp_index = malloc(sizeof(struct symbol_table_binding));
                        tmp_index->value.var = malloc(sizeof(struct variable));
                    	tmp_index->value.var->name = malloc((strlen(name) + 1) * sizeof(char));
                        strcpy(tmp_index->value.var->name, name);
	                     tmp_index->next = NULL;
                        //adespoto symbol pou den prepei na mpei sto hash!

                        struct expr* tmp_expr_index = new_expr(newtable_e,tmp_index,NULL,0,"",'\0',NULL);

                        struct symbol_table_binding* tmp_symbol=  insertVar(result ,  yylineno , scope);
                        struct expr* temp_elem = new_expr(var_e,tmp_symbol,NULL,0,"",'\0',NULL);

                        emit(table_setelem,tmp_expr_index ,tmp , temp_elem,yylineno,0);
                        printf("ELEMENTS: %s \n", tmp->sym->value.var->name );
                        tmp = tmp->next;
                        i++;
                  }
                  rvalues++;
                  (yyval.expression) = tmp_table;// epistrefw pros ta panw olo to table
            }
#line 2670 "y.tab.c"
    break;

  case 67:
#line 953 "syntax.y"
    {
                    result =malloc(5*sizeof(char));
                    sprintf(result,"_%d",rvalues);
                    struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                    struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
                    emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);

                }
#line 2683 "y.tab.c"
    break;

  case 68:
#line 961 "syntax.y"
    {
                   printf(RED "objectdef:: indexed\n" RESET);
                   struct expr* tmp = (yyvsp[-1].expression);
/*
                    while(tmp->sym!= NULL) {
                          printf("INDEXED first: %s second %s \n", tmp->sym->value.var->name, tmp->index->sym->value.var->name );
                          tmp = tmp->next;
                    }
*/
                    result =malloc(5*sizeof(char));
                    sprintf(result,"_%d",rvalues++);
                    struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                    struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);

                    (yyval.expression) = tmp_table;// epistrefw pros ta panw olo to table
            }
#line 2704 "y.tab.c"
    break;

  case 69:
#line 983 "syntax.y"
    {
                args++;
                //struct symbol_table_binding* newnode =insertVar($1->sym->value.var->name,yylineno,scope);
                //adespoto symbol pou den prepei na mpei sto hash!
                struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
                newnode->value.var = malloc(sizeof(struct variable));
                newnode->value.var->name = malloc((strlen((yyvsp[-1].expression)->sym->value.var->name) + 1) * sizeof(char));
                strcpy(newnode->value.var->name, (yyvsp[-1].expression)->sym->value.var->name);
                newnode->value.var->line = yylineno;
                newnode->symbol_type = 1;
                newnode->value.var->scope = scope;
                newnode->next = NULL;

                struct expr* temp_elem = new_expr(tableitem_e,newnode,NULL,0,"",'\0',(yyvsp[0].expression));
                //DEN prepei na ginetai edw to emit giati etsi ta bazei anapoda
                // emit(table_setelem,NULL,NULL,temp_elem,yylineno,0);

                (yyval.expression) = temp_elem;
        }
#line 2728 "y.tab.c"
    break;

  case 70:
#line 1002 "syntax.y"
    {
          struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
          (yyval.expression) = temp_elem;
          printf(RED "elist:: empty\n" RESET);
          args = 0;
        }
#line 2739 "y.tab.c"
    break;

  case 71:
#line 1010 "syntax.y"
    {
                             args++;

                             //adespoto symbol pou den prepei na mpei sto hash!
                             struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
                             newnode->value.var = malloc(sizeof(struct variable));
                             newnode->value.var->name = malloc((strlen((yyvsp[-1].expression)->sym->value.var->name) + 1) * sizeof(char));
                             strcpy(newnode->value.var->name, (yyvsp[-1].expression)->sym->value.var->name);
                             newnode->value.var->line = yylineno;
                             newnode->symbol_type = 1;
                             newnode->value.var->scope = scope;
                             newnode->next = NULL;

                             struct expr* temp_elem = new_expr(tableitem_e,newnode,NULL,0,"",'\0',(yyvsp[0].expression));
                             // bazw sto next to epomeno stoixeio

                             //DEN prepei na ginetai edw to emit giati etsi ta bazei anapoda

                             (yyval.expression) = temp_elem; //pernaw to neo expression me to next, sto $$

                        }
#line 2765 "y.tab.c"
    break;

  case 72:
#line 1031 "syntax.y"
    {
                              struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                              (yyval.expression) = temp_elem;
                      }
#line 2774 "y.tab.c"
    break;

  case 73:
#line 1043 "syntax.y"
    {

                printf(RED "indexed:: indexedelement multi\n" RESET);
                struct expr* expr_with_next = new_expr(tableitem_e,(yyvsp[-1].expression)->sym,(yyvsp[-1].expression)->index,0,"",'\0',(yyvsp[0].expression));
                (yyval.expression) = expr_with_next;
                }
#line 2785 "y.tab.c"
    break;

  case 74:
#line 1051 "syntax.y"
    {
                        printf(RED "multi_indexedelem:: comma indelem multi\n" RESET);

                        struct expr* expr_with_next = new_expr(tableitem_e,(yyvsp[-1].expression)->sym,(yyvsp[-1].expression)->index,0,"",'\0',(yyvsp[0].expression));
                        (yyval.expression) = expr_with_next;

                        }
#line 2797 "y.tab.c"
    break;

  case 75:
#line 1058 "syntax.y"
    {
                        printf(RED "multi_indexedelem:: empty\n" RESET);
                        struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                        (yyval.expression) = temp_elem;
                  }
#line 2807 "y.tab.c"
    break;

  case 76:
#line 1065 "syntax.y"
    { //printf( "indelem {expr(%s) : expr(%s)}\n",$2->sym->value.var->name,$4->sym->value.var->name);
                  result = malloc(2 * sizeof(char));
                  sprintf(result, "_%d", rvalues);
                  struct symbol_table_binding* tmp_symbol=  insertVar(result ,  yylineno , scope);
                  struct expr* temp_elem = new_expr(tableitem_e,tmp_symbol,NULL,0,"",'\0',NULL);
                  emit(table_setelem,(yyvsp[-3].expression),(yyvsp[-1].expression),temp_elem,yylineno,0);

                  //adespoto symbol pou den prepei na mpei sto hash!
                  struct symbol_table_binding *newnode1 = malloc(sizeof(struct symbol_table_binding));
                  newnode1->value.var = malloc(sizeof(struct variable));
                  newnode1->value.var->name = malloc((strlen((yyvsp[-3].expression)->sym->value.var->name) + 1) * sizeof(char));
                  strcpy(newnode1->value.var->name, (yyvsp[-3].expression)->sym->value.var->name);
                  newnode1->value.var->line = yylineno;
                  newnode1->symbol_type = 1;
                  newnode1->value.var->scope = scope;
                  newnode1->next = NULL;

                  struct symbol_table_binding *newnode2 = malloc(sizeof(struct symbol_table_binding));
                  newnode2->value.var = malloc(sizeof(struct variable));
                  newnode2->value.var->name = malloc((strlen((yyvsp[-1].expression)->sym->value.var->name) + 1) * sizeof(char));
                  strcpy(newnode2->value.var->name, (yyvsp[-1].expression)->sym->value.var->name);
                  newnode2->value.var->line = yylineno;
                  newnode2->symbol_type = 1;
                  newnode2->value.var->scope = scope;
                  newnode2->next = NULL;

                  struct expr* expr_for_symbol2 = new_expr(tableitem_e,newnode2,NULL,0,"",'\0',NULL);

                  struct expr* new_elem_withboth = new_expr(tableitem_e,newnode1,expr_for_symbol2,0,"",'\0',NULL);
                  (yyval.expression) = new_elem_withboth;

              }
#line 2844 "y.tab.c"
    break;

  case 77:
#line 1099 "syntax.y"
    { scope++; if(scope > maxScope) maxScope = scope; }
#line 2850 "y.tab.c"
    break;

  case 78:
#line 1099 "syntax.y"
    {hide_symbols(scope); scope--;  printf( RED "block:: {stmt multi stmt}\n" RESET ); }
#line 2856 "y.tab.c"
    break;

  case 79:
#line 1102 "syntax.y"
    {push_SP(tmpoffset); tmpoffset=0; insideFunc++;}
#line 2862 "y.tab.c"
    break;

  case 80:
#line 1102 "syntax.y"
    { tmpoffset=0; make_not_accessible(scope+1); }
#line 2868 "y.tab.c"
    break;

  case 81:
#line 1102 "syntax.y"
    {
			  make_accessible_again(scope+1);
			  insideFunc--;
			  emit(funcend,(yyvsp[-6].expression),NULL,NULL,yylineno,0);
			  (yyvsp[-6].expression)->sym->value.func->totalVars=tmpoffset;
			  (yyvsp[-6].expression)->sym->value.func->funcAddress=(yyvsp[-7].intValue)+2;//+1 gia indexing apo to 0 +1 giati to $1 einai to jump
			  (yyval.expression)=(yyvsp[-6].expression);
			  printf("funcstart %d\n",(int)(yyvsp[-7].intValue) );
			  quads[(int)(yyvsp[-7].intValue)].label=QuadNo+1;
			  tmpoffset=pop_SP();

			  patchReturn((int)(yyvsp[-7].intValue),(int)QuadNo);
		   	}
#line 2886 "y.tab.c"
    break;

  case 82:
#line 1117 "syntax.y"
    { emit(jump,NULL,NULL,NULL,yylineno,999); (yyval.intValue)=QuadNo-1; }
#line 2892 "y.tab.c"
    break;

  case 83:
#line 1120 "syntax.y"
    {
					tmpnode=malloc(sizeof(struct symbol_table_binding));
					tmpnode= newFunction( (yyvsp[0].stringValue), yylineno, scope);
					tmpexpr=malloc(sizeof(struct expr));
					tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);

					emit(funcstart,tmpexpr,NULL,NULL,yylineno,0);
					(yyval.expression)=tmpexpr;
			}
#line 2906 "y.tab.c"
    break;

  case 84:
#line 1129 "syntax.y"
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
#line 2923 "y.tab.c"
    break;

  case 85:
#line 1143 "syntax.y"
    {		(yyval.expression)=(yyvsp[0].expression);	}
#line 2929 "y.tab.c"
    break;

  case 86:
#line 1144 "syntax.y"
    {
                printf("STRINGGG %s \n",Lex_string );
				tmpnode=malloc(sizeof(struct symbol_table_binding));
				tmpnode->value.var = malloc(sizeof(struct variable));
				tmpnode->value.var->name = malloc((strlen(Lex_string) + 1) * sizeof(char));
				strcpy(tmpnode->value.var->name, Lex_string);
				(yyval.expression) = (struct expr *)malloc(sizeof(struct expr));
				(yyval.expression) = new_expr(conststring_e,tmpnode,NULL,0,Lex_string,'\0',NULL);
			}
#line 2943 "y.tab.c"
    break;

  case 87:
#line 1153 "syntax.y"
    { (yyval.expression) = new_expr(nil_e,nil_expr_sym,NULL,0,"",'\0',NULL); }
#line 2949 "y.tab.c"
    break;

  case 88:
#line 1154 "syntax.y"
    { (yyval.expression) = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );  }
#line 2955 "y.tab.c"
    break;

  case 89:
#line 1155 "syntax.y"
    { (yyval.expression) = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL ); }
#line 2961 "y.tab.c"
    break;

  case 90:
#line 1158 "syntax.y"
    {
     					result = malloc(50 * sizeof(char)); sprintf(result,"%0.f", ((yyvsp[0].intValue)));

    					struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
    					newnode->value.var = malloc(sizeof(struct variable));
    					newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
    					strcpy(newnode->value.var->name, result);
    					(yyval.expression) = (struct expr *)malloc(sizeof(struct expr));
    					(yyval.expression) = new_expr(const_num_e,newnode,NULL,((yyvsp[0].intValue)),"",'\0',NULL);
    					printf("%f\n",(yyvsp[0].intValue) );
    					printf("%f\n",((yyval.expression))->numconst );
					}
#line 2978 "y.tab.c"
    break;

  case 91:
#line 1170 "syntax.y"
    {
			            result = malloc(50 * sizeof(char)); sprintf(result,"%f", ((yyvsp[0].floatValue)));
			            struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
			            newnode->value.var = malloc(sizeof(struct variable));
			            newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
			            strcpy(newnode->value.var->name, result);
			            (yyval.expression) = (struct expr *)malloc(sizeof(struct expr));
			            (yyval.expression) = new_expr(const_num_e,newnode,NULL,((yyvsp[0].floatValue)),"",'\0',NULL);
			            printf("%f\n",(yyvsp[0].floatValue) );
					}
#line 2993 "y.tab.c"
    break;

  case 92:
#line 1182 "syntax.y"
    { argumentF( (yyvsp[0].stringValue), yylineno, (scope + 1)); }
#line 2999 "y.tab.c"
    break;

  case 94:
#line 1183 "syntax.y"
    { printf(RED "idlist:: empty\n" RESET); }
#line 3005 "y.tab.c"
    break;

  case 95:
#line 1186 "syntax.y"
    { argumentF(((yyvsp[0].stringValue)), yylineno, (scope+1)); }
#line 3011 "y.tab.c"
    break;

  case 97:
#line 1187 "syntax.y"
    { printf(RED "multi_idlists:: empty\n" RESET); }
#line 3017 "y.tab.c"
    break;

  case 98:
#line 1190 "syntax.y"
    {

				emit(jump,NULL,NULL,NULL,yylineno,999); /*Sto telos tis else*/
				//Kanoume patch to jump mesa stin else se periptosi pou apotixei i if
				quads[((int)(yyvsp[-3].intValue))].label=QuadNo+1;
				//Pername stin tmp mas to quad no tis kainourgias jump ekso apo tin else
				(yyvsp[-3].intValue)=QuadNo-1;

			}
#line 3031 "y.tab.c"
    break;

  case 99:
#line 1198 "syntax.y"
    {
				//Pigenoume sto quad tis jump pano apo tin else kai kanoume patch to label sto quad kato apo tin
   			 	//teleftaia entoli toy stmt tis else !!!
				printf(RED "if(exprsession) stmt else stmt\n" RESET);
				quads[((int)(yyvsp[-5].intValue))].label=QuadNo+1;
	}
#line 3042 "y.tab.c"
    break;

  case 100:
#line 1204 "syntax.y"
    {
			 printf(RED "if(exprsession) stmt\n" RESET);
			 //Pigenoume sto quad tis jump kai kanoume patch to label sto quad kato apo tin
			 //teleftaia entoli toy stmt !!!
			 quads[((int)(yyvsp[-2].intValue))].label=QuadNo+1;
	}
#line 3053 "y.tab.c"
    break;

  case 101:
#line 1212 "syntax.y"
    {
				struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
				emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tou if
				emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis if
				//Pername sto if_start to index tou quad tis jump
				(yyval.intValue)=QuadNo-1;
			}
#line 3065 "y.tab.c"
    break;

  case 102:
#line 1221 "syntax.y"
    {
					insideLoop--;
					emit(jump,NULL,NULL,NULL,yylineno,(yyvsp[-2].intValue)); //$1 quadno stin arxi tou sxpr tis while
					quads[((int)(yyvsp[-1].intValue))].label=QuadNo+1;
					printf(RED "while(expr) stmt\n" RESET);
					patchFlow((yyvsp[-2].intValue),QuadNo+1);
			}
#line 3077 "y.tab.c"
    break;

  case 103:
#line 1229 "syntax.y"
    {(yyval.intValue)=QuadNo+1;}
#line 3083 "y.tab.c"
    break;

  case 104:
#line 1232 "syntax.y"
    { insideLoop++; }
#line 3089 "y.tab.c"
    break;

  case 105:
#line 1232 "syntax.y"
    {

						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tis while
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis while
						printf("quadno%d\n",(int)QuadNo );

						}
#line 3102 "y.tab.c"
    break;

  case 106:
#line 1240 "syntax.y"
    {(yyval.intValue)=QuadNo-1;
            }
#line 3109 "y.tab.c"
    break;

  case 107:
#line 1257 "syntax.y"
    { insideLoop++; }
#line 3115 "y.tab.c"
    break;

  case 108:
#line 1257 "syntax.y"
    {

				printf(RED "for(elist; expr;elist) stmt\n" RESET);
				insideLoop--;
				printf("for elist %d for cond %d for end%d\n",(int)(yyvsp[-6].intValue),(int)(yyvsp[-4].intValue) , (int)(yyvsp[-2].intValue) );
				emit(jump,NULL,NULL,NULL,yylineno,(yyvsp[-4].intValue)+1); /*jump stin arxi tou 2ou elist*/
				quads[(int)(yyvsp[-4].intValue)-1].label=QuadNo+1; /*gia to jump sto telos tou for */
				quads[(int)(yyvsp[-4].intValue)-2].label=(yyvsp[-2].intValue)+1; /*if_eq jump arxi for*/
				quads[(int)(yyvsp[-2].intValue)-1].label=(yyvsp[-6].intValue)+1; /*gia jump sto cond tis for*/

				patchFlow((int)(yyvsp[-4].intValue)+1,(int)QuadNo+1);

			}
#line 3133 "y.tab.c"
    break;

  case 109:
#line 1273 "syntax.y"
    {printf(RED "for_elist:: \n" RESET); (yyval.intValue)=QuadNo;  }
#line 3139 "y.tab.c"
    break;

  case 110:
#line 1274 "syntax.y"
    { printf(RED "for_elist:: empty\n" RESET); }
#line 3145 "y.tab.c"
    break;

  case 111:
#line 1278 "syntax.y"
    {
						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,(yyvsp[0].expression),true_expr,NULL,yylineno,999); // jump stin arxi tis for
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis for
						(yyval.intValue)=QuadNo;
					}
#line 3156 "y.tab.c"
    break;

  case 112:
#line 1285 "syntax.y"
    {

                  emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika stin arxi tis for
                  (yyval.intValue)=QuadNo;
	      }
#line 3166 "y.tab.c"
    break;

  case 113:
#line 1291 "syntax.y"
    {
					printf(RED "return expression; \n" RESET);
					emit(ret,NULL,NULL,(yyvsp[-1].expression),yylineno,0);
					emit(jump,NULL,NULL,NULL,yylineno,999);//end of func
				}
#line 3176 "y.tab.c"
    break;

  case 114:
#line 1296 "syntax.y"
    {
                        printf(RED "return; \n" RESET);
                        emit(ret,NULL,NULL,NULL,yylineno,0);
                        emit(jump,NULL,NULL,NULL,yylineno,999);//end of func
                  }
#line 3186 "y.tab.c"
    break;


#line 3190 "y.tab.c"

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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 1303 "syntax.y"

