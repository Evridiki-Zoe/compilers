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
extern double QuadNo;
extern struct symbol_table_binding* true_expr_sym;
extern struct symbol_table_binding* false_expr_sym;
extern struct symbol_table_binding* nil_expr_sym;
extern struct symbol_table_binding* number_one;
extern char* Lex_string;

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


int flag_fortable = 0; //elpizw na brw kalutero tropo na to kanw
// kaluvei thn periptwsh tou  a().b.j.k.l; kai thn a()[b][r][w];  kai to a[7].b[8]; epeidh den grafetai to teleutaio stoixeio

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
    double floatValue;
    char *stringValue;
	struct expr* expression;
}
%type<intValue>         INTEGER
%type<floatValue>       FLOAT
%type<stringValue>      IDENTIFIER STRING
//%type<stringValue>    //  lvalue
%type<expression>      funcdef call expr const term primary number assignmexpr lvalue elist objectdef multi_exprs_for_table elist_for_table TRUE FALSE NIL indexed  indexedelem  multi_indexedelem member

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

stmt	: expr SEMICOLON  { printf(RED "expression \n" RESET);
            if(flag_fortable == 1){//ignore
            }else{
            // kaluvei thn periptwsh tou  a().b.j.k.l; kai thn a()[b][r][u][w]; epeidh den grafetai to teleutaio stoixeio
            //den tha prepe na pianei periptwseis opws: t.c.u.t.e = x; oute x = table.a.b.c.d  giati tote tha graftoun duo fores ta teleutaia
            //apparently pianei kai to a[7].b[8];

                  if($1 != NULL && $1->type == tableitem_e && $1->index !=NULL){

                  printf("EDW MESA THA PREPEI NA MPAINEI MONO STHN PERIPTWSH TYPOU: a().b.j.k.l; h a()[b][r][u]; otidhpote allo mporei na einai lathos!\n");
                      result =malloc(5*sizeof(char));
                      sprintf(result,"_%d",rvalues++);
                      struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                      struct expr* tmp_expr = new_expr(tableitem_e,newnode,NULL,0,"",'\0',NULL);
                      emit(tablegetelem,$1,$1->index,tmp_expr,yylineno,0);
                      flag_fortable = 0;
                    }
            }
      }
      | ifstmt 	{ printf(RED "if stmt \n" RESET); }
      | whilestmt 	{ printf(RED "while stmt \n" RESET); }
      | forstmt 	{ printf(RED "for stmt \n" RESET); }
      | returnstmt 	{
		  				  printf(RED "return stmt \n" RESET);
                          if( insideFunc > 0) {
                                // ok
                          } else {
                                printf("Error: RETURN STMT outside of function in line %d\n",yylineno);
                                exit(EXIT_FAILURE);
                          }
						  }
      | BREAK SEMICOLON {
		  				  printf(RED "break \n" RESET);
	                      if( insideLoop > 0) {
	                      	emit(jump,NULL,NULL,NULL,yylineno,999);
	                      } else {
	                            printf("Error: BREAK STMT outside of loop in line %d\n",yylineno);
	                            exit(EXIT_FAILURE);
	                          }
						   }
      | CONTINUE SEMICOLON { printf(RED "continue \n" RESET);
                              if( insideLoop > 0) {
                              	emit(jump,NULL,NULL,NULL,yylineno,999);
                              } else {
                                    printf("Error: CONTINUE STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              } }
      | block { printf(RED "block \n" RESET);}
      | funcdef { printf(RED "funcdef \n" RESET);}
      | SEMICOLON { printf(RED "semicolon \n" RESET);}
      ;

expr  :
      assignmexpr {

           printf("ASSIGNMENT \n");
           result =malloc(5*sizeof(char));
           sprintf(result,"_%d",rvalues++);
           struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);

           if($1->type == tableitem_e){
               flag_fortable = 1;
               struct expr* tempexp = new_expr(tableitem_e,newnode,NULL,0,"",'\0',NULL);
               emit(tablegetelem,$1->index,$1,tempexp,yylineno,0);

           }else{
               $$ = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL); //TODO mporei na mhn thelei arithmeticexp edw

               emit(assign,$1,NULL,$$,yylineno,0);
           }

       }
      |  expr PLUS expr {
		  		result =malloc(5*sizeof(char));
				sprintf(result,"_%d",rvalues++);
		  		struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);

            /*compile time type check*/
            if( ( ($1)->type == 0 || ($1)->type == 1 || ($1)->type == 8 || ($1)->type == 4 )
                        && (($3)->type == 0 || ($3)->type == 1 || ($3)->type == 8  || ($3)->type == 4) ) {
      		  		$$ = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL);
      			    emit(add,$1,$3,$$,yylineno,0);

            }
            else{
              printf("Compile time error: cannot add 2 numbers of different type:: expr1 is %d and expr2 is %d\n",($1)->type, ($3)->type );
              exit(EXIT_FAILURE);
            }
              }
      |  expr MINUS expr{

            /*compile time type check*/
            if( ( ($1)->type == 0 || ($1)->type == 1 || ($1)->type == 4 || ($1)->type == 8 )
                        && (($3)->type == 0 || ($3)->type == 1 || ($3)->type == 4  || ($3)->type == 8) ) {
          					result =malloc(5*sizeof(char));
          					sprintf(result,"_%d",rvalues++);
          					struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
          					$$ = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL);
          					emit(sub,$1,$3,$$,yylineno,0);
                }
                else{
                  printf("Compile time error: cannot sub 2 numbers of different type:: expr1 is %d and expr2 is %d\n",($1)->type, ($3)->type );
                  exit(EXIT_FAILURE);
                }
  	  			}
      |  expr MULT expr {

                /*compile time type check*/
                if( ( ($1)->type == 0 || ($1)->type == 1 || ($1)->type == 4 || ($1)->type == 8 )
                            && (($3)->type == 0 || ($3)->type == 1 || ($3)->type == 4  || ($3)->type == 8) ) {
                					result =malloc(5*sizeof(char));
                					sprintf(result,"_%d",rvalues++);
                					struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                				 	$$ = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL);
                					emit(mul,$1,$3,$$,yylineno,0);
                }
                else{
                  printf("Compile time error: cannot multiple 2 numbers of different type:: expr1 is %d and expr2 is %d\n",($1)->type, ($3)->type );
                  exit(EXIT_FAILURE);
                }
  				}
      |  expr DIV expr {

                /*compile time type check*/
                if( ( ($1)->type == 0 || ($1)->type == 1 || ($1)->type == 4 || ($1)->type == 8 )
                            && (($3)->type == 0 || ($3)->type == 1 || ($3)->type == 4  || ($3)->type == 8) ) {
                  				  	result =malloc(5*sizeof(char));
                  				  	sprintf(result,"_%d",rvalues++);
                  				  	struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                  				  	$$ = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL);
                  				  	emit(Div,$1,$3,$$,yylineno,0);
                }
                else{
                  printf("Compile time error: cannot div 2 numbers of different type:: expr1 is %d and expr2 is %d\n",($1)->type, ($3)->type );
                  exit(EXIT_FAILURE);
                }
      }
      |  expr MOD expr {

      /*compile time type check*/
      if( ( ($1)->type == 0 || ($1)->type == 1 || ($1)->type == 4 || ($1)->type == 8 )
                  && (($3)->type == 0 || ($3)->type == 1 || ($3)->type == 4  || ($3)->type == 8) ) {
          				  	result =malloc(5*sizeof(char));
          				  	sprintf(result,"_%d",rvalues++);
          				  	struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
          				  	$$ = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL);
          				  	emit(mod,$1,$3,$$,yylineno,0);
            }
            else{
              printf("Compile time error: cannot mod 2 numbers of different type:: expr1 is %d and expr2 is %d\n",($1)->type, ($3)->type );
              exit(EXIT_FAILURE);
            }
  				}
      |  expr GREATER expr {
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_greater,$1,$3,NULL,yylineno,QuadNo+3);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,$$,yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,$$,yylineno,0);

       }
      |  expr GREATER_EQUAL expr {
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_greatereq,$1,$3,NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,$$,yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,$$,yylineno,0);
      }
      |  expr LESS expr {
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_less,$1,$3,NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,$$,yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,$$,yylineno,0);

      }
      |  expr LESS_EQUAL expr {
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_lesseq,$1,$3,NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,$$,yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,$$,yylineno,0);
      }
      |  expr EQUAL expr {
            //compile time type check- MPOREI NA EINAI LATHOS
            if( ($1)->type ==1 && ($3)->type ==11 ){//table and nil ok
            }
            else if(($1)->type ==0 && (($3)->type ==1 || ($3)->type == 4 ||
                ($3)->type ==8 || ($3)->type == 9 || ($3)->type ==10 || ($3)->type ==11) ){//ok
            }
            else if( ($1)->type != ($3)->type){
                printf("Compile time error: cannot compare 2 different types! expr1 is %d and expr2 is %d\n",($1)->type, ($3)->type );
                exit(EXIT_FAILURE);
            }
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_eq,$1,$3,NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,$$,yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,$$,yylineno,0);
      }
      |  expr NEQUAL expr {
            //compile time type check- MPOREI NA EINAI LATHOS
            if( ($1)->type ==1 && ($3)->type ==11 ){//table and nil ok
            }
            else if(($1)->type ==0 && (($3)->type ==1 || ($3)->type == 4 ||
                ($3)->type ==8 || ($3)->type == 9 || ($3)->type ==10 || ($3)->type ==11) ){//ok
            }
            else if( ($1)->type != ($3)->type){
                printf("Compile time error: cannot compare 2 different types! expr1 is %d and expr2 is %d\n",($1)->type, ($3)->type );
                exit(EXIT_FAILURE);
            }
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

            struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

            emit(if_not_eq,$1,$3,NULL,yylineno,QuadNo+3);//THELEI SWSTO LABEL
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4);
            emit(assign,true_expr,NULL,$$,yylineno,0);
            emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
            emit(assign,false_expr,NULL,$$,yylineno,0);
      }
      |  expr AND expr {
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

            // struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
               // struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

               // emit(if_eq,$1,true_expr,NULL,yylineno,QuadNo+3);//epomeno expr an true
               // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+6); // jump assign false
               // emit(if_eq,$3,true_expr,NULL,yylineno,QuadNo+3);//ass true an true h methepomeno gia pollapla and (?)
               // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+4); // jump assing false
               // emit(assign,true_expr,NULL,$$,yylineno,0); //  =true
               // emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3); // jump under ass false
               // emit(assign,false_expr,NULL,$$,yylineno,0); // =false
   			emit(and,$1,$3,$$,yylineno,0);
      }
      |  expr OR expr {
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

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
  			emit(and,$1,$3,$$,yylineno,0);
      }
      | term { $$=$1; printf(RED"term\n"RESET); }
      ;

