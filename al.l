%{
int token_count = 0;

#define YY_DECL int alpha_yylex(void * yylval)

int print_list();
void add_alpha_token(int token_num, char* type, char* val, int line);

%}

%x String
%option noyywrap
%option yylineno


INTEGER				([1-9][0-9]*)
FLOAT				(0{1}|([1-9]*))\.[0-9]+
IDENTIFIER    		[a-zA-Z][a-zA-Z0-9_]*
STRING				\"



%x C
%%

{STRING}	  			{
      char c;
      char *buff=malloc(256*sizeof(char));
      while ((c=input())) {

        if (c=='\"') {
          break;
        }
        printf("%c",c );

        //PERNA TO KATHE C STO BUFF PLZ KAI ANEVASE TO

      }

      printf("buff = %s\n",buff );
}


"//".*                                    { /* DO NOTHING FOR INSIDE */
                                                token_count++; add_alpha_token(token_count, "ONELINE COMMENT", "single comment", yylineno);
                                          }


[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]       { /* DO NOTHING */
                                                token_count++; add_alpha_token(token_count, "MULTILINE COMMENT", "multi comment", yylineno);

                                          }

[/][*]                                    { yy_fatal_error("Unterminated comment"); }




"if"     	{ token_count++; add_alpha_token(token_count, "KEYWORD IF", "if", yylineno); }
"else"     	{ token_count++; add_alpha_token(token_count, "KEYWORD ELSE", "else", yylineno); }
"while"    	{ token_count++; add_alpha_token(token_count, "KEYWORD WHILE", "while", yylineno); }
"for"     	{ token_count++; add_alpha_token(token_count, "KEYWORD FOR", "for", yylineno); }
"function"  { token_count++; add_alpha_token(token_count, "KEYWORD FUNCTION", "function", yylineno); }
"return"    { token_count++; add_alpha_token(token_count, "KEYWORD RETURN", "return", yylineno); }
"break"    	{ token_count++; add_alpha_token(token_count, "KEYWORD BREAK", "break", yylineno); }
"continue"  { token_count++; add_alpha_token(token_count, "KEYWORD CONTINUE", "continue", yylineno); }
"and"     	{ token_count++; add_alpha_token(token_count, "KEYWORD AND", "and", yylineno); }
"not"     	{ token_count++; add_alpha_token(token_count, "KEYWORD NOT", "not", yylineno); }
"or"     	{ token_count++; add_alpha_token(token_count, "KEYWORD OR", "or", yylineno); }
"local"    	{ token_count++; add_alpha_token(token_count, "KEYWORD LOCAL", "local", yylineno); }
"true"     	{ token_count++; add_alpha_token(token_count, "KEYWORD TRUE", "true", yylineno); }
"false"     { token_count++; add_alpha_token(token_count, "KEYWORD FALSE", "false", yylineno); }
"nil"     	{ token_count++; add_alpha_token(token_count, "KEYWORD NIL", "nil", yylineno); }

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

";"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION SEMICOLON", ";", yylineno); }
","     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION COMMA", ",", yylineno); }
":"    		{ token_count++; add_alpha_token(token_count, "PUNCTUATION UPDOWN DOTS", ")", yylineno); }
"::"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION DOUBUPDOWN DOTS", ")", yylineno); }
"."     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION END DOT", ")", yylineno); }
".."     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION DOUBLE_END DOTS", ")", yylineno); }
"{"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION LEFT BRACE", "{", yylineno); }
"}"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION RIGHT BRACE", "}", yylineno); }
"["     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION RIGHT BRACKET", "[", yylineno); }
"]"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION LEFT BRACKET", "]", yylineno); }
"("     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION LEFT PARENTHESIS", "(", yylineno); }
")"     	{ token_count++; add_alpha_token(token_count, "PUNCTUATION RIGHT PARENTHESIS", ")", yylineno); }


{FLOAT}			{ token_count++; add_alpha_token(token_count, "FLOAT", yytext, yylineno);}
{INTEGER} 		{ token_count++; add_alpha_token(token_count, "INTEGER", yytext, yylineno);}
{IDENTIFIER} 	{ token_count++; add_alpha_token(token_count, "IDENTIFIER", yytext, yylineno);}

. 				printf("Uknown character: %s at: %d\n", yytext, yylineno);
\n				{ }

%%

//MAIN
