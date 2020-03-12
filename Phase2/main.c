#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

extern struct alpha_token_t * alpha_yylex();
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern int token_count;

//------------------------- LEX ----------------------------
void print_table();

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
//		printf("going to the end of the list !!!\n");
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
    int scope;
    struct symbol_table_binding *next;
};

struct SymTable_struct { /*TABLE*/
    struct symbol_table_binding **pinakas;
    int total_size;

};

struct SymTable_struct *table = NULL;

int SymTable_contains(struct SymTable_struct *table, const char *name, symtype sym_type, int line, int scope);
void print_table();

/*void insert_symtable_binding(const char* name, symtype sym_type, int line, int scope){
    struct symbol_table_binding *tmp = (struct symbol_table_binding *) malloc(sizeof(struct symbol_table_binding));
    tmp->symbol_name = name;
    tmp->symbol_type = sym_type;
    tmp->line_definition = line;
    tmp->scope = scope;
    tmp->next = NULL;

    if(head_table == NULL) head_table = tmp;
  	else {
  		struct symbol_table_binding* curr = head_table;
  		while(curr->next) curr = curr->next;  //proxwraw mexri to telos th lista
  		curr->next = tmp;
  	}

}
*/

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
int insert_hash_table(const char* name, symtype sym_type, int line, int scope){
  /*an den uparxei ftiagmeno table, to ftiaxnw*/
  if(table == NULL){
      table = malloc(sizeof(struct SymTable_struct *));

      table->pinakas = malloc(100*sizeof(struct symbol_table_binding*));
      table->total_size = 0;
  }

  int mapping = 0;
  struct symbol_table_binding *newnode;
  assert(table && name);

  if(SymTable_contains(table, name, sym_type, line, scope) == 1
          || SymTable_contains(table, name, sym_type, line, scope) == 2)  return 0;

  mapping = hash_function(name);

  newnode = (struct symbol_table_binding *) malloc(sizeof(struct symbol_table_binding));
  newnode->symbol_name = name;
  newnode->symbol_type = sym_type;
  newnode->line_definition = line;
  newnode->scope = scope;


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
int SymTable_contains(struct SymTable_struct *table, const char *name, symtype sym_type, int line, int scope){
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
                      check_existance->scope == scope ) return 1;/*uparxei akribws idio*/

            return 2; /*uparxei to idio name alla oxi idia ta upoloipa*/
            }
            check_existance=check_existance->next;
    }

    return 0;

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

int main(void) {
printf("oh hi parser\n");

/*init library functions = 3 */
insert_hash_table("print", 3 , 0, 0);
insert_hash_table("input", 3 , 0, 0);
insert_hash_table("objectmemberkeys", 3 , 0, 0);
insert_hash_table("objecttotalmembers", 3 , 0, 0);
insert_hash_table("objectcopy", 3 , 0, 0);
insert_hash_table("totalarguments", 3 , 0, 0);
insert_hash_table("argument", 3 , 0, 0);
insert_hash_table("typeof", 3 , 0, 0);
insert_hash_table("stronum", 3 , 0, 0);
insert_hash_table("sqrt", 3 , 0, 0);
insert_hash_table("cos", 3 , 0, 0);
insert_hash_table("sin", 3 , 0, 0);

//print_table();

return yyparse();
}
/*int main(int argc, char *argv[]) {
	FILE *file;

	if(argc > 1) {
		if(!(file = fopen(argv[1], "r"))) {
			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
		} else {
			yyin = file;
		}
		//alpha_yylex(NULL);
		struct alpha_token_t* ntoken = alpha_yylex(NULL);
	        while( ntoken ){
//			printf("INT TOKEN %d \n", ntoken);
			printf("MAAAAAAINN %d:     #%d      \"%s\"    %s\n", ntoken->line, ntoken->token_no, ntoken->value, ntoken->type);
        	        ntoken = alpha_yylex(NULL);
	        }


		print_list();
		fclose(file);
	} else {

		yyin = stdin;
		alpha_yylex(NULL);
	}

	return 0;
}
*/
