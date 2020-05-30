#include "phase5.h"
#include <string.h>

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
	 execute_jump

};

library_funcs_t executelibFuncs[] = {
	libfunc_print,
	libfunc_input,
	libfunc_objectmemberkeys,
	libfunc_objecttotalmembers,
	libfunc_objectcopy,
	libfunc_totalarguments,
	libfunc_argument,
	libfunc_typeof,
	libfunc_strtonum,
	libfunc_sqrt,
	libfunc_cos,
	libfunc_sin
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

struct instruction**  code = NULL;



struct avm_memcell*	avm_translate_operand(struct vmarg* arg , struct avm_memcell* reg){

	 printf("type of vmarg %d\n",arg->type );
	switch (arg->type) {
		case global_a: return &stack[arg->val];
		case local_a:	printf("\n\n\nperno local %f\n\n\n",stack[topsp + arg->val].data.numVal );return &stack[topsp + arg->val];
		case formal_a: {
			printf("AVM_NUMACTUALS_OFFSET %f \n",stack[topsp AVM_NUMACTUALS_OFFSET].data.numVal );
			if (arg->val > stack[topsp AVM_NUMACTUALS_OFFSET].data.numVal) {
				printf("This argument was not pushed in stack. \n" );
				executionFinished=1;
				exit(0);
			}
			printf("%d\n",topsp - AVM_STACKENV_SIZE - 1 - arg->val );
			return &stack[topsp - AVM_STACKENV_SIZE - 1 - arg->val];
		}
		case retval_a:	return &retval;

		case number_a:	{
			reg= malloc(sizeof(struct avm_memcell));

			reg->type = number_m;
			reg->data.numVal = consts_getnumber(arg->val);

			return reg;
		}

		case string_a:	{
			reg= malloc(sizeof(struct avm_memcell));
			reg->type = string_m;
			reg->data.strVal = strdup(consts_getstring(arg->val));
			return reg;
		}

		case bool_a:	{
			reg= malloc(sizeof(struct avm_memcell));
			reg->type = bool_m;
			reg->data.bool = arg->val;
			return reg;
		}

		case nil_a : {
			reg= malloc(sizeof(struct avm_memcell));
			reg->type = nil_m; return reg;
		}
		case userfunc_a : {
			reg= malloc(sizeof(struct avm_memcell));
			reg->type = userfunc_m;
			reg->data.funcVal = arg->val;
			return reg;
		}
		case libfunc_a : {
	   	reg= malloc(sizeof(struct avm_memcell));
			reg->type = lib_func_m;
			reg->data.libfuncVal = libfuncs_getused(arg->val);
			return reg;
		}
		default : assert(0);

	}
}

void avm_initstack(){
	//gia ta globals
	top = globals;
	int i;
	for ( i = 0; i < globals; i++) {
		stack[i] =*(struct avm_memcell*) malloc(sizeof(struct avm_memcell));
		stack[i].type = undef_m;
	}


}

double	consts_getnumber(unsigned index){return numConsts[index];} //TODO
char*	consts_getstring(unsigned index){return stringConsts[index];}
char*	libfuncs_getused(unsigned index){return namedLibfuncs[index];}

double add_impl(double x, double y){return x+y;}
double sub_impl(double x, double y){return x-y;}
double mul_impl(double x, double y){return (double)(x*y);}
double div_impl(double x, double y){
	if(y == 0){
		avm_error("Division by zero!" );
		executionFinished=1;
		return 0;
	}else {
	 return (double)x/y;
 }
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

		return;
	} else if (pc >= AVM_ENDING_PC) {


			executionFinished = 1;
			return;
	} else {



		assert(pc < AVM_ENDING_PC);


		struct instruction* instr = malloc(sizeof(struct instruction));
		memcpy(instr,code[pc],sizeof(struct instruction));

		printf("now running ins(%s) %d \n", enum_toString_opCodes_v(code[pc]->opcode), instr->opcode);

		assert(instr->opcode>=0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
		if (instr->srcLine) currLine = instr->srcLine; //todo mallon ??
		unsigned oldPC = pc;


	//	printf("instr type %d\n",instr->opcode);
		(*executeFuncs[instr->opcode]) (instr);
		if (pc == oldPC) { // an DEN  htan jump

			++pc;
		}
		free(instr);
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
		m->type = undef_m;
	}


}
void avm_tablecrefcounter(struct avm_table* m){}	//TODO

void memclear_string(struct avm_memcell* m){
	assert(m->data.strVal);
	//free(m->data.strVal);

}
void memclear_table(struct avm_memcell* m){
	assert(m->data.tableVal);
	avm_tablecrefcounter(m->data.tableVal);
}
void avm_tableincrefcounter(struct avm_table* m){} //TODO


struct avm_table* avm_tablenew(){
	struct avm_table* tmp = malloc(sizeof(struct avm_table));

	tmp->data= malloc(sizeof(struct avm_memcell));
	tmp->data->type=undef_m;
//	tmp->index = malloc(sizeof(struct avm_memcell));
	tmp->index="";
	tmp->next=NULL;

	return tmp;
}

//----------------------------------------------------------
struct avm_memcell* avm_tablegetelem(struct avm_table* table , char* index ){
	struct avm_table* tmp = table;
	//printStack();
	printf("psaxno gia %s\n",index );
	while (tmp) {
		if(tmp->index){
			printf("%s , %s \n",index,tmp->index);
			if (strcmp(tmp->index,index)==0) {
				return tmp->data;
			}
	}
		tmp = tmp->next;
	}
	printf("nullll\n" );
	return  NULL;

}

void avm_setelem(struct avm_table* table , char* index , struct avm_memcell* data){
	struct avm_table* tmp=table;
	struct avm_memcell* tmpdata=malloc(sizeof(struct avm_memcell));

	memcpy(tmpdata, data, sizeof(struct avm_memcell));


if (table->data->type == undef_m) {
//	printf("if to prwto table set(%s,%f)\n", index, data->data.numVal);
//	strcpy(tmp->index ,index);
	tmp->index=malloc(sizeof(index)+1);
	tmp->index = strdup(index);
	tmp->data= malloc(sizeof(struct avm_memcell));
	memcpy(tmp->data, tmpdata,sizeof(struct avm_memcell));
	free(tmpdata);
	return;
}

while (tmp) {
	if(tmp->index){
		if (strcmp(tmp->index,index)==0) {
			tmp->data= malloc(sizeof(struct avm_memcell));
        memcpy(tmp->data, tmpdata,sizeof(struct avm_memcell));
        free(tmpdata);

			return;
		}
 }
tmp = tmp->next;
}
tmp = malloc(sizeof(struct avm_table));
 tmp->index=malloc(sizeof(index)+1);
//strcpy(tmp->index ,index);
tmp->index = strdup(index);
tmp->data= malloc(sizeof(struct avm_memcell));
        memcpy(tmp->data, tmpdata,sizeof(struct avm_memcell));

tmp->next = table->next;
table->next = tmp;

free(tmpdata);
}

void avm_assign(struct avm_memcell*	lv,struct avm_memcell*	rv){
	if (lv == rv) return;

	printf("avm assign types(%d,)\n", rv->type);




	if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal ) return;

	if (rv->type == undef_m) avm_warning("Assigning from 'undef' content!");

	//avm_memcellclear(lv);
	memcpy(lv,rv,sizeof(struct avm_memcell));

	if (lv->type == string_m) {
		lv->data.strVal = strdup(rv->data.strVal);
	} else if (lv->type == table_m) {
	//	avm_tableincrefcounter(lv->data.tableVal);
	}
}

