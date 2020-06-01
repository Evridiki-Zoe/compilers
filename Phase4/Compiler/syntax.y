%{
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
    struct call* callexpr;
}
%type<intValue>         INTEGER if_start whilestart whilecond funcstart for_cond for_end for_elist epsilon
%type<floatValue>       FLOAT
%type<stringValue>      IDENTIFIER STRING
//%type<stringValue>    //  lvalue
%type<expression>      arexpr boolResexpr funcname funcdef call expr const term primary number assignmexpr lvalue elist objectdef multi_exprs_for_table elist_for_table TRUE FALSE NIL indexed  indexedelem  multi_indexedelem member multi_exprs
%type<callexpr>        callsuffix methodcall normcall

/*MHN ALLAKSETE SEIRA SE AYTA GIATI EXOUN PROTERAIOTHTA*/
%right	EQ
%left	      OR
%left		  AND
%nonassoc	EQUAL NEQUAL
%nonassoc	GREATER GREATER_EQUAL LESS LESS_EQUAL
%left	      PLUS MINUS
%left	      MULT DIV MOD
%right	NOT PPLUS MMINUS UMINUS
%left	      DOT DOTS
%left	      L_SBRACKET R_SBRACKET
%left	      L_PARENTHES R_PARENTHES
%left	      L_CBRACKET R_CBRACKET

%left       ELSE

%%
/*grammar rules*/
program  :  multi_stmts
         ;

multi_stmts : {current_rvals = 0;
		} stmt {rvalues = current_rvals;} multi_stmts { printf(RED "stmt multi_stmt\n" RESET);}
            | /*empty*/ {printf(RED "multi_stmts empty\n" RESET);}
            ;

stmt	: expr SEMICOLON  { printf(RED "expression \n" RESET);
					if (exprflag) {

						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						emit(assign,true_expr,NULL,$1,yylineno,0);
						emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						emit(assign,false_expr,NULL,$1,yylineno,0);
						exprflag=0;

						patchLists(($1),(int)QuadNo-2,(int)QuadNo);
					}


      }
      | ifstmt 	{ printf(RED "if stmt \n" RESET); }
      | whilestmt 	{ printf(RED "while stmt \n" RESET); }
      | forstmt 	{ printf(RED "for stmt \n" RESET); }
      | returnstmt  {

		  printf(RED "return stmt \n" RESET);
		  if( insideFunc > 0){ push_R((int)QuadNo-1); }
		  else {
				printf("Error: RETURN STMT outside of function in line %d\n",yylineno);
				exit(EXIT_FAILURE);
			}


	  }
      | BREAK SEMICOLON {
                        printf(RED "break \n" RESET);
	                  if( insideLoop > 0) {
	                      	emit(jump,NULL,NULL,NULL,yylineno,999);
					push_B((int)QuadNo-1);
	                  } else {
	                        printf("Error: BREAK STMT outside of loop in line %d\n",yylineno);
	                        exit(EXIT_FAILURE);
	                  }
	}
      | CONTINUE SEMICOLON {  printf(RED "continue \n" RESET);
                              if( insideLoop > 0) {
                              	emit(jump,NULL,NULL,NULL,yylineno,999);
						push_C((int)QuadNo-1);
                              } else {
                                    printf("Error: CONTINUE STMT outside of loop in line %d\n",yylineno);
                                    exit(EXIT_FAILURE);
                              }
      }
      | block { printf(RED "block \n" RESET);}
      | funcdef { printf(RED "funcdef \n" RESET);}
      | SEMICOLON { printf(RED "semicolon \n" RESET);}
      ;

