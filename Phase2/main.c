#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

//extern struct alpha_token_t * alpha_yylex();
extern int yyparse(void);
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern int token_count;
extern int scope; // current scope we are right now, as we do the syntactic analysis

extern int isFunction;
int lastActiveFunc = 0;

int print_table();
int argumentF(const char *name, int line, int scope);
int newFunction(const char* name, int line,int tmpscope);

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
	bool accessible ;
  struct symbol_table_binding *next;
};

struct SymTable_struct { /*TABLE*/
    struct symbol_table_binding **pinakas;
    int total_size;
};

struct SymTable_struct *table = NULL;

int searchValue(struct arguments *head, const char *key);

int SymTable_contains(struct SymTable_struct *table, const char *name, symtype sym_type, int line, bool active, int scope);

int insertLocalVar(const char* name, int line, int scope);


void make_not_accessible(int curr_scope){
	int i = 0;
	for(i = 0; i < 100; i++) {
		struct symbol_table_binding *curr = table->pinakas[i];
		while(curr != NULL) {
			if((curr->symbol_type == 1 || curr->symbol_type == 2)){  //edw DEN PREPEI na exei to 0, giati tis global den thelw na tis xalaw
					if(  curr->accessible == 1 &&  curr->value.var->scope<curr_scope ){
							curr->accessible = 0;
					}
					else {
						curr = curr->next ;
					}
			}
			else{
				curr = curr->next ;
			}
		}

	}

//printf("NOT ACCESSIBLE\n");
//print_table();
}

void make_accessible_again(int curr_scope){
	int i = 0;
			for(i = 0; i < 100; i++) {
				struct symbol_table_binding *curr = table->pinakas[i];
				while(curr != NULL) {
					if(( curr->symbol_type == 1 || curr->symbol_type == 2)){ //edw DEN PREPEI na exei to 0, giati tis global den thelw na tis xalaw
							if(  curr->accessible == 0 &&  curr->value.var->scope<curr_scope ){
									curr->accessible = 1;
							}
							else {
								curr = curr->next ;
							}
				}
				else{
						curr = curr->next ;
				}

				}

			}

//printf("AGAIN ACCESSIBLE\n");
//print_table();

}


/*hash function for mapping symbols in table*/
int hash_function(const char *name){
  size_t ui;
  unsigned int uiHash = 0U;

  for (ui = 0U; name[ui] != '\0'; ui++)
          uiHash = uiHash * 65599 + name[ui];

  return uiHash % 100 ;
}

void check_for_funcname(const char* lvalue_name){
	int i = 0 ;
	assert(lvalue_name);

	// struct symbol_table_binding *curr = table->pinakas[hash_function(lvalue_name)];
	// printf("name: %s\n", lvalue_name);
	// while(curr != NULL) {
	// 	if(curr->symbol_type == 3 || curr->symbol_type == 4){
	// 		if(strcmp(lvalue_name,curr->value.func->name) == 0) {
	// 				printf("Error: you are trying to assign a value to a user/library function in line %d\n", yylineno);
	// 				exit(EXIT_FAILURE);
	// 		}
	// 	}
	// 	curr = curr->next;
	// }

	for(i = 0; i < 100; i++){
		struct symbol_table_binding *curr = table->pinakas[i];
		while(curr != NULL) {
					if(curr->symbol_type == 3 || curr->symbol_type == 4){
						if(strcmp(lvalue_name,curr->value.func->name) == 0) {
								printf("Error: you are trying to assign a value to a user/library function in line %d\n", yylineno);
								exit(1);
							}
				}
			curr = curr->next;
		}
	}
}



/*creates a new table if NULL
and inserts symbol in table*/
int insert_hash_table(const char *name, symtype sym_type, int line, bool active, int scope){
	struct symbol_table_binding *newnode;
	int mapping = 0;

	assert(table && name);
	mapping = hash_function(name);

	newnode = (struct symbol_table_binding *) malloc(sizeof(struct symbol_table_binding));

	if(sym_type == 0 || sym_type == 1 || sym_type == 2){ //an einai metavlhth

		newnode->value.var = (struct variable *)malloc(sizeof(struct variable));
		newnode->value.var->name = (char *)malloc(sizeof(char));
		newnode->value.var->name = name;
		newnode->value.var->line = line;
		newnode->symbol_type = sym_type;
		newnode->value.var->scope = scope;
	} else if(sym_type == 3 || sym_type == 4){ //an einai function
		newnode->value.func = (struct function *) malloc(sizeof(struct function));
		newnode->value.func->name = (char *)malloc(sizeof(char));
		newnode->value.func->name = name;
		newnode->value.func->line = line;
		newnode->symbol_type = sym_type;
		newnode->value.func->scope = scope;
		newnode->value.func->args_list = NULL;
	}

	newnode->active = active;
	newnode->symbol_type = sym_type;
	newnode->accessible = 1;

	newnode->next = table->pinakas[mapping]; /*to bazw sthn arxh ths listas*/
	table->pinakas[mapping] = newnode;
	table->total_size++;

  return 1;
}

