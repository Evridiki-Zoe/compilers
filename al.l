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

static void skip_multiple_line_comment(void)
{
  int c;

  for(;;)
  { 
    c = input();
    switch( c )
    {
      case EOF:
        fprintf(stderr, "Error unclosed comment, expect */\n");
        exit(-1);
        goto done;
      break;
      case '*':
        if((c = input()) == '/')
          goto done;
        unput(c);
        break;
      default:
        break;
    }
  }

    done:
  /* exit entry */ ;
}

%}

%x String
%option noyywrap
%option yylineno


INTEGER				([0-9]*)
FLOAT				(0{1}|([1-9]*))\.[0-9]+
IDENTIFIER    		[a-zA-Z][a-zA-Z0-9_]*
STRING				\"



%x C
%%


{STRING}	  			{
    char c;
    char *buff = malloc(sizeof(char));
    char tmp;
    while ((c = input())) {

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
                strncat(buff, "\t", 1);
            } else if (tmp == 'n') {
                strncat(buff, "\n", 1);
            } else if (tmp == '\\') {
                strncat(buff, "\\", 1);
            } else {
                printf("warning: unkown escape sequence: '\\%c' in line: %d\n", tmp, yylineno );
                unput(tmp);
            }
        } else   {
            strncat(buff, &c, 1);
        }

    }
}


"//".*                                    { /* DO NOTHING FOR INSIDE */
                                                add_alpha_token(++token_count, "COMMENT LINE_COMMENT", "", yylineno);
                                          }

"/*"              { puts("long comment begins ");
                    skip_multiple_line_comment();
                    puts("long comment ends");}

"/*"         {
          int from[50];
          int to[50];

          from[0]=yylineno;

          char c;

          int nestopen=0;
          int nestclose=-1;



          while ((c = input())) {

            if (c=='*') {
                c=input();
                if (c=='/') {
                  to[nestopen]=yylineno;
                  nestclose++;
                  if (nestopen==nestclose) {
                        printf("Original comment from %d, to %d\n",from[0],to[0] );
                        printf("nested from %d , to %d \n",from[1],to[1] );
                        return 0;

                  }


                }


            }

            if (c=='/') {
                c=input();
                if (c=='*') {

                  from[++nestopen]=yylineno;


                }


            }


          }




}





"if"     	{ add_alpha_token(++token_count, "KEYWORD IF", "if", yylineno); }
"else"     	{ add_alpha_token(++token_count, "KEYWORD ELSE", "else", yylineno); }
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

. 				yywarning("Undendifined token");
\n				{ }

%%

//MAIN
