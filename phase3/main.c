#include "lex.h"
#include "parsing.h"
#include "quads.h"


struct SymTable_struct *table = NULL;
struct alpha_token_t *head = NULL;
struct rvalue_node* r_value_head = NULL;
struct expr* true_expr;
struct expr* false_expr;
struct quad *quads=NULL;

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
	return 0;
}