term  : L_PARENTHES expr R_PARENTHES { printf(RED " (expression) \n" RESET); }
      | MINUS expr {
		  		printf(RED " - expression \n" RESET);
				result =malloc(5*sizeof(char));
	 		   	sprintf(result,"_%d",rvalues++);
				tmpnode = malloc(sizeof(struct symbol_table_binding));
	 		   	tmpnode =insertVar(result,yylineno,scope);
				tmpexpr=malloc(sizeof(struct expr));
   			 	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
				emit(uminus,$2,NULL,tmpexpr,yylineno,0);
   			}
        | NOT expr {
              printf(RED "NOT expression\n" RESET);
            result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
                  struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                  $$ = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);

                  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
            struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",1,NULL );

                  emit(if_eq,$2,true_expr,NULL,yylineno,QuadNo+5);//THELEI SWSTO LABEL
                  emit(jump,NULL,NULL,NULL,yylineno,QuadNo+2);
                  emit(assign,true_expr,NULL,$$,yylineno,0);
                  emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
                  emit(assign,false_expr,NULL,$$,yylineno,0);

      }
      | PPLUS lvalue {
		  		printf(RED "++lvalue dassa\n" RESET);
		   		check_for_funcname(yylval.stringValue);
				result =malloc(5*sizeof(char));
			   	sprintf(result,"_%d",rvalues++);
				printf("geia\n" );
			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
			   	tmpnode =insertVar(result,yylineno,scope);
			   	tmpexpr=malloc(sizeof(struct expr));
			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
				//new expr for number 1
                struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
				// first add
				emit(add,$2,tmp_one,$2,yylineno,0);
				//then assign
			   	emit(assign,$2,NULL,tmpexpr,yylineno,0);
	   }
      | lvalue  PPLUS {
		  		check_for_funcname(yylval.stringValue);
		  		printf(RED "lvalue++\n" RESET);
				result =malloc(5*sizeof(char));
			   	sprintf(result,"_%d",rvalues++);
				printf("geia\n" );
			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
			   	tmpnode =insertVar(result,yylineno,scope);
			   	tmpexpr=malloc(sizeof(struct expr));
			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
				//new expr for number 1
                struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
				// first assing
				emit(assign,$1,NULL,tmpexpr,yylineno,0);
				//then add
				emit(add,$1,tmp_one,$1,yylineno,0);
			 }
      | MMINUS lvalue {
		  		check_for_funcname(yylval.stringValue);
				printf(RED "--lvalue\n" RESET);
				result =malloc(5*sizeof(char));
			   	sprintf(result,"_%d",rvalues++);
				printf("geia\n" );
			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
			   	tmpnode =insertVar(result,yylineno,scope);
			   	tmpexpr=malloc(sizeof(struct expr));
			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
				//new expr for number 1
                struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
				// first sub
				emit(sub,$2,tmp_one,$2,yylineno,0);
				//then assign
			   	emit(assign,$2,NULL,tmpexpr,yylineno,0);

  			}
      | lvalue  MMINUS {
		  		 check_for_funcname(yylval.stringValue);
		  		printf(RED "lvalue--\n" RESET);
				result =malloc(5*sizeof(char));
			   	sprintf(result,"_%d",rvalues++);
				printf("geia\n" );
			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
			   	tmpnode =insertVar(result,yylineno,scope);
			   	tmpexpr=malloc(sizeof(struct expr));
			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
				//new expr for number 1
                struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);
				// first assign
				emit(assign,$1,NULL,tmpexpr,yylineno,0);
				//then sub
				emit(sub,$1,tmp_one,$1,yylineno,0);
			}
      | primary { printf(RED "primary\n" RESET); $$=$1;
//      printf("(lvalue->primary is %s) and its index %s\n",$1->sym->value.var->name,$1->index->sym->value.var->name);

/*        if($1 != NULL && $1->index !=NULL){
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
            struct expr* tmp_expr = new_expr(tableitem_e,newnode,NULL,0,"",'\0',NULL);
            emit(tablegetelem,$1,$1->index,tmp_expr,yylineno,0);

          }
*/
      }
      ;

