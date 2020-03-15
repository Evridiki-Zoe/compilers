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


extern char** argtable;
extern int numOfArgs;
void print_table();
void arginsert(char* arg);
void newFunction(char* name, int line,int tmpscope);

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
	global = 0,
	local = 1,
    formal = 2,
    user = 3,
    library = 4
} symtype;


struct arguments {
	const char * name;
	struct arguments *next;
};

typedef struct variable{
    const char* name;
		unsigned int line;
		unsigned int scope;

}variable;

typedef struct function{
    const char* name;
		unsigned int line;
		unsigned int scope;
		///struct arguments *args_list;

}function;

struct symbol_table_binding{ /*NODE OF THE TABLE*/
    symtype symbol_type;
    union{
		variable *var;
		function *func;
	} value;
	bool active;
    struct symbol_table_binding *next;
};

struct SymTable_struct { /*TABLE*/
    struct symbol_table_binding **pinakas;
    int total_size;

};

struct SymTable_struct *table = NULL;

int SymTable_contains(struct SymTable_struct *table, const char *name, symtype sym_type, int line, bool active, int scope);
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
  /*an den uparxei ftiagmeno table, to ftiaxnw*/
  if(table == NULL){
      table = malloc(sizeof(struct SymTable_struct *));

      table->pinakas = malloc(100*sizeof(struct symbol_table_binding*));
      table->total_size = 0;
  }

  int mapping = 0;
  struct symbol_table_binding *newnode;
  assert(table && name);

  if(SymTable_contains(table, name, sym_type, line, active, scope) == 1 ||
			SymTable_contains(table, name, sym_type, line, active, scope) == 2)  {printf("%s already exists\n", name );return 0;}

  mapping = hash_function(name);

  newnode = (struct symbol_table_binding *) malloc(sizeof(struct symbol_table_binding));

	if(sym_type == 0 || sym_type == 1 || sym_type == 2){ //an einai metavlhth
	    newnode->value.var = (struct variable *)malloc(sizeof(struct variable));
			newnode->value.var->name = (char *)malloc(sizeof(char));
			newnode->value.var->name = name;
	  newnode->value.var->line = line;
		  newnode->value.var->scope = scope;

	}
	else if(sym_type == 3 || sym_type == 4){ //an einai function
  		newnode->value.func = (struct function *) malloc(sizeof(struct function));
			newnode->value.func->name = (char *)malloc(sizeof(char));
			newnode->value.func->name = name;
		  newnode->value.func->line = line;
		  newnode->value.func->scope = scope;
		//	newnode->value.var->args_list = NULL;
	}

  newnode->active = active;
	newnode->symbol_type = sym_type;

  newnode->next = table->pinakas[mapping]; /*to bazw sthn arxh ths listas*/
  table->pinakas[mapping] = newnode;
  table->total_size++;

  return 1;
}

/* checks if symbol already exists in table
returns 1 if symbol exists everything exactly the same
returns 2 if symbol exists only name the same!
returns 0 if it doesn't exist
*/
int SymTable_contains(struct SymTable_struct *table, const char *name, symtype sym_type, int line,bool active, int scope){
    struct symbol_table_binding *check_existance;
    int hash=0;
    assert(table && name);

    hash=hash_function(name);//briskw pou kanei hash to stoixeio
    check_existance= table->pinakas[hash];//paw se ayth th thesh

		//elegxw an uparxeihdh to stoixeio pou thelw na prosthesw
    while(check_existance){
				if(sym_type == 0 || sym_type == 1 || sym_type == 2){
			      if(strcmp(check_existance->value.var->name, name)==0 ){
							  if(check_existance->symbol_type == sym_type &&
								check_existance->value.var->line == line &&
							  check_existance->active == active &&
								check_existance->value.var->scope == scope)  return 1;//uparxei akribws idio

					  	return 2; //uparxei to idio name alla oxi idia ta upoloipa

							}
		      }
					else if(sym_type == 3 || sym_type == 4 ){
						if(strcmp(check_existance->value.func->name, name)==0 ){
								if(check_existance->symbol_type == sym_type &&
								check_existance->value.func->line == line &&
								check_existance->active == active &&
								check_existance->value.func->scope == scope)  return 1;//uparxei akribws idio

								return 2; //uparxei to idio name alla oxi idia ta upoloipa

							}

					}
      check_existance=check_existance->next;
    }

    return 0;

}

