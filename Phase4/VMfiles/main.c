
#include "phase5.h"




int main(int argc, char const *argv[]) {
//printf("vm:: cos %f\nsin %f\n",libfunc_cos(90),libfunc_sin(0) );
//printf("sqrt %f\n", libfunc_sqrt(144));
//printf("str to num %f\n",libfunc_strtonum("56") );
read_binfile();
avm_initstack();
	//register all libfuncs with avm_registerlibfunc

	while (!executionFinished) {
	//	printf("executionFinished 0\n" );
		execute_cycle();
		printf("pc is now %d\n",pc );
	}
	printStack();

	return 0;
}
