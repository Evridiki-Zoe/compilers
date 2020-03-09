#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct alpha_token_t * alpha_yylex();
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern int token_count;

struct alpha_token_t {
	unsigned int 			line;
	unsigned int 			token_no;
	char 					*value;
	char 					*type;
	struct alpha_token_t 	*next;
};

struct alpha_token_t *head = NULL;

struct alpha_token_t* add_alpha_token(int token_num, char* type, char* val, int line) {
	struct alpha_token_t *tmp = (struct alpha_token_t *) malloc(sizeof(struct alpha_token_t));
	tmp->token_no = token_num;
	tmp->type = type;
	tmp->value = strdup(val);
	tmp->line = line;
	tmp->next = NULL;

	if(head == NULL) head = tmp;
	else {
//		printf("going to the end of the list !!!\n");
		struct alpha_token_t* curr = head;
		while(curr->next) curr = curr->next;  //proxwraw mexri to telos th lista
		curr->next = tmp;
	}

	return tmp;
}

int print_list() {
	struct alpha_token_t* tmp = head;

	printf("---------------- TOKENS ----------------\n#Line  #Token  Value  	   Type\n");
	while( tmp != NULL ){
		if(strcmp(tmp->type,"FLOAT") == 0 || strcmp(tmp->type,"INTEGER") == 0 || strcmp(tmp->type, "IDENTIFIER") == 0) {
			printf("%d:     #%d      \"%s\"	   %s %s\n", tmp->line, tmp->token_no, tmp->value, tmp->type, tmp->value);
		} else if(strcmp(tmp->type,"STRING") == 0) {
			printf("%d:     #%d      \"%s\"	   %s %s\n", tmp->line, tmp->token_no, tmp->value, tmp->type, tmp->value);
		} else {
			printf("%d:     #%d      \"%s\"	   %s\n", tmp->line, tmp->token_no, tmp->value, tmp->type);
		}
		tmp= tmp->next;
	}
	return 0;
}


int main(void) {
printf("oh hi there\n");
return yyparse();
}
/*int main(int argc, char *argv[]) {
	FILE *file;

	if(argc > 1) {
		if(!(file = fopen(argv[1], "r"))) {
			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
		} else {
			yyin = file;
		}
		//alpha_yylex(NULL);
		struct alpha_token_t* ntoken = alpha_yylex(NULL);
	        while( ntoken ){
//			printf("INT TOKEN %d \n", ntoken);
			printf("MAAAAAAINN %d:     #%d      \"%s\"    %s\n", ntoken->line, ntoken->token_no, ntoken->value, ntoken->type);
        	        ntoken = alpha_yylex(NULL);
	        }


		print_list();
		fclose(file);
	} else {

		yyin = stdin;
		alpha_yylex(NULL);
	}

	return 0;
}
*/

