#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

//extern struct alpha_token_t * alpha_yylex();
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern int token_count;
extern int scope; // current scope we are right now, as we do the syntactic analysis
int lastActiveFunc = 0;

extern char **argtable;
extern int numOfArgs;

void print_table();
void arginsert(char* arg);
int newFunction(char* name, int line,int tmpscope);
void print_table();

//------------------------- LEX ----------------------------

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


//------------------------- YACC ---------------------------------

/*enum for symbol type*/
typedef enum {
	global 		= 0,
	local 		= 1,
    formal 		= 2,
    user 		= 3,
    library 	= 4
} symtype;


struct arguments {
	const char 			*name;
	struct arguments 	*next;
};

typedef struct variable{
    const char		*name;
	unsigned int 	line;
	unsigned int 	scope;
} variable;

typedef struct function{
    const char			*name;
	unsigned int 		line;
	unsigned int 		scope;
 	struct arguments 	*args_list;
} function;

struct symbol_table_binding{ /*NODE OF THE TABLE*/
    symtype 		symbol_type;
    union{
		variable 	*var;
		function 	*func;
	} value;
	bool 			active;
	bool			access;
    struct symbol_table_binding *next;
};

struct SymTable_struct { /*TABLE*/
    struct symbol_table_binding **pinakas;
    int total_size;
};

struct SymTable_struct *table = NULL;

int SymTable_contains(const char *name, symtype sym_type, int scope);
int insertLocalVar( char* name, int line, int scope);
void print_table();


/*hash function for mapping symbols in table*/
int hash_function(const char *name){
  size_t ui;
  unsigned int uiHash = 0U;

  for (ui = 0U; name[ui] != '\0'; ui++)
          uiHash = uiHash * 65599 + name[ui];

  return uiHash % 100 ;
}

/*creates a new table if NULL
and inserts symbol in table*/
int insert_hash_table(const char *name, symtype sym_type, int line, bool active, int scope){
	struct symbol_table_binding *newnode;
	int mapping = 0;
	/*an den uparxei ftiagmeno table, to ftiaxnw*/
	if(table == NULL){
		table = malloc(sizeof(struct SymTable_struct *));

		table->pinakas = malloc(100 * sizeof(struct symbol_table_binding*));
		table->total_size = 0;
	}

	assert(table && name);
	mapping = hash_function(name);

	newnode = (struct symbol_table_binding *) malloc(sizeof(struct symbol_table_binding));

	if(sym_type == 0 || sym_type == 1 || sym_type == 2){ //an einai metavlhth
		newnode->value.var = (struct variable *)malloc(sizeof(struct variable));
		newnode->value.var->name = (char *)malloc(sizeof(char));
		newnode->value.var->name = name;
		newnode->value.var->line = line;
		newnode->value.var->scope = scope;
	} else if(sym_type == 3 || sym_type == 4){ //an einai function
		newnode->value.func = (struct function *) malloc(sizeof(struct function));
		newnode->value.func->name = (char *)malloc(sizeof(char));
		newnode->value.func->name = name;
		newnode->value.func->line = line;
		newnode->value.func->scope = scope;
		newnode->value.func->args_list = NULL;
		newnode->access=true;
	}

	newnode->active = active;
	newnode->symbol_type = sym_type;

	newnode->next = table->pinakas[mapping]; /*to bazw sthn arxh ths listas*/
	table->pinakas[mapping] = newnode;
	table->total_size++;

  	return 1;
}

/* 1 gia reference , opote okay
 * idio onoma, diaforetiko scope return 2;
 * idio onoma, idio scope kai diaforetiko type return 3;
 * an den yparxei return 0;
 */
int SymTable_contains(const char *name, symtype sym_type, int scope){
    struct symbol_table_binding *curr;
    int hash = 0;
    assert(table && name);

    hash = hash_function(name);//briskw pou kanei hash to stoixeio
    curr = table->pinakas[hash];//paw se ayth th thesh

	//elegxw an uparxeihdh to stoixeio pou thelw na prosthesw
    while(curr){
		if (strcmp(curr->value.var->name,name)==0 && scope == curr->value.var->scope ) {
			printf("%d  -- %d\n",curr->symbol_type,sym_type);
			if (curr->symbol_type==sym_type) return 1;
			else {
				printf("Conflicting types of %s in line %d \n",name , yylineno );
				exit(EXIT_FAILURE);

			}
		}
    	curr = curr->next;
    }
    return 0;
}

void hide_symbols(int scope){
	int i;
	for(i = 0; i < 100; i++ ){
	  struct symbol_table_binding *curr = table->pinakas[i];
	  while(curr != NULL){
			  if(curr->value.var->scope == scope && curr->value.var->scope!=0 ) curr->active=false;
			  curr = curr-> next;
	  }
	}
}