int check_if_exists_already(const char *name, int scope) {
	struct symbol_table_binding *curr;
	int mapping = 0;

	assert(name);

	mapping = hash_function(name);
	curr = table->pinakas[mapping];

	while(curr) {
		if(strcmp(curr->value.func->name, name) == 0) {
			return 0;
		}
	}
	insert_hash_table(name, 3, yylineno, 1, scope);
	return 0;
}

int global_exists(const char *name) {
	struct symbol_table_binding *curr;
	int mapping = 0;

	assert(name);

	mapping = hash_function(name);
	curr = table->pinakas[mapping];

	while(curr) {
		if (strcmp(curr->value.func->name, name) == 0) {
			if( curr->value.func->scope == 0) {
				return 1;
			}
		}
		curr = curr->next;
	}
	return 0;
}


int contains_Func(const char *name, int scope) {
	struct symbol_table_binding *curr;
	int mapping = 0;

	assert(name);

	mapping = hash_function(name);
	curr = table->pinakas[mapping];

	while(curr) {
		if(strcmp(curr->value.func->name, name) == 0 && curr->value.func->scope == scope) {
			printf("Redefinition of \"%s\" in line: %d\n", name, yylineno);
			exit(EXIT_FAILURE);

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
			  if(curr->value.var->scope == scope && curr->value.var->scope != 0 ) curr->active = false;
			  curr = curr->next;
	  }
	}
}

int argumentF(const char *name, int line, int scope) {
	struct symbol_table_binding *tmp;
	struct arguments *newArg = NULL;

	assert(table && name);

	// /* SHADOWING OF LIBRARY FUNCTION */
	if( strcmp(name, "print") == 0 || strcmp(name, "input") == 0 || strcmp(name, "objectmemberkeys") == 0 || strcmp(name, "objectcopy") == 0 \
            || strcmp(name, "objectdef") == 0 || strcmp(name, "objecttotalmembers") == 0|| strcmp(name, "totalarguments") == 0 \
            || strcmp(name, "argument") == 0 || strcmp(name, "typeof") == 0 || strcmp(name, "strtonum") == 0 \
            || strcmp(name, "sqrt") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "sin") == 0 ) {
		printf("Error Shadowing library function \"%s\" in line %d\n", name, yylineno);
		exit(EXIT_FAILURE);
	}

	newArg = (struct arguments *)malloc(sizeof(struct arguments));
	newArg->name = name;


	tmp = table->pinakas[lastActiveFunc];
	if(tmp == NULL) {
		printf("Function you are trying to add formal argument doesnt exist, wtf.");
		exit(EXIT_FAILURE);
	}

	if(searchValue((struct arguments *)tmp->value.func->args_list, name) == 1) {
		printf("Error: Duplicate argument: \"%s\" in function: \"%s\" in line: %d\n", name, tmp->value.func->name, yylineno);
	 	exit(EXIT_FAILURE);
	}

	newArg->next = table->pinakas[lastActiveFunc]->value.func->args_list;
	table->pinakas[lastActiveFunc]->value.func->args_list = newArg;

	insert_hash_table(name, 2, line, true, scope);

	return 0;
}

