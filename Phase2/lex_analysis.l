%{
#include "y.tab.h"

int token_count = 0;

/*#define YY_DECL struct alpha_token_t* alpha_yylex(void * yylval)*/

int scope;
int print_list();
struct alpha_token_t* add_alpha_token(int token_num, char* type, char* val, int line);

void yywarning(char *text){
    printf("Warning in line %d : %s\n",yylineno,text );
}

void hide_symbols(int scope);
/*void yyerror(char *text){
    printf("Error in line %d : %s\n",yylineno,text );
    exit(0);
}*/


int yyerror (char* s){
   printf("Error in line %d, before token: '%s'\n", yylineno, yytext);
}

int commentHandler(int from);
int stringHandler();

%}


/*Dhlwsh twn token*/

%option noyywrap
%option yylineno

IF  	   "if"
ELSE     "else"
WHILE    "while"
FOR      "for"
FUNCTION  "function"
RETURN   "return"
BREAK    "break"
CONTINUE "continue"
AND      "and"
NOT      "not"
OR       "or"
LOCAL    "local"
TRUE     "true"
FALSE    "false"
NIL      "nil"

EQ		"="
PLUS		"+"
MINUS		"-"
MULT		"*"
DIV		"/"
MOD		"%"
EQUAL		"=="
NEQUAL		"!="
PPLUS		"++"
MMINUS		"--"
GREATER		">"
LESS		"<"
GREATER_EQUAL	">="
LESS_EQUAL	"<="

SEMICOLON	\;
COMMA		\,
COLON		\:
DCOLON		\:\:
DOT		\.
DOTS		\.\.
L_CBRACKET	\{
R_CBRACKET	\}
L_SBRACKET	\[
R_SBRACKET	\]
L_PARENTHES	\(
R_PARENTHES	\)

INTEGER				([0-9]*)
FLOAT				([0-9]*)\.[0-9]+
IDENTIFIER    		[a-zA-Z][a-zA-Z0-9_]*
STRING				\"

%%

"//".*      { add_alpha_token(++token_count, "COMMENT LINE_COMMENT", "", yylineno);}


"if"     	{ add_alpha_token(++token_count, "KEYWORD IF", "if", yylineno); return IF;}
"else"     	{  add_alpha_token(++token_count, "KEYWORD ELSE", "else", yylineno); return ELSE;}
"while"    	{  add_alpha_token(++token_count, "KEYWORD WHILE", "while", yylineno); return WHILE;}
"for"     	{  add_alpha_token(++token_count, "KEYWORD FOR", "for", yylineno); return FOR;}
"function"  {  add_alpha_token(++token_count, "KEYWORD FUNCTION", "function", yylineno); return FUNCTION;}
"return"    {  add_alpha_token(++token_count, "KEYWORD RETURN", "return", yylineno); return RETURN;}
"break"    	{  add_alpha_token(++token_count, "KEYWORD BREAK", "break", yylineno); return BREAK;}
"continue"  {  add_alpha_token(++token_count, "KEYWORD CONTINUE", "continue", yylineno); return CONTINUE;}
"and"     	{  add_alpha_token(++token_count, "KEYWORD AND", "and", yylineno); return AND;}
"not"     	{  add_alpha_token(++token_count, "KEYWORD NOT", "not", yylineno); return NOT;}
"or"     	  {  add_alpha_token(++token_count, "KEYWORD OR", "or", yylineno); return OR;}
"local"    	{  add_alpha_token(++token_count, "KEYWORD LOCAL", "local", yylineno); return LOCAL;}
"true"     	{  add_alpha_token(++token_count, "KEYWORD TRUE", "true", yylineno); return TRUE;}
"false"     {  add_alpha_token(++token_count, "KEYWORD FALSE", "false", yylineno); return FALSE;}
"nil"     	{  add_alpha_token(++token_count, "KEYWORD NIL", "nil", yylineno); return NIL;}

"="     	{  add_alpha_token(++token_count, "OPERATOR EQUALS", "=", yylineno); return EQ;}
"+"     	{  add_alpha_token(++token_count, "OPERATOR PLUS", "+", yylineno); return PLUS;}
"-"     	{  add_alpha_token(++token_count, "OPERATOR MINUS", "-", yylineno); return MINUS;}
"*"     	{  add_alpha_token(++token_count, "OPERATOR EPI", "*", yylineno); return MULT;}
"/"     	{  add_alpha_token(++token_count, "OPERATOR DIVISION", "/", yylineno); return DIV;}
"%"     	{  add_alpha_token(++token_count, "OPERATOR MOD", "%", yylineno); return MOD;}
"=="     	{  add_alpha_token(++token_count, "OPERATOR EQUALS_EQUALS", "==", yylineno); return EQUAL;}
"!="     	{  add_alpha_token(++token_count, "OPERATOR NOT_EQUALS", "!=", yylineno); return NEQUAL;}
"++"     	{  add_alpha_token(++token_count, "OPERATOR PLUS_PLUS", "++", yylineno); return PPLUS;}
"--"     	{  add_alpha_token(++token_count, "OPERATOR MINUS_MINUS", "--", yylineno); return MMINUS;}
">"     	{  add_alpha_token(++token_count, "OPERATOR BIGGER_THAN", ">", yylineno); return GREATER;}
"<"     	{  add_alpha_token(++token_count, "OPERATOR SMALLER_THAN", "<", yylineno); return LESS;}
">="     	{  add_alpha_token(++token_count, "OPERATOR BIGGER_EQ_THAN", ">=", yylineno); return GREATER_EQUAL;}
"<="     	{  add_alpha_token(++token_count, "OPERATOR SMALLER_EQ_THAN", "<=", yylineno); return LESS_EQUAL;}

