#include <stdio.h>

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int token_count;
extern int line_count;

int main(){
	int ntoken;
	ntoken = yylex();
//	printf("lala token:: %d \n", ntoken);
	while( ntoken ){
//		printf("line: #%d found %s count:: %d \n", yylineno, yytext, token_count);
		ntoken = yylex();
	}


	return 0;
}