int newFunction(const char* name , int line, int scope){
	struct symbol_table_binding *newnode;
	int mapping = 0;
	int flag = 1;

	if(scope == 0) flag = 0;

	assert(table && name);

	/* SHADOWING OF LIBRARY FUNCTION */
	if( strcmp(name, "print") == 0 || strcmp(name, "input") == 0 || strcmp(name, "objectmemberkeys") == 0 || strcmp(name, "objectcopy") == 0 \
            || strcmp(name, "objectdef") == 0 || strcmp(name, "objecttotalmembers") == 0|| strcmp(name, "totalarguments") == 0 \
            || strcmp(name, "argument") == 0 || strcmp(name, "typeof") == 0 || strcmp(name, "strtonum") == 0 \
            || strcmp(name, "sqrt") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "sin") == 0 ) {
		printf("Error Shadowing library function \"%s\" in line %d\n", name, yylineno);
		exit(EXIT_FAILURE);
	}

	// CHECK IF IT EXISTS LOCALLY (local/ function/ formal arg)
	if((contains_Func(name, scope))) {
		//ok;
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

int searchValue(struct arguments *head, const char *key) {
	struct arguments *curr = head;

	while(curr != NULL) {
		if(strcmp(curr->name, key) == 0) return 1;
		curr = curr->next;
	}

	return 0;
}


int insertVar(char* name , int line , int scope){
	int flag = 1;
	struct symbol_table_binding *curr, *tmp;

	assert(table && name);

	int hash = 0;
	if (scope == 0) flag = 0;
	// if( strcmp(name, "print") == 0 || strcmp(name, "input") == 0 || strcmp(name, "objectmemberkeys") == 0 || strcmp(name, "objectcopy") == 0 \
	// 		|| strcmp(name, "objectdef") == 0 || strcmp(name, "objecttotalmembers") == 0|| strcmp(name, "totalarguments") == 0 \
	// 		|| strcmp(name, "argument") == 0 || strcmp(name, "typeof") == 0 || strcmp(name, "strtonum") == 0 \
	// 		|| strcmp(name, "sqrt") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "sin") == 0 ) {
	// 	printf("Error Shadowing library function \"%s\" in line %d\n", name, yylineno);
	// 	exit(EXIT_FAILURE);
	// }

	hash = hash_function(name);//briskw pou kanei hash to stoixeio

	/*
	 * check locally gia reference, ok
	 * meta an yparxei synartisi anamesa, ERROR
	 *
	 *  meta check an yparxei ws synartisi, ERROR
	 *
	 * meta globally, ok
	 *
	 * alliws einai GG kai kanoume insert
	 */
	tmp = table->pinakas[lastActiveFunc];

	curr = table->pinakas[hash];//paw se ayth th thesh
	while(curr){

		if(strcmp(name, curr->value.var->name) == 0 && curr->active == true && curr->symbol_type == flag && curr->value.var->scope == scope) {

			printf("Reference to local var\n" );
			return 0;
		} else if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 1 && curr->active == true && curr->symbol_type == 2 ) {

			printf("Reference to formal argument\n");
			return 0;
		} else if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 0 && curr->active == true  && curr->value.var->scope != 0 ) {

				if(tmp != NULL) {
					if(tmp->value.func->scope < scope && tmp->value.func->scope >= curr->value.var->scope && curr->value.var->scope != 0) {
						printf("Cannot access \"%s\" defined in line: %d from line: %d\n", curr->value.var->name, curr->value.var->line, yylineno );
						exit(EXIT_FAILURE);
					}
				}

			printf("Reference to accessible var in another scope\n");
			return 0;
		}  else if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 1 && curr->active == true  && curr->value.var->scope != 0 ) {
			printf("Reference to accessible var in another scope\n");
			return 0;
		
		} else if(strcmp(name, curr->value.var->name) == 0 && curr->active == true && curr->value.var->scope == 0) {
			printf("Reference to global var\n");
			return 0;
		}

		printf("name: %s, acce: %d, active: %d scope: %d\n", curr->value.var->name, curr->accessible, curr->active, curr->value.var->scope);
		// yparxei locally i anamesa se synartisi
		// if (strcmp(curr->value.var->name, name) == 0 && curr->active == true && curr->value.var->scope != 0){

		// 	if(tmp != NULL) {
		// 		if(tmp->value.func->scope < scope && tmp->value.func->scope >= curr->value.var->scope && curr->value.var->scope != 0) {
		// 			printf("Cannot access \"%s\" defined in line: %d from line: %d\n", curr->value.var->name, curr->value.var->line, yylineno );
		// 			exit(EXIT_FAILURE);
		// 		}
		// 	}
		// 	return 0;

		// 	// yparxei ws synartisi
		// } else if(strcmp(curr->value.var->name, name) == 0 && curr->symbol_type == 3){
		// 	printf("Conflicting type of \"%s\" in line: %d\n", name, yylineno);
		// 	exit(EXIT_FAILURE);

		// 		// yparxei globally
		// } else  if(strcmp(curr->value.var->name, name) == 0 && curr->value.var->scope == 0) {
		// 	return 0;
		// }

		curr = curr->next;
	}
	insert_hash_table(name, flag, line, true, scope);
	return 0;
}

