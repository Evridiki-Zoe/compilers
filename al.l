%{
char* buffstr;
int token_count = 0;

#define YY_DECL int alpha_yylex(void * yylval)

struct alpha_token_t{
	unsigned int 			line;
	unsigned int 			token_no;
	char 					*type;
	char 					*value;
	struct alpha_token_t 	*next;
};

struct alpha_token_t *head = NULL;

void add_alpha_token(int token_num, char* type, char* val, int line){
	struct alpha_token_t *tmp = (struct alpha_token_t *) malloc(sizeof(struct alpha_token_t));
	tmp->token_no = token_num;
	tmp->type = type;
	tmp->value = strdup(val);
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
	printf("---------------- TOKENS ----------------\n#Line  #Token Value  	Type\n");
	while( tmp != NULL ){
		printf("%d:     #%d     \"%s\"	%s \n", tmp->line, tmp->token_no, tmp->value, tmp->type);
		tmp= tmp->next;
	}
}

<<<<<<< HEAD
%} 

STRING 	\"(([^\"]|\\\")*[^\\])?\"
=======
%}
%x String
>>>>>>> 23b94c36c52161f865d98844be181565d8b7241c
%option noyywrap
%option yylineno

INTEGER				([1-9][0-9]*)
FLOAT					(0{1}|([1-9]*))\.[0-9]+
IDENTIFIER    [a-zA-Z][a-zA-Z0-9]*
STRING				(\".\")


%%

<<<<<<< HEAD
"if"     	{ token_count++; add_alpha_token(token_count, "KEYWORD IF", "if", yylineno); }
=======



"if"     		{ token_count++; add_alpha_token(token_count, "KEYWORD IF", "if", yylineno); }
>>>>>>> 23b94c36c52161f865d98844be181565d8b7241c
"else"     	{ token_count++; add_alpha_token(token_count, "KEYWORD ELSE", "else", yylineno); }
"while"    	{ token_count++; add_alpha_token(token_count, "KEYWORD WHILE", "while", yylineno); }
"for"     	{ token_count++; add_alpha_token(token_count, "KEYWORD FOR", "for", yylineno); }
"function"  { token_count++; add_alpha_token(token_count, "KEYWORD FUNCTION", "function", yylineno); }
"return"    { token_count++; add_alpha_token(token_count, "KEYWORD RETURN", "return", yylineno); }
"break"    	{ token_count++; add_alpha_token(token_count, "KEYWORD BREAK", "break", yylineno); }
"continue"  { token_count++; add_alpha_token(token_count, "KEYWORD CONTINUE", "continue", yylineno); }
"and"     	{ token_count++; add_alpha_token(token_count, "KEYWORD AND", "and", yylineno); }
"not"     	{ token_count++; add_alpha_token(token_count, "KEYWORD NOT", "not", yylineno); }
"or"     		{ token_count++; add_alpha_token(token_count, "KEYWORD OR", "or", yylineno); }
"local"    	{ token_count++; add_alpha_token(token_count, "KEYWORD LOCAL", "local", yylineno); }
"true"     	{ token_count++; add_alpha_token(token_count, "KEYWORD TRUE", "true", yylineno); }
"false"     { token_count++; add_alpha_token(token_count, "KEYWORD FALSE", "false", yylineno); }
"nil"     	{ token_count++; add_alpha_token(token_count, "KEYWORD NIL", "nil", yylineno); }

<<<<<<< HEAD
=======

>>>>>>> 23b94c36c52161f865d98844be181565d8b7241c
"="     	{ token_count++; add_alpha_token(token_count, "OPERATOR EQUALS", "=", yylineno); }
"+"     	{ token_count++; add_alpha_token(token_count, "OPERATOR PLUS", "+", yylineno); }
"-"     	{ token_count++; add_alpha_token(token_count, "OPERATOR MINUS", "-", yylineno); }
"*"     	{ token_count++; add_alpha_token(token_count, "OPERATOR EPI", "*", yylineno); }
"/"     	{ token_count++; add_alpha_token(token_count, "OPERATOR DIVISION", "/", yylineno); }
"%"     	{ token_count++; add_alpha_token(token_count, "OPERATOR MOD", "%", yylineno); }
"=="     	{ token_count++; add_alpha_token(token_count, "OPERATOR EQUALS_EQUALS", "==", yylineno); }
"!="     	{ token_count++; add_alpha_token(token_count, "OPERATOR NOT_EQUALS", "!=", yylineno); }
"++"     	{ token_count++; add_alpha_token(token_count, "OPERATOR PLUS_PLUS", "++", yylineno); }
"--"     	{ token_count++; add_alpha_token(token_count, "OPERATOR MINUS_MINUS", "--", yylineno); }
">"     	{ token_count++; add_alpha_token(token_count, "OPERATOR BIGGER_THAN", ">", yylineno); }
"<"     	{ token_count++; add_alpha_token(token_count, "OPERATOR SMALLER_THAN", "<", yylineno); }
">="     	{ token_count++; add_alpha_token(token_count, "OPERATOR BIGGER_EQ_THAN", ">=", yylineno); }
"<="     	{ token_count++; add_alpha_token(token_count, "OPERATOR SMALLER_EQ_THAN", "<=", yylineno); }

"{"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION LEFT BRACE", "{", yylineno); }
"}"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION RIGHT BRACE", "}", yylineno); }
"["     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION RIGHT BRACKET", "[", yylineno); }
"]"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION LEFT BRACKET", "]", yylineno); }
"("     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION LEFT PARENTHESIS", "(", yylineno); }
")"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION RIGHT PARENTHESIS", ")", yylineno); }
";"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION SEMICOLON", ";", yylineno); }
","     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION COMMA", ",", yylineno); }
":"    		{ token_count++; add_alpha_token(token_count, "PUNCTUATION UPDOWN DOTS", ")", yylineno); }
"::"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION DOUBUPDOWN DOTS", ")", yylineno); }
"."     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION END DOT", ")", yylineno); }
".."     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION DOUBLE_END DOTS", ")", yylineno); }

{STRING} 	printf("%s\n", yytext);
 

<<<<<<< HEAD
=======
"hello"  	{ token_count++; add_alpha_token(token_count, "KEYWORD", "HELLO", yylineno); }
"haha"   	{ token_count++; add_alpha_token(token_count, "KEYWORD", "HAHA", yylineno); }


{FLOAT}				{	token_count++; add_alpha_token(token_count, "FLOAT", yytext, yylineno);}
{INTEGER} 		{	token_count++; add_alpha_token(token_count, "INTEGER", yytext, yylineno);}
{IDENTIFIER} 	{	token_count++; add_alpha_token(token_count, "IDENTIFIER", yytext, yylineno);}
{STRING}			{	token_count++; add_alpha_token(token_count, "STRING", yytext, yylineno);}



>>>>>>> 23b94c36c52161f865d98844be181565d8b7241c
. 			printf("Uknown character: %s at: %d\n", yytext, yylineno);


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
	fclose(file);
	return 0;
}