int argumentF(char *name, int line, int scope) {
	struct symbol_table_binding *tmp;
	struct arguments *newArg = NULL;

	assert(table && name);

	newArg = (struct arguments *)malloc(sizeof(struct arguments));
	newArg->name = name;

	tmp = table->pinakas[lastActiveFunc];

//TODO check SHADOWING
	while(tmp->value.func->args_list != NULL) {
		if(strcmp(tmp->value.func->args_list->name, name) == 0) {
			printf("Error: Duplicate argument: %s in function: %s in line: %d\n", name, tmp->value.func->name, yylineno);
			exit(EXIT_FAILURE);
		}

		tmp->value.func->args_list = tmp->value.func->args_list->next;
	}

	newArg->next = table->pinakas[lastActiveFunc]->value.func->args_list;
	table->pinakas[lastActiveFunc]->value.func->args_list = newArg;

	insert_hash_table(name, 2, line, true, scope);

	return 0;
}

int newFunction(char* name , int line, int scope){
	struct symbol_table_binding *newnode;
	int mapping = 0;
	int flag = -1;
	/*an den uparxei ftiagmeno table, to ftiaxnw*/
	if(table == NULL){
		table = malloc(sizeof(struct SymTable_struct *));

		table->pinakas = malloc(100 * sizeof(struct symbol_table_binding*));
		table->total_size = 0;
	}
	assert(table && name);

	/* SHADOWING OF LIBRARY FUNCTION */
	// if( strcmp(name, "print") == 0 || strcmp(name, "input") == 0 || strcmp(name, "objectmemberkeys") == 0 || strcmp(name, "objectcopy") == 0 \
    //         || strcmp(name, "objectdef") == 0 || strcmp(name, "objecttotalmembers") == 0|| strcmp(name, "totalarguments") == 0 \
    //         || strcmp(name, "argument") == 0 || strcmp(name, "typeof") == 0 || strcmp(name, "strtonum") == 0 \
    //         || strcmp(name, "sqrt") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "sin") == 0 ) {
	// 	printf("Error Shadowing library function \"%s\" in line %d\n", name, yylineno);
	// 	exit(EXIT_FAILURE);
	// }

//TODO
	/* DUPLICATE FUNCTION  */
	// flag = SymTable_contains(table, name, 3, line, 1);
	// if(flag == 3) {
	// 	printf("Error: Redefinition of name: \"%s\" in line: %d\n", name, yylineno);
	//  	exit(EXIT_FAILURE);
	// } else if(flag == 1) {
	// 	printf("Error: Duplicate function name: \"%s\" in line: %d\n", name, yylineno);
	//  	exit(EXIT_FAILURE);
	// }


if (SymTable_contains(name,3,scope)) {
	return 0;
}

	mapping = hash_function(name);
	lastActiveFunc = mapping;

	newnode = (struct symbol_table_binding *) malloc(sizeof(struct symbol_table_binding));
	newnode->value.func = (struct function *) malloc(sizeof(struct function));
	newnode->value.func->name = (char *)malloc(sizeof(char));
	newnode->value.func->name = name;
	newnode->value.func->line = line;
	newnode->value.func->scope = scope;
	newnode->value.func->args_list = NULL;
	newnode->active = 1;
	newnode->symbol_type = 3;

	newnode->next = table->pinakas[mapping]; /*to bazw sthn arxh ths listas*/
	table->pinakas[mapping] = newnode;
	table->total_size++;

	return 0;
}



int insertVar(char* name , int line , int scope){
	int flag = 1;
	struct symbol_table_binding *curr;
	if(table == NULL){
		table = malloc(sizeof(struct SymTable_struct *));

		table->pinakas = malloc(100 * sizeof(struct symbol_table_binding*));
		table->total_size = 0;
	}
	assert(table && name);

	int hash = 0;
	if (scope==0) flag=0;
	if( strcmp(name, "print") == 0 || strcmp(name, "input") == 0 || strcmp(name, "objectmemberkeys") == 0 || strcmp(name, "objectcopy") == 0 \
			|| strcmp(name, "objectdef") == 0 || strcmp(name, "objecttotalmembers") == 0|| strcmp(name, "totalarguments") == 0 \
			|| strcmp(name, "argument") == 0 || strcmp(name, "typeof") == 0 || strcmp(name, "strtonum") == 0 \
			|| strcmp(name, "sqrt") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "sin") == 0 ) {
		printf("Error Shadowing library function \"%s\" in line %d\n", name, yylineno);
		exit(EXIT_FAILURE);
}
	hash = hash_function(name);//briskw pou kanei hash to stoixeio
	curr = table->pinakas[hash];//paw se ayth th thesh


	while(curr){
		if (strcmp(curr->value.var->name,name)==0 && scope == curr->value.var->scope && curr->active==true ) {
			printf("%d  -- %d\n",curr->symbol_type,flag);
			if (curr->symbol_type!=flag){

				printf("Conflicting types of %s in line %d \n",name , yylineno );
				exit(EXIT_FAILURE);

			}else return 0;

		}
		curr = curr->next;
	}

	curr = table->pinakas[hash];//paw se ayth th thesh

	while(curr){
		if (strcmp(curr->value.var->name,name)==0 && curr->active==true && curr->value.var->scope!=0) {
				printf("Cannot access  %s in line %d \n",curr->value.var->name , curr->value.var->line );
				exit(EXIT_FAILURE);

			 return 0;

		}
		curr = curr->next;
	}

	curr = table->pinakas[hash];//paw se ayth th thesh

	while(curr){
		if (strcmp(curr->value.var->name,name)==0 && curr->active==true && curr->value.var->scope==0) {

			 return 0;

		}
		curr = curr->next;
	}

	if(scope == 0) {
		insert_hash_table(name, 0, line, true, scope);
	} else insert_hash_table(name, 1, line, true, scope);
}


