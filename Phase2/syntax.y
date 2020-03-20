%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

int yyerror(char* s);

extern int yylineno;
extern char * yytext;
extern int scope;

char *result;
int unnamedFuncs = 0;

int isFunction = 1;

char** table;
void print_table();
int global_exists(const char *name);

int newFunction(char* name, int line,int tmpscope);
int argumentF(char *name, int line, int scope);
int insert_hash_table(char *name, int sym_type, int line, bool active, int scope);

int localVar(const char *name, int line, int scope);

void insertVar(const char* name, int line,int tmpscope);


void make_not_accessible(int scope);
void make_accessible_again(int scope);
void check_for_funcname(char* lvalue_name);
int check_if_exists_already(const char *name, int scope);
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
    int intValue;
    float floatValue;
    char *stringValue;
}
%type<intValue>         INTEGER
%type<floatValue>       FLOAT
%type<stringValue>      IDENTIFIER
%type<stringValue>      lvalue

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

multi_stmts : stmt multi_stmts {printf("stmt multi_stmt\n");}
            | /*empty*/{printf("multi_stmts empty\n");}
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
      |  expr PLUS expr { printf(RED "expr + exp \n" RESET);}
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
      | PPLUS lvalue { printf(RED "++lvalue\n" RESET);
                              if($2 == NULL){ /**/}
                              else{
                                    char *token;
                                    /* get the first token */
                                    token = strtok($2, " ");
                                    if(strcmp(token,"sketoid") == 0) {

                                        char * idname;
                                        idname = strtok(NULL, " ");
                                        check_for_funcname(idname);
                                    }
                              }
                      }
      | lvalue PPLUS { printf(RED "lvalue++\n" RESET);
                              if($1 == NULL){ /**/}
                              else{
                                    char *token;
                                    /* get the first token */
                                    token = strtok($1, " ");
                                    if(strcmp(token,"sketoid") == 0) {

                                        char * idname;
                                        idname = strtok(NULL, " ");
                                        check_for_funcname(idname);
                                    }
                              }
                        }
      | MMINUS lvalue { printf(RED "--lvalue\n" RESET);
                            if($2 == NULL){ /**/}
                            else{
                                  char *token;
                                  /* get the first token */
                                  token = strtok($2, " ");
                                  if(strcmp(token,"sketoid") == 0) {

                                      char * idname;
                                      idname = strtok(NULL, " ");
                                      check_for_funcname(idname);
                                  }
                            }
                      }
      | lvalue MMINUS { printf(RED "lvalue--\n" RESET);
                            if($1 == NULL){ /**/}
                            else{
                                  char *token;
                                  /* get the first token */
                                  token = strtok($1, " ");
                                  if(strcmp(token,"sketoid") == 0) {

                                      char * idname;
                                      idname = strtok(NULL, " ");
                                      check_for_funcname(idname);
                                  }
                            }
                      }
      | primary { printf(RED "primary\n" RESET); }
      ;

assignmexpr   : lvalue  EQ expr {  printf(RED "lvalue = expression\n" RESET);
                                  if($1 == NULL){ }
                                  else{
                                        char *token;
                                        /* get the first token */
                                        token = strtok($1, " ");
                                        if(strcmp(token,"sketoid") == 0) {

                                            char * idname;
                                            idname = strtok(NULL, " ");
                                            check_for_funcname(idname);
                                        }
                                  }
                          }
              ;

primary  : lvalue { printf(RED "primary:: lvalue\n" RESET); }
         | call { printf(RED "primary:: call\n" RESET); }
         | objectdef { printf(RED "primary:: objectdef\n" RESET); }
         | L_PARENTHES funcdef R_PARENTHES { printf(RED "primary:: (funcdef)\n" RESET); }
         | const { printf(RED "primary:: const\n" RESET); }
         ;

lvalue   : IDENTIFIER { printf(RED "lvalue:: id\n" RESET);
                        /*pernaw to "sketoid + idvalue" sto lvalue gia na to xrhsimopoihsw meta gia thn check*/
                        char * whole = malloc(sizeof(char)*(strlen($1)+7+1)); //7 gia to sketoid, 1 gia to \0
                        strcpy(whole,"sketoid ");
                        char* id = yylval.stringValue;
                        strcat(whole, id);
                        $$ = whole;

                        insertVar( $1, yylineno, scope);  }
         | LOCAL IDENTIFIER { printf(RED "lvalue:: local identifier\n" RESET);  localVar( $2, yylineno, scope); }
         | DCOLON IDENTIFIER { if(global_exists( $2) == 0) {
                  printf("\"%s\" undeclared, (first use here), line: %d\n", $2, yylineno); \
                  exit(EXIT_FAILURE);
            }
            printf( RED "lvalue:: doublecolon\n" RESET);}
         | member { printf(RED "lvalue:: member\n" RESET); }
         ;

member   : lvalue DOT IDENTIFIER { printf(RED "member:: lvalue.id \n" RESET); }
         | lvalue L_SBRACKET expr R_SBRACKET { printf(RED "member:: lvalue[expression]\n" RESET); }
         | call DOT IDENTIFIER { printf(RED "member:: call.id\n" RESET); }
         | call L_SBRACKET expr R_SBRACKET { printf(RED "member:: call[expression]\n" RESET); }
         ;

call   : call L_PARENTHES elist R_PARENTHES { check_if_exists_already(yylval.stringValue, scope); printf(RED "call:: call (elist)\n" RESET); }
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

indexedelem	  : L_CBRACKET expr COLON expr R_CBRACKET { printf(RED "ind elem {expr:expr}\n" RESET); }
              ;

block   :  L_CBRACKET multi_stmts R_CBRACKET { printf( RED "block:: {stmt multi stmt}\n" RESET ); }
        ;

funcdef  : FUNCTION L_PARENTHES { result = malloc(2 * sizeof(char)); sprintf(result, "^%d", unnamedFuncs++); newFunction(result, yylineno, scope);} idlist R_PARENTHES { make_not_accessible(scope+1); } block  { make_accessible_again(scope+1);}
         | FUNCTION IDENTIFIER { newFunction( $2, yylineno, scope); } L_PARENTHES idlist R_PARENTHES { make_not_accessible(scope+1); } block { make_accessible_again(scope+1);}
         ;

const    : number { printf(RED "const:: number\n" RESET); }
         | STRING { printf(RED "const:: str\n" RESET); }
         | NIL { printf(RED "const:: nil\n" RESET); }
         | TRUE { printf(RED "const:: true\n" RESET); }
         | FALSE { printf(RED "const:: false\n" RESET); }
         ;

number   : INTEGER { printf(RED "integer\n" RESET); }
         | FLOAT { printf(RED "float\n" RESET); }
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

whilestmt	: WHILE L_PARENTHES expr R_PARENTHES stmt { printf(RED "while(expr) stmt\n" RESET); }
    			;

forstmt	: FOR L_PARENTHES elist SEMICOLON expr SEMICOLON elist R_PARENTHES stmt { printf(RED "for(elist; expr;elist) stmt\n" RESET); }
    		;

returnstmt	: RETURN expr  SEMICOLON {printf(RED "return expression; \n" RESET);}
    			| RETURN SEMICOLON  { printf(RED "return; \n" RESET);}
    			;

%%
