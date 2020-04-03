#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define SIZE 101	/* hash table buckets size */

int maxScope = 0;
/* extern struct alpha_token_t * alpha_yylex(); */
extern int yyparse(void);
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern int token_count;
extern int scope;
extern int ref;
extern int isFunction;
int lastActiveFunc = 0;
extern int args;

int print_table();
int argumentF(char *name, int line, int scope);
int newFunction(char* name, int line,int tmpscope);

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
	struct alpha_token_t *tmp = malloc(sizeof(struct alpha_token_t));
	tmp->token_no = token_num;
	tmp->type = type;
	tmp->value = malloc((strlen(val) + 1) * sizeof(char));
	strcpy(tmp->value, val);
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
	char 				*name;
	struct arguments 	*next;
};

typedef struct variable{
    char			*name;
	unsigned int 	line;
	unsigned int 	scope;
} variable;

typedef struct function{
    char				*name;
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

	//int val; // gia ta lvalue?????????
  struct symbol_table_binding *next;
};

struct SymTable_struct { /*TABLE*/
    struct symbol_table_binding **pinakas;
    int total_size;
};

//===================================================

/*enum for rvalue type*/
typedef enum {
number = 0,
string = 1,
boolean = 2,
nil = 3,
function_addr = 4,
lib_func = 5
} rvalue_type;

struct rvalue_node {
	char* name;
	rvalue_type type;
  struct rvalue_node* next;
};

struct rvalue_node* r_value_head = NULL;

void insert_rvalue_list(char* name, rvalue_type type){

	if(r_value_head == NULL) { //mhn to allaksete ayto
		struct rvalue_node* newnode = malloc(sizeof(struct rvalue_node));
		newnode->name = malloc((strlen(name) + 1) * sizeof(char));

		strcpy(newnode->name, name);
		newnode->type = type;
		newnode->next = NULL;
		r_value_head = newnode;
		return;
	}

	struct rvalue_node* newnode = malloc(sizeof(struct rvalue_node));
	newnode->name = malloc((strlen(name) + 1) * sizeof(char));

	strcpy(newnode->name, name);
	newnode->type = type;
	newnode->next = r_value_head;
	r_value_head = newnode;
}

void print_list_rvalues(){

	assert(r_value_head);
	struct rvalue_node* curr = r_value_head;

	while(curr != NULL){
			printf("RVALUE: %s, with type: %d\n", curr->name, curr->type);
			curr = curr->next;
		}

}


typedef enum {
	assign,
	add,
	sub,
	mul,
	Div, //oxi div alliws exei conflict type with lex
	mod,
	uminus,
	and,
	or,
	not,
	if_eq,
	if_not_eq,
	if_lesseq,
	if_greatereq,
	if_less,
	if_greater,
	call,
	param,
	ret,
	getretval,
	funcstart,
	funcend,
	tablecreate,
	tablegetelem,
	table_setelem

}iopcode;

//gia ta quads
typedef enum {
var_e,
tableitem_e,
programfunc_e,
libfunc_e,

arithmeticexp_e,
boolexp_e,
assignexp_e,
newtable_e,

const_num_e,
constbool_e,
conststring_e,
nil_e

}expr_t;

struct expr{

expr_t type;
//symbol* sym;	//mallon thelei olo to symbol node?
struct expr* index;
double numconst;
char* strconst;
unsigned char boolconst;
struct expr* next;

};

struct quad{
	iopcode opcode;
  struct expr* res;
  struct expr* arg1;
  struct expr* arg2;
	unsigned label;
	unsigned line;
};


struct SymTable_struct *table = NULL;

int searchValue(struct arguments *head, char *key);

int insertLocalVar(char* name, int line, int scope);

