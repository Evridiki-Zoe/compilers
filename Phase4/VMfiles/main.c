
#include "phase5.h"




int main(int argc, char const *argv[]) {
printf("vm:: \n" );

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