void avm_callsaveenviroment(void){
	printf("call save env:: totalActuals(%d), pc+1(%d), top+totalActuals+2(%d), topsp(%d)\n",totalActuals, pc+1, (top+totalActuals + 2), topsp );
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top-totalActuals - 2);
	avm_push_envvalue(topsp);

}

void avm_dec_top (void){

	if (top >1024 ) { // na ginei max
		avm_error("Stack overflow\n");
		executionFinished=1;
	} else ++top;
}

void avm_push_envvalue (unsigned val) {
	stack[top] = *(struct avm_memcell*)malloc(sizeof(struct avm_memcell));
	stack[top].type =number_m;
	stack[top].data.numVal =val;
	avm_dec_top();
}

unsigned avm_get_envvalue(unsigned i){
	assert(stack[i].type == number_m);
	unsigned val = (unsigned) stack[i].data.numVal;

	assert(stack[i].data.numVal == ((double) val)); // wtf?? gia poio logo afou egine molis twra
	return val;
}



void avm_calllibfunc(char* id){
	totalActuals = 0;
	topsp = top;


	if (strcmp("print",id)==0) libfunc_print();
	else if (strcmp("input",id)==0) libfunc_input();
	else if (strcmp("objectmemberkeys",id)==0) libfunc_objectmemberkeys();
	else if (strcmp("objecttotalmembers",id)==0) libfunc_objecttotalmembers();
	else if (strcmp("objectcopy",id)==0) libfunc_objectcopy();
	else if (strcmp("sqrt",id)==0)libfunc_sqrt();
	else if (strcmp("cos",id)==0) libfunc_cos();
	else if (strcmp("sin",id)==0)libfunc_sin();
	else if (strcmp("strtonum",id)==0) libfunc_strtonum();
	else if (strcmp("typeof",id)==0) libfunc_typeof();
	else if (strcmp("totalarguments",id)==0)libfunc_totalarguments();
	else if(strcmp("argument",id)==0)libfunc_argument();
	else { printf("lathos onoma i den iparki %s \n", id );}

	unsigned oldTop = top;

	top = avm_get_envvalue	(topsp  AVM_SAVEDTOP_OFFSET);
	pc 	= avm_get_envvalue	(topsp  AVM_SAVEDPC_OFFSET);
	topsp = avm_get_envvalue(topsp AVM_SAVEDTOPSP_OFFSET);


	while (--oldTop >= top) {
		avm_memcellclear(&stack[oldTop]);
	}

}

library_funcs_t avm_getlibraryfunc (char* id){

	 return 0;
}

unsigned avm_totalactuals(void) {

	return avm_get_envvalue(topsp   AVM_NUMACTUALS_OFFSET );

}

struct avm_memcell* avm_getactual(unsigned i){
	assert(i<avm_totalactuals());
	return &stack[topsp - AVM_STACKENV_SIZE  - i -1];
}

struct userfunc* avm_getfuncinfo(unsigned address){
		return userFuncs[address];
}
//--------------------------------------



//------------------libfuncs----------------
void libfunc_print(){
	unsigned n = avm_totalactuals();


	unsigned i=0;

	for (; i < n; i++) {
		char* s = malloc(sizeof(char)*10);
		s = avm_tostring(avm_getactual(i));
//strcpy(s, avm_tostring(avm_getactual(i)));
		printf("PRINT: %s ",s);
		free(s);
	}
	printf("\n" );
	//printStack();
}

void libfunc_input(){
	avm_memcellclear(&retval);
	char* str = malloc(sizeof(char)*100);

	printf( "Enter a value :");
	fgets( str, 100, stdin );
	strtok(str, "\n"); //gia na afairesw ton \n xarakthra pou bazei sto telos h fgets

	printf( "\nYou entered: ");
	puts( str );

	if(strcmp(str, "true") == 0){
		retval.type = bool_m;
		retval.data.bool = 1;
		printf("input: type: %d, value: true\n",retval.type);

	}
	else if(strcmp(str, "false") == 0 ){
		retval.type = bool_m;
		retval.data.bool = 0;
		printf("input: type: %d, value: false\n",retval.type);
	}
	else if(strcmp(str, "nil") == 0 ){
		retval.type = nil_m;
		retval.data.strVal = "nil";
		printf("input: type: %d, value: nil\n",retval.type);
	}
	else if(strncmp(str,"\"", 1) == 0 && str[strlen(str-1)] == '\"'){
// 		printf("prwto %c, teleutaio %c\n",str[0], str[strlen(str-1)] );
		printf("its a string\n" );
		retval.type = string_m;
		retval.data.strVal = str;
		printf("input: type: %d, value: %s\n",retval.type, retval.data.strVal );
	}
	else if( atoi(str) != 0 ){
		printf("number \n" );
		retval.type = number_m;
		retval.data.numVal = atoi(str);
		printf("input: type: %d, value %f\n",retval.type, retval.data.numVal );
	}
	else{

	}

}

struct avm_table* table_objectkeys = NULL;

void avm_newnode(struct avm_table** head, char* index, char* data){
	struct avm_table* newnode = NULL, *last = NULL;
	if(*head == NULL){
		*head = malloc(sizeof(struct avm_table));
		(*head)->index = index;
		(*head)->data->data.strVal = malloc(100* sizeof(char));
		(*head)->data->data.strVal= data;
		(*head)->next = NULL;
		return;
	}
	else{
			newnode = malloc(sizeof(struct avm_table));
			newnode->index = index;
			newnode->data->data.strVal = malloc(100* sizeof(char));
			newnode->data->data.strVal= data;
			newnode->next = NULL;
	}
	last = *head;
	while (last->next !=NULL) {
		  printf("while %s\n",last->data->data.strVal );
			last = last->next;
	}
	last->next = newnode;
	return;
}

