#include "quads.h"
#include "parsing.h"
#include "lex.h"
#include "targetCode.h"

extern double QuadNo;
unsigned instrNo=0;

void generate_ADD (struct quad *quad)			{generate(add_v,quad);}
void generate_SUB (struct quad *quad)			{generate(sub_v,quad);}
void generate_MUL (struct quad *quad)			{generate(mul_v,quad);}
void generate_DIV (struct quad *quad)			{generate(div_v,quad);}
void generate_MOD (struct quad *quad)			{generate(mod_v,quad);}
void generate_NEWTABLE (struct quad *quad)		{generate(newtable_v,quad);}
void generate_TABLEGETELM (struct quad *quad)	{generate(tablegetelem_v,quad);}
void generate_TABLESETELEM(struct quad *quad)	{generate(tablesetelem_v,quad);}
void generate_ASSIGN (struct quad *quad)		{generate(assign_v,quad);}
void generate_NOP (struct quad *quad)			{struct instruction *t=malloc(sizeof(struct instruction)); t->opcode=nop_v;emitIns(t);}// dunno ti rolo varaei
void generate_JUMP(struct quad *quad)			{}//TODO generate jump
void generate_IF_EQ(struct quad *quad)			{generate(jeq_v,quad);}
void generate_IF_NOTEQ(struct quad *quad)		{generate(jne_v,quad);}
void generate_IF_GREATER(struct quad *quad)		{generate(jgt_v,quad);}
void generate_IF_GREATEREQ(struct quad *quad)	{generate(jge_v,quad);}//Ta leei allios alla nomizo tha imaste komple
void generate_IF_LESS(struct quad *quad)		{generate(jlt_v,quad);}
void generate_IF_LESSEQ(struct quad *quad)		{generate(jle_v,quad);}
void generate_PARAM(struct quad *quad)			{}//TODO
void generate_CALL(struct quad *quad)			{}//TODO
void generate_GETRETVAL(struct quad *quad)		{}//TODO
void generate_FUNCSTART(struct quad *quad)		{}//TODO
void generate_RETURN(struct quad *quad)			{}//TODO
void generate_FUNCEND(struct quad *quad)		{}//TODO
void generate_UMINUS(struct quad *quad)			{}//TODO


void generate_AND(struct quad *quad){} 		//Den tha ta xreiastoume afta
void generate_OR(struct quad *quad){}
void generate_NOT(struct quad *quad){}
void generate_RET(struct quad *quad){}



typedef void (*generator_func_t) (struct quad*);

generator_func_t generators[] = {

	generate_ASSIGN,
	generate_ADD,
	generate_SUB,
	generate_MUL,
	generate_DIV,
	generate_MOD,
	generate_UMINUS,
	generate_AND,
	generate_OR,
	generate_NOT,
	generate_IF_EQ,
	generate_IF_NOTEQ,
	generate_IF_LESSEQ,
	generate_IF_GREATEREQ,
	generate_IF_LESS,
	generate_IF_GREATER,
	generate_CALL,
	generate_PARAM,
	generate_RET,
	generate_GETRETVAL,
	generate_FUNCSTART,
	generate_FUNCEND,
	generate_NEWTABLE,
	generate_TABLEGETELM,
	generate_TABLESETELEM,
	generate_JUMP,

};

void printInstructions(){
	int i;
	for (i = 0; i < instrNo; i++) {
		printf("%d)",i+1 );
		printf("result : (%d,%u)\t",instructions[i].result->type,instructions[i].result->val );
		printf("arg1 : (%d,%u)\t",instructions[i].arg1->type,instructions[i].arg1->val );
		printf("arg2 : (%d,%u)\n",instructions[i].arg2->type,instructions[i].arg2->val );
	}
}


void generateIns(void){

	int i;

	instructions= (struct instruction*)malloc(QuadNo * sizeof(struct instruction) );
	for ( i = 0; i < QuadNo; i++) {
		(*generators[quads[i].opcode])(quads+i);

	}


}