expr :
		assignmexpr {


	 result =malloc(5*sizeof(char));
	 sprintf(result,"_%d",rvalues++);
	 struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);




	 if($1->type == tableitem_e){
		 struct expr* tempexp = new_expr(tableitem_e,newnode,NULL,0,"",'\0',NULL);
		 emit(tablegetelem,$1,$1->index,tempexp,yylineno,0);

	 }else{
		 $$ = new_expr(arithmeticexp_e,newnode,NULL,0,"",'\0',NULL); //TODO mporei na mhn thelei arithmeticexp edw

		 emit(assign,$1,NULL,$$,yylineno,0);
	 }
	 printf("assignment exprsession\n" );
 }
 	| 	boolResexpr { $$=$1; exprflag=1; $$->apotimimeno=1;
		addTruelist(($$),(int)QuadNo-2);
		addFalselist(($$),(int)QuadNo-1);
	}
	| 	arexpr { $$=$1; }
	|  	expr AND  {

		 struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );


		if (!$1->apotimimeno) {
			emit(if_eq,$1,true_expr,NULL,yylineno,999);//QuadNo +4 mallon
			emit(jump,NULL,NULL,NULL,yylineno,999); // jump assign false
			addTruelist(($1),(int)QuadNo-2);
			addFalselist(($1),(int)QuadNo-1);

		}


	 } epsilon expr	{

		  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

		  if (!$5->apotimimeno) {
			 emit(if_eq,$5,true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
 			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false

			 addTruelist(($5),(int)QuadNo-2);
	 		 addFalselist(($5),(int)QuadNo-1);
		  }
		  $$ = smallFunc(boolexp_e);
		   backpatchList($1->truelist,$4+1);
		 andLists($$,$1,$5);
		 $$->apotimimeno=1;



			exprflag=1;
	}
	|	expr OR		{

			struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		 	struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			if (!$1->apotimimeno) {

				emit(if_eq,$1,true_expr,NULL,yylineno,999);//epomeno expr an true
				emit(jump,NULL,NULL,NULL,yylineno,999); // jump assign false
				addTruelist(($1),(int)QuadNo-2);
				addFalselist(($1),(int)QuadNo-1);

			}


			} epsilon expr	{



		  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
		   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

		  if (!$5->apotimimeno) {
				 emit(if_eq,$5,true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
	 			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false
				 addTruelist(($5),(int)QuadNo-2);
	 			 addFalselist(($5),(int)QuadNo-1);
		  }

			    $$ = smallFunc(boolexp_e);
				$$->apotimimeno=1;
				backpatchList($1->falselist,$4+1);
				orLists($$,$1,$5);


	 exprflag=1;
	}
	|	NOT expr {
			printf(RED "NOT expression\n" RESET);

			struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			if (!$2->apotimimeno) {
  			  emit(if_eq,$2,true_expr,NULL,yylineno,999);//ass true an true h methepomeno gia pollapla and (?)
   			 emit(jump,NULL,NULL,NULL,yylineno,999); // jump assing false
			 addTruelist(($2),(int)QuadNo-2);
			 addFalselist(($2),(int)QuadNo-1);
       		exprflag = 1;
  		  }

		   $$ = smallFunc(boolexp_e);
		   notLists($2,$$);

		  $$->apotimimeno=1;
		if (exprflag) {

			emit(assign,true_expr,NULL,$$,yylineno,0);
			emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
			emit(assign,false_expr,NULL,$$,yylineno,0);
			exprflag=0;
			patchLists(($$),(int)QuadNo-2,(int)QuadNo);

		}else exprflag = 1;

//			patchLists(($$),(int)QuadNo-2,(int)QuadNo);


}
	|	term { $$=$1; printf(RED"term (%s)\n"RESET, $1->sym->value.var->name); }
	;

epsilon : /*empty*/ {$$=QuadNo;}

arexpr :
 		   expr PLUS expr {
				/*compile time type check*/
            if(checkTypes($1, $3) == 1) {
                  $$ = smallFunc(arithmeticexp_e);
                  emit(add, $1, $3, $$, yylineno, 0);
            }
            else{
              printf("Compile time error: cannot ADD 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",($1)->type, ($3)->type, yylineno );
              exit(EXIT_FAILURE);
            }

      }
		|  expr MINUS expr {
		    if(checkTypes($1, $3) == 1) {
		          $$ = smallFunc(arithmeticexp_e);
		          emit(sub, $1, $3, $$, yylineno, 0);
		    }
		    else{
		          printf("Compile time error: cannot sub 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",($1)->type, ($3)->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
		|  expr MULT expr {
		    if(checkTypes($1, $3) == 1) {
		          $$ = smallFunc(arithmeticexp_e);
		          emit(mul, $1, $3, $$, yylineno, 0);
		    }
		    else{
		          printf("Compile time error: cannot multiple 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",($1)->type, ($3)->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
		|  expr DIV expr {
		    if(checkTypes($1, $3) == 1) {
		          $$ = smallFunc(arithmeticexp_e);
		          emit(Div, $1, $3, $$, yylineno, 0);
		    }
		    else {
		          printf("Compile time error: cannot div 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",($1)->type, ($3)->type, yylineno );
		          exit(EXIT_FAILURE);
		    }
		}
		|  expr MOD expr {
		    if(checkTypes($1, $3) == 1) {
		          $$ = smallFunc(arithmeticexp_e);
		          emit(mod, $1, $3, $$, yylineno, 0);
		    }
		    else {
		      printf("Compile time error: cannot mod 2 numbers of different type:: expr1 is %d and expr2 is %d, line: %d\n",($1)->type, ($3)->type, yylineno );
		      exit(EXIT_FAILURE);
		    }
		}



boolResexpr :  expr GREATER expr {

	  if(checkTypes($1, $3) == 1) {
			$$ = smallFunc(boolexp_e);
	  } else {
			printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
			exit(EXIT_FAILURE);
	  }

	  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
	  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

	  emit(if_greater,$1,$3,NULL,yylineno,999);
	  emit(jump,NULL,NULL,NULL,yylineno,999);

	}
	|  expr GREATER_EQUAL expr {
			  if(checkTypes($1, $3) == 1) {
					$$ = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_greatereq,$1,$3,NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
		|  expr LESS expr {
			  if(checkTypes($1, $3) == 1) {
					$$ = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_less,$1,$3,NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
		|  expr LESS_EQUAL expr {
			  if(checkTypes($1, $3) == 1) {
					$$ = smallFunc(boolexp_e);
			  } else {
					printf("Cannot compare these two values, because they have different types, line: %d\n", yylineno);
					exit(EXIT_FAILURE);
			  }

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_lesseq,$1,$3,NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
		|  expr EQUAL expr {

			  //compile time type check
			  if( ($1)->type == 1 && ($3)->type == 11 ){ //table and nil ok
			  }
			  else if(oneIsVar($1, $3)) {
					//ok
			  }

			  $$ = smallFunc(boolexp_e);

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_eq,$1,$3,NULL,yylineno,999);
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}
		|  expr NEQUAL expr {
			  if( ($1)->type ==1 && ($3)->type ==11 ){
					//table and nil ok
			  }
			  else if(oneIsVar($1, $3)) {
					//ok
			  }


			  $$ = smallFunc(boolexp_e);

			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			  struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			  emit(if_not_eq,$1,$3,NULL,yylineno,999);//THELEI SWSTO LABEL
			  emit(jump,NULL,NULL,NULL,yylineno,999);

		}



//=============================================================//=============================================================



term  : L_PARENTHES {
	push_E(exprflag); exprflag=0;
} expr R_PARENTHES { printf(RED " (expression) \n" RESET);

          $$ = $3;
		  if (exprflag == 1) {
			  struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

  			emit(assign,true_expr,NULL,$$,yylineno,0);
  			emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
  			emit(assign,false_expr,NULL,$$,yylineno,0);
			exprflag=0;
  			patchLists(($$),(int)QuadNo-2,(int)QuadNo);
  		}


		 exprflag=pop_E();

      }
      | MINUS expr %prec UMINUS  {

            printf(RED " - expression \n" RESET);
            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);
            tmpnode = malloc(sizeof(struct symbol_table_binding));
            tmpnode =insertVar(result,yylineno,scope);
            tmpexpr=malloc(sizeof(struct expr));
            tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
            emit(uminus,$2,NULL,tmpexpr,yylineno,0);
            $$ = tmpexpr;
   	}

      | PPLUS lvalue {
	      printf(RED "++lvalue\n" RESET);
            check_for_funcname($2->sym->value.var->name);

            if($2->type == 1){
			  	$$= member_item($2, $2->sym->value.var->name);
			  	//new expr for number 1
			  	struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

				emit(add,$$,tmp_one,$$,yylineno,0);
        		emit(table_setelem,$2->index,$$,$2,yylineno,0);
        } else{
                  result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
    			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
    			   	tmpnode =insertVar(result,yylineno,scope);
    			   	tmpexpr=malloc(sizeof(struct expr));
    			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
      				//new expr for number 1
              struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(add,$2,tmp_one,$2,yylineno,0);
      			emit(assign,$2,NULL,tmpexpr,yylineno,0);
              $$ = tmpexpr;
              }
	}
      | lvalue  PPLUS {
	      check_for_funcname($1->sym->value.var->name);
            result =malloc(5*sizeof(char));
  			sprintf(result,"_%d",rvalues++);

          		  if($1->type == 1){
                   struct expr* temp_expr;
          			   temp_expr= member_item($1, $1->sym->value.var->name);

          			   tmpnode =insertVar(result,yylineno,scope);
             			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
             			 //new expr for number 1
                   struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

             			 emit(assign,temp_expr,NULL,tmpexpr,yylineno,0);
          				 emit(add,temp_expr,tmp_one,temp_expr,yylineno,0);
          				 emit(table_setelem,$1->index,temp_expr,$1,yylineno,0);

                   $$ = tmpexpr;
          		  } else {
          			  tmpnode =insertVar(result,yylineno,scope);
          			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
          			   //new expr for number 1
          			 struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

          			emit(assign,$1,NULL,tmpexpr,yylineno,0);
          			emit(add,$1,tmp_one,$1,yylineno,0);
          	   			$$ = tmpexpr;
          		  }


	}
      | MMINUS lvalue {
          check_for_funcname($2->sym->value.var->name);
  				printf(RED "--lvalue\n" RESET);

				if($2->type == 1){
	  			  $$= member_item($2, $2->sym->value.var->name);
	  			  //new expr for number 1
	  			  struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

	  			  emit(sub,$$,tmp_one,$$,yylineno,0);
	  			  emit(table_setelem,$2->index,$$,$2,yylineno,0);
	  	  } else{
      				result =malloc(5*sizeof(char));
      			  sprintf(result,"_%d",rvalues++);

    			   	tmpnode = malloc(sizeof(struct symbol_table_binding));
    			   	tmpnode =insertVar(result,yylineno,scope);
    			   	tmpexpr=malloc(sizeof(struct expr));
    			   	tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
    				  //new expr for number 1
              struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(sub,$2,tmp_one,$2,yylineno,0);
    			emit(assign,$2,NULL,tmpexpr,yylineno,0);

              $$ = tmpexpr;
          }

  	}
      | lvalue  MMINUS {
            check_for_funcname($1->sym->value.var->name);
            printf(RED "lvalue--\n" RESET);

            result =malloc(5*sizeof(char));
            sprintf(result,"_%d",rvalues++);

      		  if($1->type == 1){
               struct expr* temp_expr;
      			   temp_expr= member_item($1, $1->sym->value.var->name);

      			   tmpnode =insertVar(result,yylineno,scope);
         			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
         			 //new expr for number 1
               struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

         			 emit(assign,temp_expr,NULL,tmpexpr,yylineno,0);
      				 emit(sub,temp_expr,tmp_one,temp_expr,yylineno,0);
      				 emit(table_setelem,$1->index,temp_expr,$1,yylineno,0);

               $$ = tmpexpr;
      		  }else{
      			  tmpnode =insertVar(result,yylineno,scope);
      			 tmpexpr = new_expr(0,tmpnode,NULL,0,"",'\0',NULL);
      			   //new expr for number 1
      			 struct expr* tmp_one = new_expr(const_num_e,number_one,NULL,1,"",'\0',NULL);

      			emit(assign,$1,NULL,tmpexpr,yylineno,0);
      			emit(sub,$1,tmp_one,$1,yylineno,0);
      	   			$$ = tmpexpr;
      		  }

			}
      | primary { printf(RED "primary\n" RESET); $$=$1;  }
      ;

assignmexpr   : lvalue { if(!arrayFlag && ref)   check_for_funcname($1->sym->value.var->name); push_E(exprflag); exprflag=0; } EQ expr {
							     arrayFlag = 0;
                   				 ref = 1;

								 if (exprflag) {
					 				struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					 				struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					 				emit(assign,true_expr,NULL,$4,yylineno,0);
					 				emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					 				emit(assign,false_expr,NULL,$4,yylineno,0);
									exprflag=0;

									patchLists(($4),(int)QuadNo-2,(int)QuadNo);

					 			}

                   if($1->type == tableitem_e){

                        emit(table_setelem,$1->index,$4,$1,yylineno,0);

                        struct symbol_table_binding *tmp_index = malloc(sizeof(struct symbol_table_binding));
                        tmp_index->value.var = malloc(sizeof(struct variable));
                        tmp_index->value.var->name = malloc((strlen($1->index->sym->value.var->name) + 1) * sizeof(char));
                        strcpy(tmp_index->value.var->name, $1->index->sym->value.var->name);
                        tmp_index->next = NULL;

                        struct expr*  returned_exp = new_expr(tableitem_e,tmp_index,$1,0,"",'\0',NULL);
                        $$ = $1;
                   }else{
							            emit(assign,$4,NULL,$1,yylineno,0);
										printf("assign kanoniko\n" );
                   }
				   exprflag=pop_E();
						  }
              ;

primary  : lvalue { printf(RED "primary:: lvalue \n" RESET); $$=$1;
            if($1->type == 1 ){
                  $1 = member_item($1, $1->sym->value.var->name);
            }
            $$=$1;
         }
         | call {printf(RED "primary:: call %s \n" RESET,$1->sym->value.var->name);

         }
         | objectdef { printf(RED "primary:: objectdef\n" RESET);

                $$ = $1;
         }
         | L_PARENTHES  funcdef  R_PARENTHES { printf(RED "primary:: (funcdef)\n" RESET); $$ = $2; exprflag=pop_E(); }
         | const { printf(RED "primary:: const\n" RESET);  $$=$1; }
         ;

lvalue   : IDENTIFIER {
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode= insertVar( yylval.stringValue, yylineno, scope);
            if(tmpnode->symbol_type == 3) $$=new_expr(2,tmpnode,NULL,0,"",'\0',NULL);
						else if(tmpnode->symbol_type == 4) $$=new_expr(3,tmpnode,NULL,0,"",'\0',NULL);
            else $$=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);

            }
         | LOCAL IDENTIFIER {
						printf(RED "lvalue:: local identifier\n" RESET);
						tmpnode=malloc(sizeof(struct symbol_table_binding));
						tmpnode = localVar( yylval.stringValue, yylineno, scope);
						$$=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);}
         | DCOLON IDENTIFIER {
            tmpnode=malloc(sizeof(struct symbol_table_binding));
            if((tmpnode=global_exists($2)) == NULL) {
                  printf("\"%s\" undeclared, (first use here), line: %d\n", $2, yylineno);
                  exit(EXIT_FAILURE);
            }
			if (tmpnode->symbol_type==user) $$=new_expr(programfunc_e,tmpnode,NULL,0,"",'\0',NULL);
			else if (tmpnode->symbol_type==library) $$=new_expr(libfunc_e,tmpnode,NULL,0,"",'\0',NULL);
		    else   $$=new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);

            printf( RED "lvalue:: doublecolon\n" RESET);}
         | member { printf(RED "lvalue:: member %s type %d\n" RESET, $1->sym->value.var->name, $1->type);
            $$ = $1;

         }
         ;

member : lvalue DOT IDENTIFIER {
            $$ = member_item($1, $3);
         }
         | lvalue L_SBRACKET expr R_SBRACKET {
                arrayFlag = 1;
                printf(RED"member:: lvalue[expression]\n"RESET);

				$1 = emit_iftable_item($1);
				$$ = new_expr(tableitem_e,$1->sym,$3,0,"",'\0',NULL);

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

              struct expr* tmp_exression = member_item($1, $3); //prepei to $1 na einai table item
              $$ = tmp_exression;


         }
         | call L_SBRACKET expr R_SBRACKET { \
            arrayFlag = 1;

            printf(RED "member:: call[expression]\n" RESET);
            struct symbol_table_binding *tmp_symbol_id = malloc(sizeof(struct symbol_table_binding));
            tmp_symbol_id->value.var = malloc(sizeof(struct variable));
            tmp_symbol_id->value.var->name = malloc((strlen($3->sym->value.var->name) + 1) * sizeof(char));
            strcpy(tmp_symbol_id->value.var->name, $3->sym->value.var->name);
            tmp_symbol_id->next = NULL;
            //adespoto symbol pou den prepei na mpei sto hash!

            struct expr* tmpexpr_id= new_expr(tableitem_e,tmp_symbol_id,NULL,0,"",'\0',NULL);

            $1->index = tmpexpr_id;

            struct expr* tmp_exression = member_item($1, $3->sym->value.var->name); //prepei to $1 na einai table item
            $$ = tmp_exression;

         }
         ;

call   : call L_PARENTHES elist R_PARENTHES {

				printf(RED "call:: call (elist)\n" RESET);

        //printf("1) make call type %d\n", $3->type);
        $$ = make_call($1, $3);

 			}
       | lvalue callsuffix {

          $1 = emit_iftable_item($1);
          if ($2->method ){
                struct expr* t = $1;
                t->next = $2->elist;
                $1 = emit_iftable_item(member_item(t, $2->name));
                $2->elist = t ;

          }
       //   printf("2) make call type %d\n", $2->elist->type);
          $$ = make_call($1, $2->elist);
				}
       | L_PARENTHES funcdef R_PARENTHES L_PARENTHES elist R_PARENTHES {
		   			printf(RED "call:: (funcdef)(elist)\n" RESET);
//            printf("3) make call type %d\n", $3->type);
          $$ = make_call($2, $5);

  			}
       ;

callsuffix : normcall { printf(RED"callsuffix:: (elist)\n"RESET);

                $$ = $1;
           }
           | methodcall { printf(RED "callsuffix:: ..id(elist)\n" RESET);
                $$ = $1;
           }
           ;

normcall : L_PARENTHES elist R_PARENTHES  {
              $$ = malloc(sizeof(struct call));
              $$->elist = $2;
//              $$->elist->type = $2->type;
              $$->method = 0;
              $$->name = NULL;

         }
         ;

methodcall : DOTS IDENTIFIER L_PARENTHES elist R_PARENTHES { printf(RED "methodcall\n" RESET);
                $$ = malloc(sizeof(struct call));
                $$->elist = $4;
//              $$->elist->type = $2->type;
                $$->method = 1;
                $$->name = $2;
           }
           ;

elist : expr multi_exprs {
	 				args++;

          struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
          newnode->value.var = malloc(sizeof(struct variable));
          newnode->value.var->name = malloc((strlen($1->sym->value.var->name) + 1) * sizeof(char));
          strcpy(newnode->value.var->name, $1->sym->value.var->name);
          newnode->value.var->line = yylineno;
          newnode->symbol_type = 1;
          newnode->value.var->scope = scope;
          newnode->next = NULL;

          struct expr* temp_elem = new_expr(var_e,newnode,NULL,0,"",'\0',$2);


          $$ = $1;
          $$->next = $2; ///edw

		  if (exprflag) {
			 struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
			 struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

			 emit(assign,true_expr,NULL,$1,yylineno,0);
			 emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
			 emit(assign,false_expr,NULL,$1,yylineno,0);
			 exprflag=0;
			patchLists(($1),(int)QuadNo-2,(int)QuadNo);
		 }
	}
      | /*emty*/ { printf(RED "elist:: empty\n" RESET);
                args = 0;
                struct expr* temp_elem = new_expr(var_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                $$ = temp_elem;
      }
      ;

multi_exprs	:  COMMA expr multi_exprs {
					args++;

          struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
          newnode->value.var = malloc(sizeof(struct variable));
          newnode->value.var->name = malloc((strlen($2->sym->value.var->name) + 1) * sizeof(char));
          strcpy(newnode->value.var->name, $2->sym->value.var->name);
          newnode->value.var->line = yylineno;
          newnode->symbol_type = 1;
          newnode->value.var->scope = scope;
          newnode->next = NULL;

          struct expr* temp_elem = new_expr(var_e,newnode,NULL,0,"",'\0',$3);
          // bazw sto next to epomeno stoixeio

                  if (exprflag) {
                         struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
                         struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

                         emit(assign,true_expr,NULL,$2,yylineno,0);
                         emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
                         emit(assign,false_expr,NULL,$2,yylineno,0);
                         exprflag=0;
                        patchLists(($2),(int)QuadNo-2,(int)QuadNo);
                 }

          $$ = $2;
          $$->next = $3; ///edw
	}
      |  /*empty*/ { printf(RED "multi exprsessions: empty\n" RESET);
                  args = 0; //mallon eixe ksexastei ayto
                  struct expr* temp_elem = new_expr(var_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                  $$ = NULL;
      }
      ;



objectdef   :  L_SBRACKET elist_for_table R_SBRACKET  {
                  printf(RED "objectdef:: elist\n" RESET);

                  result =malloc(5*sizeof(char));
                  sprintf(result,"_%d",rvalues++);
                  struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
                  struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
                  emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);

                  struct expr* tmp = $2;
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
                  $$ = tmp_table;// epistrefw pros ta panw olo to table
            }
            |  L_SBRACKET indexed R_SBRACKET {

                   printf(RED "objectdef:: indexed\n" RESET);
				   result =malloc(5*sizeof(char));
				   sprintf(result,"_%d",rvalues);
				   struct symbol_table_binding* newnode =insertVar(result,yylineno,scope);
				   struct expr* tmp_table = new_expr(newtable_e,newnode,NULL,0,"",'\0',NULL);
				   emit(tablecreate,NULL,NULL,tmp_table,yylineno,0);


                   struct expr* tmp = $2;

                    $$ = tmp_table;// epistrefw pros ta panw olo to table

                    int i = 0;
                    while(tmp!= NULL) {
                          printf("indexed table %d kai index(%s) val(%s)", i, tmp->index->sym->value.var->name, tmp->sym->value.var->name);
						  emit(table_setelem,tmp->index,tmp,tmp_table,yylineno,0);
                          tmp = tmp->next;
                          i++;
                    }
            }
            ;


//------------------------------------------

elist_for_table   : expr multi_exprs_for_table  {
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
                $1->next= $2;
//new_expr(tableitem_e,$1->sym,$1->index,0,"",'\0',$2);
                $$ = $1;
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
                             $2->next = $3;
                             $$ = $2; //pernaw to neo expression me to next, sto $$

                        }
                      	|  /*empty*/ {
                              struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                              $$ = NULL;//temp_elem;
                      }
                    	;

//------------------------------------------


indexed     : indexedelem  multi_indexedelem {

                printf(RED "indexed:: indexedelement multi\n" RESET);
                struct expr* expr_with_next = new_expr(tableitem_e,$1->sym,$1->index,0,"",'\0',$2);
                $1->next=$2;// = expr_with_next;
				$$=$1;

                }
            ;

multi_indexedelem	: COMMA indexedelem multi_indexedelem {
                         printf(RED "multi_indexedelem:: comma indelem multi\n" RESET);
						//
                        // struct expr* expr_with_next = new_expr(tableitem_e,$2->sym,$2->index,0,"",'\0',$3);
                        // $$ = expr_with_next;
						$2->next=$3;
						$$=$2;
                        }
                  | /*empty*/ {
                        printf(RED "multi_indexedelem:: empty\n" RESET);
                    //    struct expr* temp_elem = new_expr(tableitem_e,NULL,NULL,0,"",'\0',NULL); //to teleutaio eina null
                        $$ = NULL;
                  }
                  ;

indexedelem	  : L_CBRACKET expr  {
	if (exprflag) {
	   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
	   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

	   emit(assign,true_expr,NULL,$2,yylineno,0);
	   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
	   emit(assign,false_expr,NULL,$2,yylineno,0);
	   exprflag=0;
	  patchLists(($2),(int)QuadNo-2,(int)QuadNo);
   }
}
	COLON expr R_CBRACKET {
					if (exprflag) {
					   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					   emit(assign,true_expr,NULL,$5,yylineno,0);
					   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					   emit(assign,false_expr,NULL,$5,yylineno,0);
					   exprflag=0;
					  patchLists(($5),(int)QuadNo-2,(int)QuadNo);
				   }

				   $5->index=$2;
				   $$=$5;

              }
              ;

block   :  L_CBRACKET { scope++; if(scope > maxScope) maxScope = scope; }multi_stmts R_CBRACKET {hide_symbols(scope); scope--;  printf( RED "block:: {stmt multi stmt}\n" RESET ); }
        ;

funcdef  :  funcstart funcname  L_PARENTHES {push_SP(tmpoffset); tmpoffset=0; insideFunc++;} idlist R_PARENTHES {  $2->sym->value.func->totalArgs=tmpoffset; tmpoffset=0; make_not_accessible(scope+1);  push_E(exprflag); exprflag=0; } block {
			  make_accessible_again(scope+1);
			  insideFunc--;
			  emit(funcend,$2,NULL,NULL,yylineno,0);
			  $2->sym->value.func->totalVars=tmpoffset;
			  $2->sym->value.func->funcAddress=$1+2;//+1 gia indexing apo to 0 +1 giati to $1 einai to jump

			  $$=$2;
			  quads[(int)$1].label=QuadNo+1;
			  tmpoffset=pop_SP();

			  patchReturn((int)$1,(int)QuadNo);
			  exprflag=pop_E();
		   	}

         ;
funcstart : FUNCTION { emit(jump,NULL,NULL,NULL,yylineno,999); $$=QuadNo-1; }


funcname : IDENTIFIER {
					tmpnode=malloc(sizeof(struct symbol_table_binding));
					tmpnode= newFunction( $1, yylineno, scope);
					tmpexpr=malloc(sizeof(struct expr));
					tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);

					emit(funcstart,tmpexpr,NULL,NULL,yylineno,0);
					$$=tmpexpr;
			}
		 | /*empty*/ {
					 result = malloc(2 * sizeof(char)); sprintf(result, "^%d", unnamedFuncs++);
					 tmpnode=malloc(sizeof(struct symbol_table_binding));
					 tmpnode=newFunction(result, yylineno, scope);
					 tmpexpr=malloc(sizeof(struct expr));
					 tmpexpr = new_expr(2,tmpnode,NULL,0,"",'\0',NULL);


					 emit(funcstart,tmpexpr,NULL,NULL,yylineno,0);
					 free(result);
					 $$=tmpexpr;
		 }

const    : number {		$$=$1; 	}
         | STRING 	{
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
     					result = malloc(50 * sizeof(char)); sprintf(result,"%f", ($1));

    					struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
    					newnode->value.var = malloc(sizeof(struct variable));
    					newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
    					strcpy(newnode->value.var->name, result);
    					$$ = (struct expr *)malloc(sizeof(struct expr));

    					$$ = new_expr(const_num_e,newnode,NULL,($1),"",'\0',NULL);

					}
         | FLOAT	{
			            result = malloc(50 * sizeof(char)); sprintf(result,"%f", ($1));
			            struct symbol_table_binding* newnode = malloc(sizeof(struct symbol_table_binding));
			            newnode->value.var = malloc(sizeof(struct variable));
			            newnode->value.var->name = malloc((strlen(result) + 1) * sizeof(char));
			            strcpy(newnode->value.var->name, result);
			            $$ = (struct expr *)malloc(sizeof(struct expr));
			            $$ = new_expr(const_num_e,newnode,NULL,($1),"",'\0',NULL);


					}
         ;

idlist   : IDENTIFIER { argumentF( $1, yylineno, (scope + 1)); } multi_id
         | /*empty*/ { printf(RED "idlist:: empty\n" RESET); }
         ;

multi_id  : COMMA IDENTIFIER { argumentF(($2), yylineno, (scope+1)); } multi_id
          | /*empty*/ { printf(RED "multi_idlists:: empty\n" RESET); }
          ;

ifstmt  : if_start  R_PARENTHES  stmt  ELSE  {

				emit(jump,NULL,NULL,NULL,yylineno,999); /*Sto telos tis else*/
				//Kanoume patch to jump mesa stin else se periptosi pou apotixei i if
				quads[((int)$1)].label=QuadNo+1;
				//Pername stin tmp mas to quad no tis kainourgias jump ekso apo tin else
				$1=QuadNo-1;

			}  stmt {
				//Pigenoume sto quad tis jump pano apo tin else kai kanoume patch to label sto quad kato apo tin
   			 	//teleftaia entoli toy stmt tis else !!!
				printf(RED "if(exprsession) stmt else stmt\n" RESET);
				quads[((int)$1)].label=QuadNo+1;
	}
      | if_start  R_PARENTHES stmt   {
			 printf(RED "if(exprsession) stmt\n" RESET);
			 //Pigenoume sto quad tis jump kai kanoume patch to label sto quad kato apo tin
		 	//teleftaia entoli toy stmt !!!
		 	quads[((int)$1)].label=QuadNo+1;
	}
      ;

if_start: IF L_PARENTHES expr {

				if (exprflag) {
				   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
				   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

				   emit(assign,true_expr,NULL,$3,yylineno,0);
				   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
				   emit(assign,false_expr,NULL,$3,yylineno,0);
				   exprflag=0;
				  patchLists(($3),(int)QuadNo-2,(int)QuadNo);
			   }
				struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
				emit(if_eq,$3,true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tou if
				emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis if
				//Pername sto if_start to index tou quad tis jump
				$$=QuadNo-1;
			}

whilestmt : whilestart whilecond stmt  {
					insideLoop--;
					emit(jump,NULL,NULL,NULL,yylineno,$1); //$1 quadno stin arxi tou sxpr tis while
					quads[((int)$2)].label=QuadNo+1;
					printf(RED "while(expr) stmt\n" RESET);
					patchFlow($1,QuadNo+1);
			};

whilestart : WHILE {$$=QuadNo+1;}
			;

whilecond : L_PARENTHES{ insideLoop++; } expr {

						if (exprflag) {
						   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						   emit(assign,true_expr,NULL,$3,yylineno,0);
						   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						   emit(assign,false_expr,NULL,$3,yylineno,0);
						   exprflag=0;
						   patchLists(($3),(int)QuadNo-2,(int)QuadNo);
					   }


						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,$3,true_expr,NULL,yylineno,QuadNo+3); // jump stin arxi tis while
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis while


						}
						R_PARENTHES {$$=QuadNo-1;
            }
		;

forstmt : FOR  L_PARENTHES { insideLoop++; push_E(exprflag); exprflag=0; } for_elist {exprflag=pop_E();} SEMICOLON  for_cond  SEMICOLON for_end R_PARENTHES stmt {

				printf(RED "for(elist; expr;elist) stmt\n" RESET);
				insideLoop--;
				emit(jump,NULL,NULL,NULL,yylineno,$7+1); /*jump stin arxi tou 2ou elist*/
				quads[(int)$7-1].label=QuadNo+1; /*gia to jump sto telos tou for */
				quads[(int)$7-2].label=$9+1; /*if_eq jump arxi for*/
				quads[(int)$9-1].label=$4+1; /*gia jump sto cond tis for*/

				patchFlow((int)$7+1,(int)QuadNo+1);

			}

;

for_elist : expr multi_exprs {printf(RED "for_elist:: \n" RESET); $$=QuadNo;  }
        | /*emty*/ { printf(RED "for_elist:: empty\n" RESET); }
        ;


for_cond : expr  {
						if (exprflag) {
						   struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						   struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

						   emit(assign,true_expr,NULL,$1,yylineno,0);
						   emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
						   emit(assign,false_expr,NULL,$1,yylineno,0);
						   exprflag=0;
						  patchLists(($1),(int)QuadNo-2,(int)QuadNo);
					   }


						struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
						emit(if_eq,$1,true_expr,NULL,yylineno,999); // jump stin arxi tis for
						emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika sto telos tis for
						$$=QuadNo;
					};

for_end : for_elist {

                  emit(jump,NULL,NULL,NULL,yylineno,999); //Kanonika stin arxi tis for
                  $$=QuadNo;
	      };

returnstmt	: RETURN expr  SEMICOLON {
				if (exprflag) {

					struct expr* true_expr = new_expr(constbool_e,true_expr_sym,NULL,0,"",1,NULL );
					struct expr* false_expr = new_expr(constbool_e,false_expr_sym,NULL,0,"",0,NULL );

					emit(assign,true_expr,NULL,$2,yylineno,0);
					emit(jump,NULL,NULL,NULL,yylineno,QuadNo+3);
					emit(assign,false_expr,NULL,$2,yylineno,0);
					exprflag=0;

					patchLists(($2),(int)QuadNo-2,(int)QuadNo);
				}


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