void libfunc_objectmemberkeys(){

	unsigned n = avm_totalactuals();

	if(n != 1) avm_error("libfunc objectmemberkeys: error arguments");
	else{
		if(avm_getactual(0)->type == 3){ //table
			struct avm_table* tmp = avm_getactual(0)->data.tableVal;
			int counter = 0;
			while (tmp) {
					if(tmp->index){
						char* index = malloc(5*sizeof(char));
						sprintf(index,"%d",counter);
   					printf("objectmemberkeys lib func:(%d) (%s)\n",n, tmp->index);
					  avm_newnode(&table_objectkeys, index,tmp->index );
						counter++;
					}
				tmp = tmp->next;
			}
			while (table_objectkeys) {
					printf("test new table: %s \n",table_objectkeys->data->data.strVal );
					table_objectkeys = table_objectkeys->next;
			}
			printf("objectmemberkeys done!\n");
		}
		else{
			avm_error("libfunc objectmemberkeys: error: not valid variable type!");
			return;
		}
	}

}

void libfunc_objecttotalmembers(){
	unsigned n = avm_totalactuals();

	if(n != 1) avm_error("libfunc objecttotalmembers: error arguments");
	else{
		if(avm_getactual(0)->type == 3){ //table
			struct avm_table* tmp = avm_getactual(0)->data.tableVal;
			int counter = 0;

			while (tmp) {
				if(tmp->index)	counter++;
				tmp = tmp->next;

			}
			retval.type = number_m;
			retval.data.numVal = counter;
			printf("objecttotalmembers: %d!\n", counter);
		}
		else{
			avm_error("libfunc objecttotalmembers: error: not valid variable type!");
			return;
		}
	}
}

void libfunc_objectcopy(){
	unsigned n = avm_totalactuals();

	if(n != 1) avm_error("libfunc objectcopy: error arguments");
	else{
		if(avm_getactual(0)->type == 3){ //table
			struct avm_table* tmp = avm_getactual(0)->data.tableVal;

			//gia test oti mphkan swsta
			/*while (tmp) {
				printf("objectcopy lib func:(%d) (%f)\n",n, tmp->data->data.numVal);
				tmp = tmp->next;

			}*/
			printf("objectcopy done!\n");
		}
		else{
			avm_error("libfunc objectcopy: error: not valid variable type!");
			return;
		}
	}
}

void libfunc_totalarguments(void){
//TODO ? an kalesoume thn function me ligotera arguments apo osa exei h dhlwsh poia #args prepei na epistrepsei?
	unsigned p_topsp = avm_get_envvalue(topsp   AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	if (!p_topsp) {
		avm_error("'totalarguments' called outside a function!");
		retval.type=nil_m;
	}else {
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp  AVM_NUMACTUALS_OFFSET);
		printf("totalarguments: %f\n",	retval.data.numVal );
	}


}

void libfunc_argument(){
	unsigned p_topsp = avm_get_envvalue(topsp  + AVM_SAVEDTOPSP_OFFSET);
	printf("p_topsp = %u\n",p_topsp );
	avm_memcellclear(&retval);
	int i;
	if (!p_topsp) {
		avm_error("'libfunc arguments' called outside a function!");
		retval.type=nil_m;
	}else {
		unsigned n = avm_totalactuals();
		double num;

		if(n != 1) avm_error("libfunc arguments:: error arguments");
		else{
				if(avm_getactual(0)->type == 0){ //num type
						i = avm_getactual(0)->data.numVal+1;
						printf("i =%d\n",i );
						printf("kappa %d\n",p_topsp -4 - i );
						retval.type = number_m;
						double totalArgs = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
						if(i < 0 || i > totalArgs) {
						  	avm_error("number of argument you gave is bigger than total arguments of function\n");
						}
						else {

							retval.data.numVal = avm_get_envvalue(p_topsp -4 - i);
						 	printf("argument:: get %d at stack %d \n",i ,(p_topsp  AVM_NUMACTUALS_OFFSET - i));


						}
				}
				else{
					avm_error("libfunc arguments:: argument must be of type number");
				}
			}
	}

}

void  libfunc_typeof(){
// den eimai sigourh gia to pws ginetai h klhsh typeof me functions
		unsigned n = avm_totalactuals();

		if(n != 1) avm_error("libfunc typeof:: error arguments");
		else{

			//to return a result we set the retval register
			avm_memcellclear(&retval);
			retval.type = string_m;
			retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
			printf("typeof: %s\n", retval.data.strVal);
		}

}

//TODO oles oi lib func theloun allages

void libfunc_strtonum(){
	double tonum;
	char * str;
	unsigned n = avm_totalactuals();

	if(n != 1) avm_error("libfunc strtonum: error arguments");
	else{
		if(avm_getactual(0)->type == 1){ //str type
				printf("str to  num lib func:(%d) (%s)\n",n, avm_getactual(0)->data.strVal );
				str = avm_getactual(0)->data.strVal;
		}
		else{ //todo ??
			// den kserw an px mas dinoun ena number an thelei na to epistrefoume opws einai
			avm_error("libfunc strtonum: error: not valid variable type!");
			return;
		}
	}
	tonum = atoi(str);
	printf("strtonum: %f\n", tonum);

	//if(atoi(str) == 0) avm_error("cannot convert string to number! \n" ); //????? gamw
	//todo to nil !!!

}

//thelei check gia -1, ekei pou kaleitai!!!
void libfunc_sqrt(){
	double num;
	unsigned n = avm_totalactuals();

	if(n != 1) avm_error("libfunc sqrt: error arguments");
	else{
		if(avm_getactual(0)->type == 0){
				printf("sqrt lib func:(%d) (%f)\n",n, avm_getactual(0)->data.numVal );
				num = avm_getactual(0)->data.numVal;
		}
		else if(avm_getactual(0)->type == 3){
			struct avm_table* tmp = avm_getactual(0)->data.tableVal;
			printf("sqrt lib func:(%d) (%f)\n",n, tmp->data->data.numVal);
			num = tmp->data->data.numVal;
		}
		else{
			avm_error("libfunc sqrt: error: not valid variable type!");
			return;
		}
		if(num < 0 ) {
				avm_error("Cannot calculate sqrt of subzero number!\n");
				return;
		}
		printf("sqrt: %f\n", sqrt(num));
	}
}

