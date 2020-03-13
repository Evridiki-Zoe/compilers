#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

extern struct alpha_token_t * alpha_yylex();
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern int token_count;
extern int global_scope; // current scope we are right now, as we do the syntactic analysis

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
      variable = 0,
      typical_function_argument = 1,
      user_func = 2,
      lib_func = 3
    } symtype;


struct symbol_table_binding{ /*NODE OF THE TABLE*/
    const char* symbol_name;
    symtype symbol_type;
    int line_definition;
		bool active;
		int scope;
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
          uiHash =uiHash* 65599+ name[ui];

  return uiHash% 100 ;
}

/*creates a new table if NULL
and inserts symbol in table*/
int insert_hash_table(const char* name, symtype sym_type, int line,bool active, int scope){
  /*an den uparxei ftiagmeno table, to ftiaxnw*/
  if(table == NULL){
      table = malloc(sizeof(struct SymTable_struct *));

      table->pinakas = malloc(100*sizeof(struct symbol_table_binding*));
      table->total_size = 0;
  }

  int mapping = 0;
  struct symbol_table_binding *newnode;
  assert(table && name);

  if(SymTable_contains(table, name, sym_type, line, active, scope) == 1
          || SymTable_contains(table, name, sym_type, line, active, scope) == 2)  return 0;

  mapping = hash_function(name);

  newnode = (struct symbol_table_binding *) malloc(sizeof(struct symbol_table_binding));
  newnode->symbol_name = name;
  newnode->symbol_type = sym_type;
  newnode->line_definition = line;
  newnode->scope = scope;
  newnode->active = active;

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

    hash=hash_function(name);/*briskw pou kanei hash to stoixeio*/
    check_existance= table->pinakas[hash];/*paw se ayth th thesh*/

    /*elegxw an uparxeihdh to stoixeio pou thelw na prosthesw*/
    while(check_existance){
            if(strcmp(check_existance->symbol_name, name)==0 ){
                if(check_existance->symbol_type == sym_type &&
                      check_existance->line_definition == line &&
											check_existance->active == active &&
                      check_existance->scope == scope ) return 1;/*uparxei akribws idio*/

            return 2; /*uparxei to idio name alla oxi idia ta upoloipa*/
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

	hash=hash_function(name);/*briskw pou kanei hash to stoixeio*/
	tmp = table->pinakas[hash];/*paw se ayth th thesh*/

	while(tmp){
					if(strcmp(tmp->symbol_name, name)==0 &&
										tmp->symbol_type == sym_type &&
										tmp->line_definition == line &&
										tmp->active == active &&
										tmp->scope == scope ) tmp->active = false; /*set active status to false*/

					tmp=tmp->next;
	}

}

/*prints table*/
void print_table(){
  int i = 0;
  if(table == NULL){
    printf("table is empty");
    return ;
  }

  for(i = 0; i < 100; i++ ){
    printf("printing %d list \n", i);
    struct symbol_table_binding * curr = table->pinakas[i];
    while(curr != NULL){
      printf("name: %s", curr->symbol_name);
      curr = curr-> next;
    }
    printf("\n");
  }
}