assignmexpr   : lvalue { if(!arrayFlag && ref) check_for_funcname(yylval.stringValue);  } EQ expr {
							     arrayFlag = 0;
                   ref = 1;

                //   printf("eeeeeem egww (%s)=(%s)\n\n", $1->sym->value.var->name ,$4->sym->value.var->name);
                   if($1->type != tableitem_e && $4->type == tableitem_e){
                             //gia na grafetai to d apo to x=t.a.b.c.d;
                            // printf("ASSXP:: lvalue(%s) = eq(%s with index %s) \n",$1->sym->value.var->name, $4->sym->value.var->name, $4->index->sym->value.var->name);

                             result =malloc(5*sizeof(char));
                             sprintf(result,"_%d",rvalues++);
                             struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                             struct expr* tmp_table = new_expr(var_e,newnode,NULL,0,"",'\0',NULL);

                             emit(tablegetelem,$4,$4->index,tmp_table,yylineno,0);
                             emit(assign,tmp_table,NULL,$1,yylineno,0);

                   }
                   else if($1->type == tableitem_e){
                          // printf("else if:: lvalue(%s with type %d) = eq(%s with index %s and index type %d ) \n",$1->sym->value.var->name,$1->type, $4->sym->value.var->name, $4->index->sym->value.var->name,$4->index->type);

                         if($4->index!= NULL && $4->index->type == conststring_e){
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

                        emit(table_setelem,$1->index,$4,$1,yylineno,0);
//                                          e         x 2
                        struct symbol_table_binding *tmp_index = malloc(sizeof(struct symbol_table_binding));
                        tmp_index->value.var = malloc(sizeof(struct variable));
                        tmp_index->value.var->name = malloc((strlen($1->index->sym->value.var->name) + 1) * sizeof(char));
                        strcpy(tmp_index->value.var->name, $1->index->sym->value.var->name);
                        tmp_index->next = NULL;

                        struct expr*  returned_exp = new_expr(tableitem_e,tmp_index,$1,0,"",'\0',NULL);
                        $$ = returned_exp;
                   }else{
							            emit(assign,$4,NULL,$1,yylineno,0);
                   }
						  }
              ;

primary  : lvalue { printf(RED "primary:: lvalue \n" RESET); $$=$1;  }
         | call {printf(RED "primary:: call\n" RESET);  }
         | objectdef { printf(RED "primary:: objectdef\n" RESET);
/*                result =malloc(5*sizeof(char));
                sprintf(result,"_%d",rvalues++);
                struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                struct expr* tmp_table = new_expr(boolexp_e,newnode,NULL,0,"",'\0',NULL);
                emit(tablecreate,$1,NULL,tmp_table,yylineno,0);
*/
                $$ = $1;
         }
         | L_PARENTHES funcdef R_PARENTHES { printf(RED "primary:: (funcdef)\n" RESET); }
         | const { printf(RED "primary:: const\n" RESET);  $$=$1; }
         ;

lvalue   : IDENTIFIER { printf(RED "lvalue:: id %s\n" RESET, $1);
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode= insertVar( yylval.stringValue, yylineno, scope);
						$$=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);   }
         | LOCAL IDENTIFIER {
						printf(RED "lvalue:: local identifier\n" RESET);
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode = localVar( yylval.stringValue, yylineno, scope);
						$$=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);}
         | DCOLON IDENTIFIER {
			 			tmpnode=malloc(sizeof(struct symbol_table_binding));
						if((tmpnode=global_exists($2)) == NULL) {
			                  printf("\"%s\" undeclared, (first use here), line: %d\n", $2, yylineno); \
			                  exit(EXIT_FAILURE);
			            }
						$$=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);

            printf( RED "lvalue:: doublecolon\n" RESET);}
         | member { printf(RED "lvalue:: member\n" RESET); $$ = $1;}
         ;

