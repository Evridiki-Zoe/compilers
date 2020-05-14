#include "quads.h"
#include "parsing.h"
#include "lex.h"
#include "targetCode.h"

extern double QuadNo;


void generate_ADD (struct quad *quad){printf("add\n" ); }
void generate_SUB (struct quad *quad){printf("sub\n" );}
void generate_MUL (struct quad *quad){printf("mul\n" );}
void generate_DIV (struct quad *quad){printf("div\n" );}
void generate_MOD (struct quad *quad){printf("mod\n" );}
void generate_NEWTABLE (struct quad *quad){printf("generate_NEWTABLE\n" );}
void generate_TABLEGETELM (struct quad *quad){printf("generate_TABLEGETELM\n" );}
void generate_TABLESETELEM(struct quad *quad){printf("generate_TABLESETELEM\n" );}
void generate_ASSIGN (struct quad *quad){printf("generate_ASSIGN\n" );}
void generate_NOP (struct quad *quad){printf("generate_NOP\n" );}
void generate_JUMP(struct quad *quad){printf("generate_JUMP\n" );}
void generate_IF_EQ(struct quad *quad){printf("generate_IF_EQ\n" );}
void generate_IF_NOTEQ(struct quad *quad){printf("generate_IF_NOTEQ\n" );}
void generate_IF_GREATER(struct quad *quad){printf("generate_IF_GREATER\n" );}
void generate_IF_GREATEREQ(struct quad *quad){printf("generate_IF_GREATEREQ\n" );}
void generate_IF_LESS(struct quad *quad){printf("generate_IF_LESS\n" );}
void generate_IF_LESSEQ(struct quad *quad){printf("generate_IF_LESSEQ\n" );}
void generate_PARAM(struct quad *quad){printf("generate_PARAM\n" );}
void generate_CALL(struct quad *quad){ printf("generate_CALL\n" );}
void generate_GETRETVAL(struct quad *quad){printf("generate_GETRETVAL\n" );}
void generate_FUNCSTART(struct quad *quad){printf("generate_FUNCSTART\n" );}
void generate_RETURN(struct quad *quad){printf("generate_RETURN\n" );}
void generate_FUNCEND(struct quad *quad){printf("generate_FUNCEND\n" );}
void generate_UMINUS(struct quad *quad){printf("generate_UMINUS\n" );}
void generate_AND(struct quad *quad){printf("generate_AND\n" );}
void generate_OR(struct quad *quad){printf("generate_OR\n" );}
void generate_NOT(struct quad *quad){printf("generate_NOT\n" );}
void generate_RET(struct quad *quad){printf("generate_RET\n" );}


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


void generate(void){
	int i;
	for ( i = 0; i < QuadNo; i++) {
	printf("%d)",i+1 );
		(*generators[quads[i].opcode])(quads+1);
	}


}
