#include "phase5.h"

execute_func_t executeFuncs[] = {
	 execute_assign ,
	 execute_add 	,
	 execute_sub	,
	 execute_mul	,
	 execute_div	,
	 execute_mod	,
	 execute_uminus	,
	 execute_and 	,
	 execute_or 	,
	 execute_not 	,
	 execute_jeq	,
	 execute_jne	,
	 execute_jle	,
	 execute_jge	,
	 execute_jlt	,
	 execute_jgt	,
	 execute_call		,
	 execute_pusharg	,
	 execute_funcenter	,
	 execute_funcexit	,
	 execute_newtable		,
	 execute_tablegetelem	,
	 execute_tablesetelem	,
	 execute_nop	,

};

unsigned char	executionFinished = 0 ;
unsigned		pc = 0;
unsigned		currLine = 0;
unsigned		codeSize = 0;

struct instruction*  code = NULL;



struct avm_memcell*	avm_translate_operand(struct vmarg* arg , struct avm_memcell* reg){

	switch (arg->type) {
		case global_a:	return &stack[AVM_STACKENV_SIZE - 1 - arg->val];
		case local_a:	return &stack[topsp - arg->val];
		case formal_a:	return &stack[topsp+AVM_STACKENV_SIZE + 1 + arg->val];

		case retval_a:	return &retval;

		case number_a:	{
			reg->type = number_m;
			reg->data.numVal = consts_getnumber(arg->val);
			return reg;
		}

		case string_a:	{
			reg->type = string_m;
			reg->data.strVal = strdup(consts_getstring(arg->val));
			return reg;
		}

		case bool_a:	{
			reg->type = bool_m;
			reg->data.bool = arg->val;
			return reg;
		}

		case nil_a : reg->type = nil_m; return reg;

		case userfunc_a : {
			reg->type = userfunc_m;
			reg->data.funcVal = arg->val;
			return reg;
		}
		case libfunc_a : {
			reg->type = lib_func_m;
			reg->data.libfuncVal = libfuncs_getused(arg->val);
			return reg;
		}
		default : assert(0);

	}
}


double	consts_getnumber(unsigned index){return 0;}
char*	consts_getstring(unsigned index){return NULL;}
char*	libfuncs_getused(unsigned index){return NULL;}




void execute_assign (struct instruction* ins){}

void execute_add 	(struct instruction* ins) {}
void execute_sub	(struct instruction* ins) {}
void execute_mul	(struct instruction* ins) {}
void execute_div	(struct instruction* ins) {}
void execute_mod	(struct instruction* ins) {}
void execute_uminus	(struct instruction* ins) {}//XXXXXXXXXXXX NO USE

void execute_and 	(struct instruction* ins) {}//XXXXXXXXXXXX NO USE
void execute_or 	(struct instruction* ins){}//XXXXXXXXXXXX NO USE
void execute_not 	(struct instruction* ins){}//XXXXXXXXXXXX NO USE

void execute_jeq	(struct instruction* ins){}
void execute_jne	(struct instruction* ins){}
void execute_jle	(struct instruction* ins){}
void execute_jge	(struct instruction* ins){}
void execute_jlt	(struct instruction* ins){}
void execute_jgt	(struct instruction* ins){}

void execute_call		(struct instruction* ins){}
void execute_pusharg	(struct instruction* ins){}
void execute_funcenter	(struct instruction* ins){}
void execute_funcexit	(struct instruction* ins){}

void execute_newtable		(struct instruction* ins){}
void execute_tablegetelem	(struct instruction* ins){}
void execute_tablesetelem	(struct instruction* ins){}

void execute_nop	(struct instruction* ins){}



void execute_cycle	(void){

	if (executionFinished) {
		return;
	} else if (pc == AVM_ENDING_PC) {
			executionFinished = 1;
			return;
	} else {

		assert(pc < AVM_ENDING_PC);

		struct instruction* instr = code + pc;
		assert(instr->opcode>=0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);

		if (instr->srcLine) currLine = instr->srcLine;

		unsigned oldPC = pc;

		(*executeFuncs[instr->opcode]) (instr);
		if (pc == oldPC) {
			++pc;
		}
	}



}