member   : lvalue DOT IDENTIFIER {
                printf(RED" lvalue.id\n"RESET);
                $$ = member_item($1, $3);
                //printf("(lvalue is %s) . (id is %s)\n",$1->sym->value.var->name,$3);

         }
         | lvalue L_SBRACKET expr R_SBRACKET {
                arrayFlag = 1;
                $$ = member_item($1, $3->sym->value.var->name);
                printf(RED"member:: lvalue[expression]\n"RESET);
         }
         | call DOT IDENTIFIER {

              struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
              tmp_symbol_id->value.var = malloc(sizeof(struct variable));
              tmp_symbol_id->value.var->name = malloc((strlen($3) + 1) * sizeof(char));
              strcpy(tmp_symbol_id->value.var->name, $3);
              tmp_symbol_id->next = NULL;
              //adespoto symbol pou den prepei na mpei sto hash!

              struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);

              $1->index = tmpexpr_id;
              printf("(%s)'s index is %s\n", $1->sym->value.var->name,$1->index->sym->value.var->name);

              //$1 = emit_iftable_item($1);

              //ayto sketo pernaei to a().b; !!!!!!!!!!!
              struct expr* tmp_exression = member_item($1, $3); //prepei to $1 na einai table item
              printf("MEMBER SAYS type returned is %d\n", tmp_exression->type);
              $$ = tmp_exression;


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
         | call L_SBRACKET expr R_SBRACKET { arrayFlag = 1;

              printf(RED "member:: call[expression]\n" RESET);
              struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
              tmp_symbol_id->value.var = malloc(sizeof(struct variable));
              tmp_symbol_id->value.var->name = malloc((strlen($3->sym->value.var->name) + 1) * sizeof(char));
              strcpy(tmp_symbol_id->value.var->name, $3->sym->value.var->name);
              tmp_symbol_id->next = NULL;
              //adespoto symbol pou den prepei na mpei sto hash!

              struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);

              $1->index = tmpexpr_id;
              //printf("(%s)'s index is %s\n", $1->sym->value.var->name,$1->index->sym->value.var->name);

              //$1 = emit_iftable_item($1);

              //ayto sketo pernaei to a().b; !!!!!!!!!!!
              struct expr* tmp_exression = member_item($1, $3->sym->value.var->name); //prepei to $1 na einai table item
              //printf("MEMBER SAYS type returned is %d\n", tmp_exression->type);
              $$ = tmp_exression;
         }
         ;

