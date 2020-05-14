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

extern struct quad *quads;
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
	generate();
	return 0;
}
