#include "phase5.h"
/* TODO ???

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
*/

unsigned totalActuals=0;

tostring_func_t tostringFuncs[] = {
	number_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring,
	nil_tostring,
	undef_tostring
};

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


arithmetic_func_t arithmeticFuncs[] = {
  add_impl,
  sub_impl,
  mul_impl,
  div_impl,
  mod_impl
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

double add_impl(double x, double y){return x+y;}
double sub_impl(double x, double y){return x-y;}
double mul_impl(double x, double y){return x*y;}
double div_impl(double x, double y){if(y == 0){printf("Division by zero!\n" ); exit(1);} return x/y;}
double mod_impl(double x, double y){return (unsigned)x % (unsigned)y;} //todo error (??)

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

//-----------Cell cleaning----------------------------------
memclear_func_t memclearFuncs[] = {
	0,
	memclear_string,
	0,
	memclear_table,
	0,
	0,
	0,
	0
};

void avm_memcellclear(struct avm_memcell* m){
	if (m->type != undef_m) {
		memclear_func_t f=memclearFuncs[m->type];
		if (f) {
			(*f)(m);
			m->type = undef_m;
		}
	}


}
void avm_tablecrefcounter(struct avm_table* m){}	//TODO

void memclear_string(struct avm_memcell* m){
	assert(m->data.strVal);
	free(m->data.strVal);

}
void memclear_table(struct avm_memcell* m){
	assert(m->data.tableVal);
	avm_tablecrefcounter(m->data.tableVal);
}
void avm_tableincrefcounter(struct avm_table* m){} //TODO


//----------------------------------------------------------



void avm_assign(struct avm_memcell*	lv,struct avm_memcell*	rv){

	if (lv == rv) return;

	if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal ) return;

	if (rv->type == undef_m) avm_warning("Assigning from 'undef' content!");

	avm_memcellclear(lv);

	memcpy(lv,rv,sizeof(struct avm_memcell));

	if (lv->type == string_m) {
		lv->data.strVal = strdup(rv->data.strVal);
	} else if (lv->type == table_m) {
		avm_tableincrefcounter(lv->data.tableVal);
	}
}

void avm_callsaveenviroment(void){
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top+totalActuals + 2);
	avm_push_envvalue(topsp);
}

void avm_dec_top (void){
	if (!top) {
		avm_error("Stack overflow");
		executionFinished=1;
	} else --top;
}

void avm_push_envvalue (unsigned val) {
	stack[top].type =number_m;
	stack[top].data.numVal =val;
	avm_dec_top();
}

unsigned avm_get_envvalue(unsigned i){
	assert(stack[i].type = number_m);
	unsigned val = (unsigned) stack[i].data.numVal;
	assert(stack[i].data.numVal == ((double) val));
	return val;
}



void avm_calllibfunc(char* id){
	library_funcs_t f = avm_getlibraryfunc(id);
	if (!f) {
		char* msg="";
		sprintf(msg,"unsupported lib func '%s' called!",id );
		avm_error(msg);
		executionFinished = 1;
	} else {
		topsp = top;
		totalActuals = 0;
		(*f)();
		if (!executionFinished) {
			execute_funcexit(NULL);
		}
	}
}

library_funcs_t avm_getlibraryfunc (char* id){return NULL;} //TODO

unsigned avm_totalactuals(void) {
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

struct avm_memcell* avm_getactual(unsigned i){
	assert(i<avm_totalactuals());
	return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

struct userfunc* avm_getfuncinfo(unsigned address){return NULL;}//TODO

//--------------------------------------



//------------------libfuncs----------------
void libfunc_print(void){
	unsigned n = avm_totalactuals();
	unsigned i=0;
	for (; i < n; i++) {
		char* s = avm_tostring(avm_getactual(i));
		puts(s);
		free(s);
	}
}

void avm_registerlibfunc (char* id , library_funcs_t addr){} //?? TODO
//------------------------------------------

void execute_arithmetic(struct instruction* instr){
	  	struct avm_memcell* lv = avm_translate_operand(instr->result, (struct avm_memcell*)0);
		struct avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
		struct avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

		assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retval)); //TODO slide 25 to exei alliws
		assert(rv1 && rv2);

		if( rv1->type != number_m  || rv2->type != number_m ){
				avm_error("arithmetic ex:: not a number! \n");
				executionFinished = 1;
		}
		else{
				arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
				//avm_memcellclear(lv); //TODO
				lv->type = number_m;
				lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);

		}
}