call   : call L_PARENTHES elist R_PARENTHES {

				printf(RED "call:: call (elist)\n" RESET);
				result =malloc(5*sizeof(char));
				sprintf(result,"_%d",rvalues++);
				tmpnode=malloc(sizeof(struct symbol_table_binding));
				tmpnode =insertVar(result,yylineno,scope);
				tmpexpr=malloc(sizeof(struct expr));
				tmpexpr= new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);
				emit(call,NULL,NULL,$1,yylineno,0);
				emit(getretval,NULL,NULL,tmpexpr,yylineno,0);
				$$=tmpexpr;
 			}
       | lvalue callsuffix {
		   			check_if_exists( $1->sym->value.var->name, scope);
          if($1->type == 1) $1 = member_item($1, $1->index->sym->value.var->name);
					emit(call,NULL,NULL,$1,yylineno,0);
					result =malloc(5*sizeof(char));
	   			 	sprintf(result,"_%d",rvalues++);
		  			 tmpnode=malloc(sizeof(struct symbol_table_binding));
		   			 tmpnode =insertVar(result,yylineno,scope);
		  			 tmpexpr=malloc(sizeof(struct expr));
		   			 tmpexpr= new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);
		  			 emit(getretval,NULL,NULL,tmpexpr,yylineno,0);
					 $$=tmpexpr;

				}
       | L_PARENTHES funcdef R_PARENTHES L_PARENTHES elist R_PARENTHES {
		   			printf(RED "call:: (funcdef)(elist)\n" RESET);
					emit(call,NULL,NULL,$2,yylineno,0);
					result =malloc(5*sizeof(char));
	   			 	sprintf(result,"_%d",rvalues++);
		  			 tmpnode=malloc(sizeof(struct symbol_table_binding));
		   			 tmpnode =insertVar(result,yylineno,scope);
		  			 tmpexpr=malloc(sizeof(struct expr));
		   			 tmpexpr= new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);
		  			 emit(getretval,NULL,NULL,tmpexpr,yylineno,0);
					 $$=tmpexpr;
	   			}
       ;