void libfunc_cos( ){
	double rad;
	unsigned n = avm_totalactuals();

	if(n != 1) avm_error("libfunc cos: error arguments");
	else{
		if(avm_getactual(0)->type == 0){
				printf("cos lib func:(%d) (%f)\n",n, avm_getactual(0)->data.numVal );
				rad = avm_getactual(0)->data.numVal;
		}
		else if(avm_getactual(0)->type == 3){
			struct avm_table* tmp = avm_getactual(0)->data.tableVal;
			printf("cos lib func:(%d) (%f)\n",n, tmp->data->data.numVal);
			rad = tmp->data->data.numVal;
		}
		else{
			avm_error("libfunc cos: error: not valid variable type!");
			return;
		}

	// Converting to radian
	  rad = (rad * 3.14159265) / 180;
		printf("cos: %f\n", cos(rad));
	}
}

void libfunc_sin( ){

	double rad;
	unsigned n = avm_totalactuals();

	if(n != 1) avm_error("libfunc sin: error arguments");
	else{
		if(avm_getactual(0)->type == 0){
				printf("sin lib func:(%d) (%f)\n",n, avm_getactual(0)->data.numVal );
				rad = avm_getactual(0)->data.numVal;
		}
		else if(avm_getactual(0)->type == 3){ //table
			struct avm_table* tmp = avm_getactual(0)->data.tableVal;
			printf("sin lib func:(%d) (%f)\n",n, tmp->data->data.numVal);
			rad = tmp->data->data.numVal;
		}
		else{
			avm_error("libfunc sin: error: not valid variable type!");
			return;
		}

	// Converting to radian
		rad = (rad * 3.14159265) / 180;
		printf("sin: %f\n", sin(rad));
	}

}

void avm_registerlibfunc (char* id , library_funcs_t addr){} // TODO

//------------------------------------------



void execute_arithmetic(struct instruction* instr){
	  	struct avm_memcell* lv = avm_translate_operand(instr->result, NULL);

		struct avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
		struct avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

		//assert(lv && (&stack[0] <= lv && &stack[top] > lv || lv == &retval)); ?? slide 25 to exei alliws
		assert(rv1 && rv2);
		if( rv1->type != number_m  || rv2->type != number_m ){
				printf("arithmetic ex:: not a number!%d %d \n",rv1->type,rv2->type);
				exit(0);
				executionFinished = 1;
		}
		else{


				arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];

				//avm_memcellclear(lv);
				lv->type = number_m;
				lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);


		}
}



void execute_assign (struct instruction* ins){

	struct avm_memcell*	lv = avm_translate_operand(ins->result , NULL);
	struct avm_memcell*	rv = avm_translate_operand(ins->arg1 , &ax);


// ??	assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval ))
	avm_assign(lv,rv);
	printf("in assign after avmassign %f kai rv %f\n", lv->data.numVal, rv->data.numVal );

}

void execute_add 	(struct instruction* ins) { execute_arithmetic(ins);	} //?? }
void execute_sub	(struct instruction* ins) {	execute_arithmetic(ins);	}
void execute_mul	(struct instruction* ins) { execute_arithmetic(ins);	}
void execute_div	(struct instruction* ins) { execute_arithmetic(ins);	}
void execute_mod	(struct instruction* ins) { execute_arithmetic(ins); 	}
void execute_uminus	(struct instruction* ins) {}//XXXXXXXXXXXX NO USE

void execute_and 	(struct instruction* ins) {}//XXXXXXXXXXXX NO USE
void execute_or 	(struct instruction* ins){}//XXXXXXXXXXXX NO USE
void execute_not 	(struct instruction* ins){}//XXXXXXXXXXXX NO USE

//oles oi jump if kati exoun sto value to jump label, bazoume -1
void execute_jeq	(struct instruction* ins){
		assert(ins->result->type == label_a);
		printf("arxh jeq\n" );
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
		else 	if ( rv1->type !=rv2->type ){
						 avm_error("illegal types in jeq!\n");
				  }
		else{
			if( rv1->type == number_m &&  rv2->type == number_m ){
					printf("JEQ 2 numbers %f and %f \n", rv1->data.numVal, rv2->data.numVal );

					if(rv1->data.numVal == rv2->data.numVal ) result = 1;
					else result = 0;

					printf("result is %d\n",result );
					}
			if( rv1->type == string_m &&  rv2->type == string_m ){
					printf("JEQ 2 strings  %s and %s \n", rv1->data.strVal, rv2->data.strVal );

				  if(strcmp(rv1->data.strVal,rv2->data.strVal) == 0 ) result = 1;
					else result = 0;

					printf("result is %d\n",result );
			}
			if( rv1->type == lib_func_m &&  rv2->type == lib_func_m ){
				printf("JEQ 2 lib funcs  %s   kai %s \n", rv1->data.libfuncVal,  rv2->data.libfuncVal );

				if(strcmp( rv1->data.libfuncVal,  rv2->data.libfuncVal ) == 0 ) result = 1;
				else result = 0;
				printf("result is %d\n",result );
			}
			if( rv1->type == userfunc_m && rv2->type == userfunc_m){
				printf("JEQ 2 userfuncs %s  kai %s \n", userFuncs[rv1->data.funcVal]->id,  userFuncs[rv2->data.funcVal]->id );
				if(strcmp(userFuncs[rv1->data.funcVal]->id,  userFuncs[rv2->data.funcVal]->id) == 0) result = 1;
				else result = 0;
				printf("result is %d\n",result );

			}
			if( rv1->type == table_m && rv2->type == table_m){
				printf("JEQ 2 table  \n");
				result = table_equal(rv1,rv2);
				printf("result is %d\n",result );

			}
			printf("\n\n->>>%d %d\n\n",rv1->type , rv2->type );
		}

		if(!executionFinished && result ){
   			execute_jump(ins);
				printf("if result is 1, pc is %d\n\n",pc  );
			}
}


