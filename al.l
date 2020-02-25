%{
int token_count = 0;

#define YY_DECL int alpha_yylex(void * yylval)

int print_list();
void add_alpha_token(int token_num, char* type, char* val, int line);

void yywarning(char *text){
    printf("Warning in line %d : %s\n",yylineno,text );
}
void yyerror(char *text){
    printf("Error in line %d : %s\n",yylineno,text );
    exit(0);
}
void commentHandler(int from);

%}


%option noyywrap
%option yylineno


INTEGER				([0-9]*)
FLOAT				(0{1}|([1-9]*))\.[0-9]+
IDENTIFIER    		[a-zA-Z][a-zA-Z0-9_]*
STRING				\"




%%


{STRING}	  			{
    char c;
    char *buff = malloc(16*sizeof(char));
	  long int length = 0;
	  long int baseofre = 16;
    char tmp;

    while ((c = input())) {
		  length++;
		  if (length > baseofre) {
			  baseofre *= 2;
			  buff = realloc(buff, baseofre * sizeof(char));
	  	}
        if (c == '\"') {
            add_alpha_token(++token_count, "STRING", buff, yylineno);
            break;
        }
        if (c == '\n') {
          yywarning("Not Closing string");
        }

        if (c == '\\') {

            char tmp = input();

            if (tmp == 't') {
              strcat(buff, "\t");

            } else if (tmp == 'n') {
              strcat(buff, "\n");

            } else if (tmp == '\\') {
              strcat(buff, "\\");

            } else if (tmp == '\"'){
              strcat(buff, "\"");

            } else {
                printf("warning: unknown escape sequence: '\\%c' in line: %d\n", tmp, yylineno );
                unput(tmp);
            }
        } else   {

            strncat(buff, &c, 1);
        }

    }
}



"//".*                                 	{ add_alpha_token(++token_count, "COMMENT LINE_COMMENT", "", yylineno); }

"/*"         							{commentHandler(yylineno);	}



"if"     	  { add_alpha_token(++token_count, "KEYWORD IF", "if", yylineno); }
"else"     	{ add_alpha_token(++token_count, "KEYWORD ELSE", "else", yylineno); }
"while"    	{ add_alpha_token(++token_count, "KEYWORD WHILE", "while", yylineno); }
"for"     	{ add_alpha_token(++token_count, "KEYWORD FOR", "for", yylineno); }
"function"  { add_alpha_token(++token_count, "KEYWORD FUNCTION", "function", yylineno); }
"return"    { add_alpha_token(++token_count, "KEYWORD RETURN", "return", yylineno); }
"break"    	{ add_alpha_token(++token_count, "KEYWORD BREAK", "break", yylineno); }
"continue"  { add_alpha_token(++token_count, "KEYWORD CONTINUE", "continue", yylineno); }
"and"     	{ add_alpha_token(++token_count, "KEYWORD AND", "and", yylineno); }
"not"     	{ add_alpha_token(++token_count, "KEYWORD NOT", "not", yylineno); }
"or"     	  { add_alpha_token(++token_count, "KEYWORD OR", "or", yylineno); }
"local"    	{ add_alpha_token(++token_count, "KEYWORD LOCAL", "local", yylineno); }
"true"     	{ add_alpha_token(++token_count, "KEYWORD TRUE", "true", yylineno); }
"false"     { add_alpha_token(++token_count, "KEYWORD FALSE", "false", yylineno); }
"nil"     	{ add_alpha_token(++token_count, "KEYWORD NIL", "nil", yylineno); }

"="     	{ add_alpha_token(++token_count, "OPERATOR EQUALS", "=", yylineno); }
"+"     	{ add_alpha_token(++token_count, "OPERATOR PLUS", "+", yylineno); }
"-"     	{ add_alpha_token(++token_count, "OPERATOR MINUS", "-", yylineno); }
"*"     	{ add_alpha_token(++token_count, "OPERATOR EPI", "*", yylineno); }
"/"     	{ add_alpha_token(++token_count, "OPERATOR DIVISION", "/", yylineno); }
"%"     	{ add_alpha_token(++token_count, "OPERATOR MOD", "%", yylineno); }
"=="     	{ add_alpha_token(++token_count, "OPERATOR EQUALS_EQUALS", "==", yylineno); }
"!="     	{ add_alpha_token(++token_count, "OPERATOR NOT_EQUALS", "!=", yylineno); }
"++"     	{ add_alpha_token(++token_count, "OPERATOR PLUS_PLUS", "++", yylineno); }
"--"     	{ add_alpha_token(++token_count, "OPERATOR MINUS_MINUS", "--", yylineno); }
">"     	{ add_alpha_token(++token_count, "OPERATOR BIGGER_THAN", ">", yylineno); }
"<"     	{ add_alpha_token(++token_count, "OPERATOR SMALLER_THAN", "<", yylineno); }
">="     	{ add_alpha_token(++token_count, "OPERATOR BIGGER_EQ_THAN", ">=", yylineno); }
"<="     	{ add_alpha_token(++token_count, "OPERATOR SMALLER_EQ_THAN", "<=", yylineno); }

";"     	{ add_alpha_token(++token_count, "PUNCTUATION SEMICOLON", ";", yylineno); }
","     	{ add_alpha_token(++token_count, "PUNCTUATION COMMA", ",", yylineno); }
":"    		{ add_alpha_token(++token_count, "PUNCTUATION UPDOWN DOTS", ":", yylineno); }
"::"     	{ add_alpha_token(++token_count, "PUNCTUATION DOUBUPDOWN DOTS", "::", yylineno); }
"."     	{ add_alpha_token(++token_count, "PUNCTUATION END DOT", ".", yylineno); }
".."     	{ add_alpha_token(++token_count, "PUNCTUATION DOUBLE_END DOTS", "..", yylineno); }
"{"     	{ add_alpha_token(++token_count, "PUNCTUATION LEFT BRACE", "{", yylineno); }
"}"     	{ add_alpha_token(++token_count, "PUNCTUATION RIGHT BRACE", "}", yylineno); }
"["     	{ add_alpha_token(++token_count, "PUNCTUATION RIGHT BRACKET", "[", yylineno); }
"]"     	{ add_alpha_token(++token_count, "PUNCTUATION LEFT BRACKET", "]", yylineno); }
"("     	{ add_alpha_token(++token_count, "PUNCTUATION LEFT PARENTHESIS", "(", yylineno); }
")"     	{ add_alpha_token(++token_count, "PUNCTUATION RIGHT PARENTHESIS", ")", yylineno); }


{FLOAT}			  { add_alpha_token(++token_count, "FLOAT", yytext, yylineno);}
{INTEGER} 		{ add_alpha_token(++token_count, "INTEGER", yytext, yylineno);}
{IDENTIFIER} 	{ add_alpha_token(++token_count, "IDENTIFIER", yytext, yylineno);}

[ ]+      { }
. 				yywarning("Undefined character");
\n				{ }

%%
void commentHandler(int from){

	static int nested=0;
	char c;
	while ((c = input())) {

		if (c == '*' ) {

			c = input();
			if ( c == '/') {

				if (nested==0) {
					printf("ORIGINAL COMMENT from %d , to %d\n",from , yylineno );

					break;
				}else {
					printf("NESTED COMMENT from %d , to %d\n",from , yylineno );

					nested--;
					break;
				}

			}else unput(c);

		}

		if ( c == '/') {
			c = input();

			if (c == '*') {
				nested++;
				commentHandler(yylineno);
			}else	unput(c);

		}


	}
}

//MAIN