void generate(vmopcode code , struct quad* quad){

	struct instruction* tmpins=malloc(sizeof(struct instruction));;
	tmpins->opcode=code;
	tmpins->arg1=make_operand(quad->arg1);

	tmpins->arg2=make_operand(quad->arg2);
	tmpins->result=make_operand(quad->res);
	tmpins->srcLine=quad->line;
	// TODO den ksero ti thelei na pei o poiitis sot -> quad.taddress=nexcf/...

	emitIns(tmpins);
}


void emitIns(struct instruction* ins){

	instructions[instrNo].opcode=ins->opcode;
	instructions[instrNo].result=ins->result;
	instructions[instrNo].arg1=ins->arg1;
	instructions[instrNo].arg2=ins->arg2;
	instructions[instrNo].srcLine=ins->srcLine;
	instrNo++;
}

struct vmarg* make_operand(struct expr* expr){

	 	struct vmarg* arg= malloc(sizeof(struct vmarg));
//	printf(" type of %s  is %d \n" , expr->sym->value.var->name , expr->type );
	switch (expr->type) {
		case var_e:
		case tableitem_e:
		case arithmeticexp_e:
		case boolexp_e:
		case newtable_e: {
			arg->val=expr->sym->value.var->offset;
			switch (expr->sym->scope_space) {
				case program_var : 	arg->type=global_a;	break;
				case function_loc : arg->type=local_a;	break;
				case formal_arg : 	arg->type=formal_a;	break;
				default :	assert(0);
			}
			break;

		}
		case constbool_e: {
			arg->val= expr->boolconst;
			arg->type=bool_a;	break;
		}
		case conststring_e : {
		//	arg->val = create new string in the table TODO
			arg->type=string_a;	break;
		}
		case const_num_e : {
			//arg->val= new number in table TODO
			arg->type= number_a; break;
		}
		case nil_e : arg->type=nil_a; break;

		case programfunc_e : {
			arg->type = userfunc_a;
			arg->val = expr->sym->value.func->funcAddress;
			break;
		}
		case libfunc_e : {
			arg->type= libfunc_a;
			//arg->val = //TODO
			break;

		}
		default : assert(0);

	}

	return arg;

}

void add_rval_string(char * str){
			if(totalStringConsts == 50 );// TODO realloc pinaka, oxi 50 thelei global maxsize gia to kathena

			stringConsts[totalStringConsts] = (char*) malloc(sizeof(char) * strlen(str));
			strcpy(stringConsts[totalStringConsts] , str);
			printf("%s\n", stringConsts[totalStringConsts] );
			totalStringConsts++;
}

void add_rval_num(double number){ // xanei pshfia meta to 6o
	if(totalNumConsts == 100 );// TODO realloc pinaka

	numConsts[totalNumConsts] = number;
	printf("%f\n", numConsts[totalNumConsts] );
	totalNumConsts++;

}

void add_rval_libfuncs(char * libfunc){
	if(totalNamedLibfuncs == 50 );// TODO realloc pinaka

	namedLibfuncs[totalNamedLibfuncs] = (char*) malloc(sizeof(char) * strlen(libfunc));
	strcpy(namedLibfuncs[totalNamedLibfuncs] , libfunc);
	printf("%s\n", namedLibfuncs[totalNamedLibfuncs] );
	totalNamedLibfuncs++;

}

void add_rval_userfuncs(char * userfunc,unsigned int address, unsigned int localsize,unsigned int totalargs ){

	if(totalUserFuncs == 50 );// TODO realloc pinaka

	struct userfunc* newnode = malloc(sizeof(struct userfunc));
	newnode->address = address;
	newnode->localSize = localsize;
	newnode->totalargs =  totalargs;
	newnode->id = malloc(sizeof(char) * strlen(userfunc));
	strcpy(newnode->id, userfunc);

	userFuncs[totalUserFuncs]  = newnode;
	printf("%s\n", userFuncs[totalUserFuncs] ->id );
	totalUserFuncs++;
}
