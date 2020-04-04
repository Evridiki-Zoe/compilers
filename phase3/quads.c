#include "quads.h"
#include "parsing.h"
#include "lex.h"

double QuadsSize=1024;
double QuadNo=0;

extern struct rvalue_node* r_value_head;
extern struct quad *quads;


void initialize_quad_table(){
	quads= (struct quad*)malloc(QuadsSize * sizeof(struct quad*) );
}

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

struct expr* new_expr(expr_t expr_type, struct symbol_table_binding* sym , struct expr* index
	,double numconst ,char* strconst , unsigned char boolconst , struct expr* next){

	struct expr* expr_node = malloc(sizeof(struct expr*));

	expr_node->type = expr_type;
	expr_node->sym = sym;
	expr_node->index = index;
	expr_node->numconst=numconst;
	expr_node->strconst=strconst;
	expr_node->boolconst=boolconst;
	expr_node->next = next;

	return expr_node;

}

void emit(iopcode opcode, struct expr* arg1, struct expr* arg2, struct expr* res_expr, int line, int label){
	QuadNo++;
	if (QuadNo==QuadsSize) {
		QuadsSize*=2;
		quads= (struct quad*)realloc(quads,QuadsSize * sizeof(struct quad*) );
	}
	struct quad* new_quad = malloc(sizeof(struct quad*));
	new_quad->arg1 = malloc(sizeof(struct expr*));
	new_quad->arg2 = malloc(sizeof(struct expr* ));
	new_quad->res = malloc(sizeof(struct expr* ));
	new_quad->opcode=opcode;
	new_quad->arg1 = arg1;
	new_quad->arg2 = arg2;
	new_quad->res = res_expr;
	new_quad->line = line;
	new_quad->label = label;
	printf("%f\n",new_quad->arg1->numconst );
	quads[(int)QuadNo-1]=*new_quad;
}


void print_quads(){
	printf("------------------------------------------------\n" );
	int i;
	for ( i = 0; i < QuadNo; i++) {
		printf("%d: %d %s %s %s  \n",i,quads[i].opcode , quads[i].res->sym->value.var->name,quads[i].arg1->sym->value.var->name ,quads[i].arg2->sym->value.var->name );
	}
	printf("------------------------------------------------\n" );


}
