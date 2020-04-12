#include "quads.h"
#include "parsing.h"
#include "lex.h"

double QuadsSize=1024;
double QuadNo=0;

extern struct rvalue_node* r_value_head;
extern struct quad *quads;
extern struct SymTable_struct *table;
extern struct symbol_table_binding* true_expr_sym;
extern struct symbol_table_binding* false_expr_sym;
extern struct symbol_table_binding* nil_expr_sym;
extern struct symbol_table_binding* number_one;

extern int yylineno, scope;
extern int rvalues;

extern int  scope_spaces[];
extern int 	flow_Break[50];
extern int flow_Continue[50];
extern int flow_Return[50];
int stack_top=-1;
int break_top=-1;
int continue_top=-1;
int return_top=-1;


char* enum_toString_opCodes(iopcode sym) {
	switch (sym) {
		case 0:
				return "assign";
		case 1:
				return "add";
		case 2:
				return "sub";
		case 3:
				return "mul";
	    case 4:
				return "div";
		case 5:
				return "mod";
		case 6:
				return "uminus";
		case 7:
				return "and";
		case 8:
				return "or";
		case 9:
				return "not";
		case 10:
				return "if_eq";
		case 11:
				return "if_not_eq";
		case 12:
				return "if_lesseq";
		case 13:
				return "if_greatereq";
		case 14:
				return "if_less";
	    case 15:
				return "if_greater";
		case 16:
				return "call";
		case 17:
				return "param";
		case 18:
				return "return";
		case 19:
				return "getretval";
		case 20:
				return "funcstart";
		case 21:
				return "funcend";
		case 22:
				return "tablecreate";
		case 23:
				return "tablegetelem";
		case 24:
				return "table_setelem";
		case 25:
				return "jump";
		default:
				return "not compatible type";

	}
}


void initialize_quad_table(){
	quads= (struct quad*)malloc(QuadsSize * sizeof(struct quad) );

	true_expr_sym=malloc(sizeof(struct symbol_table_binding));
	false_expr_sym=malloc(sizeof(struct symbol_table_binding));
	nil_expr_sym=malloc(sizeof(struct symbol_table_binding));
	number_one=malloc(sizeof(struct symbol_table_binding));

	true_expr_sym->value.var = malloc(sizeof(struct variable));
	true_expr_sym->value.var->name = malloc(5* sizeof(char));
	strcpy(true_expr_sym->value.var->name, "true");// newnode->value.var->name = name;
	true_expr_sym->value.var->line = 0;
	true_expr_sym->symbol_type = 4;
	true_expr_sym->value.var->scope = 0;

	false_expr_sym->value.var = malloc(sizeof(struct variable));
	false_expr_sym->value.var->name = malloc(5 * sizeof(char));
	strcpy(false_expr_sym->value.var->name, "false");// newnode->value.var->name = name;
	false_expr_sym->value.var->line = 0;
	false_expr_sym->symbol_type = 4;
	false_expr_sym->value.var->scope = 0;

	nil_expr_sym->value.var = malloc(sizeof(struct variable));
	nil_expr_sym->value.var->name = malloc(5* sizeof(char));
	strcpy(nil_expr_sym->value.var->name, "nil");// newnode->value.var->name = name;
	nil_expr_sym->value.var->line = 0;
	nil_expr_sym->symbol_type = 4;
	nil_expr_sym->value.var->scope = 0;

	number_one->value.var = malloc(sizeof(struct variable));
	number_one->value.var->name = malloc(5* sizeof(char));
	strcpy(number_one->value.var->name, "1");// newnode->value.var->name = name;
	number_one->value.var->line = 0;
	number_one->symbol_type = 4;
	number_one->value.var->scope = 0;



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

	struct expr* expr_node = malloc(sizeof(struct expr));

	expr_node->index = malloc(sizeof(struct expr ));
	expr_node->next = malloc(sizeof(struct expr ));
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
		printf("realloc in emit\n" );
		quads= (struct quad*)realloc(quads,QuadsSize * sizeof(struct quad) );
	}
	struct quad* new_quad = malloc(sizeof(struct quad));
	printf("type: %d\n", opcode);
	new_quad->arg1 = malloc(sizeof(struct expr ));
	new_quad->arg2 = malloc(sizeof(struct expr ));
	new_quad->res = malloc(sizeof(struct expr ));
	new_quad->opcode=opcode;
	new_quad->arg1 = arg1;
	new_quad->arg2 = arg2;
	new_quad->res = res_expr;
	new_quad->line = line;
	new_quad->label = label;
