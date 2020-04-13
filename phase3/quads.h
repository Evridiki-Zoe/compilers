#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>



/*enum for rvalue type*/
typedef enum {
	number = 0,
	string = 1,
	boolean = 2,
	nil = 3,
	function_addr = 4,
	lib_func = 5
} rvalue_type;

struct rvalue_node {
	char* name;
	rvalue_type type;
  	struct rvalue_node* next;
};

typedef enum {
	assign,
	add,
	sub,
	mul,
	Div, //oxi div alliws exei conflict me thn stdlib
	mod,
	uminus,
	and,
	or,
	not,
	if_eq,
	if_not_eq,
	if_lesseq,
	if_greatereq,
	if_less,
	if_greater,
	call,
	param,
	ret,
	getretval,
	funcstart,
	funcend,
	tablecreate,
	tablegetelem,
	table_setelem,
	jump
}iopcode;


//gia ta quads
typedef enum {
	var_e = 0,
	tableitem_e = 1,
	programfunc_e = 2,
	libfunc_e = 3,

	arithmeticexp_e = 4,
	boolexp_e = 5,
	assignexp_e = 6,
	newtable_e = 7,

	const_num_e = 8,
	constbool_e = 9,
	conststring_e = 10,
	nil_e = 11

}expr_t;

struct expr{

	expr_t type;
	struct symbol_table_binding* sym;
	struct expr* index;
	double numconst;
	char* strconst;
	unsigned char boolconst;
	struct expr* next;
};

struct quad{
	iopcode opcode;
  	struct expr* res;
  	struct expr* arg1;
  	struct expr* arg2;
	unsigned label;
	unsigned line;
};

struct call {

  struct expr* elist;
  unsigned char method;
	char* name;

};


int checkTypes(struct expr *op1, struct expr *op2);

struct expr* dothings(iopcode opcode);

void insert_rvalue_list(char* name, rvalue_type type);

void print_list_rvalues();

struct expr* new_expr(expr_t expr_type, struct symbol_table_binding* sym , struct expr* index
	,double numconst ,char* strconst , unsigned char boolconst , struct expr* next);

void emit(iopcode opcode, struct expr* arg1, struct expr* arg2, struct expr* res_expr, int line, int label);

void initialize_quad_table();
void print_quads();

struct symbol_table_binding* SearchFunction(char* name);

struct expr* emit_iftable_item(struct expr* exp);
struct expr* member_item(struct expr* lvalue ,char* name);
struct expr* make_call (struct expr* lv, struct expr* elist);

struct expr* apotimhsh_seboolean(struct expr* expr);

int  patchFlow(double  con , double bre);
int patchReturn(int from , int to);
char* enum_toString_opCodes(iopcode sym);

//Stack functions

int pop_SP();
int push_SP(int num);

int pop_B();
int push_B(int num);
int isEmptyB();

int pop_C();
int push_C(int num);
int isEmptyC();

int pop_R();
int push_R(int num);
int isEmptyR();
