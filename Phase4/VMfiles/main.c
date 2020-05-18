
#include "phase5.h"




int main(int argc, char const *argv[]) {
printf("vm:: \n" );
	avm_initstack();
read_binfile();
	//register all libfuncs with avm_registerlibfunc

	while (!executionFinished) {
		printf("executionFinished 0\n" );
		execute_cycle();
	}

	return 0;
}
