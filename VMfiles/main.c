
#include "phase5.h"




int main(int argc, char const *argv[]) {
//printf("vm:: cos %f\nsin %f\n",libfunc_cos(90),libfunc_sin(0) );
//printf("sqrt %f\n", libfunc_sqrt(144));
//printf("str to num %f\n",libfunc_strtonum("56") );
namedLibfuncs=malloc(sizeof(char*)*12);
add_consts_libfuncs("print");
add_consts_libfuncs("input");
add_consts_libfuncs("objectmemberkeys");
add_consts_libfuncs("objecttotalmembers");
add_consts_libfuncs("objectcopy");
add_consts_libfuncs("totalarguments");
add_consts_libfuncs("argument");
add_consts_libfuncs("typeof");
add_consts_libfuncs("strtonum");
add_consts_libfuncs("sqrt");
add_consts_libfuncs("cos");
add_consts_libfuncs("sin");

read_binfile();
avm_initstack();
	//register all libfuncs with avm_registerlibfunc

	while (!executionFinished) {
	//	printf("executionFinished 0\n" );
		execute_cycle();
//		printf("pc is now %d\n",pc );
	}
//	printStack();

	return 0;
}
