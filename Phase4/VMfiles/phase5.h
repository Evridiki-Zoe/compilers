#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

#define AVM_NUMACTUALS_OFFSET 	+4
#define AVM_SAVEDPC_OFFSET		+3
#define AVM_SAVEDTOP_OFFSET		+2
#define AVM_SAVEDTOPSP_OFFSET	+1


#define AVM_STACKENV_SIZE	4
#define AVM_ENDING_PC	codeSize

typedef double (*arithmetic_func_t) (double x, double y);

void avm_initstack();

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

struct avm_table{
		struct avm_memcell* data;
		struct avm_table* next;
		union	{
			double	numVal;
			char*	strVal;
			unsigned char	bool;
			struct avm_table*		tableVal;
			unsigned		funcVal;
			char*			libfuncVal;
		} index;
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

struct userfunc {

	unsigned int 	address;
	unsigned int 	localSize;
	unsigned int 	totalargs;
	char* 			id;

};

//----------from phase4----------------------


double	consts_getnumber(unsigned index);
char*	consts_getstring(unsigned index);
char*	libfuncs_getused(unsigned index);

struct avm_memcell*	avm_translate_operand(struct vmarg* arg , struct avm_memcell* reg);



//---------------------Dispacher----------------------------

typedef void (*execute_func_t) (struct instruction* ins);

#define AVM_MAX_INSTRUCTIONS (unsigned) jump_v

void execute_arithmetic(struct instruction* instr);

void avm_assign(struct avm_memcell*	lv,struct avm_memcell*	rv);

void avm_dec_top (void);
void avm_push_envvalue (unsigned val);
unsigned avm_get_envvalue(unsigned i);

unsigned avm_totalactuals(void);

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
void execute_jump	(struct instruction* ins);



unsigned char	executionFinished ;
unsigned		pc ;
unsigned		currLine ;
unsigned		codeSize ;

struct instruction**  code;

void avm_error(char *msg);
void execute_cycle	(void);

typedef void (*memclear_func_t) (struct avm_memcell*);

void avm_memcellclear(struct avm_memcell* m);
void memclear_string(struct avm_memcell* m);
void memclear_table(struct avm_memcell* m);

void avm_tablecrefcounter(struct avm_table* m);
void avm_tableincrefcounter(struct avm_table* m);
struct avm_table* avm_tablenew();
void avm_setelem(struct avm_table* table , struct avm_memcell* index , struct avm_memcell* data);

void avm_warning(char* msg );



typedef void (*library_funcs_t)(void);
library_funcs_t avm_getlibraryfunc (char* id);

typedef char* (*tostring_func_t)(struct avm_memcell*);
char* avm_tostring(struct avm_memcell* cell);

char* number_tostring (struct avm_memcell* cell);
char* string_tostring (struct avm_memcell* cell);
char* bool_tostring (struct avm_memcell* cell);
char* table_tostring (struct avm_memcell* cell);
char* userfunc_tostring (struct avm_memcell* cell);
char* libfunc_tostring (struct avm_memcell* cell);
char* nil_tostring (struct avm_memcell* cell);
char* undef_tostring (struct avm_memcell* cell);

struct userfunc* avm_getfuncinfo(unsigned address);

void avm_registerlibfunc (char* id , library_funcs_t addr);

void avm_callsaveenviroment();
void avm_calllibfunc(char* name);

unsigned char avm_tobool(struct avm_memcell* m);

void  libfunc_typeof();

void libfunc_totalarguments(void);

void read_binfile();
void printStack();
//-----------------tables retrieve----
double* 	numConsts; //rvalue numbers
unsigned	totalNumConsts; //total number of  numbers
char**		stringConsts; //rvalue strings
unsigned	totalStringConsts; //total number of strings
char**		namedLibfuncs;
unsigned	totalNamedLibfuncs;
struct userfunc**	userFuncs;
unsigned	totalUserFuncs;
unsigned globals;

void add_consts_string(char * str);
void add_consts_num(double number);
void add_consts_libfuncs(char * libfunc);
void add_consts_userfuncs(char * userfunc,unsigned int address, unsigned int localsize,unsigned int totalargs );

char* enum_toString_opCodes_v(vmopcode sym);
///----------------------------------
