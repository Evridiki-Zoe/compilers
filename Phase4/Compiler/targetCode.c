#include "quads.h"
#include "parsing.h"
#include "lex.h"
#include "targetCode.h"

extern double QuadNo;
unsigned instrNo=0;
unsigned prossessquad=0;
int maxsize_num = 50;
int maxsize_str = 50;
int maxsize_libfunc = 50;
int maxsize_userfunc = 50;

unsigned	totalNumConsts=0; //total number of  numbers
unsigned	totalStringConsts=0; //total number of strings
unsigned	totalNamedLibfuncs=0;
unsigned	totalUserFuncs=0;


struct incomplete_jump* ij_head=NULL;
unsigned ij_total;

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
void generate_JUMP(struct quad *quad)			{generate_relational(jump_v,quad);}
void generate_IF_EQ(struct quad *quad)			{generate_relational(jeq_v,quad);}	// thelei ta relational giati petaei segm
void generate_IF_NOTEQ(struct quad *quad)		{generate_relational(jne_v,quad);}
void generate_IF_GREATER(struct quad *quad)		{generate_relational(jgt_v,quad);}
void generate_IF_GREATEREQ(struct quad *quad)	{generate_relational(jge_v,quad);}//Ta leei allios alla nomizo tha imaste komple
void generate_IF_LESS(struct quad *quad)		{generate_relational(jlt_v,quad);}
void generate_IF_LESSEQ(struct quad *quad)		{generate_relational(jle_v,quad);}
void generate_PARAM(struct quad *quad) {
		//quad->taddress = 	instrNo; // TODO
  	struct instruction* t;
		t->opcode = pusharg_v;
		t->arg1 = make_operand(quad->arg1);
	  emitIns(t);
}

void generate_CALL(struct quad *quad) {
		//quad->taddress = 	instrNo; // TODO
		struct instruction* t;
		t->opcode =  call_v;
		t->arg1 = make_operand(quad->arg1);
		emitIns(t);
}

void generate_GETRETVAL(struct quad *quad) {
  	//quad->taddress = 	instrNo; // TODO
		struct instruction* t;
		t->opcode = assign_v;
		t->result = make_operand(quad->res);
		//make_retvaloperand(&t->arg1);
		emitIns(t);
}

void generate_FUNCSTART(struct quad *quad)		{}//TODO
void generate_RETURN(struct quad *quad)			{}//TODO
void generate_FUNCEND(struct quad *quad)		{}//TODO
void generate_UMINUS(struct quad *quad)			{ generate(mul_v,quad);}	// todo peiragmeno quad ????


void generate_AND(struct quad *quad){ return ;} 		//Den tha ta xreiastoume afta
void generate_OR(struct quad *quad){ return ;}
void generate_NOT(struct quad *quad){ return ;}
void generate_RET(struct quad *quad){ return ;}




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
		printf("%d) type: %d ",i+1, instructions[i].opcode);
		if (instructions[i].result!=NULL) {
			printf("result : (%d,%u)\t",instructions[i].result->type,instructions[i].result->val );
		}

		if (instructions[i].arg1!=NULL) {
			printf("arg1 : (%d,%u)\t",instructions[i].arg1->type,instructions[i].arg1->val );
		}
		if (instructions[i].arg2!=NULL) {
			printf("arg2 : (%d,%u)\t",instructions[i].arg2->type,instructions[i].arg2->val );
		}
		printf("\n" );
	}
}


void generateIns(void){

	int i;

	instructions= (struct instruction*)malloc(QuadNo * sizeof(struct instruction) );
	for ( i = 0; i < QuadNo; i++) {
		(*generators[quads[i].opcode])(quads + i);
		prossessquad++;
	}

	//theloume patch ta incomplete jumps giati exoume segm

}


void add_incomplete_jump(unsigned instrNo,unsigned iaddress){
	if (ij_head==NULL) {
		ij_head=malloc(sizeof(struct incomplete_jump));
		ij_head->instrNo=instrNo;
		ij_head->iadress=iaddress;
		return;
	}

	struct incomplete_jump* tmp=ij_head;
	while (tmp->next!=NULL) {
		tmp=tmp->next;
	}
	tmp->next=malloc(sizeof(struct incomplete_jump));
	tmp->instrNo=instrNo;
	tmp->iadress=iaddress;
	return;
}

void generate_relational(vmopcode code , struct quad* quad){

	struct instruction* t=malloc(sizeof(struct instruction));
	t->opcode=code;


	if (quad->arg1!=NULL) {
	t->arg1=make_operand(quad->arg1);
	printf("geiaa\n" );
	}

	if (quad->arg2!=NULL) {
		t->arg2=make_operand(quad->arg2);
			printf("geiaa\n" );
	}

	t->result=malloc(sizeof(struct vmarg));
	t->result->type=label_a;

	if (quad->label<prossessquad) {
		t->result->val=quads[quad->label].taddress;
	} else {
		add_incomplete_jump(instrNo,quad->label);
	}

	quad->taddress=instrNo;
	emitIns(t);


}


