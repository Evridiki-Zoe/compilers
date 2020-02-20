// gia na to trexw kanw:
//  lex comp2.l
//  gcc comp.c lex.yy.c 
//  ./a.out < input.txt

%{ 

int token_count = 0; 
int line_count = 0;

struct alpha_token_t{

	int token_no;
	char* type;
	char* value;
	int line;
	struct alpha_token_t* next;

};
struct alpha_token_t *head = NULL;

struct alpha_token_t* add_alpha_token(int token_num, char* type, char* val, int line){
	struct alpha_token_t* tmp = (struct alpha_token_t *) malloc(sizeof(struct alpha_token_t));
	tmp->token_no = token_num;
	tmp->type = type;
	tmp->value = val;
	tmp->line = line;
	tmp->next=NULL;

//	printf("ADDING TOKEN TO LIST: type:: %s value %s in line %d \n", tmp->type, tmp->value, tmp->line);

	if(head == NULL) head = tmp;
	else{ 
//		printf("going to the end of the list !!!\n");
		struct alpha_token_t* curr = head;
		while(curr->next) curr = curr->next;  //proxwraw mexri to telos th lista
		curr->next = tmp; 
	}
}

struct alpha_token_t* print_list(){
	struct alpha_token_t* tmp = head;

	while( tmp != NULL ){
		printf("%d: #%d   ''%s'' with type:: %s \n", tmp->line, tmp->token_no, tmp->value, tmp->type);
		tmp= tmp->next;
	}

}

%} 
%option yylineno

%%

"if"     { token_count++; add_alpha_token(token_count, "KEYWORD", "IF", yylineno); return 1; }
"hello"  { token_count++; add_alpha_token(token_count, "KEYWORD", "HELLO", yylineno); return 2; }
"haha"   { token_count++; add_alpha_token(token_count, "KEYWORD", "HAHA", yylineno); return 3; }
"printlist" print_list();


\n { }  // MHN TO BGALETE APO DW, EINAI GIA NA YPOLOGIZONTAI SWSTA OI GRAMMES :)

%%


int yywrap(void){

	return 1;

}