//	printf("emit :: %f\n",new_quad->arg1->numconst );
	quads[(int)QuadNo-1]=*new_quad;
}



struct symbol_table_binding* SearchFunction(char* name){
		int hash = 0;
		struct symbol_table_binding *curr;
		hash = hash_function(name);//briskw pou kanei hash to stoixeio
		curr = table->pinakas[hash];

		while (curr) {
			if(strcmp(name, curr->value.var->name) == 0 && curr->active == true) {
				return curr;
			}
			curr = curr->next;
		}
		curr = NULL;
		return curr;
}


struct expr* emit_iftable_item(struct expr* exp){

		if(exp->type != tableitem_e){
		//	printf("den eimai table %s \n",exp->sym->value.var->name);
			 return exp;
		 }
		else {
	//		printf("eimai table %s \n",exp->sym->value.var->name);

  		char *name =malloc(5*sizeof(char));
      sprintf(name,"_%d",rvalues++);
      struct symbol_table_binding* newnode =insertVar(name,yylineno,scope);
     	struct expr* result = new_expr(var_e,newnode,exp->index,0,"",'\0',NULL);
//mporei na thelei result = new_expr(var_e,newnode,exp->index,0,"",'\0',NULL);
			emit(tablegetelem,exp,exp->index,result,yylineno,0);
			return result;
		}
}

struct expr* member_item(struct expr* lvalue ,char* name){
			lvalue = emit_iftable_item(lvalue);

			struct symbol_table_binding *newnode = malloc(sizeof(struct symbol_table_binding));
			newnode->value.var = malloc(sizeof(struct variable));
			newnode->value.var->name = malloc((strlen(name) + 1) * sizeof(char));
			strcpy(newnode->value.var->name,name);
			newnode->value.var->line = yylineno;
			newnode->symbol_type = 1;
			newnode->value.var->scope = scope;
			newnode->next = NULL;

			struct expr* index = new_expr(conststring_e,newnode,NULL,0,name,'\0',NULL);
			struct expr* item = new_expr(tableitem_e,lvalue->sym,index,0,"",'\0',NULL);
			return item;
}

struct expr* make_call (struct expr* lv, struct expr* elist) {
			 struct expr* func = emit_iftable_item(lv);

			 /*ftiaxnw ena reversed list mesa se ena stack*/
			 struct expr* reversed_stack[20];
			 int rev_stack_top=-1;

			 while (elist != NULL && elist->sym != NULL) {
    				rev_stack_top++; //push
				 		reversed_stack[rev_stack_top] =  malloc(sizeof(struct expr));
					  reversed_stack[rev_stack_top] = elist;//push
						//	emit(param, NULL, NULL, elist,yylineno,0);
						elist = elist->next;
				}
				while(rev_stack_top>=0){
							emit(param, NULL, NULL,reversed_stack[rev_stack_top],yylineno,0); //pop
							rev_stack_top -= 1;//pop
				}
				emit(call, func,NULL, NULL,yylineno,0);
				char* name =malloc(5*sizeof(char));
				sprintf(name,"_%d",rvalues++);
				struct symbol_table_binding* tmpnode=malloc(sizeof(struct symbol_table_binding));
				tmpnode =insertVar(name,yylineno,scope);
				struct expr* result = new_expr(var_e,tmpnode,NULL,0,"",'\0',NULL);
				emit(getretval,NULL,NULL,result,yylineno,0);
				return result;
}


//proto orisma to quad pou prepei na paei se periptosi continue , to deftero se periptosi break
int patchFlow(double con,double bre){
	int tmp=-1;
//For breaks
	if (!isEmptyB()) tmp=pop_B();


	while (tmp >= con ) {
		printf("Break at quad %d\n",tmp );
		quads[tmp].label=bre;

		if (!isEmptyB()) tmp=pop_B();
		else break;
	}
	if(tmp < con) push_B(tmp); // An vrike break ekso apo tin trexousa loupa

	//----------------
	if (!isEmptyC()) tmp=pop_C();
	else return 0;

	while (tmp >= con ) {

		quads[tmp].label=con;

		if (!isEmptyC()) tmp=pop_C();
		else break;
	}
	if(tmp < con) push_C(tmp); // An vrike continue ekso apo tin trexousa loupa


	return 0;
}

