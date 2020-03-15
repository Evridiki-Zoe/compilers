%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

int yyerror (char* s);
int numOfArgs = 0;

extern int yylineno;
extern char * yytext;
extern int scope;


char** argtable;
void print_table();
void arginsert(char* arg);
void newFunction(char* name, int line,int tmpscope);
void insertlocalVar(char* name, int line,int tmpscope);
void insertglobalVar(char* name, int line,int tmpscope);
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
%left	L_SBRACKET R_SBRACKET
%left	L_PARENTHES R_PARENTHES
%left	L_CBRACKET R_CBRACKET

%left ELSE



%%
/*grammar rules*/
program  :  multi_stmts
         ;

multi_stmts : stmt multi_stmts {printf("stmt multi_stmt");}
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

expr  : assignmexpr { printf(RED "ASSIGNMENT \n" RESET);}
      |  expr PLUS expr { printf(RED "expr+exp \n" RESET);}
      |  expr MINUS expr{ printf(RED "expr - expr \n" RESET);}
      |  expr MULT expr { printf(RED "expr * expr \n" RESET);}
      |  expr DIV expr { printf(RED "expr / expr \n" RESET);}
      |  expr MOD expr { printf(RED "expr mod expr \n" RESET);}
      |  expr GREATER expr { printf(RED "expr > expr \n" RESET);}
      |  expr GREATER_EQUAL expr { printf(RED "expr >= expr \n" RESET);}
      |  expr LESS expr { printf(RED "expr < expr \n" RESET);}
      |  expr LESS_EQUAL expr { printf(RED "expr < = expr \n" RESET);}
      |  expr EQUAL expr { printf(RED "expr == expr \n" RESET);}
      |  expr NEQUAL expr { printf(RED "expr != expr \n" RESET);}
      |  expr AND expr { printf(RED "expr and expr \n" RESET);}
      |  expr OR expr { printf(RED "expr or expr \n" RESET);}
      | term { printf(RED "TERM \n" RESET);}
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

primary  : lvalue { printf(RED "primary:: lvalue\n" RESET); }
         | call { printf(RED "primary:: call\n" RESET); }
         | objectdef { printf(RED "primary:: objectdef\n" RESET); }
         | L_PARENTHES funcdef R_PARENTHES { printf(RED "primary:: (funcdef)\n" RESET); }
         | const { printf(RED "primary:: const\n" RESET); }
         ;

lvalue   : IDENTIFIER { printf(RED "lvalue:: id\n" RESET); insertlocalVar(($1), yylineno, scope);  }
         | LOCAL IDENTIFIER { insertlocalVar(($2), yylineno, scope);printf("LOCAL VAR :%s\n",($2)); }
         | DCOLON IDENTIFIER { insertglobalVar(($2), yylineno, 0); printf( "lvalue:: doublecolon %s\n",($2) ); }
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


/*DEN HTAN OR AYTO POU EIXE EKEI*/
objectdef   :  L_SBRACKET elist  R_SBRACKET  { printf(RED "objectdef:: elist\n" RESET); }
            |  L_SBRACKET indexed R_SBRACKET { printf(RED "objectdef:: indexed\n" RESET); }
            ;

indexed     : indexedelem  multi_indexedelem { printf(RED "indexed:: indexedelement multi\n" RESET); }
            ;

multi_indexedelem	: COMMA indexedelem multi_indexedelem { printf(RED "multi_indexedelem:: comma indelem multi\n" RESET); }
                  | /*empty*/ { printf(RED "multi_indexedelem:: empty\n" RESET); }
                  ;

indexedelem		: L_CBRACKET expr COLON expr R_CBRACKET { printf(RED "ind elem {expr:expr}\n" RESET); }
              ;

block   :  L_CBRACKET multi_stmts R_CBRACKET { printf(RED "block:: {stmt multi stmt}\n" RESET); }
        ;

funcdef  : FUNCTION L_PARENTHES idlist R_PARENTHES block { newFunction("OTI THELETE",yylineno,scope);printf("Komple adeio onoma\n"); }
         | FUNCTION IDENTIFIER L_PARENTHES idlist R_PARENTHES block { newFunction(($2),yylineno,scope);printf("komple\n"); }
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

idlist   : IDENTIFIER multi_id { arginsert(($1)); }
         | /*empty*/ { printf(RED "idlist:: empty\n" RESET); }
         ;

multi_id  : COMMA IDENTIFIER multi_id { arginsert(($2)); }
          | /*empty*/ { printf(RED "multi_idlists:: empty\n" RESET); }
          ;

ifstmt	: IF L_PARENTHES expr R_PARENTHES stmt ELSE stmt { printf(RED "if(exprsession) stmt else stmt\n" RESET); }
        | IF L_PARENTHES expr R_PARENTHES stmt { printf(RED "if(exprsession) stmt\n" RESET); }
        ;


whilestmt	: WHILE L_PARENTHES expr R_PARENTHES stmt { printf(RED "while(expr) stmt\n" RESET); }
    			;

forstmt	: FOR L_PARENTHES elist SEMICOLON expr SEMICOLON elist R_PARENTHES stmt { printf(RED "for(elist; expr;elist) stmt\n" RESET); }
    		;

returnstmt	: RETURN expr  SEMICOLON {printf(RED "return expression; \n" RESET);}
    			| RETURN SEMICOLON  { printf(RED "return; \n" RESET);}
    			;


%%

void insertglobalVar(char* name, int line,int tmpscope){
	//Lookup an iparxei . An nai komple apla kanei reference , an oxi tin vazoume

	//if(contains...==1) return;
	//else
	insert_hash_table(name, 0, line, true, scope);
}

void insertlocalVar(char* name , int line , int scope){
	//Lookup an iparxei , an oxi insert
      if(scope == 0) {
            insert_hash_table(name, 0, line, true, scope);
      }
	insert_hash_table(name, 1, line, true, scope);
}

int main(void) {



insert_hash_table("print", 4 , 0, true, 0);
insert_hash_table("input", 4 , 0, true, 0);
insert_hash_table("objectmemberkeys", 4 , 0, true, 0);
insert_hash_table("objecttotalmembers", 4 , 0, true, 0);
insert_hash_table("objectcopy", 4 , 0, true, 0);
insert_hash_table("totalarguments", 4 , 0, true, 0);
insert_hash_table("argument", 4 , 0, true, 0);
insert_hash_table("typeof", 4 , 0, true, 0);
insert_hash_table("strtonum", 4 , 0, true, 0);
insert_hash_table("sqrt", 4 , 0, true, 0);
insert_hash_table("cos", 4 , 0, true, 0);
insert_hash_table("cos", 4 , 0, true, 0);
insert_hash_table("sin", 4 , 0, true, 0);

yyparse();

print_table();

return 0;
}