int table_equal(struct avm_memcell* rv1,struct avm_memcell* rv2){
		struct avm_table* table1 = rv1->data.tableVal;
		struct avm_table* table2 = rv2->data.tableVal;
		printf("eimai %d\n", table1->data->type);
		int flag = 0;

		while(table1 ){
			flag = 0;
			table2 = rv2->data.tableVal;
			while( table2){

				if(strcmp(table1->index,table2->index) == 0 ){
					if(table1->data->type != table2->data->type) return 0;
					switch (table1->data->type) {
						case  number_m: 	if(table1->data->data.numVal == table2->data->data.numVal) {flag = 1; break;} else{ return 0;}
						case	string_m:	if( strcmp( table1->data->data.strVal, table2->data->data.strVal)) {flag = 1; break;} else{ return 0;}
						case 	bool_m	: if(table1->data->data.bool == table2->data->data.bool) {flag = 1; break;} else{ return 0;}
						case	table_m	:	 if(table_equal(table1->data, table2->data) == 0) return 0; else {flag = 1; break;}
						case	userfunc_m	:	 if(table1->data->data.funcVal == table2->data->data.funcVal) {flag = 1; break;} else{ return 0;}
						case	lib_func_m	:	 if( strcmp( table1->data->data.libfuncVal, table2->data->data.libfuncVal)) {flag = 1; break;} else{ return 0;}
						case	nil_m	: flag = 1; break;
						case	undef_m	:	flag = 1;  break;
					}
				}
				table2 = table2->next;

			}
			if(flag  == 0 ) return 0;
			table1 = table1->next;
		}

return 1;
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
		if( rv1->type == number_m &&  rv2->type == number_m ){
				printf("JNE 2 numbers %f and %f \n", rv1->data.numVal, rv2->data.numVal );

				if(rv1->data.numVal != rv2->data.numVal ) result = 1;
				else result = 0;

				printf("result is %d\n",result );
				}
		if( rv1->type == string_m &&  rv2->type == string_m ){
				printf("JNE 2 strings  %s and %s \n", rv1->data.strVal, rv2->data.strVal );

				if(strcmp(rv1->data.strVal,rv2->data.strVal) == 0 ) result = 0;
				else result = 1;

				printf("result is %d\n",result );
		}
		if( rv1->type == lib_func_m &&  rv2->type == lib_func_m ){
			printf("JNE 2 lib funcs  %s kai %s \n", rv1->data.libfuncVal,  rv2->data.libfuncVal );

			if(strcmp( rv1->data.libfuncVal,  rv2->data.libfuncVal ) == 0 ) result = 0;
			else result = 1;
			printf("result is %d\n",result );
		}
		if( rv1->type == userfunc_m && rv2->type == userfunc_m){
			printf("JNE 2 userfuncs %s  kai %s \n", userFuncs[rv1->data.funcVal]->id,  userFuncs[rv2->data.funcVal]->id );
			if(strcmp(userFuncs[rv1->data.funcVal]->id,  userFuncs[rv2->data.funcVal]->id) == 0) result = 0;
			else result = 1;
			printf("result is %d\n",result );

		}

	}

	if(!executionFinished && result )
			execute_jump(ins);
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
		if( rv1->type == number_m &&  rv2->type == number_m ){
				printf("JLE 2 numbers %f and %f \n", rv1->data.numVal, rv2->data.numVal );

				if(rv1->data.numVal <= rv2->data.numVal ) result = 1;
				else result = 0;

				printf("result is %d\n",result );
				}
	}

	if(!executionFinished && result )
			execute_jump(ins);
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
		if( rv1->type == number_m &&  rv2->type == number_m ){
				printf("JGE 2 numbers %f and %f \n", rv1->data.numVal, rv2->data.numVal );

				if(rv1->data.numVal >= rv2->data.numVal ) result = 1;
				else result = 0;

				printf("result is %d\n",result );
			}
	}

	if(!executionFinished && result )
			execute_jump(ins);
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
		if( rv1->type == number_m &&  rv2->type == number_m ){
				printf("JLT 2 numbers %f and %f \n", rv1->data.numVal, rv2->data.numVal );

				if(rv1->data.numVal < rv2->data.numVal ) result = 1;
				else result = 0;

				printf("result is %d\n",result );
			}
	}

	if(!executionFinished && result )
			execute_jump(ins);
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
		if( rv1->type == number_m &&  rv2->type == number_m ){
				printf("JGT 2 numbers %f and %f \n", rv1->data.numVal, rv2->data.numVal );

				if(rv1->data.numVal > rv2->data.numVal ) result = 1;
				else result = 0;

				printf("result is %d\n",result );
			}
	}

	if(!executionFinished && result )
			execute_jump(ins);
}

//to quad call exei sto arg1 -> val to label quad pou theloume na paei opote vazoume val-1!!!
void execute_call		(struct instruction* ins){
		unsigned oldpc = pc;
		struct avm_memcell* func = avm_translate_operand(ins->arg1 , &ax);
		assert(func);
		avm_callsaveenviroment();


		switch (func->type) {
			case userfunc_m: {

				struct userfunc* tmpFunc = avm_getfuncinfo(func->data.funcVal);
				pc = tmpFunc->address;

				printf("user func call pc %d ending %d\n", pc,AVM_ENDING_PC);
				assert(pc < AVM_ENDING_PC);
				if (code[pc]->opcode != funcenter_v){
					  //funcenter_v is funcstart
					  //an den einai orismenh h sunarthsh prepei na petaksei error
					  printf("Undefined user function %s!\n", userFuncs[func->data.funcVal]->id);
						executionFinished =1;
						exit(0);
					}
//					assert(code[pc]->opcode == funcenter_v);

				break;
			}
			case string_m:		printf("STRING\n" );avm_calllibfunc(func->data.strVal); break;
			case lib_func_m:	avm_calllibfunc(func->data.libfuncVal); break;
			case table_m:	{

						switch (func->data.tableVal->data->type) {
							case string_m:		printf("TABLE => STRING\n" );avm_calllibfunc(func->data.strVal); break;
							case lib_func_m:	avm_calllibfunc(func->data.libfuncVal); break;
							case userfunc_m:	{
								struct userfunc* tmpFunc = avm_getfuncinfo(func->data.tableVal->data->data.funcVal);
								pc = tmpFunc->address;
								printf("%d\n",func->data.tableVal->data->data.funcVal );

								printf("user func call pc %d ending %d\n", pc,AVM_ENDING_PC);
								assert(pc < AVM_ENDING_PC);
								if (code[pc]->opcode != funcenter_v){
									  //funcenter_v is funcstart
									  //an den einai orismenh h sunarthsh prepei na petaksei error
									  printf("Undefined user function %s!\n", userFuncs[func->data.tableVal->data->data.funcVal]->id);
										executionFinished =1;
										exit(0);
									}
				//					assert(code[pc]->opcode == funcenter_v);

								break;

							}
							default: printf("\nTABLE TIPOTA %d\n",func->data.tableVal->data->type);
						}
						break;
			}
			default : {
				printf("Error: This is not a function, type: %d\n", func->type);
				exit(0);
				executionFinished=1;
			}
			}
}
void execute_pusharg	(struct instruction* ins){
	//printf("push: type %d val %d \n",ins->arg1->type , ins->arg1->val  );
	struct avm_memcell* arg = avm_translate_operand(ins->arg1,&ax);
	assert(arg);
	//printf("arg is %d\n", arg->type );
	stack[top] = *(struct avm_memcell*) malloc(sizeof(struct avm_memcell));
	avm_assign(&stack[top],arg);
	++totalActuals;
	avm_dec_top();
	 printf("stack after push arg\n" );

}