int insertLocalVar( char* name, int line, int scope){
	int flag=1;
	struct symbol_table_binding *curr;
    int hash = 0;
	if(table == NULL){
		table = malloc(sizeof(struct SymTable_struct *));

		table->pinakas = malloc(100 * sizeof(struct symbol_table_binding*));
		table->total_size = 0;
	}
    assert(table && name);
	if (scope==0) flag=0;
	if( strcmp(name, "print") == 0 || strcmp(name, "input") == 0 || strcmp(name, "objectmemberkeys") == 0 || strcmp(name, "objectcopy") == 0 \
			|| strcmp(name, "objectdef") == 0 || strcmp(name, "objecttotalmembers") == 0|| strcmp(name, "totalarguments") == 0 \
			|| strcmp(name, "argument") == 0 || strcmp(name, "typeof") == 0 || strcmp(name, "strtonum") == 0 \
			|| strcmp(name, "sqrt") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "sin") == 0 ) {
		printf("Error Shadowing library function \"%s\" in line %d\n", name, yylineno);
		exit(EXIT_FAILURE);
}
    hash = hash_function(name);//briskw pou kanei hash to stoixeio
    curr = table->pinakas[hash];//paw se ayth th thesh

	//elegxw an uparxeihdh to stoixeio pou thelw na prosthesw
    while(curr){
		if (strcmp(curr->value.var->name,name)==0 && scope == curr->value.var->scope && curr->active==true ) {
			printf("%d  -- %d\n",curr->symbol_type,flag);
			if (curr->symbol_type!=flag){

				printf("Conflicting types of %s in line %d \n",name , yylineno );
				exit(EXIT_FAILURE);

			}else return 0;

		}
    	curr = curr->next;
    }

		insert_hash_table(name, flag, line, true, scope);


    return 0;

}


char* enum_toString(symtype sym) {
	if(sym == 0) return "global";
	else if(sym == 1) return "local";
	else if(sym == 2) return "formal";
	else if(sym == 3) return "user";
	else if(sym == 4) return "library";
	else return "lathos";
}

/*prints table*/
void print_table(){
  	int i = 0, scope = 0;

  	if(table == NULL){
    	printf("table is empty\n");
    	return ;
  	}
	printf("\n\"NAME\"   [TYPE]    (LINE)   (SCOPE)\n");
	for(scope = 0; scope < 10; scope++) {
		printf("----------Scope #%d ----------", scope);
		for(i = 0; i < 100; i++) {
			struct symbol_table_binding *curr = table->pinakas[i];
			while(curr != NULL) {
				if((curr->symbol_type == 0 || curr->symbol_type == 1 || curr->symbol_type == 2) && curr->value.var->scope == scope )
      				printf("\n \"%s\" [%s variable] (line %d) (scope %d) ", curr->value.var->name, enum_toString(curr->symbol_type), curr->value.var->line, curr->value.var->scope);

				if((curr->symbol_type == 3 || curr->symbol_type == 4) && curr->value.func->scope == scope ) {
			 		printf("\n \"%s\" [%s function] (line %d) (scope %d) ", curr->value.func->name, enum_toString(curr->symbol_type), curr->value.func->line, curr->value.func->scope);
					//printf gia oti mpikan swsta <3
					printf("func name: %s ", curr->value.func->name);
					struct arguments *tmp = curr->value.func->args_list;
					//printf("arg1 %s arg2 %s",tmp->name, tmp->next->name);
					while(tmp != NULL) {
						printf("args %s\n", tmp->name);
						tmp = tmp->next;
					}
					while(curr->value.func->args_list != NULL) {
						printf("args: %s\n", curr->value.func->args_list->name);
						curr->value.func->args_list = curr->value.func->args_list->next;
					}
				}
				curr = curr-> next;
			}
		}
		printf("\n");
	}
}
