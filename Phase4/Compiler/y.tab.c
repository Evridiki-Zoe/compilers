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
#line 108 "syntax.y"
{
    double intValue;
    double floatValue;
    char *stringValue;
	struct expr* expression;
    struct call* callexpr;
}
/* Line 193 of yacc.c.  */
#line 253 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 266 "y.tab.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   481

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNRULES -- Number of states.  */
#define YYNSTATES  208

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

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
      45,    46,    47,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     7,    12,    13,    16,    18,
      20,    22,    24,    27,    30,    32,    34,    36,    38,    40,
      42,    43,    49,    50,    56,    59,    61,    62,    66,    70,
      74,    78,    82,    86,    90,    94,    98,   102,   106,   107,
     112,   115,   118,   121,   124,   127,   129,   130,   135,   137,
     139,   141,   145,   147,   149,   152,   155,   157,   161,   166,
     170,   175,   180,   183,   190,   192,   194,   198,   204,   207,
     208,   212,   213,   217,   218,   223,   226,   227,   231,   232,
     235,   239,   240,   241,   248,   249,   254,   255,   256,   265,
     267,   269,   270,   272,   274,   276,   278,   280,   282,   284,
     285,   289,   290,   291,   296,   297,   298,   305,   309,   313,
     317,   319,   320,   321,   327,   328,   329,   341,   344,   345,
     347,   349,   353
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    -1,    -1,    -1,    52,    54,    53,
      51,    -1,    -1,    55,    32,    -1,    95,    -1,    98,    -1,
     103,    -1,   109,    -1,     9,    32,    -1,    10,    32,    -1,
      82,    -1,    84,    -1,    32,    -1,    63,    -1,    60,    -1,
      59,    -1,    -1,    55,    11,    56,    58,    55,    -1,    -1,
      55,    13,    57,    58,    55,    -1,    12,    55,    -1,    61,
      -1,    -1,    55,    19,    55,    -1,    55,    20,    55,    -1,
      55,    21,    55,    -1,    55,    22,    55,    -1,    55,    23,
      55,    -1,    55,    28,    55,    -1,    55,    30,    55,    -1,
      55,    29,    55,    -1,    55,    31,    55,    -1,    55,    24,
      55,    -1,    55,    25,    55,    -1,    -1,    42,    62,    55,
      43,    -1,    20,    55,    -1,    26,    66,    -1,    66,    26,
      -1,    27,    66,    -1,    66,    27,    -1,    65,    -1,    -1,
      66,    64,    18,    55,    -1,    66,    -1,    68,    -1,    74,
      -1,    42,    84,    43,    -1,    89,    -1,    47,    -1,    14,
      47,    -1,    35,    47,    -1,    67,    -1,    66,    36,    47,
      -1,    66,    40,    55,    41,    -1,    68,    36,    47,    -1,
      68,    40,    55,    41,    -1,    68,    42,    72,    43,    -1,
      66,    69,    -1,    42,    84,    43,    42,    72,    43,    -1,
      70,    -1,    71,    -1,    42,    72,    43,    -1,    37,    47,
      42,    72,    43,    -1,    55,    73,    -1,    -1,    33,    55,
      73,    -1,    -1,    40,    76,    41,    -1,    -1,    40,    75,
      78,    41,    -1,    55,    77,    -1,    -1,    33,    55,    77,
      -1,    -1,    80,    79,    -1,    33,    80,    79,    -1,    -1,
      -1,    38,    55,    81,    34,    55,    39,    -1,    -1,    38,
      83,    51,    39,    -1,    -1,    -1,    87,    88,    42,    85,
      91,    43,    86,    82,    -1,     7,    -1,    47,    -1,    -1,
      90,    -1,    46,    -1,    17,    -1,    15,    -1,    16,    -1,
      44,    -1,    45,    -1,    -1,    47,    92,    93,    -1,    -1,
      -1,    33,    47,    94,    93,    -1,    -1,    -1,    97,    43,
      54,     4,    96,    54,    -1,    97,    43,    54,    -1,     3,
      42,    55,    -1,    99,   100,    54,    -1,     5,    -1,    -1,
      -1,    42,   101,    55,   102,    43,    -1,    -1,    -1,     6,
      42,   104,   106,   105,    32,   107,    32,   108,    43,    54,
      -1,    55,    73,    -1,    -1,    55,    -1,   106,    -1,     8,
      55,    32,    -1,     8,    32,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   140,   140,   143,   144,   143,   145,   148,   164,   165,
     166,   167,   178,   188,   197,   198,   199,   203,   224,   228,
     229,   229,   265,   265,   302,   334,   337,   340,   352,   362,
     372,   382,   395,   411,   426,   441,   456,   474,   499,   499,
     519,   532,   558,   590,   619,   652,   655,   655,   692,   698,
     701,   705,   706,   709,   717,   722,   732,   738,   741,   746,
     764,   785,   793,   806,   814,   818,   823,   833,   842,   870,
     877,   896,   905,   945,   945,   976,   993,  1001,  1020,  1029,
    1039,  1046,  1053,  1053,  1122,  1122,  1125,  1125,  1125,  1141,
    1144,  1153,  1166,  1167,  1175,  1176,  1177,  1180,  1192,  1205,
    1205,  1206,  1209,  1209,  1210,  1213,  1213,  1227,  1235,  1254,
    1262,  1265,  1265,  1265,  1289,  1289,  1289,  1304,  1305,  1309,
    1328,  1334,  1353
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
  "R_PARENTHES", "INTEGER", "FLOAT", "STRING", "IDENTIFIER", "UMINUS",
  "$accept", "program", "multi_stmts", "@1", "@2", "stmt", "expr", "@3",
  "@4", "epsilon", "arexpr", "boolResexpr", "term", "@5", "assignmexpr",
  "@6", "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "multi_exprs", "objectdef", "@7",
  "elist_for_table", "multi_exprs_for_table", "indexed",
  "multi_indexedelem", "indexedelem", "@8", "block", "@9", "funcdef",
  "@10", "@11", "funcstart", "funcname", "const", "number", "idlist",
  "@12", "multi_id", "@13", "ifstmt", "@14", "if_start", "whilestmt",
  "whilestart", "whilecond", "@15", "@16", "forstmt", "@17", "@18",
  "for_elist", "for_cond", "for_end", "returnstmt", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

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
      73,    73,    74,    75,    74,    76,    76,    77,    77,    78,
      79,    79,    81,    80,    83,    82,    85,    86,    84,    87,
      88,    88,    89,    89,    89,    89,    89,    90,    90,    92,
      91,    91,    94,    93,    93,    96,    95,    95,    97,    98,
      99,   101,   102,   100,   104,   105,   103,   106,   106,   107,
     108,   109,   109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     0,     4,     0,     2,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       0,     5,     0,     5,     2,     1,     0,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       2,     2,     2,     2,     2,     1,     0,     4,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     3,     4,     3,
       4,     4,     2,     6,     1,     1,     3,     5,     2,     0,
       3,     0,     3,     0,     4,     2,     0,     3,     0,     2,
       3,     0,     0,     6,     0,     4,     0,     0,     8,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     0,     0,     4,     0,     0,     6,     3,     3,     3,
       1,     0,     0,     5,     0,     0,    11,     2,     0,     1,
       1,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     0,     1,     0,   110,     0,    89,     0,
       0,     0,     0,     0,    95,    96,    94,     0,     0,     0,
      16,     0,    84,    73,    38,    97,    98,    93,    53,     4,
       0,    19,    18,    25,    17,    45,    48,    56,    49,    50,
      14,    15,    91,    52,    92,     8,     0,     9,     0,    10,
      11,     0,   114,   122,     0,    12,    13,    24,    54,    40,
       0,    41,     0,    43,    55,     3,    78,     0,     0,     0,
       0,     3,    20,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,    42,    44,     0,     0,
       0,    69,     0,    62,    64,    65,     0,     0,    69,    90,
       0,     0,   111,     0,   108,   118,   121,     0,     0,     0,
      75,     0,     0,    81,    72,     0,    51,     5,    26,    26,
      27,    28,    29,    30,    31,    36,    37,    32,    34,    33,
      35,    57,     0,     0,    71,     0,     0,    59,     0,     0,
      86,   107,     0,   109,    71,   115,     0,    85,    78,    82,
      74,     0,    79,    39,    69,     0,     0,    69,    58,     0,
      68,    66,    47,    60,    61,   101,   105,   112,   117,     0,
      77,     0,    81,     0,    21,    23,     0,    71,    99,     0,
       0,     0,     0,     0,    80,    63,    67,    70,   104,    87,
     106,   113,   119,     0,     0,     0,   100,     0,   118,    83,
     102,    88,   120,     0,   104,     0,   103,   116
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    71,    29,    30,   118,   119,   155,
      31,    32,    33,    69,    34,    92,    35,    36,    37,    38,
      93,    94,    95,   135,   160,    39,    67,    68,   110,   112,
     152,   113,   171,    40,    65,    41,   165,   197,    42,   100,
      43,    44,   179,   188,   196,   204,    45,   180,    46,    47,
      48,   103,   142,   181,    49,   105,   169,   145,   193,   203,
      50
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -132
static const yytype_int16 yypact[] =
{
       7,     9,  -132,   150,  -132,   -30,  -132,   -18,  -132,     3,
      -6,    -4,   186,   -16,  -132,  -132,  -132,   186,    -3,    -3,
    -132,   -14,  -132,    78,    27,  -132,  -132,  -132,  -132,  -132,
     365,  -132,  -132,  -132,  -132,  -132,   295,  -132,    15,  -132,
    -132,  -132,    12,  -132,  -132,  -132,    13,  -132,    22,  -132,
    -132,   186,  -132,  -132,   387,  -132,  -132,  -132,  -132,  -132,
      27,   -15,    15,   -15,  -132,    37,   323,    39,    38,   186,
      35,     1,  -132,  -132,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,  -132,  -132,  -132,    33,    40,
     186,   186,    66,  -132,  -132,  -132,    50,   186,   186,  -132,
      43,   150,  -132,   150,   409,   186,  -132,    48,    47,   186,
    -132,   186,    58,    68,  -132,   216,    61,  -132,  -132,  -132,
      31,    31,  -132,  -132,  -132,   437,   437,   109,   109,   109,
     109,  -132,    64,   241,   344,    67,   186,  -132,   264,    69,
    -132,   103,   186,  -132,   344,  -132,    61,  -132,   323,   409,
    -132,    39,  -132,  -132,   186,   186,   186,   186,  -132,   186,
    -132,  -132,   409,  -132,  -132,    62,  -132,   409,  -132,    79,
    -132,    80,    68,    72,   450,   424,    73,   344,  -132,    74,
     150,    83,   186,   186,  -132,  -132,  -132,  -132,    88,  -132,
    -132,  -132,   409,   102,   287,    89,  -132,    97,   186,  -132,
    -132,  -132,  -132,    98,    88,   150,  -132,  -132
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,   -55,  -132,  -132,   -97,    -9,  -132,  -132,    23,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,    18,  -132,    44,
    -132,  -132,  -132,   -96,  -131,  -132,  -132,  -132,    -5,  -132,
     -28,    -2,  -132,   -46,  -132,   -19,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,   -52,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,   -44,  -132,  -132,
    -132
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -77
static const yytype_int16 yytable[] =
{
      54,    -6,   139,    57,   141,    70,   143,    -6,    59,     4,
     108,    13,    51,   168,    66,    12,   117,    13,    14,    15,
      16,    88,    89,    17,    52,    90,    55,    91,    56,    18,
      19,    58,    21,    64,     8,    53,    61,    63,    21,    60,
      -6,   107,   104,    23,    28,    24,   187,    25,    26,    27,
      28,    96,    76,    77,    78,    97,   101,    98,   173,    99,
     115,   176,    62,    62,   102,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,    -6,   111,   116,   114,
     131,   133,   134,   190,   136,   140,   147,   132,   138,   134,
      12,   146,    13,    14,    15,    16,   144,   137,    17,   150,
     148,   151,   149,   154,    18,    19,   157,   166,   207,   178,
     161,   182,   164,    21,   183,   185,   186,   189,    23,   -76,
      24,   195,    25,    26,    27,    28,   191,   162,    74,    75,
      76,    77,    78,   167,   198,    22,   200,   -77,   -77,   -77,
     -77,   205,   156,   170,   184,   134,   174,   175,   134,   172,
     177,   201,   206,     5,   202,     6,     7,     8,     9,    10,
      11,     0,    12,     0,    13,    14,    15,    16,     0,     0,
      17,     0,     0,   192,   194,     0,    18,    19,     0,     0,
       0,     0,    20,     0,     0,    21,     0,     0,    22,   144,
      23,     0,    24,     0,    25,    26,    27,    28,    12,     0,
      13,    14,    15,    16,     0,     0,    17,     0,     0,     0,
       0,     0,    18,    19,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,    23,    72,    24,    73,
      25,    26,    27,    28,     0,    74,    75,    76,    77,    78,
      79,    80,     0,     0,    81,    82,    83,    84,     0,     0,
       0,     0,    72,     0,    73,     0,     0,     0,     0,   153,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,    83,    84,     0,     0,    72,     0,    73,     0,     0,
       0,     0,   158,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,     0,     0,    72,     0,
      73,     0,     0,     0,     0,   163,    74,    75,    76,    77,
      78,    79,    80,   -46,     0,    81,    82,    83,    84,     0,
       0,    86,    87,     0,     0,     0,   199,     0,     0,     0,
       0,    88,    89,     0,    72,    90,    73,    91,     0,     0,
       0,     0,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    83,    84,    72,   109,    73,     0,     0,
       0,     0,     0,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,    72,   159,    73,     0,
       0,     0,     0,     0,    74,    75,    76,    77,    78,    79,
      80,     0,     0,    81,    82,    83,    84,    85,    72,     0,
      73,     0,     0,     0,     0,     0,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84,   106,
      72,     0,    73,     0,     0,     0,     0,     0,    74,    75,
      76,    77,    78,    79,    80,    72,     0,    81,    82,    83,
      84,     0,     0,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,    74,    75,    76,    77,
      78,   -77,   -77,     0,     0,    81,    82,    83,    84,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      83,    84
};

static const yytype_int16 yycheck[] =
{
       9,     0,    98,    12,   101,    24,   103,     0,    17,     0,
      65,    14,    42,   144,    23,    12,    71,    14,    15,    16,
      17,    36,    37,    20,    42,    40,    32,    42,    32,    26,
      27,    47,    35,    47,     7,    32,    18,    19,    35,    42,
      39,    60,    51,    40,    47,    42,   177,    44,    45,    46,
      47,    36,    21,    22,    23,    40,    43,    42,   154,    47,
      69,   157,    18,    19,    42,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    39,    38,    43,    41,
      47,    90,    91,   180,    18,    42,    39,    47,    97,    98,
      12,    43,    14,    15,    16,    17,   105,    47,    20,    41,
     109,    33,   111,    42,    26,    27,    42,     4,   205,    47,
      43,    32,    43,    35,    34,    43,    43,    43,    40,    41,
      42,    33,    44,    45,    46,    47,    43,   136,    19,    20,
      21,    22,    23,   142,    32,    38,    47,    28,    29,    30,
      31,    43,   119,   148,   172,   154,   155,   156,   157,   151,
     159,   197,   204,     3,   198,     5,     6,     7,     8,     9,
      10,    -1,    12,    -1,    14,    15,    16,    17,    -1,    -1,
      20,    -1,    -1,   182,   183,    -1,    26,    27,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    35,    -1,    -1,    38,   198,
      40,    -1,    42,    -1,    44,    45,    46,    47,    12,    -1,
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
      23,    24,    25,    18,    -1,    28,    29,    30,    31,    -1,
      -1,    26,    27,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    36,    37,    -1,    11,    40,    13,    42,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    11,    33,    13,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    11,    33,    13,    -1,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    32,    11,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    32,
      11,    -1,    13,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    11,    -1,    28,    29,    30,
      31,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    51,    52,     0,     3,     5,     6,     7,     8,
       9,    10,    12,    14,    15,    16,    17,    20,    26,    27,
      32,    35,    38,    40,    42,    44,    45,    46,    47,    54,
      55,    59,    60,    61,    63,    65,    66,    67,    68,    74,
      82,    84,    87,    89,    90,    95,    97,    98,    99,   103,
     109,    42,    42,    32,    55,    32,    32,    55,    47,    55,
      42,    66,    68,    66,    47,    83,    55,    75,    76,    62,
      84,    53,    11,    13,    19,    20,    21,    22,    23,    24,
      25,    28,    29,    30,    31,    32,    26,    27,    36,    37,
      40,    42,    64,    69,    70,    71,    36,    40,    42,    47,
      88,    43,    42,   100,    55,   104,    32,    84,    51,    33,
      77,    38,    78,    80,    41,    55,    43,    51,    56,    57,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    47,    47,    55,    55,    72,    18,    47,    55,    72,
      42,    54,   101,    54,    55,   106,    43,    39,    55,    55,
      41,    33,    79,    43,    42,    58,    58,    42,    41,    33,
      73,    43,    55,    41,    43,    85,     4,    55,    73,   105,
      77,    81,    80,    72,    55,    55,    72,    55,    47,    91,
      96,   102,    32,    34,    79,    43,    43,    73,    92,    43,
      54,    43,    55,   107,    55,    33,    93,    86,    32,    39,
      47,    82,   106,   108,    94,    43,    93,    54
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
#line 143 "syntax.y"
    {current_rvals = 0;
		}
    break;

  case 4:
#line 144 "syntax.y"
    {rvalues = current_rvals;}
    break;

  case 5:
#line 144 "syntax.y"
    { printf(RED "stmt multi_stmt\n" RESET);}
    break;

  case 6:
#line 145 "syntax.y"
    {printf(RED "multi_stmts empty\n" RESET);}
    break;

  case 7:
#line 148 "syntax.y"
    { printf(RED "expression \n" RESET);
					if (exprflag) {

						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						emit(assign,true_expr,NULL,(yyvsp[(1) - (2)].expression),yylineno,0);
						emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						emit(assign,false_expr,NULL,(yyvsp[(1) - (2)].expression),yylineno,0);
						exprflag=0;

						patchLists(((yyvsp[(1) - (2)].expression)),(int)QuadNo-2,(int)QuadNo);
					}


      }
    break;

  case 8:
#line 164 "syntax.y"
    { printf(RED "if stmt \n" RESET); }
    break;

  case 9:
#line 165 "syntax.y"
    { printf(RED "while stmt \n" RESET); }
    break;

  case 10:
#line 166 "syntax.y"
    { printf(RED "for stmt \n" RESET); }
    break;

  case 11:
#line 167 "syntax.y"
    {

		  printf(RED "return stmt \n" RESET);
		  if( insideFunc > 0){ push_R((int)QuadNo-1); }
		  else {
				printf("Error: RETURN STMT outside of function in line %d\n",yylineno);
				exit(EXIT_FAILURE);
			}


	  }
    break;

  case 12:
#line 178 "syntax.y"
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
    break;

  case 13:
#line 188 "syntax.y"
    {  printf(RED "continue \n" RESET);
                              if( insideLoop > 0) {
                              	emit(jump,NULL,NULL,NULL,yylineno,999);
						push_C((int)QuadNo-1);
                              } else {
                                    printf("Error: CONTINUE STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              }
      }
    break;

  case 14:
#line 197 "syntax.y"
    { printf(RED "block \n" RESET);}
    break;

  case 15:
#line 198 "syntax.y"
    { printf(RED "funcdef \n" RESET);}
    break;

  case 16:
#line 199 "syntax.y"
    { printf(RED "semicolon \n" RESET);}
    break;

  case 17:
#line 203 "syntax.y"
    {


	 result =malloc(5*sizeof(char));
	 sprintf(result,"_%d",rvalues++);
	 struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);




	 if((yyvsp[(1) - (1)].expression)->type == tableitem_e){
		 struct expr* tempexp = new_expr(tableitem_e,newnode,NULL,0,"",'\0',NULL);
		 emit(tablegetelem,(yyvsp[(1) - (1)].expression),(yyvsp[(1) - (1)].expression)->index,tempexp,yylineno,0);

	 }else{
		 (yyval.expression) = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL); //TODO mporei na mhn thelei arithmeticexp edw

		 emit(assign,(yyvsp[(1) - (1)].expression),NULL,(yyval.expression),yylineno,0);
	 }

 }
    break;

  case 18:
#line 224 "syntax.y"
    { (yyval.expression)=(yyvsp[(1) - (1)].expression); exprflag=1; (yyval.expression)->apotimimeno=1;
		addTruelist(((yyval.expression)),(int)QuadNo-2);
		addFalselist(((yyval.expression)),(int)QuadNo-1);
	}
    break;

  case 19:
#line 228 "syntax.y"
    { (yyval.expression)=(yyvsp[(1) - (1)].expression); }
    break;

  case 20:
#line 229 "syntax.y"
    {

		 struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );


		if (!(yyvsp[(1) - (2)].expression)->apotimimeno) {
			emit(if_eq,(yyvsp[(1) - (2)].expression),true_expr,NULL,yylineno,999);//QuadNo +4 mallon
			emit(jump,NULL,NULL,NULL,yylineno,999); // jump assign false
			addTruelist(((yyvsp[(1) - (2)].expression)),(int)QuadNo-2);
			addFalselist(((yyvsp[(1) - (2)].expression)),(int)QuadNo-1);

		}


	 }
    break;

  case 21:
#line 244 "syntax.y"
    {

		  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

		  if (!(yyvsp[(5) - (5)].expression)->apotimimeno) {
			 emit(if_eq,(yyvsp[(5) - (5)].expression),true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
 			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false

			 addTruelist(((yyvsp[(5) - (5)].expression)),(int)QuadNo-2);
	 		 addFalselist(((yyvsp[(5) - (5)].expression)),(int)QuadNo-1);
		  }
		  (yyval.expression) = smallFunc(boolexp_e);
		   backpatchList((yyvsp[(1) - (5)].expression)->truelist,(yyvsp[(4) - (5)].intValue)+1);
		 andLists((yyval.expression),(yyvsp[(1) - (5)].expression),(yyvsp[(5) - (5)].expression));
		 (yyval.expression)->apotimimeno=1;



			exprflag=1;
	}
    break;

  case 22:
#line 265 "syntax.y"
    {

			struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		 	struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			if (!(yyvsp[(1) - (2)].expression)->apotimimeno) {

				emit(if_eq,(yyvsp[(1) - (2)].expression),true_expr,NULL,yylineno,999);//epomeno expr an true
				emit(jump,NULL,NULL,NULL,yylineno,999); // jump assign false
				addTruelist(((yyvsp[(1) - (2)].expression)),(int)QuadNo-2);
				addFalselist(((yyvsp[(1) - (2)].expression)),(int)QuadNo-1);

			}


			}
    break;

  case 23:
#line 280 "syntax.y"
    {



		  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

		  if (!(yyvsp[(5) - (5)].expression)->apotimimeno) {
				 emit(if_eq,(yyvsp[(5) - (5)].expression),true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
	 			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false
				 addTruelist(((yyvsp[(5) - (5)].expression)),(int)QuadNo-2);
	 			 addFalselist(((yyvsp[(5) - (5)].expression)),(int)QuadNo-1);
		  }

			    (yyval.expression) = smallFunc(boolexp_e);
				(yyval.expression)->apotimimeno=1;
				backpatchList((yyvsp[(1) - (5)].expression)->falselist,(yyvsp[(4) - (5)].intValue)+1);
				orLists((yyval.expression),(yyvsp[(1) - (5)].expression),(yyvsp[(5) - (5)].expression));


	 exprflag=1;
	}
    break;

  case 24:
#line 302 "syntax.y"
    {
			printf(RED "NOT expression\n" RESET);

			struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",1,NULL );

			if (!(yyvsp[(2) - (2)].expression)->apotimimeno) {
  			  emit(if_eq,(yyvsp[(2) - (2)].expression),true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
   			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false
			 addTruelist(((yyvsp[(2) - (2)].expression)),(int)QuadNo-2);
			 addFalselist(((yyvsp[(2) - (2)].expression)),(int)QuadNo-1);
  		  }

		   (yyval.expression) = smallFunc(boolexp_e);
		   notLists((yyvsp[(2) - (2)].expression),(yyval.expression));

		  (yyval.expression)->apotimimeno=1;
		if(exprflag == 1) {

			emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
			emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
			emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);

			patchLists(((yyval.expression)),(int)QuadNo-2,(int)QuadNo);
		}

		exprflag = 1;

//			patchLists(($$),(int)QuadNo-2,(int)QuadNo);


}
    break;

  case 25:
#line 334 "syntax.y"
    { (yyval.expression)=(yyvsp[(1) - (1)].expression); printf(RED"term (%s)\n"RESET, (yyvsp[(1) - (1)].expression)->sym->value.var->name); }
    break;

  case 26:
#line 337 "syntax.y"
    {(yyval.intValue)=QuadNo;}
    break;

  case 27:
#line 340 "syntax.y"
    {
				/*compile time type check*/
            if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
                  (yyval.expression) = smallFunc(arithmeticexp_e);
                  emit(add, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyval.expression), yylineno, 0);
            }
            else{
              printf("Compile time error: cannot ADD 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[(1) - (3)].expression))->type, ((yyvsp[(3) - (3)].expression))->type, yylineno );
              exit(EXIT_FAILURE);
            }

      }
    break;

  case 28:
#line 352 "syntax.y"
    {
		    if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
		          (yyval.expression) = smallFunc(arithmeticexp_e);
		          emit(sub, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyval.expression), yylineno, 0);
		    }
		    else{
		          printf("Compile time error: cannot sub 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[(1) - (3)].expression))->type, ((yyvsp[(3) - (3)].expression))->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
    break;

  case 29:
#line 362 "syntax.y"
    {
		    if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
		          (yyval.expression) = smallFunc(arithmeticexp_e);
		          emit(mul, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyval.expression), yylineno, 0);
		    }
		    else{
		          printf("Compile time error: cannot multiple 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[(1) - (3)].expression))->type, ((yyvsp[(3) - (3)].expression))->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
    break;

  case 30:
#line 372 "syntax.y"
    {
		    if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
		          (yyval.expression) = smallFunc(arithmeticexp_e);
		          emit(Div, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyval.expression), yylineno, 0);
		    }
		    else {
		          printf("Compile time error: cannot div 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[(1) - (3)].expression))->type, ((yyvsp[(3) - (3)].expression))->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
    break;

  case 31:
#line 382 "syntax.y"
    {
		    if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
		          (yyval.expression) = smallFunc(arithmeticexp_e);
		          emit(mod, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), (yyval.expression), yylineno, 0);
		    }
		    else {
		      printf("Compile time error: cannot mod 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",((yyvsp[(1) - (3)].expression))->type, ((yyvsp[(3) - (3)].expression))->type, yylineno );
		      exit(EXIT_FAILURE);
		    }
		}
    break;

  case 32:
#line 395 "syntax.y"
    {

	  if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
			(yyval.expression) = smallFunc(boolexp_e);
	  } else {
			printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
			exit(EXIT_FAILURE);
	  }

	  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
	  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

	  emit(if_greater,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression),NULL,yylineno,999);
	  emit(jump,NULL,NULL,NULL,yylineno,999);

	}
    break;

  case 33:
#line 411 "syntax.y"
    {
			  if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
					(yyval.expression) = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_greatereq,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression),NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
    break;

  case 34:
#line 426 "syntax.y"
    {
			  if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
					(yyval.expression) = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_less,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression),NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
    break;

  case 35:
#line 441 "syntax.y"
    {
			  if(checkTypes((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)) == 1) {
					(yyval.expression) = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_lesseq,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression),NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
    break;

  case 36:
#line 456 "syntax.y"
    {

			  //compile time type check
			  if( ((yyvsp[(1) - (3)].expression))->type == 1 && ((yyvsp[(3) - (3)].expression))->type == 11 ){ //table and nil ok
			  }
			  else if(oneIsVar((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression))) {
					//ok
			  }

			  (yyval.expression) = smallFunc(boolexp_e);

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_eq,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression),NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
    break;

  case 37:
#line 474 "syntax.y"
    {
			  if( ((yyvsp[(1) - (3)].expression))->type ==1 && ((yyvsp[(3) - (3)].expression))->type ==11 ){
					//table and nil ok
			  }
			  else if(oneIsVar((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression))) {
					//ok
			  }


			  (yyval.expression) = smallFunc(boolexp_e);

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_not_eq,(yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].expression),NULL,yylineno,999);//THELEI SWSTO LABEL
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
    break;

  case 38:
#line 499 "syntax.y"
    {
	push_E(exprflag); exprflag=0;
}
    break;

  case 39:
#line 501 "syntax.y"
    { printf(RED " (expression) \n" RESET);

          (yyval.expression) = (yyvsp[(3) - (4)].expression);
		  if(exprflag == 1) {
			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

  			emit(assign,true_expr,NULL,(yyval.expression),yylineno,0);
  			emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
  			emit(assign,false_expr,NULL,(yyval.expression),yylineno,0);

  			patchLists(((yyval.expression)),(int)QuadNo-2,(int)QuadNo);
  		}


		 exprflag=pop_E();

      }
    break;

  case 40:
#line 519 "syntax.y"
    {

            printf(RED " - expression \n" RESET);
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues);
            tmpnode = malloc(sizeof(struct symbol_table_binding));
            tmpnode =insertVar(result,yylineno,scope);
            tmpexpr=malloc(sizeof(struct expr));
            tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
            emit(uminus,(yyvsp[(2) - (2)].expression),NULL,tmpexpr,yylineno,0);
            (yyval.expression) = tmpexpr;
   	}
    break;

  case 41:
#line 532 "syntax.y"
    {
	      printf(RED "++lvalue\n" RESET);
            check_for_funcname((yyvsp[(2) - (2)].expression)->sym->value.var->name);

            if((yyvsp[(2) - (2)].expression)->type == 1){
			  	(yyval.expression)= member_item((yyvsp[(2) - (2)].expression), (yyvsp[(2) - (2)].expression)->sym->value.var->name);
			  	//new expr for number 1
			  	struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

				emit(add,(yyval.expression),tmp_one,(yyval.expression),yylineno,0);
        		emit(table_setelem,(yyvsp[(2) - (2)].expression)->index,(yyval.expression),(yyvsp[(2) - (2)].expression),yylineno,0);
        } else{
                  result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
    			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
    			   	tmpnode =insertVar(result,yylineno,scope);
    			   	tmpexpr=malloc(sizeof(struct expr));
    			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
      				//new expr for number 1
              struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(add,(yyvsp[(2) - (2)].expression),tmp_one,(yyvsp[(2) - (2)].expression),yylineno,0);
      			emit(assign,(yyvsp[(2) - (2)].expression),NULL,tmpexpr,yylineno,0);
              (yyval.expression) = tmpexpr;
              }
	}
    break;

  case 42:
#line 558 "syntax.y"
    {
	      check_for_funcname((yyvsp[(1) - (2)].expression)->sym->value.var->name);
            result =malloc(5*sizeof(char));
  			sprintf(result,"_%d",rvalues++);

          		  if((yyvsp[(1) - (2)].expression)->type == 1){
                   struct expr* temp_expr;
          			   temp_expr= member_item((yyvsp[(1) - (2)].expression), (yyvsp[(1) - (2)].expression)->sym->value.var->name);

          			   tmpnode =insertVar(result,yylineno,scope);
             			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
             			 //new expr for number 1
                   struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

             			 emit(assign,temp_expr,NULL,tmpexpr,yylineno,0);
          				 emit(add,temp_expr,tmp_one,temp_expr,yylineno,0);
          				 emit(table_setelem,(yyvsp[(1) - (2)].expression)->index,temp_expr,(yyvsp[(1) - (2)].expression),yylineno,0);

                   (yyval.expression) = tmpexpr;
          		  } else {
          			  tmpnode =insertVar(result,yylineno,scope);
          			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
          			   //new expr for number 1
          			 struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

          			emit(assign,(yyvsp[(1) - (2)].expression),NULL,tmpexpr,yylineno,0);
          			emit(add,(yyvsp[(1) - (2)].expression),tmp_one,(yyvsp[(1) - (2)].expression),yylineno,0);
          	   			(yyval.expression) = tmpexpr;
          		  }


	}
    break;

  case 43:
#line 590 "syntax.y"
    {
          check_for_funcname((yyvsp[(2) - (2)].expression)->sym->value.var->name);
  				printf(RED "--lvalue\n" RESET);

				if((yyvsp[(2) - (2)].expression)->type == 1){
	  			  (yyval.expression)= member_item((yyvsp[(2) - (2)].expression), (yyvsp[(2) - (2)].expression)->sym->value.var->name);
	  			  //new expr for number 1
	  			  struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

	  			  emit(sub,(yyval.expression),tmp_one,(yyval.expression),yylineno,0);
	  			  emit(table_setelem,(yyvsp[(2) - (2)].expression)->index,(yyval.expression),(yyvsp[(2) - (2)].expression),yylineno,0);
	  	  } else{
      				result =malloc(5*sizeof(char));
      			  sprintf(result,"_%d",rvalues++);

    			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
    			   	tmpnode =insertVar(result,yylineno,scope);
    			   	tmpexpr=malloc(sizeof(struct expr));
    			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
    				  //new expr for number 1
              struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(sub,(yyvsp[(2) - (2)].expression),tmp_one,(yyvsp[(2) - (2)].expression),yylineno,0);
    			emit(assign,(yyvsp[(2) - (2)].expression),NULL,tmpexpr,yylineno,0);

              (yyval.expression) = tmpexpr;
          }

  	}
    break;

  case 44:
#line 619 "syntax.y"
    {
            check_for_funcname((yyvsp[(1) - (2)].expression)->sym->value.var->name);
            printf(RED "lvalue--\n" RESET);

            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);

      		  if((yyvsp[(1) - (2)].expression)->type == 1){
               struct expr* temp_expr;
      			   temp_expr= member_item((yyvsp[(1) - (2)].expression), (yyvsp[(1) - (2)].expression)->sym->value.var->name);

      			   tmpnode =insertVar(result,yylineno,scope);
         			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
         			 //new expr for number 1
               struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

         			 emit(assign,temp_expr,NULL,tmpexpr,yylineno,0);
      				 emit(sub,temp_expr,tmp_one,temp_expr,yylineno,0);
      				 emit(table_setelem,(yyvsp[(1) - (2)].expression)->index,temp_expr,(yyvsp[(1) - (2)].expression),yylineno,0);

               (yyval.expression) = tmpexpr;
      		  }else{
      			  tmpnode =insertVar(result,yylineno,scope);
      			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
      			   //new expr for number 1
      			 struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(assign,(yyvsp[(1) - (2)].expression),NULL,tmpexpr,yylineno,0);
      			emit(add,(yyvsp[(1) - (2)].expression),tmp_one,(yyvsp[(1) - (2)].expression),yylineno,0);
      	   			(yyval.expression) = tmpexpr;
      		  }

			}
    break;

  case 45:
#line 652 "syntax.y"
    { printf(RED "primary\n" RESET); (yyval.expression)=(yyvsp[(1) - (1)].expression);  }
    break;

  case 46:
#line 655 "syntax.y"
    { if(!arrayFlag && ref)   check_for_funcname((yyvsp[(1) - (1)].expression)->sym->value.var->name); push_E(exprflag); exprflag=0; }
    break;

  case 47:
#line 655 "syntax.y"
    {
							     arrayFlag = 0;
                   				 ref = 1;

								 if (exprflag) {
					 				struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					 				struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					 				emit(assign,true_expr,NULL,(yyvsp[(4) - (4)].expression),yylineno,0);
					 				emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					 				emit(assign,false_expr,NULL,(yyvsp[(4) - (4)].expression),yylineno,0);
									exprflag=0;

									patchLists(((yyvsp[(4) - (4)].expression)),(int)QuadNo-2,(int)QuadNo);

					 			}

                   if((yyvsp[(1) - (4)].expression)->type == tableitem_e){

                        emit(table_setelem,(yyvsp[(1) - (4)].expression)->index,(yyvsp[(4) - (4)].expression),(yyvsp[(1) - (4)].expression),yylineno,0);

                        struct symbol_table_binding *tmp_index = malloc(sizeof(struct symbol_table_binding));
                        tmp_index->value.var = malloc(sizeof(struct variable));
                        tmp_index->value.var->name = malloc((strlen((yyvsp[(1) - (4)].expression)->index->sym->value.var->name) + 1) * sizeof(char));
                        strcpy(tmp_index->value.var->name, (yyvsp[(1) - (4)].expression)->index->sym->value.var->name);
                        tmp_index->next = NULL;

                        struct expr*  returned_exp = new_expr(tableitem_e,tmp_index,(yyvsp[(1) - (4)].expression),0,"",'\0',NULL);
                        (yyval.expression) = (yyvsp[(1) - (4)].expression);
                   }else{
							            emit(assign,(yyvsp[(4) - (4)].expression),NULL,(yyvsp[(1) - (4)].expression),yylineno,0);

                   }
				   exprflag=pop_E();
						  }
    break;

  case 48:
#line 692 "syntax.y"
    { printf(RED "primary:: lvalue \n" RESET); (yyval.expression)=(yyvsp[(1) - (1)].expression);
            if((yyvsp[(1) - (1)].expression)->type == 1 ){
                  (yyvsp[(1) - (1)].expression) = member_item((yyvsp[(1) - (1)].expression), (yyvsp[(1) - (1)].expression)->sym->value.var->name);
            }
            (yyval.expression)=(yyvsp[(1) - (1)].expression);
         }
    break;

  case 49:
#line 698 "syntax.y"
    {printf(RED "primary:: call %s \n" RESET,(yyvsp[(1) - (1)].expression)->sym->value.var->name);

         }
    break;

  case 50:
#line 701 "syntax.y"
    { printf(RED "primary:: objectdef\n" RESET);

                (yyval.expression) = (yyvsp[(1) - (1)].expression);
         }
    break;

  case 51:
#line 705 "syntax.y"
    { printf(RED "primary:: (funcdef)\n" RESET); (yyval.expression) = (yyvsp[(2) - (3)].expression); exprflag=pop_E(); }
    break;

  case 52:
#line 706 "syntax.y"
    { printf(RED "primary:: const\n" RESET);  (yyval.expression)=(yyvsp[(1) - (1)].expression); }
    break;

  case 53:
#line 709 "syntax.y"
    {
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode= insertVar( yylval.stringValue, yylineno, scope);
            if(tmpnode->symbol_type == 3) (yyval.expression)=new_expr(2,tmpnode,NULL,0,"",'\0',NULL);
						else if(tmpnode->symbol_type == 4) (yyval.expression)=new_expr(3,tmpnode,NULL,0,"",'\0',NULL);
            else (yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);

            }
    break;

  case 54:
#line 717 "syntax.y"
    {
						printf(RED "lvalue:: local identifier\n" RESET);
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode = localVar( yylval.stringValue, yylineno, scope);
						(yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);}
    break;

  case 55:
#line 722 "syntax.y"
    {
            tmpnode=malloc(sizeof(struct symbol_table_binding));
            if((tmpnode=global_exists((yyvsp[(2) - (2)].stringValue))) == NULL) {
                  printf("\"%s\" undeclared, (first use here), line: %d\n", (yyvsp[(2) - (2)].stringValue), yylineno);
                  exit(EXIT_FAILURE);
            }

		        (yyval.expression)=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);

            printf( RED "lvalue:: doublecolon\n" RESET);}
    break;

  case 56:
#line 732 "syntax.y"
    { printf(RED "lvalue:: member %s type %d\n" RESET, (yyvsp[(1) - (1)].expression)->sym->value.var->name, (yyvsp[(1) - (1)].expression)->type);
            (yyval.expression) = (yyvsp[(1) - (1)].expression);

         }
    break;

  case 57:
#line 738 "syntax.y"
    {
            (yyval.expression) = member_item((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].stringValue));
         }
    break;

  case 58:
#line 741 "syntax.y"
    {
                arrayFlag = 1;
                printf(RED"member:: lvalue[expression]\n"RESET);
                (yyval.expression) = member_item((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression)->sym->value.var->name);
         }
    break;

  case 59:
#line 746 "syntax.y"
    {

              struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
              tmp_symbol_id->value.var = malloc(sizeof(struct variable));
              tmp_symbol_id->value.var->name = malloc((strlen((yyvsp[(3) - (3)].stringValue)) + 1) * sizeof(char));
              strcpy(tmp_symbol_id->value.var->name, (yyvsp[(3) - (3)].stringValue));
              tmp_symbol_id->next = NULL;
              //adespoto symbol pou den prepei na mpei sto hash!

              struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);

              (yyvsp[(1) - (3)].expression)->index = tmpexpr_id;

              struct expr* tmp_exression = member_item((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].stringValue)); //prepei to $1 na einai table item
              (yyval.expression) = tmp_exression;


         }
    break;

  case 60:
#line 764 "syntax.y"
    { \
            arrayFlag = 1;

            printf(RED "member:: call[expression]\n" RESET);
            struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
            tmp_symbol_id->value.var = malloc(sizeof(struct variable));
            tmp_symbol_id->value.var->name = malloc((strlen((yyvsp[(3) - (4)].expression)->sym->value.var->name) + 1) * sizeof(char));
            strcpy(tmp_symbol_id->value.var->name, (yyvsp[(3) - (4)].expression)->sym->value.var->name);
            tmp_symbol_id->next = NULL;
            //adespoto symbol pou den prepei na mpei sto hash!

            struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);

            (yyvsp[(1) - (4)].expression)->index = tmpexpr_id;

            struct expr* tmp_exression = member_item((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression)->sym->value.var->name); //prepei to $1 na einai table item
            (yyval.expression) = tmp_exression;

         }
    break;

  case 61:
#line 785 "syntax.y"
    {

				printf(RED "call:: call (elist)\n" RESET);

        //printf("1) make call type %d\n", $3->type);
        (yyval.expression) = make_call((yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression));

 			}
    break;

  case 62:
#line 793 "syntax.y"
    {

          (yyvsp[(1) - (2)].expression) = emit_iftable_item((yyvsp[(1) - (2)].expression));
          if ((yyvsp[(2) - (2)].callexpr)->method ){
                struct expr* t = (yyvsp[(1) - (2)].expression);
                t->next = (yyvsp[(2) - (2)].callexpr)->elist;
                (yyvsp[(1) - (2)].expression) = emit_iftable_item(member_item(t, (yyvsp[(2) - (2)].callexpr)->name));
                (yyvsp[(2) - (2)].callexpr)->elist = t ;

          }
       //   printf("2) make call type %d\n", $2->elist->type);
          (yyval.expression) = make_call((yyvsp[(1) - (2)].expression), (yyvsp[(2) - (2)].callexpr)->elist);
				}
    break;

  case 63:
#line 806 "syntax.y"
    {
		   			printf(RED "call:: (funcdef)(elist)\n" RESET);
//            printf("3) make call type %d\n", $3->type);
          (yyval.expression) = make_call((yyvsp[(2) - (6)].expression), (yyvsp[(5) - (6)].expression));

  			}
    break;

  case 64:
#line 814 "syntax.y"
    { printf(RED"callsuffix:: (elist)\n"RESET);

                (yyval.callexpr) = (yyvsp[(1) - (1)].callexpr);
           }
    break;

  case 65:
#line 818 "syntax.y"
    { printf(RED "callsuffix:: ..id(elist)\n" RESET);
                (yyval.callexpr) = (yyvsp[(1) - (1)].callexpr);
           }
    break;

  case 66:
#line 823 "syntax.y"
    {
              (yyval.callexpr) = malloc(sizeof(struct call));
              (yyval.callexpr)->elist = (yyvsp[(2) - (3)].expression);
//              $$->elist->type = $2->type;
              (yyval.callexpr)->method = 0;
              (yyval.callexpr)->name = NULL;

         }
    break;

  case 67:
#line 833 "syntax.y"
    { printf(RED "methodcall\n" RESET);
                (yyval.callexpr) = malloc(sizeof(struct call));
                (yyval.callexpr)->elist = (yyvsp[(4) - (5)].expression);
//              $$->elist->type = $2->type;
                (yyval.callexpr)->method = 1;
                (yyval.callexpr)->name = (yyvsp[(2) - (5)].stringValue);
           }
    break;

  case 68:
#line 842 "syntax.y"
    {
	 				args++;

          struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
          newnode->value.var = malloc(sizeof(struct variable));
          newnode->value.var->name = malloc((strlen((yyvsp[(1) - (2)].expression)->sym->value.var->name) + 1) * sizeof(char));
          strcpy(newnode->value.var->name, (yyvsp[(1) - (2)].expression)->sym->value.var->name);
          newnode->value.var->line = yylineno;
          newnode->symbol_type = 1;
          newnode->value.var->scope = scope;
          newnode->next = NULL;

          struct expr* temp_elem = new_expr(var_e,newnode,NULL,0,"",'\0',(yyvsp[(2) - (2)].expression));


          (yyval.expression) = (yyvsp[(1) - (2)].expression);
          (yyval.expression)->next = (yyvsp[(2) - (2)].expression); ///edw
		  if (exprflag) {
			 struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			 emit(assign,true_expr,NULL,(yyvsp[(1) - (2)].expression),yylineno,0);
			 emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
			 emit(assign,false_expr,NULL,(yyvsp[(1) - (2)].expression),yylineno,0);
			 exprflag=0;
			patchLists(((yyvsp[(1) - (2)].expression)),(int)QuadNo-2,(int)QuadNo);
		 }
	}
    break;

  case 69:
#line 870 "syntax.y"
    { printf(RED "elist:: empty\n" RESET);
                args = 0;
                struct expr* temp_elem = new_expr(var_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                (yyval.expression) = temp_elem;
      }
    break;

  case 70:
#line 877 "syntax.y"
    {
					args++;

          struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
          newnode->value.var = malloc(sizeof(struct variable));
          newnode->value.var->name = malloc((strlen((yyvsp[(2) - (3)].expression)->sym->value.var->name) + 1) * sizeof(char));
          strcpy(newnode->value.var->name, (yyvsp[(2) - (3)].expression)->sym->value.var->name);
          newnode->value.var->line = yylineno;
          newnode->symbol_type = 1;
          newnode->value.var->scope = scope;
          newnode->next = NULL;

          struct expr* temp_elem = new_expr(var_e,newnode,NULL,0,"",'\0',(yyvsp[(3) - (3)].expression));
          // bazw sto next to epomeno stoixeio


          (yyval.expression) = (yyvsp[(2) - (3)].expression);
          (yyval.expression)->next = (yyvsp[(3) - (3)].expression); ///edw
	}
    break;

  case 71:
#line 896 "syntax.y"
    { printf(RED "multi exprsessions: empty\n" RESET);
                  args = 0; //mallon eixe ksexastei ayto
                  struct expr* temp_elem = new_expr(var_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                  (yyval.expression) = NULL;
      }
    break;

  case 72:
#line 905 "syntax.y"
    {
                  printf(RED "objectdef:: elist\n" RESET);

                  result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
                  struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                  struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
                  emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);

                  struct expr* tmp = (yyvsp[(2) - (3)].expression);
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
    break;

  case 73:
#line 945 "syntax.y"
    {
                    result =malloc(5*sizeof(char));
                    sprintf(result,"_%d",rvalues);
                    struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                    struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
                    emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);

                }
    break;

  case 74:
#line 953 "syntax.y"
    {
                   printf(RED "objectdef:: indexed\n" RESET);
                   struct expr* tmp = (yyvsp[(3) - (4)].expression);

                    result =malloc(5*sizeof(char));
                    sprintf(result,"_%d",rvalues++);
                    struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                    struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);

                    (yyval.expression) = tmp_table;// epistrefw pros ta panw olo to table

                    int i = 0;
                    while(tmp->sym!= NULL) {
                          printf("indexed table %d kai index(%s) val(%s)", i, tmp->index->sym->value.var->name, tmp->sym->value.var->name);
                          tmp = tmp->next;
                          i++;
                    }
            }
    break;

  case 75:
#line 976 "syntax.y"
    {
                args++;
                //adespoto symbol pou den prepei na mpei sto hash!
                struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
                newnode->value.var = malloc(sizeof(struct variable));
                newnode->value.var->name = malloc((strlen((yyvsp[(1) - (2)].expression)->sym->value.var->name) + 1) * sizeof(char));
                strcpy(newnode->value.var->name, (yyvsp[(1) - (2)].expression)->sym->value.var->name);
                newnode->value.var->line = yylineno;
                newnode->symbol_type = 1;
                newnode->value.var->scope = scope;
                newnode->next = NULL;

                struct expr* temp_elem = new_expr(tableitem_e,newnode,NULL,0,"",'\0',(yyvsp[(2) - (2)].expression));
                (yyvsp[(1) - (2)].expression)->next= (yyvsp[(2) - (2)].expression);
//new_expr(tableitem_e,$1->sym,$1->index,0,"",'\0',$2);
                (yyval.expression) = (yyvsp[(1) - (2)].expression);
        }
    break;

  case 76:
#line 993 "syntax.y"
    {
          struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
          (yyval.expression) = temp_elem;
          printf(RED "elist:: empty\n" RESET);
          args = 0;
        }
    break;

  case 77:
#line 1001 "syntax.y"
    {
                             args++;

                             //adespoto symbol pou den prepei na mpei sto hash!
                             struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
                             newnode->value.var = malloc(sizeof(struct variable));
                             newnode->value.var->name = malloc((strlen((yyvsp[(2) - (3)].expression)->sym->value.var->name) + 1) * sizeof(char));
                             strcpy(newnode->value.var->name, (yyvsp[(2) - (3)].expression)->sym->value.var->name);
                             newnode->value.var->line = yylineno;
                             newnode->symbol_type = 1;
                             newnode->value.var->scope = scope;
                             newnode->next = NULL;

                             struct expr* temp_elem = new_expr(tableitem_e,newnode,NULL,0,"",'\0',(yyvsp[(3) - (3)].expression));
                             // bazw sto next to epomeno stoixeio
                             (yyvsp[(2) - (3)].expression)->next = (yyvsp[(3) - (3)].expression);
                             (yyval.expression) = (yyvsp[(2) - (3)].expression); //pernaw to neo expression me to next, sto $$

                        }
    break;

  case 78:
#line 1020 "syntax.y"
    {
                              struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                              (yyval.expression) = NULL;//temp_elem;
                      }
    break;

  case 79:
#line 1029 "syntax.y"
    {

                printf(RED "indexed:: indexedelement multi\n" RESET);
                struct expr* expr_with_next = new_expr(tableitem_e,(yyvsp[(1) - (2)].expression)->sym,(yyvsp[(1) - (2)].expression)->index,0,"",'\0',(yyvsp[(2) - (2)].expression));
                (yyval.expression) = expr_with_next;


                }
    break;

  case 80:
#line 1039 "syntax.y"
    {
                        printf(RED "multi_indexedelem:: comma indelem multi\n" RESET);

                        struct expr* expr_with_next = new_expr(tableitem_e,(yyvsp[(2) - (3)].expression)->sym,(yyvsp[(2) - (3)].expression)->index,0,"",'\0',(yyvsp[(3) - (3)].expression));
                        (yyval.expression) = expr_with_next;

                        }
    break;

  case 81:
#line 1046 "syntax.y"
    {
                        printf(RED "multi_indexedelem:: empty\n" RESET);
                        struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                        (yyval.expression) = temp_elem;
                  }
    break;

  case 82:
#line 1053 "syntax.y"
    {
	if (exprflag) {
	   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
	   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

	   emit(assign,true_expr,NULL,(yyvsp[(2) - (2)].expression),yylineno,0);
	   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
	   emit(assign,false_expr,NULL,(yyvsp[(2) - (2)].expression),yylineno,0);
	   exprflag=0;
	  patchLists(((yyvsp[(2) - (2)].expression)),(int)QuadNo-2,(int)QuadNo);
   }
}
    break;

  case 83:
#line 1065 "syntax.y"
    {
					if (exprflag) {
					   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					   emit(assign,true_expr,NULL,(yyvsp[(5) - (6)].expression),yylineno,0);
					   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					   emit(assign,false_expr,NULL,(yyvsp[(5) - (6)].expression),yylineno,0);
					   exprflag=0;
					  patchLists(((yyvsp[(5) - (6)].expression)),(int)QuadNo-2,(int)QuadNo);
				   }

				   if ((yyvsp[(2) - (6)].expression)->type==9 || (yyvsp[(2) - (6)].expression)->type==5) {
					   (yyvsp[(2) - (6)].expression)->type = 10;
					   (yyvsp[(2) - (6)].expression)->strconst = malloc(sizeof(char)*5);
					   if ((yyvsp[(2) - (6)].expression)->boolconst) strcpy((yyvsp[(2) - (6)].expression)->strconst , "true");
					   else  strcpy((yyvsp[(2) - (6)].expression)->strconst , "false");

				   }else  if ((yyvsp[(2) - (6)].expression)->type!=10) {
					   (yyvsp[(2) - (6)].expression)->type = 10;
    				   (yyvsp[(2) - (6)].expression)->strconst = malloc(sizeof(char)*5);
    				   sprintf((yyvsp[(2) - (6)].expression)->strconst,"%f",(yyvsp[(2) - (6)].expression)->numconst);
				   }

                  result = malloc(2 * sizeof(char));
                  sprintf(result, "_%d", rvalues);
                  struct symbol_table_binding* tmp_symbol=  insertVar(result ,  yylineno , scope);
                  struct expr* temp_elem = new_expr(tableitem_e,tmp_symbol,NULL,0,"",'\0',NULL);
                  emit(table_setelem,(yyvsp[(2) - (6)].expression),(yyvsp[(5) - (6)].expression),temp_elem,yylineno,0);

                  //adespoto symbol pou den prepei na mpei sto hash!
                  struct symbol_table_binding *newnode1 = malloc(sizeof(struct symbol_table_binding));
                  newnode1->value.var = malloc(sizeof(struct variable));
                  newnode1->value.var->name = malloc((strlen((yyvsp[(2) - (6)].expression)->sym->value.var->name) + 1) * sizeof(char));
                  strcpy(newnode1->value.var->name, (yyvsp[(2) - (6)].expression)->sym->value.var->name);
                  newnode1->value.var->line = yylineno;
                  newnode1->symbol_type = 1;
                  newnode1->value.var->scope = scope;
                  newnode1->next = NULL;

                  struct symbol_table_binding *newnode2 = malloc(sizeof(struct symbol_table_binding));
                  newnode2->value.var = malloc(sizeof(struct variable));
                  newnode2->value.var->name = malloc((strlen((yyvsp[(5) - (6)].expression)->sym->value.var->name) + 1) * sizeof(char));
                  strcpy(newnode2->value.var->name, (yyvsp[(5) - (6)].expression)->sym->value.var->name);
                  newnode2->value.var->line = yylineno;
                  newnode2->symbol_type = 1;
                  newnode2->value.var->scope = scope;
                  newnode2->next = NULL;

                  struct expr* expr_for_symbol2 = new_expr(tableitem_e,newnode2,NULL,0,"",'\0',NULL);

                  struct expr* new_elem_withboth = new_expr(tableitem_e,newnode1,expr_for_symbol2,0,"",'\0',NULL);
                  (yyval.expression) = new_elem_withboth;

              }
    break;

  case 84:
#line 1122 "syntax.y"
    { scope++; if(scope > maxScope) maxScope = scope; }
    break;

  case 85:
#line 1122 "syntax.y"
    {hide_symbols(scope); scope--;  printf( RED "block:: {stmt multi stmt}\n" RESET ); }
    break;

  case 86:
#line 1125 "syntax.y"
    {push_SP(tmpoffset); tmpoffset=0; insideFunc++;}
    break;

  case 87:
#line 1125 "syntax.y"
    {  (yyvsp[(2) - (6)].expression)->sym->value.func->totalArgs=tmpoffset; tmpoffset=0; make_not_accessible(scope+1);  push_E(exprflag); exprflag=0; }
    break;

  case 88:
#line 1125 "syntax.y"
    {
			  make_accessible_again(scope+1);
			  insideFunc--;
			  emit(funcend,(yyvsp[(2) - (8)].expression),NULL,NULL,yylineno,0);
			  (yyvsp[(2) - (8)].expression)->sym->value.func->totalVars=tmpoffset;
			  (yyvsp[(2) - (8)].expression)->sym->value.func->funcAddress=(yyvsp[(1) - (8)].intValue)+2;//+1 gia indexing apo to 0 +1 giati to $1 einai to jump

			  (yyval.expression)=(yyvsp[(2) - (8)].expression);
			  quads[(int)(yyvsp[(1) - (8)].intValue)].label=QuadNo+1;
			  tmpoffset=pop_SP();

			  patchReturn((int)(yyvsp[(1) - (8)].intValue),(int)QuadNo);
			  exprflag=pop_E();
		   	}
    break;

  case 89:
#line 1141 "syntax.y"
    { emit(jump,NULL,NULL,NULL,yylineno,999); (yyval.intValue)=QuadNo-1; }
    break;

  case 90:
#line 1144 "syntax.y"
    {
					tmpnode=malloc(sizeof(struct symbol_table_binding));
					tmpnode= newFunction( (yyvsp[(1) - (1)].stringValue), yylineno, scope);
					tmpexpr=malloc(sizeof(struct expr));
					tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);

					emit(funcstart,tmpexpr,NULL,NULL,yylineno,0);
					(yyval.expression)=tmpexpr;
			}
    break;

  case 91:
#line 1153 "syntax.y"
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
    break;

  case 92:
#line 1166 "syntax.y"
    {		(yyval.expression)=(yyvsp[(1) - (1)].expression); 	}
    break;

  case 93:
#line 1167 "syntax.y"
    {
				tmpnode=malloc(sizeof(struct symbol_table_binding));
				tmpnode->value.var = malloc(sizeof(struct variable));
				tmpnode->value.var->name = malloc((strlen(Lex_string) + 1) * sizeof(char));
				strcpy(tmpnode->value.var->name, Lex_string);
				(yyval.expression) = (struct expr *)malloc(sizeof(struct expr));
				(yyval.expression) = new_expr(conststring_e,tmpnode,NULL,0,Lex_string,'\0',NULL);
			}
    break;

  case 94:
#line 1175 "syntax.y"
    { (yyval.expression) = new_expr(nil_e,nil_expr_sym,NULL,0,"",'\0',NULL); }
    break;

  case 95:
#line 1176 "syntax.y"
    { (yyval.expression) = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );  }
    break;

  case 96:
#line 1177 "syntax.y"
    { (yyval.expression) = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL ); }
    break;

  case 97:
#line 1180 "syntax.y"
    {
     					result = malloc(50 * sizeof(char)); sprintf(result,"%f", ((yyvsp[(1) - (1)].intValue)));

    					struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
    					newnode->value.var = malloc(sizeof(struct variable));
    					newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
    					strcpy(newnode->value.var->name, result);
    					(yyval.expression) = (struct expr *)malloc(sizeof(struct expr));

    					(yyval.expression) = new_expr(const_num_e,newnode,NULL,((yyvsp[(1) - (1)].intValue)),"",'\0',NULL);

					}
    break;

  case 98:
#line 1192 "syntax.y"
    {
			            result = malloc(50 * sizeof(char)); sprintf(result,"%f", ((yyvsp[(1) - (1)].floatValue)));
			            struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
			            newnode->value.var = malloc(sizeof(struct variable));
			            newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
			            strcpy(newnode->value.var->name, result);
			            (yyval.expression) = (struct expr *)malloc(sizeof(struct expr));
			            (yyval.expression) = new_expr(const_num_e,newnode,NULL,((yyvsp[(1) - (1)].floatValue)),"",'\0',NULL);


					}
    break;

  case 99:
#line 1205 "syntax.y"
    { argumentF( (yyvsp[(1) - (1)].stringValue), yylineno, (scope + 1)); }
    break;

  case 101:
#line 1206 "syntax.y"
    { printf(RED "idlist:: empty\n" RESET); }
    break;

  case 102:
#line 1209 "syntax.y"
    { argumentF(((yyvsp[(2) - (2)].stringValue)), yylineno, (scope+1)); }
    break;

  case 104:
#line 1210 "syntax.y"
    { printf(RED "multi_idlists:: empty\n" RESET); }
    break;

  case 105:
#line 1213 "syntax.y"
    {

				emit(jump,NULL,NULL,NULL,yylineno,999); /*Sto telos tis else*/
				//Kanoume patch to jump mesa stin else se periptosi pou apotixei i if
				quads[((int)(yyvsp[(1) - (4)].intValue))].label=QuadNo+1;
				//Pername stin tmp mas to quad no tis kainourgias jump ekso apo tin else
				(yyvsp[(1) - (4)].intValue)=QuadNo-1;

			}
    break;

  case 106:
#line 1221 "syntax.y"
    {
				//Pigenoume sto quad tis jump pano apo tin else kai kanoume patch to label sto quad kato apo tin
   			 	//teleftaia entoli toy stmt tis else !!!
				printf(RED "if(exprsession) stmt else stmt\n" RESET);
				quads[((int)(yyvsp[(1) - (6)].intValue))].label=QuadNo+1;
	}
    break;

  case 107:
#line 1227 "syntax.y"
    {
			 printf(RED "if(exprsession) stmt\n" RESET);
			 //Pigenoume sto quad tis jump kai kanoume patch to label sto quad kato apo tin
		 	//teleftaia entoli toy stmt !!!
		 	quads[((int)(yyvsp[(1) - (3)].intValue))].label=QuadNo+1;
	}
    break;

  case 108:
#line 1235 "syntax.y"
    {

				if (exprflag) {
				   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
				   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

				   emit(assign,true_expr,NULL,(yyvsp[(3) - (3)].expression),yylineno,0);
				   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
				   emit(assign,false_expr,NULL,(yyvsp[(3) - (3)].expression),yylineno,0);
				   exprflag=0;
				  patchLists(((yyvsp[(3) - (3)].expression)),(int)QuadNo-2,(int)QuadNo);
			   }
				struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
				emit(if_eq,(yyvsp[(3) - (3)].expression),true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tou if
				emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis if
				//Pername sto if_start to index tou quad tis jump
				(yyval.intValue)=QuadNo-1;
			}
    break;

  case 109:
#line 1254 "syntax.y"
    {
					insideLoop--;
					emit(jump,NULL,NULL,NULL,yylineno,(yyvsp[(1) - (3)].intValue)); //$1 quadno stin arxi tou sxpr tis while
					quads[((int)(yyvsp[(2) - (3)].intValue))].label=QuadNo+1;
					printf(RED "while(expr) stmt\n" RESET);
					patchFlow((yyvsp[(1) - (3)].intValue),QuadNo+1);
			}
    break;

  case 110:
#line 1262 "syntax.y"
    {(yyval.intValue)=QuadNo+1;}
    break;

  case 111:
#line 1265 "syntax.y"
    { insideLoop++; }
    break;

  case 112:
#line 1265 "syntax.y"
    {

						if (exprflag) {
						   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						   emit(assign,true_expr,NULL,(yyvsp[(3) - (3)].expression),yylineno,0);
						   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						   emit(assign,false_expr,NULL,(yyvsp[(3) - (3)].expression),yylineno,0);
						   exprflag=0;
						   patchLists(((yyvsp[(3) - (3)].expression)),(int)QuadNo-2,(int)QuadNo);
					   }


						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,(yyvsp[(3) - (3)].expression),true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tis while
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis while


						}
    break;

  case 113:
#line 1285 "syntax.y"
    {(yyval.intValue)=QuadNo-1;
            }
    break;

  case 114:
#line 1289 "syntax.y"
    { insideLoop++; push_E(exprflag); exprflag=0; }
    break;

  case 115:
#line 1289 "syntax.y"
    {exprflag=pop_E();}
    break;

  case 116:
#line 1289 "syntax.y"
    {

				printf(RED "for(elist; expr;elist) stmt\n" RESET);
				insideLoop--;
				emit(jump,NULL,NULL,NULL,yylineno,(yyvsp[(7) - (11)].intValue)+1); /*jump stin arxi tou 2ou elist*/
				quads[(int)(yyvsp[(7) - (11)].intValue)-1].label=QuadNo+1; /*gia to jump sto telos tou for */
				quads[(int)(yyvsp[(7) - (11)].intValue)-2].label=(yyvsp[(9) - (11)].intValue)+1; /*if_eq jump arxi for*/
				quads[(int)(yyvsp[(9) - (11)].intValue)-1].label=(yyvsp[(4) - (11)].intValue)+1; /*gia jump sto cond tis for*/

				patchFlow((int)(yyvsp[(7) - (11)].intValue)+1,(int)QuadNo+1);

			}
    break;

  case 117:
#line 1304 "syntax.y"
    {printf(RED "for_elist:: \n" RESET); (yyval.intValue)=QuadNo;  }
    break;

  case 118:
#line 1305 "syntax.y"
    { printf(RED "for_elist:: empty\n" RESET); }
    break;

  case 119:
#line 1309 "syntax.y"
    {
						if (exprflag) {
						   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						   emit(assign,true_expr,NULL,(yyvsp[(1) - (1)].expression),yylineno,0);
						   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						   emit(assign,false_expr,NULL,(yyvsp[(1) - (1)].expression),yylineno,0);
						   exprflag=0;
						  patchLists(((yyvsp[(1) - (1)].expression)),(int)QuadNo-2,(int)QuadNo);
					   }


						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,(yyvsp[(1) - (1)].expression),true_expr,NULL,yylineno,999); // jump stin arxi tis for
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis for
						(yyval.intValue)=QuadNo;
					}
    break;

  case 120:
#line 1328 "syntax.y"
    {

                  emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika stin arxi tis for
                  (yyval.intValue)=QuadNo;
	      }
    break;

  case 121:
#line 1334 "syntax.y"
    {
				if (exprflag) {

					struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					emit(assign,true_expr,NULL,(yyvsp[(2) - (3)].expression),yylineno,0);
					emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					emit(assign,false_expr,NULL,(yyvsp[(2) - (3)].expression),yylineno,0);
					exprflag=0;

					patchLists(((yyvsp[(2) - (3)].expression)),(int)QuadNo-2,(int)QuadNo);
				}


					printf(RED "return expression; \n" RESET);
					emit(ret,NULL,NULL,(yyvsp[(2) - (3)].expression),yylineno,0);
					emit(jump,NULL,NULL,NULL,yylineno,999);//end of func
				}
    break;

  case 122:
#line 1353 "syntax.y"
    {
                        printf(RED "return; \n" RESET);
                        emit(ret,NULL,NULL,NULL,yylineno,0);
                        emit(jump,NULL,NULL,NULL,yylineno,999);//end of func
                  }
    break;


/* Line 1267 of yacc.c.  */
#line 3327 "y.tab.c"
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


#line 1360 "syntax.y"