void execute_funcenter	(struct instruction* ins){
	printf("funcenter!! \n" );
	struct avm_memcell* func = avm_translate_operand(ins->result , &ax);
	assert(func);
	printf("pc is %d and funcval address  is %d\n",pc, userFuncs[func->data.funcVal]->address );
	assert(pc == userFuncs[func->data.funcVal]->address );

	totalActuals = 0;

//	struct userfunc* funcInfo = avm_getfuncinfo(userFuncs[func->data.funcVal]->address );
//	assert(funcInfo);
	printf("in funcenter top is %d and function size is %d\n", top, userFuncs[func->data.funcVal]->localSize);
	topsp=top;
	top = top + userFuncs[func->data.funcVal]->localSize;

}
void execute_funcexit	(struct instruction* ins){

	unsigned oldTop = top;

	top = avm_get_envvalue	(topsp  AVM_SAVEDTOP_OFFSET);
	pc 	= avm_get_envvalue	(topsp  AVM_SAVEDPC_OFFSET);
	topsp = avm_get_envvalue(topsp AVM_SAVEDTOPSP_OFFSET);
	printf("\n\n\n\n%d %d %d \n\n\n",top,pc,topsp );

	while (--oldTop >= top) {


		avm_memcellclear(&stack[oldTop]);
	}
}