/*makes all variables (type 1 or 2) of scope equal to current scope or less, not accessible
used for checking inside function*/
void make_not_accessible(int curr_scope){
	size_t i = 0;
	for(i = 0; i < SIZE; i++) {
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
}

/*makes all variables (type 1 or 2) accessible*/
void make_accessible_again(int curr_scope){
	size_t i = 0;
	for(i = 0; i < SIZE; i++) {
		struct symbol_table_binding *curr = table->pinakas[i];
		while(curr != NULL) {
			if(( curr->symbol_type == 1 || curr->symbol_type == 2)){ //edw DEN PREPEI na exei to 0, giati tis global den thelw na tis xalaw
					if(  curr->accessible == 0 &&  curr->value.var->scope<curr_scope ){
							curr->accessible = 1;
					}
					else {
						curr = curr->next ;
					}
			} else{
				curr = curr->next ;
			}
		}
	}
}

/*hash function for mapping symbols in table*/
int hash_function(const char *name){
  size_t ui;
  unsigned int uiHash = 0U;

  for (ui = 0U; name[ui] != '\0'; ui++)
          uiHash = uiHash * 65599 + name[ui];

  return uiHash % SIZE ;
}

int check_for_funcname(const char *name){
	struct symbol_table_binding *curr;

	assert(name);

	curr = table->pinakas[hash_function(name)];
	while(curr != NULL) {
		if(curr->symbol_type == 3 || curr->symbol_type == 4){
			if(strcmp(name,curr->value.func->name) == 0 && curr->active == 1) {
					printf("Error: you are trying to assign a value to a user/library function in line %d\n", yylineno);
					exit(EXIT_FAILURE);
			}
		}
		curr = curr->next;
	}
	return 1;
}


/*
 * Inserts a new node
 * in hashtable
 */
int insert_hash_table(char *name, symtype sym_type, int line, bool active, int scope){
	struct symbol_table_binding *newnode;
	int mapping = 0;

	assert(table && name);
	mapping = hash_function(name);

	newnode = malloc(sizeof(struct symbol_table_binding));

	if(sym_type == 0 || sym_type == 1 || sym_type == 2){ //an einai metavlhth
		newnode->value.var = malloc(sizeof(struct variable));
		newnode->value.var->name = malloc((strlen(name) + 1) * sizeof(char));
		strcpy(newnode->value.var->name, name);// newnode->value.var->name = name;
		newnode->value.var->line = line;
		newnode->symbol_type = sym_type;
		newnode->value.var->scope = scope;

	} else if(sym_type == 3 || sym_type == 4){ //an einai function
		newnode->value.func = malloc(sizeof(struct function));
		newnode->value.func->name = malloc((strlen(name) + 1) * sizeof(char));
		strcpy(newnode->value.func->name, name); //newnode->value.func->name = name;
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

/*checks if exists, returns 0 if exists
inserts in hash table if not*/
int check_if_exists(char *name, int scope) {
	struct symbol_table_binding *curr;
	int mapping = 0;
	// int counter2 = 0;

	assert(name);

	mapping = hash_function(name);
	curr = table->pinakas[mapping];
	while(curr) {
		if(strcmp(curr->value.func->name, name) == 0 && curr->active == 1) {
			// while(curr->value.func->args_list != NULL) {
			// 	counter2++;
			// 	curr->value.func->args_list = curr->value.func->args_list->next;
			// }
			// if(counter2 > args) {
			// 	printf("Function \"%s\" in line: %d has less arguments than the one defined at line: %d\n", name, yylineno, curr->value.func->line);
			// 	exit(EXIT_FAILURE);
			// }
			return 0;
		}
		curr = curr->next;
	}
	insert_hash_table(name, 3, yylineno, 1, scope);
	return 1;
}

/*
 * Return values:
 * 1 if it exists globally
 * 0 in any other case
 */
int global_exists(const char *name) {
	struct symbol_table_binding *curr;
	int mapping = 0;

	assert(name);

	mapping = hash_function(name);
	curr = table->pinakas[mapping];

	while(curr) {
		if (strcmp(curr->value.var->name, name) == 0) {
			if( curr->value.var->scope == 0) {
				return 1;
			}
		}
		curr = curr->next;
	}
	return 0;
}

/*
 * Return values:
 * 1 if it exists already in current scope
 * else 0
 */
int contains_Func(char *name, int scope) {
	struct symbol_table_binding *curr;
	int mapping = 0;

	assert(name);

	mapping = hash_function(name);
	curr = table->pinakas[mapping];

	while(curr) {
		if(strcmp(curr->value.func->name, name) == 0 && curr->value.func->scope == scope && curr->active == 1) {
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}

void hide_symbols(int scope){
	size_t i;
	for(i = 0; i < SIZE; i++ ){
	  	struct symbol_table_binding *curr = table->pinakas[i];
	  	while(curr != NULL){
			if(curr->value.var->scope == scope && curr->value.var->scope != 0 )	curr->active = false;
			curr = curr->next;
	  }
	}
}

int argumentF(char *name, int line, int scope) {
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

	newArg = malloc(sizeof(struct arguments));
	newArg->name = malloc((strlen(name) + 1) * sizeof(char));
	strcpy(newArg->name, name);
	newArg->next = NULL;

	tmp = table->pinakas[lastActiveFunc];
	if(tmp == NULL) {
		printf("Function you are trying to add formal argument doesnt exist, wtf.");
		exit(EXIT_FAILURE);
	}

	if(searchValue(tmp->value.func->args_list, name) == 1) {
		printf("Error: Duplicate argument: \"%s\" in function: \"%s\" in line: %d\n", name, tmp->value.func->name, yylineno);
	 	exit(EXIT_FAILURE);
	}

	newArg->next = table->pinakas[lastActiveFunc]->value.func->args_list;
	table->pinakas[lastActiveFunc]->value.func->args_list = newArg;

	insert_hash_table(newArg->name, 2, line, true, scope);

	return 0;
}

int newFunction(char* name , int line, int scope){
	struct symbol_table_binding *newnode;
	int mapping = 0;

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
	if(contains_Func(name, scope) == 1) {
		printf("Redefinition of \"%s\" in line: %d\n", name, yylineno);
		exit(EXIT_FAILURE);
	}

	mapping = hash_function(name);
	lastActiveFunc = mapping;

	newnode = malloc(sizeof(struct symbol_table_binding));
	newnode->value.func = malloc(sizeof(struct function));
	newnode->value.func->name = malloc((strlen(name) + 1) * sizeof(char));
	strcpy(newnode->value.func->name, name);
	newnode->value.func->line = line;
	newnode->value.func->scope = scope;
	newnode->value.func->args_list = NULL;
	newnode->active = 1;
	newnode->symbol_type = 3;
	newnode->accessible = 1;

	newnode->next = table->pinakas[mapping]; /*to bazw sthn arxh ths listas*/
	table->pinakas[mapping] = newnode;
	//table->total_size++;

	return 0;
}

/*
 * Function to check if there is
 * duplicate formal argument.
 * Return:
 * 1 on success, found this key.
 * 0 if head == NULL or if key not found.
 */
int searchValue(struct arguments *head, char *key) {
	struct arguments *curr = head;

	if(head == NULL) return 0;

	while(curr != NULL) {
		if(strcmp(curr->name, key) == 0) return 1;
		curr = curr->next;
	}

	return 0;
}


int insertVar(char* name , int line , int scope){
	int hash = 0, flag = 1;
	struct symbol_table_binding *curr, *tmp;
	//printf("searching name : %s , line %d , scope %d\n",name,line,scope );
	assert(table && name);

	if (scope == 0) flag = 0;

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
	hash = hash_function(name);//briskw pou kanei hash to stoixeio
	curr = table->pinakas[hash];//paw se ayth th thesh

	tmp = table->pinakas[lastActiveFunc];

	while (curr) {
		if(strcmp(name, curr->value.var->name) == 0 && curr->active == true && curr->symbol_type == flag && curr->value.var->scope == scope) {
		//	 printf("Reference to local var\n" );
			ref = 0;
			return 0;
		}
		curr = curr->next;
	}

	curr = table->pinakas[hash];

	while (curr) {
		if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 1 && curr->active == true && curr->symbol_type == 2 ) {

		//	printf("Reference to formal argument\n");
			ref = 0;
			return 0;
		}
		curr = curr->next;
	}

	curr = table->pinakas[hash];

	while (curr) {
		if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 0 && curr->active == true  && curr->value.var->scope != 0  ) {
				if(tmp != NULL) {
					if(tmp->value.func->scope < scope && tmp->value.func->scope >= curr->value.var->scope && curr->value.var->scope != 0) {
						printf("Cannot access \"%s\" defined in line: %d from line: %d\n", curr->value.var->name, curr->value.var->line, yylineno );
						exit(EXIT_FAILURE);
					}
				}
		//	printf("Reference to accessible var in another scope\n");
			return 0;
		}
		curr = curr->next;
	}

	curr = table->pinakas[hash];

	while (curr) {
//		printf("name %s active %d  , type %d , line %d \n",curr->value.var->name , curr->active ,curr->symbol_type ,curr->value.var->line  );
		if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 1 && curr->active == true  && curr->value.var->scope != 0 ) {
		//	printf("Reference to accessible var in another scope\n");
			return 0;
		}
		curr = curr->next;
	}

	curr = table->pinakas[hash];

	while (curr) {
		if(strcmp(name, curr->value.var->name) == 0 && curr->active == true && curr->value.var->scope == 0) {
		//	printf("Reference to global var\n");
			return 0;
		}
		curr = curr->next;
	}

// 	while(curr){
// //		printf("name %s active %d  , type %d , line %d \n",curr->value.var->name , curr->active ,curr->symbol_type ,curr->value.var->line  );
// 		if(strcmp(name, curr->value.var->name) == 0 && curr->active == true && curr->symbol_type == flag && curr->value.var->scope == scope) {
//
// //			 printf("Reference to local var\n" );
// 			ref = 0;
// 			return 0;
// 		} else if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 1 && curr->active == true && curr->symbol_type == 2 ) {
//
// //			printf("Reference to formal argument\n");
// 			ref = 0;
// 			return 0;
// 		} else if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 0 && curr->active == true  && curr->value.var->scope != 0  ) {
//
// 				if(tmp != NULL) {
// 					if(tmp->value.func->scope < scope && tmp->value.func->scope >= curr->value.var->scope && curr->value.var->scope != 0) {
// 						printf("Cannot access \"%s\" defined in line: %d from line: %d\n", curr->value.var->name, curr->value.var->line, yylineno );
// 						exit(EXIT_FAILURE);
// 					}
// 				}
//
// //			printf("Reference to accessible var in another scope\n");
// 			return 0;
// 		}  else if(strcmp(name, curr->value.var->name) == 0 && curr->accessible == 1 && curr->active == true  && curr->value.var->scope != 0 ) {
// //			printf("Reference to accessible var in another scope\n");
// 			return 0;
//
// 		} else if(strcmp(name, curr->value.var->name) == 0 && curr->active == true && curr->value.var->scope == 0) {
// //			printf("Reference to global var\n");
//
// 			return 0;
// 		}
//
// 		curr = curr->next;
// 	}
	insert_hash_table(name, flag, line, true, scope);
	return 1;
}

int localVar(char* name, int line, int scope){
	int flag = 1;
	struct symbol_table_binding *curr;
    int hash = 0;

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

	// elegxw an uparxeihdh to stoixeio pou thelw na prosthesw
    while(curr){
		if (strcmp(curr->value.var->name, name) == 0 && scope == curr->value.var->scope && curr->active == true ) {
			if (curr->symbol_type == 3 || curr->symbol_type == 4){
				printf("Conflicting types of \"%s\" in line: %d \n",name , yylineno );
				exit(EXIT_FAILURE);

			} else {
				ref = 0;
				return 0;
			}
		}
    	curr = curr->next;
    }
	ref = 0;
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

int free_table(void) {
	int i = 0;
	struct symbol_table_binding *curr, *prev;
	struct arguments *prev_arg;
	for(i = 0; i < SIZE; i++) {
		curr = table->pinakas[i];
		while(curr != NULL) {
			prev = curr;
			curr = curr->next;

			if(prev->symbol_type == 3) {
				while(prev->value.func->args_list != NULL)  {
					prev_arg = prev->value.func->args_list;
					prev->value.func->args_list = prev->value.func->args_list->next;
					free(prev_arg);
				}

				free(prev->value.func->name);
				free(prev->value.func);
			} else {
				free(prev->value.var->name);
				free(prev->value.var);
			}

			free(prev);
		}
	}
	free(table->pinakas);
	table->pinakas = NULL;

	free(table);
	table = NULL;

	return 1;
}

void free_list() {
	struct alpha_token_t *prev = NULL;

	while(head != NULL) {
		prev = head;
		head = head->next;
		free(prev->value);
		free(prev);
	}
}
/*prints table*/
int print_table(){
  	size_t i = 0, scope = 0;
	struct symbol_table_binding *curr = NULL;

  	if(table == NULL){
    	printf("Table is empty\n");
    	return 0;
  	}

	printf("\n\"NAME\"   [TYPE]    (LINE)   (SCOPE)\n");
	for(scope = 0; scope <= maxScope; scope++) {
		printf("----------Scope #%lu ----------", scope);
		for(i = 0; i < SIZE; i++) {
			curr = table->pinakas[i];
			while(curr != NULL) {
				if((curr->symbol_type == 0 || curr->symbol_type == 1 || curr->symbol_type == 2) && curr->value.var->scope == scope )
      				printf("\n \"%s\" [%s variable] (line %d) (scope %d)", curr->value.var->name, enum_toString(curr->symbol_type), curr->value.var->line, curr->value.var->scope);

				if((curr->symbol_type == 3 || curr->symbol_type == 4) && curr->value.func->scope == scope ) {
			 		printf("\n \"%s\" [%s function] (line %d) (scope %d)", curr->value.func->name, enum_toString(curr->symbol_type), curr->value.func->line, curr->value.func->scope);
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
		printf("\n\n");
	}
	printf("---------------END------------\n");
	return 1;
}

int main(void) {

	table = malloc(sizeof(struct SymTable_struct));

	table->pinakas = malloc(SIZE* sizeof(struct symbol_table_binding *));//oxi calloc, tha to diorthwsw kapoia stigmh
	table->total_size = 0;

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
	print_list_rvalues();
	return 0;
}