void execute_assign (struct instruction* ins){

	struct avm_memcell*	lv = avm_translate_operand(ins->result , NULL); // ??
	struct avm_memcell*	rv = avm_translate_operand(ins->arg1 , &ax);

// ??	assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval ))
	avm_assign(lv,rv);
}

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

void execute_call		(struct instruction* ins){

		struct avm_memcell* func = avm_translate_operand(ins->result , &ax);
		assert(func);
		avm_callsaveenviroment();

		switch (func->type) {
			case userfunc_m: {

				pc = func->data.funcVal;
				assert(pc < AVM_ENDING_PC);
				assert(code[pc].opcode == funcenter_v);
				break;
			}
			case string_m:		avm_calllibfunc(func->data.strVal); break;
			case lib_func_m:	avm_calllibfunc(func->data.libfuncVal); break;

			default : {
				char* s = avm_tostring(func);
				char* msg="";
				sprintf(msg,"call: cannot bind '%s' to function!",s );
				avm_error(msg);
				free(s);
				executionFinished=1;
			}
			}
}
void execute_pusharg	(struct instruction* ins){
	struct avm_memcell* arg = avm_translate_operand(ins->arg1,&ax);
	assert(arg);
	avm_assign(&stack[top],arg);
	++totalActuals;
	avm_dec_top();
}
void execute_funcenter	(struct instruction* ins){
	struct avm_memcell* func = avm_translate_operand(ins->result , &ax);
	assert(func);
	assert(pc == func->data.funcVal);

	totalActuals = 0;

	struct userfunc* funcInfo = avm_getfuncinfo(pc);
	topsp=top;
	top = top - funcInfo->localSize;

}
void execute_funcexit	(struct instruction* ins){

	unsigned oldTop = top;

	top = avm_get_envvalue	(topsp  AVM_SAVEDPC_OFFSET);
	pc 	= avm_get_envvalue	(topsp  AVM_SAVEDPC_OFFSET);
	topsp = avm_get_envvalue(topsp AVM_SAVEDTOPSP_OFFSET);

	while (++oldTop <= top) {
		avm_memcellclear(&stack[oldTop]);
	}
}

void execute_newtable		(struct instruction* ins){}
void execute_tablegetelem	(struct instruction* ins){}
void execute_tablesetelem	(struct instruction* ins){}
void execute_nop	(struct instruction* ins){}

//den exw balei to executon executionFinished =1 edw, na to bazoume kathe fora pou thn  kaloume
void avm_error(char *msg){
  printf("\nError: %s ",msg);
	exit(1); //???
}
void avm_warning(char* msg ){
	 printf("\nWarning: %s ",msg);
}

char* avm_tostring(struct avm_memcell* cell){
	assert(cell->type >= 0 && cell->type <= undef_m);
	return (*tostringFuncs[cell->type])(cell);
}



char* number_tostring (struct avm_memcell* cell){return NULL;}
char* string_tostring (struct avm_memcell* cell){return NULL;}
char* bool_tostring (struct avm_memcell* cell){return NULL;}
char* table_tostring (struct avm_memcell* cell){return NULL;}
char* userfunc_tostring (struct avm_memcell* cell){return NULL;}
char* libfunc_tostring (struct avm_memcell* cell){return NULL;}
char* nil_tostring (struct avm_memcell* cell){return NULL;}
char* undef_tostring (struct avm_memcell* cell){return NULL;}
