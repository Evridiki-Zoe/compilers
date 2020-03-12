%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

int yyerror (char* s);
int global_scope; // current scope we are right now, as we do the syntactic analysis

extern int yylineno;
extern char * yyval;
extern char * yytext;


%}

/*%glr-parser*/
%start program /*indicates starting rule*/
%token IF
%token  ELSE
%token	WHILE
%token	FOR
%token	FUNCTION
%token	RETURN
%token	BREAK
%token	CONTINUE
%token	AND
%token	NOT
%token	OR
%token	LOCAL
%token	TRUE
%token	FALSE
%token 	NIL

%token	EQ
%token	PLUS
%token	MINUS
%token	MULT
%token	DIV
%token	MOD
%token	EQUAL
%token	NEQUAL
%token	PPLUS
%token	MMINUS
%token	GREATER
%token	LESS
%token	GREATER_EQUAL
%token	LESS_EQUAL

%token	SEMICOLON
%token	COMMA
%token	COLON
%token	DCOLON
%token	DOT
%token	DOTS
%token	L_CBRACKET
%token	R_CBRACKET
%token	L_SBRACKET
%token	R_SBRACKET
%token	L_PARENTHES
%token	R_PARENTHES

%token INTEGER
%token FLOAT
%token STRING
%token IDENTIFIER


/*The %union declaration modifies the type of yylval*/
%union
{
    int intValue;
    float floatValue;
    char *stringValue;
}
%type<intValue> INTEGER
%type<floatValue> FLOAT
%type<stringValue> IDENTIFIER


/*MHN ALLAKSETE SEIRA SE AYTA GIATI EXOUN PROTERAIOTHTA*/
%right	EQ
%left	AND OR
%nonassoc	EQUAL NEQUAL
%nonassoc	GREATER GREATER_EQUAL LESS LESS_EQUAL
%left	PLUS MINUS
%left	MULT DIV MOD
%right	NOT PPLUS MMINUS
%left	DOT DOTS
%left	L_SBRANCKET R_SBRANCKET
%left	L_PARENTHES R_PARENTHES
%left	L_CBRANCKET R_CBRANCKET

%left IF
%left ELSE


%%

/*description of expected inputs*/

program  :  multi_stmts
         | /*empty*/		{printf("empty statement\n");}
         ;

multi_stmts : stmt multi_stmts
            | /*empty*/
            ;

stmt	: expr SEMICOLON  { printf(RED "expression \n" RESET); }
      | ifstmt 	{ printf(RED "if stmt \n" RESET); }
      | whilestmt 	{ printf(RED "while stmt \n" RESET); }
      | forstmt 	{ printf(RED "for stmt \n" RESET); }
      | returnstmt 	{ printf(RED "return stmt \n" RESET); }
      | BREAK SEMICOLON { printf(RED "break \n" RESET);}
      | CONTINUE SEMICOLON { printf(RED "continue \n" RESET);}
      | block { printf(RED "block \n" RESET);}
      | funcdef { printf(RED "funcdef \n" RESET);}
      | SEMICOLON { printf(RED "semicolon \n" RESET);}
      ;

/*    expr 	: assignmexpr
      		| expr AND expr
      		| expr OR expr
      		| expr PLUS expr {$$ = $1 + $3;}
      		| expr MINUS expr {$$ = $1 - $3;}
      		| expr MULT expr {$$ = $1 * $3;}
      		| expr DIV expr {   if($3 == 0)
                                  yyerror("divide by zero");
                              else $$ = $1 / $3; }
      		| expr MOD expr {$$ = $1 % $3;}
      		| expr EQUAL expr
      		| expr NEQUAL expr
      		| expr GREATER expr
      		| expr LESS expr
      		| expr GREATER_EQUAL expr
      		| expr LESS_EQUAL expr
      		| term
      		;

*/
expr  : assignmexpr { printf(RED "ASSIGNMENT \n" RESET);}
      | expr op expr { printf(RED " EXPR OP EXPR\n" RESET);}
      | term { printf(RED "TERM \n" RESET);}
      ;


op    : PLUS
      | MINUS
      | MULT
      | DIV
      | MOD
      | GREATER
      | GREATER_EQUAL
      | LESS
      | LESS_EQUAL
      | EQUAL
      | NEQUAL
      | AND
      | OR
      ;

term  : L_PARENTHES expr R_PARENTHES { printf(RED " (expression) \n" RESET); }
      | MINUS expr { printf(RED " - expression \n" RESET); }
      | NOT expr { printf(RED "NOT expression\n" RESET); }
      | PPLUS lvalue { printf(RED "++lvalue\n" RESET); }
      | lvalue PPLUS { printf(RED "lvalue++\n" RESET); }
      | MMINUS lvalue { printf(RED "--lvalue\n" RESET); }
      | lvalue MMINUS { printf(RED "lvalue--\n" RESET); }
      | primary { printf(RED "primary\n" RESET); }
      ;

assignmexpr   : lvalue EQ expr { printf(RED "lvalue=expression\n" RESET); }
              ;

primary  :  lvalue { printf(RED "primary:: lvalue\n" RESET); }
         | call { printf(RED "primary:: call\n" RESET); }
         | objectdef { printf(RED "primary:: objectdef\n" RESET); }
         | L_PARENTHES funcdef R_PARENTHES { printf(RED "primary:: (funcdef)\n" RESET); }
         | const { printf(RED "primary:: const\n" RESET); }
         ;

