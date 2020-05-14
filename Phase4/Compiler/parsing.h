#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define SIZE 101	/* hash table buckets size */

/*enum for symbol type*/
typedef enum {
	global 		= 0,
	local 		= 1,
    formal 		= 2,
    user 		= 3,
    library 	= 4
} symtype;


typedef enum {
	program_var = 0,
	formal_arg = 1,
	function_loc = 2

} symbol_space;


struct arguments {
	char 				*name;
	struct arguments 	*next;
};

typedef struct variable{
    char			*name;
	unsigned int 	line;
	unsigned int 	scope;
	int 			offset;
} variable;

typedef struct function {
    char				*name;
	unsigned int 		line;
	unsigned int 		scope;
	int 				totalVars;
	int					funcAddress;
 	struct arguments 	*args_list;
} function;

struct symbol_table_binding{ /*NODE OF THE TABLE*/
    symtype 		symbol_type;
    union{
		variable 	*var;
		function 	*func;
	} value;
	bool 			active;
	bool 			accessible ;

	symbol_space scope_space;

  struct symbol_table_binding *next;
};

struct SymTable_struct { /*TABLE*/
    struct symbol_table_binding **pinakas;
    int total_size;
};



int argumentF(char *name, int line, int scope);
struct symbol_table_binding * newFunction(char* name, int line,int tmpscope);
int searchValue(struct arguments *head, char *key);
int insertLocalVar(char* name, int line, int scope);
void make_not_accessible(int curr_scope);
void make_accessible_again(int curr_scope);
int hash_function(const char *name);
int check_for_funcname(const char *name);
struct symbol_table_binding* insert_hash_table(char *name, symtype sym_type, int line, bool active, int scope);
int check_if_exists(char *name, int scope);
struct symbol_table_binding* global_exists(const char *name);
int contains_Func(char *name, int scope);
void hide_symbols(int scope);
struct symbol_table_binding* insertVar(char* name , int line , int scope);
struct symbol_table_binding* localVar(char* name, int line, int scope);
char* enum_toString(symtype sym);
char* enum_toString_symbolSpace(symbol_space sym);
int free_table(void);
void free_list();
int print_table();