/* MPOREI NA THELEI DIORTHWSH !!!!!!!
finds symbol and sets active status to false*/
void hide_symbol(struct SymTable_struct *table, const char *name, symtype sym_type, int line,bool active, int scope){
	struct symbol_table_binding *tmp;
	int hash=0;
	assert(table && name);

	if(SymTable_contains(table, name, sym_type, line, active, scope) == 0) return; //it doesnt exist

	hash=hash_function(name);//briskw pou kanei hash to stoixeio
	tmp = table->pinakas[hash];//paw se ayth th thesh

	while(tmp){
		if( strcmp(tmp->value.func->name, name)==0 &&
				tmp->symbol_type == sym_type &&
				tmp->value.func->line == line &&
				tmp->active == active &&
				tmp->value.func->scope == scope) tmp->active = false; //set active status to false

				tmp=tmp->next;
	}

}

void arginsert(char *arg){
	//TODO
	/*
	Idanika realloc kai static metavliti gia itterate (allios pointers). tora mexri 4 orismata.
	*/
	if (numOfArgs==0) {
			argtable = (char**)malloc(4*sizeof(char*));
		int i = 0;	
		for (i = 0; i < 4; i++) {
				argtable[i]=(char*)malloc(255*sizeof(char));

			}
			strcpy(argtable[0],arg);
      insert_hash_table(arg ,2,666,true,666);

	}
  else{

		strcpy(argtable[numOfArgs],arg);
    insert_hash_table(arg ,2,666,true,666);

	}
  	numOfArgs++;
}

void newFunction(char* name , int line, int tmpscope){
	//TODO
	//For loop me contains gia numOfArgs kai afto mesa se else
	//To scope to pernao gia asfaleia apo otan to vriskei
	insert_hash_table(name,3,line,true,tmpscope); //Thelei kai ton pinaka argtable.

  /*psaxnw ta pseudo-arg pou evala prin kai tous bazw swsta line kai Scope*/
  int i = 0;
  for (i = 0; i < numOfArgs; i++) {

    int mapping = hash_function(argtable[i]);
    struct symbol_table_binding *tmp = table->pinakas[mapping];//paw se ayth th thesh
    while(tmp){
      if(tmp->symbol_type == 2 && strcmp(tmp->value.var->name,argtable[i])==0 && tmp->value.var->scope == 666 && tmp->value.var->line == 666){
			    tmp->value.var->line = line;
          tmp->value.var->scope = (tmpscope+1);
          break;
      }
      tmp = tmp->next;
    }

  }

  /*re malaka pernas pointer se ayto ton pinaka kai meta pas kai ton kaneis free ???? */
  int j = 0;
	for (j = 0; j< 4; j++) {	// mexri numOfArgs kanonika
		free(argtable[j]);
	}
	free(argtable);
	numOfArgs=0;


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
  	int i = 0;
  	if(table == NULL){
    	printf("table is empty\n");
    	return ;
  	}

	printf("\n");
	int scope = 0;
	for(scope = 0; scope < 10; scope++) {
		printf("----------Scope #%d ----------", scope);
		for(i = 0; i < 100; i++) {
			struct symbol_table_binding *curr = table->pinakas[i];
			while(curr != NULL) {
				if((curr->symbol_type == 0 || curr->symbol_type == 1 || curr->symbol_type == 2) && curr->value.var->scope == scope )
      				printf("\n \"%s\" [%s variable] (line %d) (scope %d) ", curr->value.var->name, enum_toString(curr->symbol_type), curr->value.var->line, curr->value.var->scope);

				  if((curr->symbol_type == 3 || curr->symbol_type == 4) && curr->value.func->scope == scope )
			 		printf("\n \"%s\" [%s function] (line %d) (scope %d) ", curr->value.func->name, enum_toString(curr->symbol_type), curr->value.func->line, curr->value.func->scope);

				// if(curr->value.func->scope == 0 || curr->value.var->scope == 0) {
				// 	printf("\"%s\" [%s function] (line %d) (scope %d)\n", curr->value.func->name);
				// }
				curr = curr-> next;
			}
		}
		printf("\n");
	}

//   for(i = 0; i < 100; i++ ){
//     printf("%d::		", i);
//     struct symbol_table_binding *curr = table->pinakas[i];
//     while(curr != NULL){
// 			if(curr->symbol_type == 0 || curr->symbol_type == 1 || curr->symbol_type == 2)
//       			printf("VARIABLE name: %s, line: %d, scope: %d ", curr->value.var->name, curr->value.var->line, curr->value.var->scope);
// 		  if(curr->symbol_type == 3 || curr->symbol_type == 4)
// 			 			printf("FUNCTION name: %s, line: %d, scope: %d ", curr->value.func->name, curr->value.func->line, curr->value.func->scope);
//       curr = curr-> next;
//     }
//     printf("\n");
//   }
}
