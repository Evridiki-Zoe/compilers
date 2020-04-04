#include "quads.h"
#include "parsing.h"
#include "lex.h"

extern struct rvalue_node* r_value_head;

void insert_rvalue_list(char* name, rvalue_type type){

	if(r_value_head == NULL) { //mhn to allaksete ayto
		struct rvalue_node* newnode = malloc(sizeof(struct rvalue_node));
		newnode->name = malloc((strlen(name) + 1) * sizeof(char));

		strcpy(newnode->name, name);
		newnode->type = type;
		newnode->next = NULL;
		r_value_head = newnode;
		return;
	}

	struct rvalue_node* newnode = malloc(sizeof(struct rvalue_node));
	newnode->name = malloc((strlen(name) + 1) * sizeof(char));

	strcpy(newnode->name, name);
	newnode->type = type;
	newnode->next = r_value_head;
	r_value_head = newnode;
}

void print_list_rvalues(){

	assert(r_value_head);
	struct rvalue_node* curr = r_value_head;

	while(curr != NULL){
			printf("RVALUE: %s, with type: %d\n", curr->name, curr->type);
			curr = curr->next;
		}

}

struct expr* new_expr(expr_t expr_type){
	struct expr* expr_node = malloc(sizeof(struct expr*));

	expr_node->type = expr_type;
//	expr_node->sym = NULL;
	expr_node->index = NULL; //??
	expr_node->next = NULL;

	return expr_node;

}

void emit(iopcode opcode, struct expr* arg1, struct expr* arg2, struct expr* res_expr, int line, int label){

	struct quad* new_quad = malloc(sizeof(struct quad*));
	new_quad->arg1 = arg1;
	new_quad->arg2 = arg2;
	new_quad->res = res_expr;
	new_quad->line = line;
	new_quad->label = label;

}
