#include "phase5.h"
#include <string.h>

/* TODO

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

char* typeStrings[] = {
		"number",
		"string",
		"bool",
		"table",
		"userfunc",
		"libfunc",
		"nil",
		"undef"
};

arithmetic_func_t arithmeticFuncs[] = {
  add_impl,
  sub_impl,
  mul_impl,
  div_impl,
  mod_impl
};


typedef unsigned char (*tobool_func_t)(struct avm_memcell* m);

unsigned char number_tobool(struct avm_memcell* m){ return m->data.numVal != 0;}
unsigned char string_tobool(struct avm_memcell* m){ return m->data.strVal[0] != 0;}
unsigned char bool_tobool(struct avm_memcell* m){ return m->data.bool; }
unsigned char table_tobool(struct avm_memcell* m){ return 1;}
unsigned char userfunc_tobool(struct avm_memcell* m){ return 1;}
unsigned char libfunc_tobool(struct avm_memcell* m){ return 1;}
unsigned char nil_tobool(struct avm_memcell* m){ return 0;}
unsigned char undef_tobool(struct avm_memcell* m){ assert(0); return 0;}

tobool_func_t toboolFuncs[] ={
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool

};

unsigned char	executionFinished = 0 ;
unsigned		pc = 0; //deixnei sthn epoemnh instruction
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

void avm_initstack(){

}

double	consts_getnumber(unsigned index){return 0;} //TODO
char*	consts_getstring(unsigned index){return NULL;}
char*	libfuncs_getused(unsigned index){return NULL;}

double add_impl(double x, double y){return x+y;}
double sub_impl(double x, double y){return x-y;}
double mul_impl(double x, double y){return x*y;}
double div_impl(double x, double y){
	if(y == 0){
		avm_error("Division by zero!" );
		executionFinished=1;
		return 0;
	}else  return x/y;
}
double mod_impl(double x, double y){
	if(y == 0){
		avm_error("Mod by zero!" );
		executionFinished=1;
		return 0;
	}else return (unsigned)x % (unsigned)y;
}

void execute_cycle	(void){

	if (executionFinished) {
		printf("if \n");
		return;
	} else if (pc == AVM_ENDING_PC) {
		printf("else if \n");

			executionFinished = 1;
			return;
	} else {
		printf("else \n");


		assert(pc < AVM_ENDING_PC);


		struct instruction* instr = malloc(sizeof(struct instruction));
		instr = code + pc;
		printf("instr type %d noop is %d\n",instr->opcode, AVM_MAX_INSTRUCTIONS );

		assert(instr->opcode>=0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
		if (instr->srcLine) currLine = instr->srcLine;
printf("edwww\n" );
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


struct avm_table* avm_tablenew(){return NULL;}//TODO

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

void  libfunc_typeof(){

unsigned n = avm_totalactuals();

if(n != 1) avm_error("libfunc typeof:: error ");
else{

	//to return a result we set the retval register
	avm_memcellclear(&retval);
	retval.type = string_m;
	retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
}

}

void avm_registerlibfunc (char* id , library_funcs_t addr){} // TODO

void libfunc_totalarguments(void){

	unsigned p_topsp = avm_get_envvalue(topsp  + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	if (!p_topsp) {
		avm_error("'totalarguments' called outside a function!");
		retval.type=nil_m;
	}else {
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
	}


}
//------------------------------------------

void execute_arithmetic(struct instruction* instr){
	  	struct avm_memcell* lv = avm_translate_operand(instr->result, (struct avm_memcell*)0);
		struct avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
		struct avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

		//assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retval)); ?? slide 25 to exei alliws
		assert(rv1 && rv2);

		if( rv1->type != number_m  || rv2->type != number_m ){
				avm_error("arithmetic ex:: not a number! \n");
				executionFinished = 1;
		}
		else{
				arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
				avm_memcellclear(lv);
				lv->type = number_m;
				lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);

		}
}



void execute_assign (struct instruction* ins){

	struct avm_memcell*	lv = avm_translate_operand(ins->result , NULL);
	struct avm_memcell*	rv = avm_translate_operand(ins->arg1 , &ax);

// ??	assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval ))
	avm_assign(lv,rv);
}

void execute_add 	(struct instruction* ins) {  execute_arithmetic(ins); } //?? }
void execute_sub	(struct instruction* ins) {}
void execute_mul	(struct instruction* ins) {}
void execute_div	(struct instruction* ins) {}
void execute_mod	(struct instruction* ins) {}
void execute_uminus	(struct instruction* ins) {}//XXXXXXXXXXXX NO USE

void execute_and 	(struct instruction* ins) {}//XXXXXXXXXXXX NO USE
void execute_or 	(struct instruction* ins){}//XXXXXXXXXXXX NO USE
void execute_not 	(struct instruction* ins){}//XXXXXXXXXXXX NO USE

void execute_jeq	(struct instruction* ins){
		assert(ins->result->type == label_a);
		struct avm_memcell* rv1 = avm_translate_operand(ins->arg1, &ax);
		struct avm_memcell* rv2 = avm_translate_operand(ins->arg2, &bx);

		unsigned char result = 0;
		if (rv1->type == undef_m || rv2->type == undef_m) {
				avm_error("undef involved in equality\n");
				executionFinished = 1;
		}
		else if( rv1->type == nil_m  || rv2->type == nil_m ){
			 	result = (rv1->type == nil_m  && rv2->type == nil_m );

		}
		else if ( rv1->type == bool_m  || rv2->type == bool_m ){
			 	result = (avm_tobool(rv1) && avm_tobool(rv2)  );
		}
		else if ( rv1->type !=rv2->type ){
				avm_error("illegal types in jeq!\n");
		}
		else{
			// TODO Equality check with Dispaching for rv1
		}

		if(!executionFinished && result )
				pc = ins->result->val;

}

void execute_jne	(struct instruction* ins){

	assert(ins->result->type == label_a);
	struct avm_memcell* rv1 = avm_translate_operand(ins->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(ins->arg2, &bx);

	unsigned char result = 0;
	if (rv1->type == undef_m || rv2->type == undef_m) {
			avm_error("undef involved in equality\n");
			executionFinished = 1;
	}
	else if( rv1->type == nil_m  || rv2->type == nil_m ){
			result = (rv1->type == nil_m  && rv2->type == nil_m );

	}
	else if ( rv1->type == bool_m  || rv2->type == bool_m ){
			result = (avm_tobool(rv1) && avm_tobool(rv2)  );
	}
	else if ( rv1->type !=rv2->type ){
			avm_error("illegal types in jeq!\n");
	}
	else{
		// TODO Equality check with Dispaching for rv1
		//+++++++
	}

	if(!executionFinished && result )
			pc = ins->result->val;
}

void execute_jle	(struct instruction* ins){
	assert(ins->result->type == label_a);
	struct avm_memcell* rv1 = avm_translate_operand(ins->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(ins->arg2, &bx);

	unsigned char result = 0;
	if (rv1->type == undef_m || rv2->type == undef_m) {
			avm_error("undef involved in equality\n");
			executionFinished = 1;
	}
	else if( rv1->type == nil_m  || rv2->type == nil_m ){
			result = (rv1->type == nil_m  && rv2->type == nil_m );

	}
	else if ( rv1->type == bool_m  || rv2->type == bool_m ){
			result = (avm_tobool(rv1) && avm_tobool(rv2)  );
	}
	else if ( rv1->type !=rv2->type ){
			avm_error("illegal types in jeq!\n");
	}
	else{
		// TODO Equality check with Dispaching for rv1
		//+++++++
	}

	if(!executionFinished && result )
			pc = ins->result->val;
}

void execute_jge	(struct instruction* ins){

	assert(ins->result->type == label_a);
	struct avm_memcell* rv1 = avm_translate_operand(ins->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(ins->arg2, &bx);

	unsigned char result = 0;
	if (rv1->type == undef_m || rv2->type == undef_m) {
			avm_error("undef involved in equality\n");
			executionFinished = 1;
	}
	else if( rv1->type == nil_m  || rv2->type == nil_m ){
			result = (rv1->type == nil_m  && rv2->type == nil_m );

	}
	else if ( rv1->type == bool_m  || rv2->type == bool_m ){
			result = (avm_tobool(rv1) && avm_tobool(rv2)  );
	}
	else if ( rv1->type !=rv2->type ){
			avm_error("illegal types in jeq!\n");
	}
	else{
		// TODO Equality check with Dispaching for rv1
		//+++++++
	}

	if(!executionFinished && result )
			pc = ins->result->val;
}

void execute_jlt	(struct instruction* ins){

	assert(ins->result->type == label_a);
	struct avm_memcell* rv1 = avm_translate_operand(ins->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(ins->arg2, &bx);

	unsigned char result = 0;
	if (rv1->type == undef_m || rv2->type == undef_m) {
			avm_error("undef involved in equality\n");
			executionFinished = 1;
	}
	else if( rv1->type == nil_m  || rv2->type == nil_m ){
			result = (rv1->type == nil_m  && rv2->type == nil_m );

	}
	else if ( rv1->type == bool_m  || rv2->type == bool_m ){
			result = (avm_tobool(rv1) && avm_tobool(rv2)  );
	}
	else if ( rv1->type !=rv2->type ){
			avm_error("illegal types in jeq!\n");
	}
	else{
		// TODO Equality check with Dispaching for rv1
		//+++++++
	}

	if(!executionFinished && result )
			pc = ins->result->val;
}

void execute_jgt(struct instruction* ins){
	assert(ins->result->type == label_a);
	struct avm_memcell* rv1 = avm_translate_operand(ins->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(ins->arg2, &bx);

	unsigned char result = 0;
	if (rv1->type == undef_m || rv2->type == undef_m) {
			avm_error("undef involved in equality\n");
			executionFinished = 1;
	}
	else if( rv1->type == nil_m  || rv2->type == nil_m ){
			result = (rv1->type == nil_m  && rv2->type == nil_m );

	}
	else if ( rv1->type == bool_m  || rv2->type == bool_m ){
			result = (avm_tobool(rv1) && avm_tobool(rv2)  );
	}
	else if ( rv1->type !=rv2->type ){
			avm_error("illegal types in jeq!\n");
	}
	else{
		// TODO Equality check with Dispaching for rv1
		//+++++++
	}

	if(!executionFinished && result )
			pc = ins->result->val;
}

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


void execute_newtable		(struct instruction* ins){
	struct avm_memcell* lv = avm_translate_operand(ins->result , NULL);
	//assert(lv &&)
	avm_memcellclear(lv);

	lv->type 			=table_m;
	lv->data.tableVal	=avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
}
void execute_tablegetelem	(struct instruction* ins){

	struct avm_memcell* lv = avm_translate_operand(ins->result, (struct avm_memcell*)0);
	struct avm_memcell* t = avm_translate_operand(ins->arg1, (struct avm_memcell*)0);
	struct avm_memcell* i = avm_translate_operand(ins->arg2, &ax);

	//assert(lv && &stack[N - 1] >= lv && &stack[top] < lv || lv == &retval);// TODO N
	//assert(t && &stack[N - 1] >= t && t > &stack[top] ); //TODO
	assert(i);

	avm_memcellclear(lv);
	lv->type = nil_m; //default val

	if(t->type != table_m ){
		avm_error("illegal use of variable as a table! \n");

	}
	else{
			struct avm_memcell* content;// = avm_tablegetelem(t->data.tableVal, i ); //todo
			if(content){
				avm_assign(lv,content);
			}
			else{
					char * ts = avm_tostring(t);
					char * is = avm_tostring(i);
					avm_warning("getelem:: Not found! \n");
					free(ts);
					free(is);

			}

	}


}
void execute_tablesetelem	(struct instruction* ins){

		struct avm_memcell* t = avm_translate_operand(ins->result, (struct avm_memcell*)0);
		struct avm_memcell* i = avm_translate_operand(ins->arg1, &ax);
		struct avm_memcell* c = avm_translate_operand(ins->arg2, &bx);

		//assert(t && &stack[N - 1] >= t && t > &stack[top] ); //TODO
		assert(i && c);

		if(t->type != table_m)		avm_error("illegal use of variable as a table! \n");
		else {
			//avm_setelem(t->data.tableVal, i, c); //todo
		}
}

void execute_nop	(struct instruction* ins){}

//den exw balei to executon executionFinished =1 edw, na to bazoume kathe fora pou thn  kaloume
void avm_error(char *msg){
	executionFinished = 1;
  	printf("\nError: %s ",msg);
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


unsigned char avm_tobool(struct avm_memcell* m){
		assert(m->type >= 0 && m->type < undef_m);
		return (*toboolFuncs[m->type])(m);
}


void read_binfile(){
				FILE *fp = NULL;
				int i =0;
		 		//   fputs("2", fp);
	   		fp = fopen("test.bin", "rb");
		 		int magic;
		 		unsigned int totalStr, totalNums, totaluserF, totallibF, totalins;
	      fread(&magic, sizeof(int), 1, fp);
	      printf("\nmagic number is: %d \n", magic);
				fread(&totalStr, sizeof(unsigned int), 1, fp);
				printf("\ntotal string is %d \n", totalStr);

		    for(i=0; i<totalStr; i++){
								unsigned int len = 0;

							 if(fread(&len,sizeof(unsigned int), 1, fp) != 1) //length of each string
							 		printf("Error reading file \n");
							printf("size (%d)  ",len );
							char* str = malloc(sizeof(char) *len);
							int i = 0;
							for ( ;i < len; i++) {
								if(fread(&str[i],sizeof(char ) , 1, fp)!= 1)
									printf("Error reading file \n");
							}

							printf("str: %s\n",str );
		    }

				fread(&totalNums, sizeof(unsigned int), 1, fp);
				printf("\ntotal nums is %d \n", totalNums);
				for(i=0; i<totalNums; i++){
			        double num;
			        fread(&num,sizeof(double), 1, fp);
			        printf("num:%f\n", num);
				}

				fread(&totaluserF, sizeof(unsigned int), 1, fp);
				printf("\ntotal userfuncs is %d \n", totaluserF);

	 	    for(i=0; i<totaluserF; i++){
	 							unsigned int len, addr, localsize;
								fread(&addr,sizeof(unsigned int), 1, fp); //total strings
								fread(&localsize,sizeof(unsigned int), 1, fp); //total strings
	 						  	fread(&len,sizeof(unsigned int), 1, fp); //total strings
									char * id = malloc(sizeof(char )*len);

									int i = 0;
									for ( ;i < len; i++) {
										if(fread(&id[i],sizeof(char ) , 1, fp)!= 1)
											printf("Error reading file \n");
									}
	   							printf("size (%d) of %s, with address %d and localsize %d\n",len,id,  addr, localsize );


	 	    }
				fread(&totallibF, sizeof(unsigned int), 1, fp);
				printf("\ntotal libfuncs is %d \n", totallibF);
				for(i=0; i<totallibF; i++){
								unsigned int len;
							  fread(&len,sizeof(unsigned int), 1, fp); //length of each string
								char * libF = malloc(sizeof(char )*len);

								int i = 0;
								for ( ;i < len; i++) {
									if(fread(&libF[i],sizeof(char ) , 1, fp)!= 1)
										printf("Error reading file \n");
								}
								printf("size (%d) of libF: %s\n",len, libF );
		    }

				fread(&totalins, sizeof(unsigned int), 1, fp);
				printf("\ntotal instructions is %d \n", totalins);

				codeSize = totalins;
					 for (i = 0; i < totalins; i++) {
						 			 int opcode, type, val;
									 fread(&opcode,sizeof(int ), 1, fp);

									 if(code == NULL) code = malloc(sizeof(struct instruction));
									 if(i ==0 ) // giati theloume mono to prwto na graftei sto code
									 	  code->opcode = opcode;

									 // result
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);
									 if(i ==0 ){ // giati theloume mono to prwto na graftei sto code
											 if(type == -1 && val == -1){ code->arg1 = NULL;}
											 else{
												  code->result = malloc(sizeof(	struct vmarg));
												  code->result->type = type;
												  code->result->val = val;
											 }
								   }
									 printf("%d) opcode(%d) RESULT: type(%d), value(%d) \n",i+1, opcode, type, val );

									 // arg1
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);
									 if(i ==0 ){ // giati theloume mono to prwto na graftei sto code

												 if(type == -1 && val == -1) code->arg1 = NULL;
												 else{
													  code->arg1 = malloc(sizeof(	struct vmarg));

													  code->arg1->type = type;
													  code->arg1->val = val;
												 }
								 	 }
									 printf("\tARG1: type(%d), value(%d) \n", type, val );

									 // arg2
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);
									 if(i ==0 ){ // giati theloume mono to prwto na graftei sto code

											 if(type == -1 && val == -1) code->arg2 = NULL;
											 else{
												  code->arg2 = malloc(sizeof(	struct vmarg));

												  code->arg2->type = type;
												  code->arg2->val = val;
											 }
									 }
									 printf("\tARG2: type(%d), value(%d) \n", type, val );

					}

				printf("code at the end:: %d type %d val %d\n", code->opcode, code->result->type,  code->result->val );
				fclose(fp);
}
