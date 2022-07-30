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
	tablegetelem_v,	tablesetelem_v, 	nop_v,
	jump_v

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
	unsigned 	val;

};
//array of instruction , san to quads[]

struct instruction *instructions;

struct instruction {

	vmopcode		opcode;
	struct vmarg*			result;
	struct vmarg*			arg1;
	struct vmarg* 			arg2;
	unsigned  	srcLine;

};

struct userfunc {

	unsigned int 	address;
	unsigned int 	localSize;
	unsigned int 	totalargs;
	unsigned int 	scope;
	char* 			id;

};

unsigned globals;

double* 	numConsts; //rvalue numbers
unsigned	totalNumConsts; //total number of  numbers
char**		stringConsts; //rvalue strings
unsigned	totalStringConsts; //total number of strings
char**		namedLibfuncs;
unsigned	totalNamedLibfuncs;
struct userfunc**	userFuncs;
unsigned	totalUserFuncs;

unsigned add_rval_string(char * str);
unsigned add_rval_num(double number);
unsigned add_rval_libfuncs(char * libfunc);
unsigned add_rval_userfuncs(char * userfunc,unsigned int address, unsigned int localsize,unsigned int totalargs,unsigned scope );

struct vmarg* make_operand(struct expr* expr);
void printInstructions();
void emitIns(struct instruction* ins);

void generateIns(void);
void generate(vmopcode code , struct quad* quad);
void generate_relational(vmopcode code , struct quad* quad);


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
void generate_FUNCEND(struct quad *quad);
void generate_UMINUS(struct quad *quad);
void generate_AND(struct quad *quad);
void generate_OR(struct quad *quad);
void generate_NOT(struct quad *quad);
void generate_RET(struct quad *quad);



struct incomplete_jump {
	unsigned	instrNo;
	unsigned	iaddress;
	struct incomplete_jump* next;
};

 struct incomplete_jump*	ij_head;
 unsigned			ij_total;

void add_incomplete_jump(unsigned instrNo,unsigned iaddress);
void patch_incomplete_jump();

int  create_bin();

void read_binfile();


unsigned searchFunctionTable(struct expr* exp);
unsigned searchLibFunc(struct expr* expr);
