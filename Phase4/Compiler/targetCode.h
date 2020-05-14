#include <stdio.h>
#include <stdlib.h>

typedef enum  {

	assign_v,		add_v,				sub_v,
	mul_v,			div_v,				mod_v,
	uminus_v,		and_v,				or_v,
	not_v,			jeq_v,				jne_v,
	jle_v,			jge_v,				jlt_v,
	jgt_v,			call_v,				pusharg_v,
	funcenter_v,	funcexit_v,			newtable_v,
	tablegetelem_v,	tablesetelem_v, 	nop_v

}vmopcode;

typedef enum  {

	label_a		= 0,
	global_a 	= 1,
	formal_a	= 2,
	local_a		= 3,
	number_a	= 4,
	string_a	= 5,
	bool_a		= 6,
	nil_a		= 7,
	userfunc_a	= 8,
	libfunc_a	= 9,
	retval_a	= 10,


}vmarg_t;

struct vmarg {

	vmarg_t 		type;
	unsigned int	val;

};

struct instruction {

	vmopcode		opcode;
	struct vmarg*			result;
	struct vmarg*			arg1;
	struct vmarg* 			arg2;
	unsigned int 	srcLine;

};

struct userfunc {

	unsigned int 	address;
	unsigned int 	localSize;
	unsigned int 	totalargs;
	char* 			id;

};


double* 	numConsts;
unsigned	totalNumConsts;
char**		stringConsts;
unsigned	totalStringConsts;
char**		namedLibfuncs;
unsigned	totalNamedLibfuncs;
struct userfunc*	userFuncs;
unsigned	totalUserFuncs;


void generate(void);

void generate_ADD (struct quad *quad);
void generate_SUB (struct quad *quad);
void generate_MUL (struct quad *quad);
void generate_DIV (struct quad *quad);
void generate_MOD (struct quad *quad);
void generate_NEWTABLE (struct quad *quad);
void generate_TABLEGETELM (struct quad *quad);
void generate_TABLESETELEM(struct quad *quad);
void generate_ASSIGN (struct quad *quad);
void generate_NOP (struct quad *quad);
void generate_JUMP(struct quad *quad);
void generate_IF_EQ(struct quad *quad);
void generate_IF_NOTEQ(struct quad *quad);
void generate_IF_GREATER(struct quad *quad);
void generate_IF_GREATEREQ(struct quad *quad);
void generate_IF_LESS(struct quad *quad);
void generate_IF_LESSEQ(struct quad *quad);
void generate_NOT(struct quad *quad);
void generate_OR(struct quad *quad);
void generate_PARAM(struct quad *quad);
void generate_CALL(struct quad *quad);
void generate_GETRETVAL(struct quad *quad);
void generate_FUNCSTART(struct quad *quad);
void generate_RETURN(struct quad *quad);
void generate_FUNCEND(struct quad *quad);
