%{ 

int token_count = 0; 

#define YY_DECL int alpha_yylex(void * yylval)

struct alpha_token_t{

	int token_no;
	char* type;
	char* value;
	int line;
	struct alpha_token_t* next;

};

struct alpha_token_t *head = NULL;

struct alpha_token_t* add_alpha_token(int token_num, char* type, char* val, int line){
	struct alpha_token_t *tmp = (struct alpha_token_t *) malloc(sizeof(struct alpha_token_t));
	tmp->token_no = token_num;
	tmp->type = type;
	tmp->value = val;
	tmp->line = line;
	tmp->next=NULL;

//	printf("ADDING TOKEN TO LIST: type:: %s value %s in line %d \n", tmp->type, tmp->value, tmp->line);

	if(head == NULL) head = tmp;
	else { 
//		printf("going to the end of the list !!!\n");
		struct alpha_token_t* curr = head;
		while(curr->next) curr = curr->next;  //proxwraw mexri to telos th lista
		curr->next = tmp; 
	}
}

struct alpha_token_t* print_list(){
	struct alpha_token_t* tmp = head;
	printf("---------------- TOKENS ----------------\n");
	while( tmp != NULL ){
		printf("%d: #%d  \"%s\"	 type: %s \n", tmp->line, tmp->token_no, tmp->value, tmp->type);
		tmp= tmp->next;
	}
}

%} 

%option noyywrap
%option yylineno

%%

"if"     	{ token_count++; add_alpha_token(token_count, "KEYWORD", "IF", yylineno); }
"hello"  	{ token_count++; add_alpha_token(token_count, "KEYWORD", "HELLO", yylineno); }
"haha"   	{ token_count++; add_alpha_token(token_count, "KEYWORD", "HAHA", yylineno); }
. 			printf("Uknown character: %s at: %d\n", yytext, yylineno);

\n { }  // MHN TO BGALETE APO DW, EINAI GIA NA YPOLOGIZONTAI SWSTA OI GRAMMES :)

%%

int main(int argc, char *argv[]) {
	FILE *file;

	if(argc > 1) {
		if(!(file = fopen(argv[1], "r"))) {
			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
		} else {
			yyin = file;
		}
	}

	alpha_yylex(NULL);
	print_list();
	return 0;
}