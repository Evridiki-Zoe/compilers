#include "quads.h"
#include "parsing.h"
#include "lex.h"
#include "targetCode.h"

extern double QuadNo;


void generate_ADD (struct quad *quad){}
void generate_SUB (struct quad *quad){}
void generate_MUL (struct quad *quad){}
void generate_DIV (struct quad *quad){}
void generate_MOD (struct quad *quad){}
void generate_NEWTABLE (struct quad *quad){}
void generate_TABLEGETELM (struct quad *quad){}
void generate_TABLESETELEM(struct quad *quad){}
void generate_ASSIGN (struct quad *quad){}
void generate_NOP (struct quad *quad){}
void generate_JUMP(struct quad *quad){}
void generate_IF_EQ(struct quad *quad){}
void generate_IF_NOTEQ(struct quad *quad){}
void generate_IF_GREATER(struct quad *quad){}
void generate_IF_GREATEREQ(struct quad *quad){}
void generate_IF_LESS(struct quad *quad){}
void generate_IF_LESSEQ(struct quad *quad){}
void generate_NOT(struct quad *quad){}
void generate_OR(struct quad *quad){}
void generate_PARAM(struct quad *quad){}
void generate_CALL(struct quad *quad){}
void generate_GETRETVAL(struct quad *quad){}
void generate_FUNCSTART(struct quad *quad){}
void generate_RETURN(struct quad *quad){}
void generate_FUNCEND(struct quad *quad){}


typedef void (*generator_func_t) (struct quad*);

generator_func_t generators[] = {

	generate_ASSIGN,
	generate_ADD,
	generate_SUB,
	generate_MUL,
	generate_DIV,
	generate_MOD,
	generate_JUMP,
	generate_IF_EQ,
	generate_IF_NOTEQ,
	generate_IF_LESSEQ,
	generate_IF_GREATEREQ,
	generate_IF_LESS,
	generate_IF_GREATER,
	generate_CALL,
	generate_PARAM,
	generate_FUNCSTART,
	generate_FUNCEND,
	generate_NEWTABLE,
	generate_TABLEGETELM,
	generate_TABLESETELEM,
	generate_GETRETVAL,
	generate_NOP,
	generate_RETURN,

};


void generate(void){

	for (size_t i = 0; i < QuadNo; i++) {
		/* code */
	}


}