";"     	{ add_alpha_token(++token_count, "PUNCTUATION SEMICOLON", ";", yylineno); return SEMICOLON; }
","     	{ add_alpha_token(++token_count, "PUNCTUATION COMMA", ",", yylineno); return COMMA; }
":"    		{ add_alpha_token(++token_count, "PUNCTUATION UPDOWN DOTS", ":", yylineno); return COLON; }
"::"     	{ add_alpha_token(++token_count, "PUNCTUATION DOUBUPDOWN DOTS", "::", yylineno); return DCOLON; }
"."     	{ add_alpha_token(++token_count, "PUNCTUATION END DOT", ".", yylineno); return DOT; }
".."     	{ add_alpha_token(++token_count, "PUNCTUATION DOUBLE_END DOTS", "..", yylineno); return DOTS;}
"{"     	{ add_alpha_token(++token_count, "PUNCTUATION LEFT CURLY BRACE", "{", yylineno); scope++; return L_CBRACKET;}
"}"     	{ add_alpha_token(++token_count, "PUNCTUATION RIGHT CURLY BRACE", "}", yylineno);hide_symbols(scope--); return R_CBRACKET; }
"["     	{ add_alpha_token(++token_count, "PUNCTUATION RIGHT BRACKET", "[", yylineno);return L_SBRACKET; }
"]"     	{ add_alpha_token(++token_count, "PUNCTUATION LEFT BRACKET", "]", yylineno);return R_SBRACKET; }
"("     	{ add_alpha_token(++token_count, "PUNCTUATION LEFT PARENTHESIS", "(", yylineno);  return L_PARENTHES; }
")"     	{ add_alpha_token(++token_count, "PUNCTUATION RIGHT PARENTHESIS", ")", yylineno); return R_PARENTHES; }


{FLOAT}			{ add_alpha_token(++token_count, "FLOAT", yytext, yylineno); yylval.floatValue = atof(yytext); return FLOAT;}
{INTEGER} 		{ add_alpha_token(++token_count, "INTEGER", yytext, yylineno); yylval.intValue = atoi(yytext); return INTEGER;}
{IDENTIFIER} 	{ add_alpha_token(++token_count, "IDENTIFIER", yytext, yylineno);	yylval.stringValue = strdup(yytext); return IDENTIFIER;}
{STRING}	  	{ stringHandler(); yylval.stringValue = strdup(yytext); return STRING; } //TODO uparxei periptwsh na einai lathos kai na prepei to return string na brisketai sthn stringHandler
"/*"  { commentHandler(yylineno);	}

[ \t]+            { }
. 				yywarning("Undefined character");
\n				{ }

%%


int commentHandler(int from){

	static int nested=0;
	char c;
    char integer_string [5];
    char *buff = malloc(sizeof(char));
	while ((c = input()) != EOF) {

		if (c == '*' ) {

			c = input();
			if ( c == '/') {

				if (nested == 0) {
                    sprintf(integer_string, "%d", from);
                    strcat(buff, integer_string);
                    strcat(buff, " - ");
                    sprintf(integer_string, "%d", yylineno);
                    strcat(buff, integer_string);

                    add_alpha_token(++token_count, "COMMENT BLOCK_COMMENT", buff, yylineno);

					return 0;
				} else {
                    sprintf(integer_string, "%d", from);
                    strcat(buff, integer_string);
                    strcat(buff, " - ");
                    sprintf(integer_string, "%d", yylineno);
                    strcat(buff, integer_string);

                    add_alpha_token(++token_count, "COMMENT NESTED_COMMENT", buff, yylineno);
					nested--;
					return 0;
				}

			} else unput(c);

		}

		if ( c == '/') {
			c = input();

			if (c == '*') {
				nested++;
				commentHandler(yylineno);
			} else	unput(c);
		}
	}

	yyerror("Not closing comment");
	return 0;
}


int stringHandler(){
	char c;
    char *buff = malloc(16*sizeof(char));
	long int length = 0;
	long int baseofre = 16;
    char tmp;

    while ((c = input()) ) {
    		length++;
		  if (length > baseofre) {
			  baseofre *= 2;
			  buff = realloc(buff, baseofre * sizeof(char));
	  	}
        if (c == '\"') {
            add_alpha_token(++token_count, "STRING", buff, yylineno);
            return 1;
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

		strcat(buff,"\\");

                printf("Warning: unknown escape sequence: '\\%c' in line: %d\n", tmp, yylineno );
                unput(tmp);
            }
        } else   {

            strncat(buff, &c, 1);
        }

    }
	yyerror("not closing string");

}