void generate(vmopcode code , struct quad* quad){

	struct instruction* tmpins=malloc(sizeof(struct instruction));
	tmpins->opcode=code;

	if (quad->arg1!=NULL) {
		tmpins->arg1=make_operand(quad->arg1);
	}

	if (quad->arg2!=NULL) {
		tmpins->arg2=make_operand(quad->arg2);

	if (quad->res!=NULL) {
	tmpins->result=make_operand(quad->res);
	}
	
	tmpins->srcLine=quad->line;
	quad->taddress=instrNo;
	emitIns(tmpins);
}

//void generate_relational()  afou exoume meriki tha xreiastei gia kapoia jumps (ypothetw)

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
	//printf(" type of %s  is %d \n" , expr->sym->value.var->name , expr->type );
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
   		arg->val = add_rval_string(expr->strconst);

			arg->type=string_a;	break;
		}
		case const_num_e : {
			arg->val= add_rval_num(expr->numconst);
			arg->type= number_a; break;
		}
		case nil_e : arg->type=nil_a; break;

		case programfunc_e : {
			arg->type = userfunc_a;
			arg->val = add_rval_userfuncs(expr->sym->value.func->name,instrNo,50,expr->sym->value.func->totalVars);
			break;
		}
		case libfunc_e : {
			arg->type= libfunc_a;
			arg->val = add_rval_libfuncs(expr->sym->value.func->name);
			break;

		}
		default : assert(0);

	}

	return arg;
}

unsigned add_rval_string(char * str){
			if(totalStringConsts == maxsize_str ){
					maxsize_str = maxsize_str * 2;
					stringConsts = (char**) realloc(stringConsts, maxsize_str * sizeof(char *));
			}
			stringConsts[totalStringConsts] = (char*) malloc(sizeof(char) * strlen(str));
			strcpy(stringConsts[totalStringConsts] , str);
			printf("string: %s\n", stringConsts[totalStringConsts] );
			return totalStringConsts++;
}

unsigned add_rval_num(double number){ // xanei pshfia meta to 6o
	if(totalNumConsts == maxsize_num ){

			maxsize_num = maxsize_num * 2;
			numConsts = (double *)	realloc(numConsts, maxsize_num * sizeof(double));
	}

	numConsts[totalNumConsts] = number;
	printf("num: %f\n", number );	//to epsaksa giati typwnei mono 6 psifia. Auto einai to default tou %f
	// alla an to allakseis den ksereis posa psifia exeis esy kai mporei na typwnei midenika
	return totalNumConsts++;

}

/* Isws xreiazetai na tsekaroume an yparxei idi mesa, etsi den tha vazoume kopies tis idias func */
unsigned add_rval_libfuncs(char * libfunc){

	if(totalNamedLibfuncs == maxsize_libfunc ){
		maxsize_libfunc = maxsize_libfunc * 2;
		namedLibfuncs = (char**) realloc(namedLibfuncs, maxsize_libfunc * sizeof(char *));
	}

	namedLibfuncs[totalNamedLibfuncs] = (char*) malloc(sizeof(char) * strlen(libfunc));
	strcpy(namedLibfuncs[totalNamedLibfuncs] , libfunc);
	printf("libfunc: %s\n", namedLibfuncs[totalNamedLibfuncs] );
	return totalNamedLibfuncs++;
}

/* Isws xreiazetai check to onoma gia kopia */
unsigned add_rval_userfuncs(char * userfunc,unsigned int address, unsigned int localsize,unsigned int totalargs ){

	if(totalUserFuncs == maxsize_userfunc ){

		maxsize_userfunc = maxsize_userfunc * 2;
		userFuncs = (struct userfunc**)realloc(userFuncs, maxsize_userfunc * sizeof(struct userfunc*) );

	}

	struct userfunc* newnode = malloc(sizeof(struct userfunc));
	newnode->address = address;
	newnode->localSize = localsize;
	newnode->totalargs =  totalargs;
	newnode->id = malloc(sizeof(char) * strlen(userfunc));
	strcpy(newnode->id, userfunc);

	userFuncs[totalUserFuncs]  = newnode;
	printf("userfunc: %s\n", userFuncs[totalUserFuncs] ->id );
	return totalUserFuncs++;
}



/* Einai stis dialekseis, den kserw pou tha xreiastoun */
void make_booloperand(struct vmarg *arg, unsigned val) {
	arg->val = val;
	arg->type = bool_a;
}

void make_numberoperand(struct vmarg *arg, double val) {
	arg->val = add_rval_num(val);
	arg->type = number_a;
}

void make_revaloperand(struct vmarg *arg) {
	arg->type = retval_a;
}
