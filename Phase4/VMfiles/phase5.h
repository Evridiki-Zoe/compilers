#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

#define AVM_STACKENV_SIZE	4
#define AVM_ENDING_PC	codeSize

typedef double (*arithmetic_func_t) (double x, double y);

double add_impl(double x, double y);
double sub_impl(double x, double y);
double mul_impl(double x, double y);
double div_impl(double x, double y);
double mod_impl(double x, double y);

typedef enum 	{

	number_m	=0,
	string_m	=1,
	bool_m		=2,
	table_m		=3,
	userfunc_m	=4,
	lib_func_m	=5,
	nil_m		=6,
	undef_m		=7

}avm_memcell_t;



struct avm_memcell {
	avm_memcell_t type;
	union	{
		double	numVal;
		char*	strVal;
		unsigned char	bool;
		struct avm_table*		tableVal;
		unsigned		funcVal;
		char*			libfuncVal;
	} data;
};

struct avm_memcell stack[1024];

struct avm_memcell	ax,bx,cx;
struct avm_memcell	retval;

unsigned topsp , top;


//----------from phase4----------------------
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

struct instruction {

	vmopcode		opcode;
	struct vmarg*			result;
	struct vmarg*			arg1;
	struct vmarg* 			arg2;
	unsigned  	srcLine;

};

//----------from phase4----------------------


double	consts_getnumber(unsigned index);
char*	consts_getstring(unsigned index);
char*	libfuncs_getused(unsigned index);

struct avm_memcell*	avm_translate_operand(struct vmarg* arg , struct avm_memcell* reg);



//---------------------Dispacher----------------------------

typedef void (*execute_func_t) (struct instruction* ins);

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v

void execute_arithmetic(struct instruction* instr);


void execute_assign (struct instruction* ins);

void execute_add 	(struct instruction* ins);
void execute_sub	(struct instruction* ins);
void execute_mul	(struct instruction* ins);
void execute_div	(struct instruction* ins);
void execute_mod	(struct instruction* ins);
void execute_uminus	(struct instruction* ins);//XXXXXXXXXXXX NO USE

void execute_and 	(struct instruction* ins);//XXXXXXXXXXXX NO USE
void execute_or 	(struct instruction* ins);//XXXXXXXXXXXX NO USE
void execute_not 	(struct instruction* ins);//XXXXXXXXXXXX NO USE

void execute_jeq	(struct instruction* ins);
void execute_jne	(struct instruction* ins);
void execute_jle	(struct instruction* ins);
void execute_jge	(struct instruction* ins);
void execute_jlt	(struct instruction* ins);
void execute_jgt	(struct instruction* ins);

void execute_call		(struct instruction* ins);
void execute_pusharg	(struct instruction* ins);
void execute_funcenter	(struct instruction* ins);
void execute_funcexit	(struct instruction* ins);

void execute_newtable		(struct instruction* ins);
void execute_tablegetelem	(struct instruction* ins);
void execute_tablesetelem	(struct instruction* ins);

void execute_nop	(struct instruction* ins);




unsigned char	executionFinished ;
unsigned		pc ;
unsigned		currLine ;
unsigned		codeSize ;

struct instruction*  code;

void avm_error(char *msg);
void execute_cycle	(void);
