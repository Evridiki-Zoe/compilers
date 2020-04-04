/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     IDENTIFIER = 302
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




/* Copy the first part of user declarations.  */
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

extern int yylineno;
extern char * yytext;
extern int scope;
extern int maxScope;
int ref = 1;
int args = 0;
char *result;
int unnamedFuncs = 0;
int rvalues = 0;

int insideLoop = 0;
int insideFunc = 0;
int arrayFlag;

char** table;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 88 "syntax.y"
{
    double intValue;
    float floatValue;
    char *stringValue;
	struct expr* expression;
}
/* Line 193 of yacc.c.  */
#line 231 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 244 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   573

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  187

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    14,    16,    18,
      20,    23,    26,    28,    30,    32,    34,    38,    42,    46,
      50,    54,    58,    62,    66,    70,    74,    78,    82,    86,
      88,    92,    95,    98,   101,   102,   106,   109,   110,   114,
     116,   117,   122,   124,   126,   128,   132,   134,   136,   139,
     142,   144,   148,   153,   157,   162,   167,   170,   177,   181,
     187,   190,   191,   195,   196,   200,   204,   207,   211,   212,
     218,   219,   224,   225,   226,   234,   235,   236,   237,   247,
     249,   251,   253,   255,   257,   259,   261,   262,   266,   267,
     268,   273,   274,   282,   288,   289,   296,   297,   308,   312
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    51,    50,    -1,    -1,    52,
      32,    -1,    83,    -1,    84,    -1,    86,    -1,    88,    -1,
       9,    32,    -1,    10,    32,    -1,    69,    -1,    71,    -1,
      32,    -1,    56,    -1,    52,    19,    52,    -1,    52,    20,
      52,    -1,    52,    21,    52,    -1,    52,    22,    52,    -1,
      52,    23,    52,    -1,    52,    28,    52,    -1,    52,    30,
      52,    -1,    52,    29,    52,    -1,    52,    31,    52,    -1,
      52,    24,    52,    -1,    52,    25,    52,    -1,    52,    11,
      52,    -1,    52,    13,    52,    -1,    53,    -1,    42,    52,
      43,    -1,    20,    52,    -1,    12,    52,    -1,    26,    59,
      -1,    -1,    59,    54,    26,    -1,    27,    59,    -1,    -1,
      59,    55,    27,    -1,    58,    -1,    -1,    59,    57,    18,
      52,    -1,    59,    -1,    61,    -1,    65,    -1,    42,    71,
      43,    -1,    77,    -1,    47,    -1,    14,    47,    -1,    35,
      47,    -1,    60,    -1,    59,    36,    47,    -1,    59,    40,
      52,    41,    -1,    61,    36,    47,    -1,    61,    40,    52,
      41,    -1,    61,    42,    63,    43,    -1,    59,    62,    -1,
      42,    71,    43,    42,    63,    43,    -1,    42,    63,    43,
      -1,    37,    47,    42,    63,    43,    -1,    52,    64,    -1,
      -1,    33,    52,    64,    -1,    -1,    40,    63,    41,    -1,
      40,    66,    41,    -1,    68,    67,    -1,    33,    68,    67,
      -1,    -1,    38,    52,    34,    52,    39,    -1,    -1,    38,
      70,    50,    39,    -1,    -1,    -1,     7,    42,    72,    79,
      43,    73,    69,    -1,    -1,    -1,    -1,     7,    47,    74,
      42,    75,    79,    43,    76,    69,    -1,    78,    -1,    46,
      -1,    17,    -1,    15,    -1,    16,    -1,    44,    -1,    45,
      -1,    -1,    47,    80,    81,    -1,    -1,    -1,    33,    47,
      82,    81,    -1,    -1,     3,    42,    52,    43,    51,     4,
      51,    -1,     3,    42,    52,    43,    51,    -1,    -1,     5,
      42,    85,    52,    43,    51,    -1,    -1,     6,    42,    87,
      63,    32,    52,    32,    63,    43,    51,    -1,     8,    52,
      32,    -1,     8,    32,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   120,   121,   124,   125,   126,   127,   128,
     135,   142,   149,   150,   151,   154,   155,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     175,   176,   177,   178,   179,   179,   180,   181,   181,   182,
     185,   185,   188,   189,   190,   191,   192,   195,   196,   197,
     202,   205,   206,   207,   208,   211,   212,   213,   216,   217,
     220,   221,   224,   225,   229,   230,   233,   236,   237,   240,
     243,   243,   246,   247,   246,   248,   248,   248,   248,   253,
     254,   255,   260,   264,   270,   277,   280,   280,   281,   284,
     284,   285,   288,   289,   292,   292,   295,   295,   298,   299
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "R_PARENTHES", "INTEGER", "FLOAT", "STRING", "IDENTIFIER", "$accept",
  "program", "multi_stmts", "stmt", "expr", "term", "@1", "@2",
  "assignmexpr", "@3", "primary", "lvalue", "member", "call", "callsuffix",
  "elist", "multi_exprs", "objectdef", "indexed", "multi_indexedelem",
  "indexedelem", "block", "@4", "funcdef", "@5", "@6", "@7", "@8", "@9",
  "const", "number", "idlist", "@10", "multi_id", "@11", "ifstmt",
  "whilestmt", "@12", "forstmt", "@13", "returnstmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    53,    53,    53,    54,    53,    53,    55,    53,    53,
      57,    56,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    60,    60,    60,    60,    61,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    66,    67,    67,    68,
      70,    69,    72,    73,    71,    74,    75,    76,    71,    77,
      77,    77,    77,    77,    78,    78,    80,    79,    79,    82,
      81,    81,    83,    83,    85,    84,    87,    86,    88,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     0,     3,     2,     0,     3,     1,
       0,     4,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     2,     6,     3,     5,
       2,     0,     3,     0,     3,     3,     2,     3,     0,     5,
       0,     4,     0,     0,     7,     0,     0,     0,     9,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     0,     0,
       4,     0,     7,     5,     0,     6,     0,    10,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,    83,    81,     0,     0,     0,    14,     0,    70,    61,
       0,    84,    85,    80,    47,     0,     2,     4,     0,    29,
      15,    39,    42,    50,    43,    44,    12,    13,    46,    79,
       6,     7,     8,     9,     0,    94,    96,    72,    75,    99,
       0,    10,    11,    32,    48,    31,     0,    33,     0,    36,
      49,     4,     0,    63,     0,     0,    68,     0,     0,     1,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     0,     0,     0,    61,     0,
       0,     0,    56,     0,     0,    61,     0,     0,    61,    88,
       0,    98,     0,     0,     0,     0,    60,    64,    65,     0,
      66,    30,    45,    27,    28,    16,    17,    18,    19,    20,
      25,    26,    21,    23,    22,    24,    51,     0,     0,     0,
      35,    38,     0,    53,     0,     0,     0,     0,     0,    86,
       0,    76,     0,    71,     0,    63,    68,    61,    61,    52,
      58,    41,    54,    55,    93,     0,     0,    91,    73,    88,
       0,    62,    67,     0,     0,     0,    95,     0,     0,    87,
       0,     0,    69,    57,    59,    92,    61,    89,    74,    77,
       0,    91,     0,     0,    90,    78,    97
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    89,    90,    30,    91,
      31,    32,    33,    34,    92,    64,   106,    35,    65,   110,
      66,    36,    61,    37,    99,   170,   100,   159,   182,    38,
      39,   140,   157,   169,   181,    40,    41,    97,    42,    98,
      43
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -166
static const yytype_int16 yypact[] =
{
     114,   -33,   -32,   -20,   -36,   186,    -8,    -6,   258,   -18,
    -166,  -166,  -166,   258,    -7,    -7,  -166,     3,  -166,   222,
     150,  -166,  -166,  -166,  -166,    61,  -166,   114,   450,  -166,
    -166,  -166,    69,  -166,   -17,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,   258,  -166,  -166,  -166,  -166,  -166,
     472,  -166,  -166,  -166,  -166,    37,    34,   -24,   -17,   -24,
    -166,   114,   258,   429,    21,    22,    32,   288,    38,  -166,
    -166,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,  -166,    39,    44,   258,   258,    58,
      67,    70,  -166,    50,   258,   258,   313,   258,   258,    51,
      43,  -166,    56,    62,   407,   258,  -166,  -166,  -166,    64,
    -166,  -166,    65,   529,   529,    37,    37,  -166,  -166,  -166,
     542,   542,   224,   224,   224,   224,  -166,    68,    23,    60,
    -166,  -166,   258,  -166,   363,    71,   114,   338,    72,  -166,
      73,  -166,    65,  -166,   258,   429,    32,   258,   258,  -166,
    -166,   516,  -166,  -166,   108,   114,   258,    80,  -166,    51,
     386,  -166,  -166,    75,    82,   114,  -166,   494,    85,  -166,
      77,    90,  -166,  -166,  -166,  -166,   258,  -166,  -166,  -166,
      92,    80,    77,   114,  -166,  -166,  -166
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,   -23,  -134,    -5,  -166,  -166,  -166,  -166,  -166,
    -166,    18,  -166,    41,  -166,   -68,    -9,  -166,  -166,    -2,
      28,  -165,  -166,   -19,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,   -21,  -166,   -34,  -166,  -166,  -166,  -166,  -166,  -166,
    -166
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -41
static const yytype_int16 yytable[] =
{
      50,    68,   154,    53,    70,   178,    47,     9,    55,    44,
      45,    48,    85,    86,    63,    67,    87,   185,    88,    93,
     129,   166,    46,    94,    51,    95,    52,   135,    17,    54,
     138,   175,    57,    59,    71,    56,    72,   102,   103,    96,
      24,     4,    73,    74,    75,    76,    77,    78,    79,   186,
      60,    80,    81,    82,    83,    58,    58,   104,    75,    76,
      77,    69,   107,   108,   149,   109,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   163,
     164,   112,   128,    63,   130,   141,   126,   -40,   132,   134,
      63,   127,   137,    63,   131,   -34,   -37,   133,   139,   142,
     145,   143,    62,   150,   156,    85,    86,   147,   180,    87,
     148,    88,   165,   168,   153,    18,   158,     1,   173,     2,
       3,     4,     5,     6,     7,   174,     8,   151,     9,    10,
      11,    12,   177,   179,    13,   183,   161,   146,   171,   160,
      14,    15,    63,    63,   162,     0,    16,   184,     0,    17,
       0,   167,    18,     0,    19,     0,    20,     4,    21,    22,
      23,    24,     8,     0,     9,    10,    11,    12,     0,     0,
      13,    63,     0,     0,     0,     0,    14,    15,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,     0,     0,
      19,     0,    20,     0,    21,    22,    23,    24,     8,     0,
       9,    10,    11,    12,     0,     0,    13,     0,     0,     0,
       0,     0,    14,    15,     0,     0,     0,     0,    49,     0,
       0,    17,     0,     0,     0,     0,    19,     0,    20,     0,
      21,    22,    23,    24,     8,     0,     9,    10,    11,    12,
       0,     0,    13,    73,    74,    75,    76,    77,    14,    15,
       0,     0,   -41,   -41,   -41,   -41,     0,    17,     0,     0,
      62,     0,    19,     0,    20,     0,    21,    22,    23,    24,
       8,     0,     9,    10,    11,    12,     0,     0,    13,     0,
       0,     0,     0,     0,    14,    15,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,    19,    71,
      20,    72,    21,    22,    23,    24,     0,    73,    74,    75,
      76,    77,    78,    79,     0,     0,    80,    81,    82,    83,
       0,     0,     0,     0,    71,     0,    72,     0,     0,     0,
       0,   111,    73,    74,    75,    76,    77,    78,    79,     0,
       0,    80,    81,    82,    83,     0,     0,     0,     0,    71,
       0,    72,     0,     0,     0,     0,   136,    73,    74,    75,
      76,    77,    78,    79,     0,     0,    80,    81,    82,    83,
       0,     0,     0,     0,    71,     0,    72,     0,     0,     0,
       0,   155,    73,    74,    75,    76,    77,    78,    79,     0,
       0,    80,    81,    82,    83,     0,     0,    71,     0,    72,
       0,     0,     0,     0,   152,    73,    74,    75,    76,    77,
      78,    79,     0,     0,    80,    81,    82,    83,    71,     0,
      72,     0,     0,     0,     0,   172,    73,    74,    75,    76,
      77,    78,    79,     0,     0,    80,    81,    82,    83,     0,
      71,   144,    72,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,    79,     0,     0,    80,    81,    82,
      83,    71,   105,    72,     0,     0,     0,     0,     0,    73,
      74,    75,    76,    77,    78,    79,     0,     0,    80,    81,
      82,    83,    84,    71,     0,    72,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    78,    79,     0,     0,
      80,    81,    82,    83,   101,    71,     0,    72,     0,     0,
       0,     0,     0,    73,    74,    75,    76,    77,    78,    79,
       0,     0,    80,    81,    82,    83,   176,    71,     0,    72,
       0,     0,     0,     0,     0,    73,    74,    75,    76,    77,
      78,    79,     0,     0,    80,    81,    82,    83,    73,    74,
      75,    76,    77,    78,    79,     0,     0,    80,    81,    82,
      83,    73,    74,    75,    76,    77,   -41,   -41,     0,     0,
      80,    81,    82,    83
};

static const yytype_int16 yycheck[] =
{
       5,    20,   136,     8,    27,   170,    42,    14,    13,    42,
      42,    47,    36,    37,    19,    20,    40,   182,    42,    36,
      88,   155,    42,    40,    32,    42,    32,    95,    35,    47,
      98,   165,    14,    15,    11,    42,    13,    56,    61,    44,
      47,     7,    19,    20,    21,    22,    23,    24,    25,   183,
      47,    28,    29,    30,    31,    14,    15,    62,    21,    22,
      23,     0,    41,    41,    41,    33,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,   147,
     148,    43,    87,    88,    26,    42,    47,    18,    18,    94,
      95,    47,    97,    98,    27,    26,    27,    47,    47,    43,
     105,    39,    38,    43,    32,    36,    37,    42,   176,    40,
      42,    42,     4,    33,    43,    38,    43,     3,    43,     5,
       6,     7,     8,     9,    10,    43,    12,   132,    14,    15,
      16,    17,    47,    43,    20,    43,   145,   109,   159,   144,
      26,    27,   147,   148,   146,    -1,    32,   181,    -1,    35,
      -1,   156,    38,    -1,    40,    -1,    42,     7,    44,    45,
      46,    47,    12,    -1,    14,    15,    16,    17,    -1,    -1,
      20,   176,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      40,    -1,    42,    -1,    44,    45,    46,    47,    12,    -1,
      14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    40,    -1,    42,    -1,
      44,    45,    46,    47,    12,    -1,    14,    15,    16,    17,
      -1,    -1,    20,    19,    20,    21,    22,    23,    26,    27,
      -1,    -1,    28,    29,    30,    31,    -1,    35,    -1,    -1,
      38,    -1,    40,    -1,    42,    -1,    44,    45,    46,    47,
      12,    -1,    14,    15,    16,    17,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    40,    11,
      42,    13,    44,    45,    46,    47,    -1,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    11,    -1,    13,    -1,    -1,    -1,
      -1,    43,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    11,
      -1,    13,    -1,    -1,    -1,    -1,    43,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    11,    -1,    13,    -1,    -1,    -1,
      -1,    43,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    -1,    -1,    11,    -1,    13,
      -1,    -1,    -1,    -1,    41,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    11,    -1,
      13,    -1,    -1,    -1,    -1,    39,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      11,    34,    13,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    11,    33,    13,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    32,    11,    -1,    13,    -1,    -1,    -1,    -1,
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
       0,     3,     5,     6,     7,     8,     9,    10,    12,    14,
      15,    16,    17,    20,    26,    27,    32,    35,    38,    40,
      42,    44,    45,    46,    47,    49,    50,    51,    52,    53,
      56,    58,    59,    60,    61,    65,    69,    71,    77,    78,
      83,    84,    86,    88,    42,    42,    42,    42,    47,    32,
      52,    32,    32,    52,    47,    52,    42,    59,    61,    59,
      47,    70,    38,    52,    63,    66,    68,    52,    71,     0,
      50,    11,    13,    19,    20,    21,    22,    23,    24,    25,
      28,    29,    30,    31,    32,    36,    37,    40,    42,    54,
      55,    57,    62,    36,    40,    42,    52,    85,    87,    72,
      74,    32,    71,    50,    52,    33,    64,    41,    41,    33,
      67,    43,    43,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    47,    47,    52,    63,
      26,    27,    18,    47,    52,    63,    43,    52,    63,    47,
      79,    42,    43,    39,    34,    52,    68,    42,    42,    41,
      43,    52,    41,    43,    51,    43,    32,    80,    43,    75,
      52,    64,    67,    63,    63,     4,    51,    52,    33,    81,
      73,    79,    39,    43,    43,    51,    32,    47,    69,    43,
      63,    82,    76,    43,    81,    69,    51
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 120 "syntax.y"
    { printf(RED "stmt multi_stmt\n" RESET);}
    break;

  case 4:
#line 121 "syntax.y"
    {printf(RED "multi_stmts empty\n" RESET);}
    break;

  case 5:
#line 124 "syntax.y"
    { printf(RED "expression \n" RESET); }
    break;

  case 6:
#line 125 "syntax.y"
    { printf(RED "if stmt \n" RESET); }
    break;

  case 7:
#line 126 "syntax.y"
    { printf(RED "while stmt \n" RESET); }
    break;

  case 8:
#line 127 "syntax.y"
    { printf(RED "for stmt \n" RESET); }
    break;

  case 9:
#line 128 "syntax.y"
    { printf(RED "return stmt \n" RESET);
                              if( insideFunc > 0) {
                                    // ok
                              } else {
                                    printf("Error: RETURN STMT outside of function in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              } }
    break;

  case 10:
#line 135 "syntax.y"
    { printf(RED "break \n" RESET);
                              if( insideLoop > 0) {
                              // ok
                              } else {
                                    printf("Error: BREAK STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              } }
    break;

  case 11:
#line 142 "syntax.y"
    { printf(RED "continue \n" RESET);
                              if( insideLoop > 0) {
                              // ok
                              } else {
                                    printf("Error: CONTINUE STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              } }
    break;

  case 12:
#line 149 "syntax.y"
    { printf(RED "block \n" RESET);}
    break;

  case 13:
#line 150 "syntax.y"
    { printf(RED "funcdef \n" RESET);}
    break;

  case 14:
#line 151 "syntax.y"
    { printf(RED "semicolon \n" RESET);}
    break;

  case 15:
#line 154 "syntax.y"
    { printf(RED "ASSIGNMENT \n" RESET);}
    break;

  case 16:
#line 155 "syntax.y"
    {
		  	   
			   emit(add,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression),(yyval.expression),yylineno,0);

              }
    break;

  case 17:
#line 160 "syntax.y"
    { printf(RED "expr - expr \n" RESET);}
    break;

  case 18:
#line 161 "syntax.y"
    { printf(RED "expr * expr \n" RESET);}
    break;

  case 19:
#line 162 "syntax.y"
    { printf(RED "expr / expr \n" RESET);}
    break;

  case 20:
#line 163 "syntax.y"
    { printf(RED "expr mod expr \n" RESET);}
    break;

  case 21:
#line 164 "syntax.y"
    { printf(RED "expr > expr \n" RESET);}
    break;

  case 22:
#line 165 "syntax.y"
    { printf(RED "expr >= expr \n" RESET);}
    break;

  case 23:
#line 166 "syntax.y"
    { printf(RED "expr < expr \n" RESET);}
    break;

  case 24:
#line 167 "syntax.y"
    { printf(RED "expr < = expr \n" RESET);}
    break;

  case 25:
#line 168 "syntax.y"
    { printf(RED "expr == expr \n" RESET);}
    break;

  case 26:
#line 169 "syntax.y"
    { printf(RED "expr != expr \n" RESET);}
    break;

  case 27:
#line 170 "syntax.y"
    { printf(RED "expr and expr \n" RESET);}
    break;

  case 28:
#line 171 "syntax.y"
    { printf(RED "expr or expr \n" RESET);}
    break;

  case 29:
#line 172 "syntax.y"
    { printf(RED "TERM \n" RESET); (yyval.expression)=(yyvsp[(1) - (1)].expression); }
    break;

  case 30:
#line 175 "syntax.y"
    { printf(RED " (expression) \n" RESET); }
    break;

  case 31:
#line 176 "syntax.y"
    { printf(RED " - expression \n" RESET); }
    break;

  case 32:
#line 177 "syntax.y"
    { printf(RED "NOT expression\n" RESET); }
    break;

  case 33:
#line 178 "syntax.y"
    { check_for_funcname(yylval.stringValue); }
    break;

  case 34:
#line 179 "syntax.y"
    { check_for_funcname(yylval.stringValue); }
    break;

  case 35:
#line 179 "syntax.y"
    { printf(RED "lvalue++\n" RESET); }
    break;

  case 36:
#line 180 "syntax.y"
    { check_for_funcname(yylval.stringValue); printf(RED "--lvalue\n" RESET); }
    break;

  case 37:
#line 181 "syntax.y"
    { check_for_funcname(yylval.stringValue);  }
    break;

  case 38:
#line 181 "syntax.y"
    { printf(RED "lvalue--\n" RESET); }
    break;

  case 39:
#line 182 "syntax.y"
    { printf(RED "primary\n" RESET); (yyval.expression)=(yyvsp[(1) - (1)].expression); }
    break;

  case 40:
#line 185 "syntax.y"
    { if(!arrayFlag && ref) check_for_funcname(yylval.stringValue);  }
    break;

  case 41:
#line 185 "syntax.y"
    { printf(RED "lvalue = expression\n" RESET); arrayFlag = 0; ref = 1;}
    break;

  case 42:
#line 188 "syntax.y"
    { printf(RED "primary:: lvalue \n" RESET);  }
    break;

  case 43:
#line 189 "syntax.y"
    { printf(RED "primary:: call\n" RESET); }
    break;

  case 44:
#line 190 "syntax.y"
    { printf(RED "primary:: objectdef\n" RESET); }
    break;

  case 45:
#line 191 "syntax.y"
    { printf(RED "primary:: (funcdef)\n" RESET); }
    break;

  case 46:
#line 192 "syntax.y"
    { printf(RED "primary:: const\n" RESET);  (yyval.expression)=(yyvsp[(1) - (1)].expression); }
    break;

  case 47:
#line 195 "syntax.y"
    { printf(RED "lvalue:: id\n" RESET); insertVar( yylval.stringValue, yylineno, scope);  }
    break;

  case 48:
#line 196 "syntax.y"
    { localVar( yylval.stringValue, yylineno, scope); printf(RED "lvalue:: local identifier\n" RESET); }
    break;

  case 49:
#line 197 "syntax.y"
    { if(global_exists((yyvsp[(2) - (2)].stringValue)) == 0) {
                  printf("\"%s\" undeclared, (first use here), line: %d\n", (yyvsp[(2) - (2)].stringValue), yylineno); \
                  exit(EXIT_FAILURE);
            }
            printf( RED "lvalue:: doublecolon\n" RESET);}
    break;

  case 50:
#line 202 "syntax.y"
    { printf(RED "lvalue:: member\n" RESET); }
    break;

  case 51:
#line 205 "syntax.y"
    { printf(RED "member:: lvalue.id \n" RESET); }
    break;

  case 52:
#line 206 "syntax.y"
    { arrayFlag = 1; printf(RED "member:: lvalue[expression]\n" RESET); }
    break;

  case 53:
#line 207 "syntax.y"
    { printf(RED "member:: call.id\n" RESET); }
    break;

  case 54:
#line 208 "syntax.y"
    { arrayFlag = 1; printf(RED "member:: call[expression]\n" RESET); }
    break;

  case 55:
#line 211 "syntax.y"
    { printf(RED "call:: call (elist)\n" RESET); }
    break;

  case 56:
#line 212 "syntax.y"
    { check_if_exists( (yyvsp[(1) - (2)].stringValue), scope); printf(RED "call:: lvalue callsuffix\n" RESET); }
    break;

  case 57:
#line 213 "syntax.y"
    { printf(RED "call:: (funcdef)(elist)\n" RESET); }
    break;

  case 58:
#line 216 "syntax.y"
    { printf(RED "callsuffix:: (elist)\n" RESET); }
    break;

  case 59:
#line 217 "syntax.y"
    { printf(RED "callsuffix:: ..id(elist)\n" RESET); }
    break;

  case 60:
#line 220 "syntax.y"
    { args++; printf(RED "elist:: \n" RESET); }
    break;

  case 61:
#line 221 "syntax.y"
    { printf(RED "elist:: empty\n" RESET); args = 0; }
    break;

  case 62:
#line 224 "syntax.y"
    { args++; printf(RED "multiexpr commma expr exprs\n" RESET); }
    break;

  case 63:
#line 225 "syntax.y"
    { printf(RED "multi exprsessions: empty\n" RESET); }
    break;

  case 64:
#line 229 "syntax.y"
    { printf(RED "objectdef:: elist\n" RESET); }
    break;

  case 65:
#line 230 "syntax.y"
    { printf(RED "objectdef:: indexed\n" RESET); }
    break;

  case 66:
#line 233 "syntax.y"
    { printf(RED "indexed:: indexedelement multi\n" RESET); }
    break;

  case 67:
#line 236 "syntax.y"
    { printf(RED "multi_indexedelem:: comma indelem multi\n" RESET); }
    break;

  case 68:
#line 237 "syntax.y"
    { printf(RED "multi_indexedelem:: empty\n" RESET); }
    break;

  case 69:
#line 240 "syntax.y"
    { printf(RED "ind elem {expr:expr}\n" RESET); }
    break;

  case 70:
#line 243 "syntax.y"
    { scope++; if(scope > maxScope) maxScope = scope; }
    break;

  case 71:
#line 243 "syntax.y"
    {hide_symbols(scope); scope--;  printf( RED "block:: {stmt multi stmt}\n" RESET ); }
    break;

  case 72:
#line 246 "syntax.y"
    { insideFunc++; result = malloc(2 * sizeof(char)); sprintf(result, "^%d", unnamedFuncs++); newFunction(result, yylineno, scope);
      free(result); }
    break;

  case 73:
#line 247 "syntax.y"
    { make_not_accessible(scope+1); }
    break;

  case 74:
#line 247 "syntax.y"
    { make_accessible_again(scope+1); insideFunc--; }
    break;

  case 75:
#line 248 "syntax.y"
    { newFunction( (yyvsp[(2) - (2)].stringValue), yylineno, scope); }
    break;

  case 76:
#line 248 "syntax.y"
    { insideFunc++;}
    break;

  case 77:
#line 248 "syntax.y"
    { make_not_accessible(scope+1); }
    break;

  case 78:
#line 248 "syntax.y"
    { make_accessible_again(scope+1); insideFunc--; }
    break;

  case 79:
#line 253 "syntax.y"
    {		(yyval.expression)=(yyvsp[(1) - (1)].expression);	}
    break;

  case 80:
#line 254 "syntax.y"
    { /*printf("STRINGGG %s \n",yylval.stringValue );*/ insert_rvalue_list(yylval.stringValue ,1); }
    break;

  case 81:
#line 255 "syntax.y"
    {
			// insert_rvalue_list("nil" ,2);
			 result = malloc(2 * sizeof(char));  sprintf(result, "_%d", rvalues++); struct symbol_table_binding* tmp=  insertVar(result ,  yylineno , scope);

		  }
    break;

  case 82:
#line 260 "syntax.y"
    {
			 // insert_rvalue_list("true" ,2);
			 result = malloc(2 * sizeof(char));  sprintf(result, "_%d", rvalues++);  struct symbol_table_binding* tmp= insertVar(result ,  yylineno , scope);
		 }
    break;

  case 83:
#line 264 "syntax.y"
    {
			  //insert_rvalue_list("false" ,2);
			  result = malloc(2 * sizeof(char));  sprintf(result, "_%d", rvalues++); struct symbol_table_binding* tmp=  insertVar(result ,  yylineno , scope);
		  }
    break;

  case 84:
#line 270 "syntax.y"
    { result = malloc(2 * sizeof(char));  sprintf(result, "_%d", rvalues++);
 					struct symbol_table_binding* tmp= insertVar(result ,  yylineno , scope);
					(yyval.expression) = (struct expr *)malloc(sizeof(struct expr));
					(yyval.expression) = new_expr(const_num_e,tmp,NULL,((yyvsp[(1) - (1)].intValue)),"",'\0',NULL);
					printf("%f\n",(yyvsp[(1) - (1)].intValue) );
					printf("%f\n",((yyval.expression))->numconst );
				}
    break;

  case 85:
#line 277 "syntax.y"
    { char buff[100]; sprintf(buff, "%f", yylval.floatValue); insert_rvalue_list( buff,0);   }
    break;

  case 86:
#line 280 "syntax.y"
    { argumentF( (yyvsp[(1) - (1)].stringValue), yylineno, (scope + 1)); }
    break;

  case 88:
#line 281 "syntax.y"
    { printf(RED "idlist:: empty\n" RESET); }
    break;

  case 89:
#line 284 "syntax.y"
    { argumentF(((yyvsp[(2) - (2)].stringValue)), yylineno, (scope+1)); }
    break;

  case 91:
#line 285 "syntax.y"
    { printf(RED "multi_idlists:: empty\n" RESET); }
    break;

  case 92:
#line 288 "syntax.y"
    { printf(RED "if(exprsession) stmt else stmt\n" RESET); }
    break;

  case 93:
#line 289 "syntax.y"
    { printf(RED "if(exprsession) stmt\n" RESET); }
    break;

  case 94:
#line 292 "syntax.y"
    { insideLoop++; }
    break;

  case 95:
#line 292 "syntax.y"
    { insideLoop--; printf(RED "while(expr) stmt\n" RESET); }
    break;

  case 96:
#line 295 "syntax.y"
    { insideLoop++; }
    break;

  case 97:
#line 295 "syntax.y"
    {printf(RED "for(elist; expr;elist) stmt\n" RESET); insideLoop--; }
    break;

  case 98:
#line 298 "syntax.y"
    {printf(RED "return expression; \n" RESET);}
    break;

  case 99:
#line 299 "syntax.y"
    { printf(RED "return; \n" RESET);}
    break;


/* Line 1267 of yacc.c.  */
#line 2204 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 302 "syntax.y"