callsuffix : L_PARENTHES elist R_PARENTHES { printf(RED"callsuffix:: (elist)"RESET); }
           | DOTS IDENTIFIER L_PARENTHES elist R_PARENTHES { printf(RED "callsuffix:: ..id(elist)\n" RESET); }
           ;

elist   : expr multi_exprs {
	 				args++; printf(RED "elist:: \n" RESET);
					emit(param,$1,NULL,NULL,yylineno,0);
				}
        | /*emty*/ { printf(RED "elist:: empty\n" RESET); args = 0; }
        ;

multi_exprs	:  COMMA expr multi_exprs {
					args++; printf(RED "multiexpr commma expr exprs\n" RESET);
					emit(param,$2,NULL,NULL,yylineno,0);
				}
        	|  /*empty*/ { printf(RED "multi exprsessions: empty\n" RESET); }
      	;



/*DEN HTAN OR AYTO POU EIXE EKEI*/ //TODO prepei na epistrefoume to temp list sto objectdef
objectdef   :  L_SBRACKET elist_for_table R_SBRACKET  {
                  printf(RED "objectdef:: elist\n" RESET);

                  result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
                  struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                  struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
                  emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);

                  //edw tupwnontai ola ta stoixeia tou pinaka
                  struct expr* tmp = $2;
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

                        result = malloc(2 * sizeof(char));
                        sprintf(result, "_%d", rvalues++);
                        struct symbol_table_binding* tmp_symbol=  insertVar(result ,  yylineno , scope);
                        struct expr* temp_elem = new_expr(var_e,tmp_symbol,NULL,0,"",'\0',NULL);

                        emit(table_setelem,tmp_expr_index ,tmp , temp_elem,yylineno,0);
                        printf("ELEMENTS: %s \n", tmp->sym->value.var->name );
                        tmp = tmp->next;
                        i++;
                  }

                  $$ = tmp_table;// epistrefw pros ta panw olo to table
            }
            |  L_SBRACKET {
                    result =malloc(5*sizeof(char));
                    sprintf(result,"_%d",rvalues++);
                    struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                    struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
                    emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);

                }
            indexed R_SBRACKET {
                   printf(RED "objectdef:: indexed\n" RESET);
                   struct expr* tmp = $3;

                    while(tmp->sym!= NULL) {
                          printf("INDEXED first: %s second %s \n", tmp->sym->value.var->name, tmp->index->sym->value.var->name );
                          tmp = tmp->next;
                    }

                    result =malloc(5*sizeof(char));
                    sprintf(result,"_%d",rvalues++);
                    struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                    struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);

                    $$ = tmp_table;// epistrefw pros ta panw olo to table
            }
            ;


//------------------------------------------
//ONLY FOR TABLE ELEMENTS
// se ayta ta expr tha gietai to emit table_setelem
elist_for_table   : expr multi_exprs_for_table  {
                args++;
                //struct symbol_table_binding* newnode =insertVar($1->sym->value.var->name,yylineno,scope);
                //adespoto symbol pou den prepei na mpei sto hash!
                struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
                newnode->value.var = malloc(sizeof(struct variable));
                newnode->value.var->name = malloc((strlen($1->sym->value.var->name) + 1) * sizeof(char));
                strcpy(newnode->value.var->name, $1->sym->value.var->name);
                newnode->value.var->line = yylineno;
                newnode->symbol_type = 1;
                newnode->value.var->scope = scope;
                newnode->next = NULL;

                struct expr* temp_elem = new_expr(tableitem_e,newnode,NULL,0,"",'\0',$2);
                //DEN prepei na ginetai edw to emit giati etsi ta bazei anapoda
                // emit(table_setelem,NULL,NULL,temp_elem,yylineno,0);

                $$ = temp_elem;
        }
        | /*emty*/ {
          struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
          $$ = temp_elem;
          printf(RED "elist:: empty\n" RESET);
          args = 0;
        }
        ;