void execute_newtable		(struct instruction* ins){
	struct avm_memcell* lv = avm_translate_operand(ins->result , NULL);

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

	//avm_memcellclear(lv);
	//lv->type = nil_m; //default val

	if(t->type != table_m ){
		avm_error("illegal use of variable as a table! \n");

	}
	else{
		char* res=malloc(5);

		switch (i->type) {

			case number_m:	sprintf(res , "%f",i->data.numVal); break;
			case string_m:	res=strdup(i->data.strVal); break;
                                case userfunc_m: {
                                        printf("eimai mia loulou %d %s", i->data.funcVal, userFuncs[i->data.funcVal]->id);
                                        char* tmp = malloc(10);
                                        sprintf(tmp,"%f",(double)i->data.funcVal);
                                        res=strdup(tmp);
                                        free(tmp);
                                        break;

                                }
								case bool_m : res = strdup(bool_tostring(i)); break;
                                case table_m: printf("EIMAI TABLEEEE\n"); res = strdup(table_tostring(i)); break;
                                case lib_func_m: res = strdup(i->data.libfuncVal); break;
			default : 	res=strdup(i->data.strVal); break;
		}


			struct avm_memcell* content= avm_tablegetelem(t->data.tableVal, res );
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


		assert(i && c);
		printf("%d\n", t->type );
		printf("dssss\n" );
		if(t->type != table_m)	{	avm_error("illegal use of variable as a table in setelem! \n"); exit(0);}
		else {
			printf("edwww\n");
			char* res=malloc(5);
                        printf("edwwwqqqq\n");


			switch (i->type) {


				case number_m:{
                        printf("edwwwweafd\n");

				char* tmp = malloc(10);
                        printf("edwww number\n");

				sprintf(tmp,"%f",i->data.numVal);
				res=strdup(tmp);
				free(tmp);
				break;
				}
				case string_m:	res=strdup(i->data.strVal); break;
				case userfunc_m: {
					printf("eimai mia loulou %d %s", i->data.funcVal, userFuncs[i->data.funcVal]->id);
					char* tmp = malloc(10);
					sprintf(tmp,"%f",(double)i->data.funcVal);
	                                res=strdup(tmp);
        	                        free(tmp);
					break;

				}
				case bool_m : res = strdup(bool_tostring(i)); break;
				case table_m: printf("EIMAI TABLEEEE\n"); res = strdup(table_tostring(i)); break;
                                case lib_func_m: res = strdup(i->data.libfuncVal); break;
				default :   res=strdup(i->data.strVal); break;
			}

			printf("\n\n\nres =%s \n\n\n",res );
			avm_setelem(t->data.tableVal, res, c);
printf("prin ffree\n");
			free(res);
printf("meta free\n");
		}
}

void execute_nop	(struct instruction* ins){}
void execute_jump	(struct instruction* ins){
	  // to jump quad exei sto value to label poy kanei jump, prepei na einai -1
		pc = ins->result->val -1; printf("jumping to %d \n", pc );
	}

//den exw balei to executon executionFinished =1 edw, na to bazoume kathe fora pou thn  kaloume
void avm_error(char *msg){
	  executionFinished = 1;
  	printf("Error: %s\n",msg);
}
void avm_warning(char* msg ){
	 printf("\nWarning: %s ",msg);
}


char* avm_tostring(struct avm_memcell* cell){
	assert(cell->type >= 0 && cell->type <= undef_m);
	return (*tostringFuncs[cell->type])(cell);
}


char* number_tostring (struct avm_memcell* cell){

		char* str=malloc(sizeof(char)*6);
    	sprintf(str,"%.2f",cell->data.numVal );
		return str;
	}
char* string_tostring (struct avm_memcell* cell){return cell->data.strVal;}
char* bool_tostring (struct avm_memcell* cell){
	char* str=malloc(sizeof(char)*6);

	if ((int)cell->data.bool==1) strcpy(str , "true");
	else strcpy(str , "false");
	return str;
}

char* userfunc_tostring (struct avm_memcell* cell){

	char* str=malloc(sizeof(char*)*20);
	sprintf(str,"user function: %u",userFuncs[cell->data.funcVal]->address);
	return str;
}
char* libfunc_tostring (struct avm_memcell* cell){

	char* str = malloc(sizeof(char)*strlen(cell->data.libfuncVal)+18);
	sprintf(str,"library function: %s",cell->data.libfuncVal);
	return str;

}
char* nil_tostring (struct avm_memcell* cell){char* str=malloc(sizeof(char*)*3); str = strdup("nil"); return str;}
char* undef_tostring (struct avm_memcell* cell){char* str=malloc(sizeof(char*)*5); str = strdup("undef"); return str;}

char* table_tostring (struct avm_memcell* cell){
	char* str=malloc(sizeof(char));
	str = strdup("[");
	struct avm_table* tmp = cell->data.tableVal;
	while (tmp) {
		if (tmp->index==NULL) return strdup("[ ]");
		char* elemdata;
		switch (tmp->data->type) {
			case  	number_m: 	elemdata=number_tostring(tmp->data); break;
			case	string_m:	elemdata=string_tostring(tmp->data); break;
			case 	bool_m	:	elemdata=bool_tostring(tmp->data); break;
			case	table_m	:	elemdata=table_tostring(tmp->data); break;
			case	userfunc_m	:	elemdata=userfunc_tostring(tmp->data); break;
			case	lib_func_m	:	elemdata=libfunc_tostring(tmp->data); break;
			case	nil_m	:	elemdata=nil_tostring(tmp->data); break;
			case	undef_m	:	elemdata=undef_tostring(tmp->data); break;
		}
		char* index=malloc(sizeof(char)*strlen(tmp->index));
		index = strdup(tmp->index);

		char* whole=malloc(sizeof(char)*strlen(index) + sizeof(char)*strlen(elemdata) + 14);
		sprintf(whole,"{ \"%s\" : %s } , ",index,elemdata);

		str=realloc(str,sizeof(char)*strlen(str) + sizeof(char)*strlen(whole)+1 ); // fixes error 3
		strcat(str,whole);
		tmp=tmp->next;
	}
	str[strlen(str)-2]=*strdup("]");
	return str;
}

unsigned char avm_tobool(struct avm_memcell* m){
		assert(m->type >= 0 && m->type < undef_m);
		return (*toboolFuncs[m->type])(m);
}


void read_binfile(){
				FILE *fp = NULL;
				int i =0;
		 		//   fputs("2", fp);
				//printf("ff\n" );
	   			fp = fopen("test.bin", "rb");
		 		int magic;
		 		unsigned int totalStr, totalNums, totaluserF, totallibF, totalins;
	      		fread(&magic, sizeof(int), 1, fp);
	      		//printf("\nmagic number is: %d \n", magic);
		  		fread(&globals,sizeof(unsigned int),1,fp);

				fread(&totalStr, sizeof(unsigned int), 1, fp);
				//printf("\ntotal string is %d \n", totalStr);
				totalNumConsts=totalStringConsts=totalNamedLibfuncs=totalUserFuncs=0;
				stringConsts = malloc(sizeof(char*) * totalStr);

		    for(i=0; i<totalStr; i++){
								unsigned int len = 0;

							 if(fread(&len,sizeof(unsigned int), 1, fp) != 1) //length of each string
							 		printf("Error reading file \n");
							//printf("size (%d)  ",len );
							char* str = malloc(sizeof(char) *len);
							int i = 0;
							for ( ;i < len; i++) {
								if(fread(&str[i],sizeof(char ) , 1, fp)!= 1)
									printf("Error reading file \n");
							}
							add_consts_string(str);

							//printf("str: %s\n",str );
		    }

				fread(&totalNums, sizeof(unsigned int), 1, fp);
			//	printf("\ntotal nums is %d \n", totalNums);
				numConsts = malloc(sizeof(double)* totalNums);
				for(i=0; i<totalNums; i++){
			        double num;
			        fread(&num,sizeof(double), 1, fp);
			       // printf("num:%f\n", num);
				 add_consts_num(num);
				// printf("fasd\n" );

				}

				fread(&totaluserF, sizeof(unsigned int), 1, fp);
				//printf("\ntotal userfuncs is %d \n", totaluserF);
				userFuncs = malloc(sizeof(struct userfunc)* totaluserF);

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
								add_consts_userfuncs(id,addr,localsize,-1);


	 	    }
				fread(&totallibF, sizeof(unsigned int), 1, fp);
				printf("\ntotal libfuncs is %d \n", totallibF);
				//namedLibfuncs=malloc(sizeof(char*)*totaluserF);
				for(i=0; i<totallibF; i++){
								unsigned int len;
							  fread(&len,sizeof(unsigned int), 1, fp); //length of each string
								char * libF = malloc(sizeof(char )*len);

								int i = 0;
								for ( ;i < len; i++) {
									if(fread(&libF[i],sizeof(char ) , 1, fp)!= 1)
										printf("Error reading file \n");
								}
							//	add_consts_libfuncs(libF);

								printf("size (%d) of libF: %s\n",len, libF );
		    }

				fread(&totalins, sizeof(unsigned int), 1, fp);
				//printf("\ntotal instructions is %d \n", totalins);

				codeSize = totalins;
					 for (i = 0; i < totalins; i++) {
						 			 int opcode, type, val;
									 fread(&opcode,sizeof(int ), 1, fp);

									 if(code == NULL) code = malloc(sizeof(struct instruction *)*codeSize);
									 	  code[i] = malloc(sizeof(struct instruction));
											code[i]->opcode = opcode;
										//	printf("opcode %d kai code opcode %d\n",opcode , code[i]->opcode );
									 // result
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);
											 if(type == -1 && val == -1){
												  code[i]->result = NULL;
											 }
											 else{
												  code[i]->result = malloc(sizeof(struct instruction));
												  code[i]->result = malloc(sizeof(	struct vmarg));
												  code[i]->result->type = type;
												  code[i]->result->val = val;
											 }

								//	 printf("%d) opcode(%d) RESULT: type(%d), value(%d) \n",i+1, opcode, type, val );

									 // arg1
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);

												 if(type == -1 && val == -1){
													  code[i]->arg1 = NULL;
													}
												 else{
 													  code[i]->arg1 = malloc(sizeof(struct instruction));
													  code[i]->arg1 = malloc(sizeof(	struct vmarg));
													  code[i]->arg1->type = type;
													  code[i]->arg1->val = val;
												 }

								//	 printf("\tARG1: type(%d), value(%d) \n", type, val );

									 // arg2
									 fread(&type,sizeof( int), 1, fp);
					 			   fread(&val,sizeof( int), 1, fp);
									 //if(i ==0 ){ // giati theloume mono to prwto na graftei sto code

											 if(type == -1 && val == -1) {
 												    code[i]->arg2 = malloc(sizeof(struct instruction));
												 	code[i]->arg2 = NULL;
											}
											 else{
												 	code[i]->arg2 = malloc(sizeof(struct instruction));
												  code[i]->arg2 = malloc(sizeof(	struct vmarg));

												  code[i]->arg2->type = type;
												  code[i]->arg2->val = val;
											 }

								//	 printf("\tARG2: type(%d), value(%d) \n", type, val );

					}
				fclose(fp);
				printf("=========strings:============\n" );

					int j=0;
					while (j< totalStringConsts) {
						 printf("%s \n", stringConsts[j]);
						j++;
					}
				printf("=========nums:============\n" );
					j=0;
					while (j< totalNumConsts) {
						 printf("%f \n", numConsts[j]);
						j++;
					}

					printf("========lib funcs:============\n" );
					j=0;
					while (j< 12) {
						 printf("%s \n", namedLibfuncs[j]);
						j++;
					}
					printf("========user funcs:============\n" );
					j=0;
					while (j< totalUserFuncs) {
						 printf("%s #args %d   locals %d address %d\n", userFuncs[j]->id, userFuncs[j]->totalargs,userFuncs[j]->localSize, userFuncs[j]->address);
						j++;
					}

					j=0;
					while (j< totalins) {
						 printf("opcode %d\n", code[j]->opcode);
						j++;
					}
}


