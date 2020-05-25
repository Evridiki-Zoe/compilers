#include "lex.h"
#include "parsing.h"
#include "quads.h"
#include "targetCode.h"
#include "y.tab.h"

int yyparse();

struct SymTable_struct *table = NULL;
struct alpha_token_t *head = NULL;
struct rvalue_node* r_value_head = NULL;
struct symbol_table_binding* true_expr_sym;
struct symbol_table_binding* false_expr_sym;
struct symbol_table_binding* nil_expr_sym;
struct symbol_table_binding* number_one;


int scope_spaces[50];
int flow_Break[50];
int flow_Continue[50];
int flow_Return[50];
int tmpoffset=0;
int exprflag_stack[50];

int trueList[100];
int falseList[100];



int main(void) {

	initialize_quad_table();
	table = malloc(sizeof(struct SymTable_struct));

	table->pinakas = malloc(SIZE* sizeof(struct symbol_table_binding *));//oxi calloc, tha to diorthwsw kapoia stigmh
	table->total_size = 0;

	stringConsts = (char**) malloc(50 * sizeof(char*)); //pianw 50 theseis gia ta strings
	totalStringConsts=0;

	numConsts = (double *) malloc(50 * sizeof(double)); //pianw 100 theseis gia numbers
	totalNumConsts = 0 ;

	namedLibfuncs = (char**) malloc(50 * sizeof(char*)); //pianw 50 theseis gia ta libfunc
	totalNamedLibfuncs=0;

	userFuncs = (struct userfunc**) malloc(50 * sizeof(struct userfunc*)); //pianw 50 theseis gia ta user's func
	totalUserFuncs=0;

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
	insert_hash_table("sin", 4 , 0, true, 0);




	yyparse();

	print_table();
//	print_list_rvalues();
	print_quads();

	add_rval_libfuncs("print");
	add_rval_libfuncs("input");
	add_rval_libfuncs("objectmemberkeys");
	add_rval_libfuncs("objecttotalmembers");
	add_rval_libfuncs("objectcopy");
	add_rval_libfuncs("totalarguments");
	add_rval_libfuncs("argument");
	add_rval_libfuncs("typeof");
	add_rval_libfuncs("strtonum");
	add_rval_libfuncs("sqrt");
	add_rval_libfuncs("cos");
	add_rval_libfuncs("sin");



	generateIns();
	patch_incomplete_jump();
	printInstructions();

/*
	add_rval_string("lalal");
	add_rval_string("lalal2");
	add_rval_string("lalal3");
	add_rval_string("lalal4");
	add_rval_string("lalal5");

	add_rval_num(5);
	add_rval_num(3.123456789);
	add_rval_num(-9);
	add_rval_num(34);
	add_rval_num(1);

	add_rval_libfuncs("libfunc");
	add_rval_libfuncs("libfunc2");
	add_rval_libfuncs("libfunc3");
	add_rval_libfuncs("libfunc4");
	add_rval_libfuncs("libfunc5");


	add_rval_userfuncs("userfunc",4,3,2);
	add_rval_userfuncs("userfunc2",1,3,3);
	add_rval_userfuncs("userfunc3",2,3,7);
*/
printf("=========strings:============\n" );

	int j=0;
	while (j< totalStringConsts) {
		 printf("%s \n", stringConsts[j]);
		j++;
	}
printf("=========nums:============\n" );
	j=0;
	while (j< totalNumConsts) {
		 printf("%f \n", numConsts[j]);
		j++;
	}

	printf("========lib funcs:============\n" );
	j=0;
	while (j< totalNamedLibfuncs) {
		 printf("%s \n", namedLibfuncs[j]);
		j++;
	}
	printf("========user funcs:============\n" );
	j=0;
	while (j< totalUserFuncs) {
		 printf("%s #args %d   locals %d address %d\n", userFuncs[j]->id, userFuncs[j]->totalargs,userFuncs[j]->localSize, userFuncs[j]->address);
		j++;
	}




printf("\n\n");

 create_bin();

// read_binfile();
	return 0;
}