// int localVar(const char *name, int line, int scope) {
// 	printf("WTF");
// 	return 1;
// }
int localVar(const char* name, int line, int scope){
	int flag = 1;
	struct symbol_table_binding *curr;
    int hash = 0;
	printf("gamw ti mana sou");
    assert(table && name);
	if (scope == 0) flag = 0;

	if( strcmp(name, "print") == 0 || strcmp(name, "input") == 0 || strcmp(name, "objectmemberkeys") == 0 || strcmp(name, "objectcopy") == 0 \
			|| strcmp(name, "objectdef") == 0 || strcmp(name, "objecttotalmembers") == 0|| strcmp(name, "totalarguments") == 0 \
			|| strcmp(name, "argument") == 0 || strcmp(name, "typeof") == 0 || strcmp(name, "strtonum") == 0 \
			|| strcmp(name, "sqrt") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "sin") == 0 ) {
		printf("Error Shadowing library function \"%s\" in line %d\n", name, yylineno);
		exit(EXIT_FAILURE);
	}

    hash = hash_function(name);//briskw pou kanei hash to stoixeio
    curr = table->pinakas[hash];//paw se ayth th thesh

	// // elegxw an uparxeihdh to stoixeio pou thelw na prosthesw
    while(curr){
		if (strcmp(curr->value.var->name, name) == 0 && scope == curr->value.var->scope && curr->active == true ) {
			if (curr->symbol_type == 3 || curr->symbol_type == 4){
				printf("Conflicting types of \"%s\" in line: %d \n",name , yylineno );
				exit(EXIT_FAILURE);

			} else return 0;
		}
    	curr = curr->next;
    }

	insert_hash_table(name, flag, line, true, scope);
	return 1;
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
int print_table(){
  	int i = 0, scope = 0;

  	if(table == NULL){
    	printf("table is empty\n");
    	return 0;
  	}
	printf("\n\"NAME\"   [TYPE]    (LINE)   (SCOPE)\n");
	for(scope = 0; scope < 10; scope++) {
		printf("----------Scope #%d ----------", scope);
		for(i = 0; i < 100; i++) {
			struct symbol_table_binding *curr = table->pinakas[i];
			while(curr != NULL) {
				if((curr->symbol_type == 0 || curr->symbol_type == 1 || curr->symbol_type == 2) && curr->value.var->scope == scope )
      				printf("\n \"%s\" [%s variable] (line %d) (scope %d) (active %d) (accessible %d) ", curr->value.var->name, enum_toString(curr->symbol_type), curr->value.var->line, curr->value.var->scope, curr->active, curr->accessible);

				if((curr->symbol_type == 3 || curr->symbol_type == 4) && curr->value.func->scope == scope ) {
			 		printf("\n \"%s\" [%s function] (line %d) (scope %d) (active %d)", curr->value.func->name, enum_toString(curr->symbol_type), curr->value.func->line, curr->value.func->scope, curr->active);
					//printf gia oti mpikan swsta <3
					// struct arguments *tmp = curr->value.func->args_list;
					// //printf("arg1 %s arg2 %s",tmp->name, tmp->next->name);
					// while(tmp != NULL) {
					// 	printf("args %s\n", tmp->name);
					// 	tmp = tmp->next;
					// }
				}
				curr = curr-> next;
			}
		}
		printf("\n");
	}

	return 1;
}


int main(void) {

	if(table == NULL){
		table = malloc(sizeof(struct SymTable_struct *));

		table->pinakas = malloc(100 * sizeof(struct symbol_table_binding*));
		table->total_size = 0;
	}

	insert_hash_table("print", 4 , 0, true, 0);
	insert_hash_table("input", 4 , 0, true, 0);
	insert_hash_table("objectmemberkeys", 4 , 0, true, 0);
	insert_hash_table("objecttotalmembers", 4 , 0, true, 0);
	insert_hash_table("objectcopy", 4 , 0, true, 0);
	insert_hash_table("totalarguments", 4 , 0, true, 0);
	insert_hash_table("argument", 4 , 0, true, 0);
	insert_hash_table("typeof", 4 , 0, true, 0);
	insert_hash_table("strtonum", 4 , 0, true, 0);
	insert_hash_table("sqrt", 4 , 0, true, 0);
	insert_hash_table("cos", 4 , 0, true, 0);
	insert_hash_table("sin", 4 , 0, true, 0);

	yyparse();

	print_table();

	return 0;
}
