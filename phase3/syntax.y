%{
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

struct expr *tmpexpr;
struct symbol_table_binding *tmpnode;
%}

/*%glr-parser*/
%start program /*indicates starting rule*/
%token      IF
%token      ELSE
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
    double intValue;
    float floatValue;
    char *stringValue;
	struct expr* expression;
}
%type<intValue>         INTEGER
%type<floatValue>       FLOAT
%type<stringValue>      IDENTIFIER
//%type<stringValue>    //  lvalue
%type<expression>       expr const term primary number assignmexpr lvalue

/*MHN ALLAKSETE SEIRA SE AYTA GIATI EXOUN PROTERAIOTHTA*/
%right	EQ
%left	      AND OR
%nonassoc	EQUAL NEQUAL
%nonassoc	GREATER GREATER_EQUAL LESS LESS_EQUAL
%left	      PLUS MINUS
%left	      MULT DIV MOD
%right	NOT PPLUS MMINUS
%left	      DOT DOTS
%left	      L_SBRACKET R_SBRACKET
%left	      L_PARENTHES R_PARENTHES
%left	      L_CBRACKET R_CBRACKET

%left       ELSE

%%
/*grammar rules*/
program  :  multi_stmts
         ;

multi_stmts : stmt multi_stmts { printf(RED "stmt multi_stmt\n" RESET);}
            | /*empty*/ {printf(RED "multi_stmts empty\n" RESET);}
            ;