multi_exprs_for_table 	:  COMMA expr  multi_exprs_for_table  {
                             args++;

                             //adespoto symbol pou den prepei na mpei sto hash!
                             struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
                             newnode->value.var = malloc(sizeof(struct variable));
                             newnode->value.var->name = malloc((strlen($2->sym->value.var->name) + 1) * sizeof(char));
                             strcpy(newnode->value.var->name, $2->sym->value.var->name);
                             newnode->value.var->line = yylineno;
                             newnode->symbol_type = 1;
                             newnode->value.var->scope = scope;
                             newnode->next = NULL;

                             struct expr* temp_elem = new_expr(tableitem_e,newnode,NULL,0,"",'\0',$3);
                             // bazw sto next to epomeno stoixeio

                             //DEN prepei na ginetai edw to emit giati etsi ta bazei anapoda

                             $$ = temp_elem; //pernaw to neo expression me to next, sto $$

                        }
                      	|  /*empty*/ {
                              struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                              $$ = temp_elem;
                      }
                    	;

//------------------------------------------





indexed     : indexedelem  multi_indexedelem {

                printf(RED "indexed:: indexedelement multi\n" RESET);
                struct expr* expr_with_next = new_expr(tableitem_e,$1->sym,$1->index,0,"",'\0',$2);
                $$ = expr_with_next;
                }
            ;

multi_indexedelem	: COMMA indexedelem multi_indexedelem {
                        printf(RED "multi_indexedelem:: comma indelem multi\n" RESET);

                        struct expr* expr_with_next = new_expr(tableitem_e,$2->sym,$2->index,0,"",'\0',$3);
                        $$ = expr_with_next;

                        }
                  | /*empty*/ {
                        printf(RED "multi_indexedelem:: empty\n" RESET);
                        struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                        $$ = temp_elem;
                  }
                  ;

indexedelem	  : L_CBRACKET expr COLON expr R_CBRACKET { printf(RED "ind elem {expr:expr}\n" RESET);
                  result = malloc(2 * sizeof(char));
                  sprintf(result, "_%d", rvalues++);
                  struct symbol_table_binding* tmp_symbol=  insertVar(result ,  yylineno , scope);
                  struct expr* temp_elem = new_expr(tableitem_e,tmp_symbol,NULL,0,"",'\0',NULL);
                  emit(table_setelem,$2,$4,temp_elem,yylineno,0);

                  //adespoto symbol pou den prepei na mpei sto hash!
                  struct symbol_table_binding *newnode1 = malloc(sizeof(struct symbol_table_binding));
                  newnode1->value.var = malloc(sizeof(struct variable));
                  newnode1->value.var->name = malloc((strlen($2->sym->value.var->name) + 1) * sizeof(char));
                  strcpy(newnode1->value.var->name, $2->sym->value.var->name);
                  newnode1->value.var->line = yylineno;
                  newnode1->symbol_type = 1;
                  newnode1->value.var->scope = scope;
                  newnode1->next = NULL;

                  struct symbol_table_binding *newnode2 = malloc(sizeof(struct symbol_table_binding));
                  newnode2->value.var = malloc(sizeof(struct variable));
                  newnode2->value.var->name = malloc((strlen($4->sym->value.var->name) + 1) * sizeof(char));
                  strcpy(newnode2->value.var->name, $4->sym->value.var->name);
                  newnode2->value.var->line = yylineno;
                  newnode2->symbol_type = 1;
                  newnode2->value.var->scope = scope;
                  newnode2->next = NULL;

                  struct expr* expr_for_symbol2 = new_expr(tableitem_e,newnode2,NULL,0,"",'\0',NULL);

                  struct expr* new_elem_withboth = new_expr(tableitem_e,newnode1,expr_for_symbol2,0,"",'\0',NULL);
                  $$ = new_elem_withboth;

              }
              ;

block   :  L_CBRACKET { scope++; if(scope > maxScope) maxScope = scope; }multi_stmts R_CBRACKET {hide_symbols(scope); scope--;  printf( RED "block:: {stmt multi stmt}\n" RESET ); }
        ;