lvalue   : IDENTIFIER { printf(RED "lvalue::\n" RESET); }
         | LOCAL IDENTIFIER { printf(RED "lvalue:: local id\n" RESET); }
         | DCOLON IDENTIFIER { printf(RED "lvalue:: doublecolon id\n" RESET); }
         | member { printf(RED "lvalue:: member\n" RESET); }
         ;

member   : lvalue DOT IDENTIFIER { printf(RED "member:: lvalue.id \n" RESET); }
         | lvalue L_SBRACKET expr R_SBRACKET { printf(RED "member:: lvalue[expression]\n" RESET); }
         | call DOT IDENTIFIER { printf(RED "member:: call.id\n" RESET); }
         | call L_SBRACKET expr R_SBRACKET { printf(RED "member:: call[expression]\n" RESET); }
         ;

call   : call L_PARENTHES elist R_PARENTHES { printf(RED "call:: call (elist)\n" RESET); }
       | lvalue callsuffix { printf(RED "call:: lvalue callsuffix\n" RESET); }
       | L_PARENTHES funcdef R_PARENTHES L_PARENTHES elist R_PARENTHES { printf(RED "call:: (funcdef)(elist)\n" RESET); }
       ;

callsuffix : L_PARENTHES elist R_PARENTHES { printf(RED "callsuffix:: (elist)\n" RESET); }
           | DOTS IDENTIFIER L_PARENTHES elist R_PARENTHES { printf(RED "callsuffix:: ..id(elist)\n" RESET); }
           ;

elist   : expr multi_exprs { printf(RED "elist:: \n" RESET); }
        | /*emty*/ { printf(RED "elist:: empty\n" RESET); }
        ;

multi_exprs	:  COMMA expr multi_exprs { printf(RED "multiexpr commma expr exprs\n" RESET); }
        		|  /*empty*/ { printf(RED "multi exprsessions: empty\n" RESET); }
        		;

objectdef   :  elist OR  indexed { printf(RED "objectdef:: \n" RESET); }
            |  /*empty*/ { printf(RED "objectdef:: empty\n" RESET); }
            ;

indexed     : indexedelem  multi_indexedelem { printf(RED "indexed:: indexedelement multi\n" RESET); }
            ;

multi_indexedelem	: COMMA indexedelem multi_indexedelem { printf(RED "multi_indexedelem:: comma indelem multi\n" RESET); }
    | /*empty*/ { printf(RED "multi_indexedelem:: empty\n" RESET); }
    ;

indexedelem		: L_CBRACKET expr COLON expr R_CBRACKET { printf(RED "ind elem {expr:expr}\n" RESET); }
              ;

block   :  L_CBRACKET  R_CBRACKET { printf(RED "block:: {}\n" RESET); }
        |  L_CBRACKET stmt multi_stmts R_CBRACKET { printf(RED "block:: {stmt multi stmt}\n" RESET); }
        ;

funcdef  : FUNCTION L_PARENTHES idlist R_PARENTHES block { printf(RED "funcdef:: function (idlist)block\n" RESET); }
         | FUNCTION IDENTIFIER L_PARENTHES idlist R_PARENTHES block { printf(RED "funcdef:: function id (idlist) block\n" RESET); }
         ;

const    : number { printf(RED "const:: number\n" RESET); }
         | STRING { printf(RED "const:: str\n" RESET); }
         | NIL { printf(RED "const:: nil\n" RESET); }
         | TRUE { printf(RED "const:: true\n" RESET); }
         | FALSE { printf(RED "const:: false\n" RESET); }
         ;

number   : INTEGER { printf("%d\n",($1)); printf(RED "integer\n" RESET); }
         | FLOAT { printf("%f\n",($1)); printf(RED "float\n" RESET); }
         ;

idlist   : IDENTIFIER multi_id { printf(RED "idlist:: id multi_id\n" RESET); }
         | /*empty*/ { printf(RED "idlist:: empty\n" RESET); }
         ;

multi_id  : COMMA IDENTIFIER multi_id { printf(RED "multi_idlists:: comma id multiid\n" RESET); }
          | /*empty*/ { printf(RED "multi_idlists:: empty\n" RESET); }
          ;

ifstmt	: IF L_PARENTHES expr R_PARENTHES stmt { printf(RED "if(exprsession) stmt\n" RESET); }
        | IF L_PARENTHES expr R_PARENTHES stmt ELSE stmt { printf(RED "if(exprsession) stmt else stmt\n" RESET); }
        ;


whilestmt	: WHILE L_PARENTHES expr R_PARENTHES stmt { printf(RED "while(expr) stmt\n" RESET); }
    			;

forstmt	: FOR L_PARENTHES elist SEMICOLON expr SEMICOLON elist R_PARENTHES stmt { printf(RED "for(elist; expr;elist) stmt\n" RESET); }
    		;

returnstmt	: RETURN expr  SEMICOLON {printf(RED "return expression; \n" RESET);}
    			| RETURN SEMICOLON  { printf(RED "return; \n" RESET);}
    			;


%%

int yyerror (char* s){
   printf("%s: at line %d, before token: '%s'\n", s, yylineno, yytext);
}
