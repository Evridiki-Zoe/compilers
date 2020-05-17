
#include "phase5.h"





int main(int argc, char const *argv[]) {

	avm_initstack();

	//register all libfuncs with avm_registerlibfunc

	while (!executionFinished) {
		execute_cycle();
	}

	return 0;
}