stmt	: expr SEMICOLON  { printf(RED "expression \n" RESET); }
      | ifstmt 	{ printf(RED "if stmt \n" RESET); }
      | whilestmt 	{ printf(RED "while stmt \n" RESET); }
      | forstmt 	{ printf(RED "for stmt \n" RESET); }
      | returnstmt 	{ printf(RED "return stmt \n" RESET);
                              if( insideFunc > 0) {
                                    // ok
                              } else {
                                    printf("Error: RETURN STMT outside of function in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              } }
      | BREAK SEMICOLON { printf(RED "break \n" RESET);
                              if( insideLoop > 0) {
                              // ok
                              } else {
                                    printf("Error: BREAK STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              } }
      | CONTINUE SEMICOLON { printf(RED "continue \n" RESET);
                              if( insideLoop > 0) {
                              // ok
                              } else {
                                    printf("Error: CONTINUE STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              } }
      | block { printf(RED "block \n" RESET);}
      | funcdef { printf(RED "funcdef \n" RESET);}
      | SEMICOLON { printf(RED "semicolon \n" RESET);}
      ;

expr  : assignmexpr { printf(RED "ASSIGNMENT \n" RESET);}
      |  expr PLUS expr {
		  		result =malloc(5*sizeof(char));
				sprintf(result,"_%d",rvalues++);
		  		struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);

            if( ( ($1)->type == 0 || ($1)->type == 1 || ($1)->type == 8 || ($1)->type == 4 ) && (($3)->type == 0 || ($3)->type == 1 || ($3)->type == 8  || ($3)->type == 4) ) {
      		  		$$ = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL);
      			    emit(add,$1,$3,$$,yylineno,0);

            }
            else{
            printf("Compile time error: cannot add 2 numbers of different type:: expr1 is %d and expr2 is %d\n",($1)->type, ($3)->type );
              exit(EXIT_FAILURE);

            }
              }
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
      | term { printf(RED "TERM \n" RESET); $$=$1; }
      ;

term  : L_PARENTHES expr R_PARENTHES { printf(RED " (expression) \n" RESET); }
      | MINUS expr { printf(RED " - expression \n" RESET); }
      | NOT expr { printf(RED "NOT expression\n" RESET); }
      | PPLUS lvalue { check_for_funcname(yylval.stringValue); }
      | lvalue { check_for_funcname(yylval.stringValue); } PPLUS { printf(RED "lvalue++\n" RESET); }
      | MMINUS lvalue { check_for_funcname(yylval.stringValue); printf(RED "--lvalue\n" RESET); }
      | lvalue { check_for_funcname(yylval.stringValue);  } MMINUS { printf(RED "lvalue--\n" RESET); }
      | primary { printf(RED "primary\n" RESET); $$=$1; }
      ;

assignmexpr   : lvalue { if(!arrayFlag && ref) check_for_funcname(yylval.stringValue);  } EQ expr {
							printf(RED "lvalue = expression\n" RESET) ; arrayFlag = 0; ref = 1;
							emit(assign,$4,NULL,$1,yylineno,0);
						}
              ;

primary  : lvalue { printf(RED "primary:: lvalue \n" RESET); $$=$1;  }
         | call { printf(RED "primary:: call\n" RESET); }
         | objectdef { printf(RED "primary:: objectdef\n" RESET); }
         | L_PARENTHES funcdef R_PARENTHES { printf(RED "primary:: (funcdef)\n" RESET); }
         | const { printf(RED "primary:: const\n" RESET);  $$=$1; }
         ;

lvalue   : IDENTIFIER { printf(RED "lvalue:: id %s\n" RESET, $1);
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpexpr=malloc(sizeof(struct expr));
						tmpnode= insertVar( yylval.stringValue, yylineno, scope);
						$$=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);   }
         | LOCAL IDENTIFIER { localVar( yylval.stringValue, yylineno, scope); printf(RED "lvalue:: local identifier\n" RESET); }
         | DCOLON IDENTIFIER { if(global_exists($2) == 0) {
                  printf("\"%s\" undeclared, (first use here), line: %d\n", $2, yylineno); \
                  exit(EXIT_FAILURE);
            }
            printf( RED "lvalue:: doublecolon\n" RESET);}
         | member { printf(RED "lvalue:: member\n" RESET); }
         ;

member   : lvalue DOT IDENTIFIER { printf(RED "member:: lvalue.id \n" RESET); }
         | lvalue L_SBRACKET expr R_SBRACKET { arrayFlag = 1; printf(RED "member:: lvalue[expression]\n" RESET); }
         | call DOT IDENTIFIER { printf(RED "member:: call.id\n" RESET); }
         | call L_SBRACKET expr R_SBRACKET { arrayFlag = 1; printf(RED "member:: call[expression]\n" RESET); }
         ;

call   : call L_PARENTHES elist R_PARENTHES { printf(RED "call:: call (elist)\n" RESET); }
       | lvalue callsuffix { check_if_exists( $1->sym->value.var->name, scope); printf(RED "call:: lvalue callsuffix\n" RESET); }
       | L_PARENTHES funcdef R_PARENTHES L_PARENTHES elist R_PARENTHES { printf(RED "call:: (funcdef)(elist)\n" RESET); }
       ;

callsuffix : L_PARENTHES elist R_PARENTHES { printf(RED "callsuffix:: (elist)\n" RESET); }
           | DOTS IDENTIFIER L_PARENTHES elist R_PARENTHES { printf(RED "callsuffix:: ..id(elist)\n" RESET); }
           ;

elist   : expr multi_exprs { args++; printf(RED "elist:: \n" RESET); }
        | /*emty*/ { printf(RED "elist:: empty\n" RESET); args = 0; }
        ;

multi_exprs	:  COMMA expr multi_exprs { args++; printf(RED "multiexpr commma expr exprs\n" RESET); }
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

indexedelem	  : L_CBRACKET expr COLON expr R_CBRACKET { printf(RED "ind elem {expr:expr}\n" RESET); }
              ;

block   :  L_CBRACKET { scope++; if(scope > maxScope) maxScope = scope; }multi_stmts R_CBRACKET {hide_symbols(scope); scope--;  printf( RED "block:: {stmt multi stmt}\n" RESET ); }
        ;

funcdef  : FUNCTION L_PARENTHES { insideFunc++; result = malloc(2 * sizeof(char)); sprintf(result, "^%d", unnamedFuncs++); newFunction(result, yylineno, scope);
      free(result); } idlist R_PARENTHES { make_not_accessible(scope+1); } block  { make_accessible_again(scope+1); insideFunc--; }
         | FUNCTION IDENTIFIER { newFunction( $2, yylineno, scope); } L_PARENTHES { insideFunc++;} idlist R_PARENTHES { make_not_accessible(scope+1); } block { make_accessible_again(scope+1); insideFunc--; }
         ;

//rvalue is const mazi me libfunc kai userfunc?

const    : number {		$$=$1;	}
         | STRING { /*printf("STRINGGG %s \n",yylval.stringValue );*/ insert_rvalue_list(yylval.stringValue ,1); } //DEN EXOUME KANEI O LEX NA APOTHIKEYEI TO STRING
         | NIL {
			// insert_rvalue_list("nil" ,2);
			 result = malloc(2 * sizeof(char));  sprintf(result, "_%d", rvalues++); struct symbol_table_binding* tmp=  insertVar(result ,  yylineno , scope);

		  }
         | TRUE {
			 // insert_rvalue_list("true" ,2);
			 result = malloc(2 * sizeof(char));  sprintf(result, "_%d", rvalues++);  struct symbol_table_binding* tmp= insertVar(result ,  yylineno , scope);
		 }
         | FALSE {
			  //insert_rvalue_list("false" ,2);
			  result = malloc(2 * sizeof(char));  sprintf(result, "_%d", rvalues++); struct symbol_table_binding* tmp=  insertVar(result ,  yylineno , scope);
		  }
         ;

number   : INTEGER {
 					result = malloc(50 * sizeof(char)); sprintf(result,"%0.f", ($1));

					struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
					newnode->value.var = malloc(sizeof(struct variable));
					newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
					strcpy(newnode->value.var->name, result);
					$$ = (struct expr *)malloc(sizeof(struct expr));
					$$ = new_expr(const_num_e,newnode,NULL,($1),"",'\0',NULL);
					printf("%f\n",$1 );
					printf("%f\n",($$)->numconst );
				}
         | FLOAT { char buff[100]; sprintf(buff, "%f", yylval.floatValue); insert_rvalue_list( buff,0);   }
         ;

idlist   : IDENTIFIER { argumentF( $1, yylineno, (scope + 1)); } multi_id
         | /*empty*/ { printf(RED "idlist:: empty\n" RESET); }
         ;

multi_id  : COMMA IDENTIFIER { argumentF(($2), yylineno, (scope+1)); } multi_id
          | /*empty*/ { printf(RED "multi_idlists:: empty\n" RESET); }
          ;

ifstmt  : IF L_PARENTHES expr R_PARENTHES stmt ELSE stmt { printf(RED "if(exprsession) stmt else stmt\n" RESET); }
        | IF L_PARENTHES expr R_PARENTHES stmt { printf(RED "if(exprsession) stmt\n" RESET); }
        ;

whilestmt	: WHILE L_PARENTHES{ insideLoop++; } expr R_PARENTHES stmt { insideLoop--; printf(RED "while(expr) stmt\n" RESET); }
    			;

forstmt	: FOR L_PARENTHES { insideLoop++; } elist SEMICOLON expr SEMICOLON elist R_PARENTHES stmt {printf(RED "for(elist; expr;elist) stmt\n" RESET); insideLoop--; }
    		;

returnstmt	: RETURN expr  SEMICOLON {printf(RED "return expression; \n" RESET);}
    			| RETURN SEMICOLON  { printf(RED "return; \n" RESET);}
    			;

%%