int patchReturn(int from , int to){
	int tmp;
	if (!isEmptyR()) tmp=pop_R();
	else return 0;

	while (tmp >= from ) {

		quads[tmp].label=to;

		if (!isEmptyR()) tmp=pop_R();
		else break;
	}
	if(tmp < from) push_R(tmp); // An vrike continue ekso apo tin trexousa loupa


	return 0;

}


void print_quads(){
	int i;
	FILE *fp;

	fp = stdout;
	//fp = fopen ("quads.txt","w"); // gia na grapsei se arxeio

	fprintf(fp,"------------------------------------------------\n" );

	for ( i = 0; i < QuadNo; i++) {

		fprintf(fp, "%d: %s",i+1,enum_toString_opCodes(quads[i].opcode) );

		if(quads[i].opcode== 0){ //gia to assign
			if (quads[i].res!=NULL) {
				if( quads[i].res->sym !=NULL)
				fprintf(fp," %s", quads[i].res->sym->value.var->name );
			}
			if (quads[i].arg1->sym!=NULL) fprintf(fp," %s",quads[i].arg1->sym->value.var->name);
			fprintf(fp,"  [line %d]\n",quads[i].line );

			continue;
		}
		else if(quads[i].opcode>= 10 && quads[i].opcode<= 15  ){//gia to if_eq
			if (quads[i].arg1!=NULL) {
				if( quads[i].arg1->sym !=NULL)
				fprintf(fp," %s", quads[i].arg1->sym->value.var->name );
			}
			fprintf(fp," %s",quads[i].arg2->sym->value.var->name);
			fprintf(fp," %d",quads[i].label );
			fprintf(fp,"  [line %d]\n",quads[i].line );

			continue;
		}
		if (quads[i].opcode==25) {
			fprintf(fp," %d",quads[i].label );
		}

		if (quads[i].res!=NULL) {
			if( quads[i].res->sym !=NULL)
			fprintf(fp," %s\t", quads[i].res->sym->value.var->name );

		/*	if (quads[i].res->index!=NULL) {
				if( quads[i].res->index->sym !=NULL)
				printf(" (INDEX %s)", quads[i].res->index->sym->value.var->name );
			}*/
		}
		if (quads[i].arg1!=NULL) {
			if( quads[i].arg1->sym !=NULL)
			fprintf(fp," %s\t", quads[i].arg1->sym->value.var->name );
		}
		if (quads[i].arg2!=NULL) {
			if( quads[i].arg2->sym !=NULL)
			fprintf(fp," %s\t", quads[i].arg2->sym->value.var->name );
		}

		fprintf(fp,"  [line %d]\n",quads[i].line );
	}
	fprintf(fp,"------------------------------------------------\n" );

	fclose (fp);

}


//Stack functions


int pop_SP(){
	int data = scope_spaces[stack_top];
	stack_top -= 1;
	return data;
}

int push_SP(int num){
	stack_top++;
    scope_spaces[stack_top] = num;
	return 0;
}

int pop_B(){
	int data = flow_Break[break_top];
	break_top -= 1;

	return data;
}

int push_B(int num){

	break_top++;
    flow_Break[break_top] = num;
	return 0;
}

int isEmptyB(){
	if (break_top<0) return 1;
	else return 0;
}
//------------------------------------------------------

int pop_C(){
	int data = flow_Continue[continue_top];
	continue_top -= 1;

	return data;
}
//gia to stack continue

int push_C(int num){
	printf("%d\n",num );
	continue_top++;
    flow_Continue[continue_top] = num;
	return 0;
}

int isEmptyC(){
	if (continue_top<0) return 1;
	else return 0;
}

//------------------------------------------------------

int pop_R(){
	int data = flow_Return[return_top];
	return_top -= 1;

	return data;
}
//gia to stack return

int push_R(int num){
	printf("%d\n",num );
	return_top++;
    flow_Return[return_top] = num;
	return 0;
}

int isEmptyR(){
	if (return_top<0) return 1;
	else return 0;
}