void printStack(){
	int i;
	for ( i = 0; i < 50; i++) {

		printf("stack[%d]", i);
		switch (stack[i].type) {
			case number_m:	printf(" n %.2f\n", stack[i].data.numVal); break;
			case string_m:	printf("%s\n", stack[i].data.strVal );	break;
			case bool_m:	if(stack[i].data.bool) printf(" true \n"); else printf(" false \n"); 	break;
			case lib_func_m:printf("%s\n",stack[i].data.libfuncVal);break;
			case userfunc_m:printf("%.s\n", userFuncs[stack[i].data.funcVal]->id);break;
			case undef_m:	printf("undef\n" ); break;
			case nil_m:		printf("nilllllll\n" );break;
			case table_m:{
				print_tables(stack[i]);
				printf("\n" );
				break;
			}
			default: printf("ekanes malakia %d\n", stack[i].type);
		}
	}
}


void print_tables(struct avm_memcell stack){
	struct avm_table* tmp = stack.data.tableVal;
	while (tmp) {
		if(tmp->index){
			//printf(" index: %s data: ",tmp->index );
			switch(tmp->data->type){
				case number_m:	printf("%.2f,\t",tmp->data->data.numVal ); break;
				case bool_m:    if(tmp->data->data.bool) printf("true,\t"); else printf("false,\t");	break;
				case string_m:	printf("%s,\t",tmp->data->data.strVal );	break;
				case lib_func_m: 	printf("%s,\t",tmp->data->data.libfuncVal ); break;
				case userfunc_m:	printf("%1u,\t",tmp->data->data.funcVal ); break;
				case nil_m:		printf("nil\t" );break;
				case table_m:	print_tables(*tmp->data); break;
			}
		}
		tmp=tmp->next;

	}
}

void add_consts_string(char * str){
		stringConsts[totalStringConsts] = (char*) malloc(sizeof(char) * strlen(str));
		strcpy(stringConsts[totalStringConsts] , str);
		totalStringConsts++;
}

void add_consts_num(double number){
		numConsts[totalNumConsts] = number;
		totalNumConsts++;
}

void add_consts_libfuncs(char * libfunc){
		namedLibfuncs[totalNamedLibfuncs] = malloc(sizeof(char) * strlen(libfunc));
		namedLibfuncs[totalNamedLibfuncs] = strdup(libfunc);
		totalNamedLibfuncs++;

}

void add_consts_userfuncs(char * userfunc,unsigned int address, unsigned int localsize,unsigned int totalargs ){

		struct userfunc* newnode = malloc(sizeof(struct userfunc));
		newnode->address = address;
		newnode->localSize = localsize;
		newnode->totalargs =  totalargs;
		newnode->id = malloc(sizeof(char) * strlen(userfunc));
		strcpy(newnode->id, userfunc);

		userFuncs[totalUserFuncs]  = newnode;
		totalUserFuncs++;
	}

char* enum_toString_opCodes_v(vmopcode sym) {
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
					return "funcstart";
			case 19:
					return "funcend";
			case 20:
					return "tablecreate";
			case 21:
					return "tablegetelem";
			case 22:
					return "table_setelem";
			case 23:
					return "nop_v";
			case 24:
					return "jump";
			default:
					return "not compatible type";

		}
	}
	/*
	void avm_setelem(struct avm_table* table , char* index , struct avm_memcell* data){
		struct avm_table* tmp=table;
		struct avm_memcell* tmpdata=malloc(sizeof(struct avm_memcell));

		memcpy(tmpdata, data, sizeof(struct avm_memcell));
	if(tmpdata->type ==userfunc_m) printf("EEE EIMAI SUNARTHSH me name %s\n", userFuncs[tmpdata->data.funcVal]->id );

	if (table->data->type == undef_m) {
	//	printf("if to prwto table set(%s,%f)\n", index, data->data.numVal);
	//	strcpy(tmp->index ,index);
		//tmp->index = malloc(sizeof(char)*strlen(index)+1);

		tmp->index= index;
		printf("sset elem :( %s)\n", tmp->index );
		//edww
		tmp->data= malloc(sizeof(struct avm_memcell));
	if(tmpdata->type == 1)
			tmp->data->data.strVal= malloc(sizeof(char)*10);
	else if( tmpdata->type == 5)
			tmp->data->data.libfuncVal= malloc(sizeof(char)*10);
	else if( tmpdata->type == 3)
			tmp->data->data.tableVal= malloc(sizeof(struct avm_table));

		tmp->data= tmpdata;

		return;
	}

	while (tmp) {
		if(tmp->index){
			if (strcmp(tmp->index,index)==0) {
				tmp->data= tmpdata;
				return;
			}
	 }
	tmp = tmp->next;
	}
	tmp = malloc(sizeof(struct avm_table));
	//strcpy(tmp->index ,index);
	//tmp->index = malloc(sizeof(char)*strlen(index)+1);
	printf("set elem :( %s)\n", index );
	tmp->index = index;

	//edww
	tmp->data= malloc(sizeof(struct avm_memcell));
	if(tmpdata->type == 1)
		tmp->data->data.strVal= malloc(sizeof(char)*10);
	else if( tmpdata->type == 5)
		tmp->data->data.libfuncVal= malloc(sizeof(char)*10);
	else if( tmpdata->type == 3)
		tmp->data->data.tableVal= malloc(sizeof(struct avm_table));



	tmp->data= tmpdata;
	tmp->next = table->next;
	table->next = tmp;
	}


	*/