funcdef  : FUNCTION L_PARENTHES {
				insideFunc++; result = malloc(2 * sizeof(char)); sprintf(result, "^%d", unnamedFuncs++);
				tmpnode=malloc(sizeof(struct symbol_table_binding));
				tmpnode=newFunction(result, yylineno, scope);
				tmpexpr=malloc(sizeof(struct expr));
				tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);


				emit(jump,NULL,NULL,NULL,yylineno,999); // jump sto telos tis func
  			  	emit(funcstart,tmpexpr,NULL,NULL,yylineno,0);
      			free(result);
			} idlist R_PARENTHES { make_not_accessible(scope+1); } block  {

				 make_accessible_again(scope+1); insideFunc--;
				 tmpexpr=malloc(sizeof(struct expr));

				 //Thelei to expr tou function
				 emit(funcend,NULL,NULL,NULL,yylineno,0);
			}

         | FUNCTION IDENTIFIER {
			 tmpnode=malloc(sizeof(struct symbol_table_binding));
			 tmpnode= newFunction( $2, yylineno, scope);
			 tmpexpr=malloc(sizeof(struct expr));
			 tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);
			  emit(jump,NULL,NULL,NULL,yylineno,999); // jump sto telos tis func
			  emit(funcstart,tmpexpr,NULL,NULL,yylineno,0);

		  	}
			   L_PARENTHES { insideFunc++;} idlist R_PARENTHES { make_not_accessible(scope+1); } block {
			  make_accessible_again(scope+1); insideFunc--;
			  tmpnode=malloc(sizeof(struct symbol_table_binding));
 			  tmpnode= SearchFunction( $2);
 			  tmpexpr=malloc(sizeof(struct expr));
 			  tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);
			  emit(funcend,tmpexpr,NULL,NULL,yylineno,0);
			  $$=tmpexpr;
		   	}
         ;

//rvalue is const mazi me libfunc kai userfunc?

const    : number {		$$=$1;	}
         | STRING 	{
                printf("STRINGGG %s \n",Lex_string );
				tmpnode=malloc(sizeof(struct symbol_table_binding));
				tmpnode->value.var = malloc(sizeof(struct variable));
				tmpnode->value.var->name = malloc((strlen(Lex_string) + 1) * sizeof(char));
				strcpy(tmpnode->value.var->name, Lex_string);
				$$ = (struct expr *)malloc(sizeof(struct expr));
				$$ = new_expr(conststring_e,tmpnode,NULL,0,Lex_string,'\0',NULL);
			}
         | NIL	 	{ $$ = new_expr(nil_e,nil_expr_sym,NULL,0,"",'\0',NULL); }
         | TRUE 	{ $$ = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );  }
         | FALSE 	{ $$ = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL ); }
         ;

number   : INTEGER 	{
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
         | FLOAT	{
			            result = malloc(50 * sizeof(char)); sprintf(result,"%f", ($1));
			            struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
			            newnode->value.var = malloc(sizeof(struct variable));
			            newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
			            strcpy(newnode->value.var->name, result);
			            $$ = (struct expr *)malloc(sizeof(struct expr));
			            $$ = new_expr(const_num_e,newnode,NULL,($1),"",'\0',NULL);
			            printf("%f\n",$1 );
					}
         ;

idlist   : IDENTIFIER { argumentF( $1, yylineno, (scope + 1)); } multi_id
         | /*empty*/ { printf(RED "idlist:: empty\n" RESET); }
         ;

multi_id  : COMMA IDENTIFIER { argumentF(($2), yylineno, (scope+1)); } multi_id
          | /*empty*/ { printf(RED "multi_idlists:: empty\n" RESET); }
          ;

ifstmt  : if_start R_PARENTHES  stmt  ELSE  {emit(jump,NULL,NULL,NULL,yylineno,999); /*Sto telos tis else*/}  stmt { printf(RED "if(exprsession) stmt else stmt\n" RESET); }
        | if_start  R_PARENTHES  stmt  { printf(RED "if(exprsession) stmt\n" RESET); }
        ;

if_start: IF L_PARENTHES expr {
				struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
				emit(if_eq,$3,true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tou if
				emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis if
			}

whilestmt	: WHILE L_PARENTHES{ insideLoop++; } expr {

						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,$4,true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tis while
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis while

						}
						R_PARENTHES stmt {
						insideLoop--;
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika stin arxi tou expr tis  while
						printf(RED "while(expr) stmt\n" RESET); }
    			;

forstmt	: FOR L_PARENTHES { insideLoop++; } elist SEMICOLON expr {

						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,$6,true_expr,NULL,yylineno,999); // jump stin arxi tis for
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis for

					}
					 SEMICOLON elist {
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika stin arxi tis for
					}
					 R_PARENTHES stmt { emit(jump,NULL,NULL,NULL,yylineno,999); /*jump stin arxi tou 2ou elist*/ printf(RED "for(elist; expr;elist) stmt\n" RESET); insideLoop--; }
    		;

returnstmt	: RETURN expr  SEMICOLON {
					printf(RED "return expression; \n" RESET);
					emit(ret,NULL,NULL,$2,yylineno,0);
					emit(jump,NULL,NULL,NULL,yylineno,999);//end of func
				}
    			| RETURN SEMICOLON  {
					printf(RED "return; \n" RESET);
					emit(ret,NULL,NULL,NULL,yylineno,0);
					emit(jump,NULL,NULL,NULL,yylineno,999);//end of func
				}
    			;

%%
