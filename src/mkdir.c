#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
int main(int argc, char *argv[]){ 

	int fileStart = 1;
	int flagV = 0;
	int flagP = 0;
	for( ; fileStart < argc; fileStart++) {
		if(!strcmp("-v", argv[fileStart])) {
			flagV = 1;
		}
		if(!strcmp("-p", argv[fileStart])) {
			flagP = 1;
		}
	}
	for(int i = flagP + flagV + 1; i < argc; i++) {
		int result = mkdir(argv[i], 0777);
		if(result == -1 && flagP == 0) {
			printf("%s\n", "Can't make directory");
		}
		if(flagV == 1) {
			printf("%s %s\n", "Directory created", argv[i]);
		}
	}
	printf("\n");
 	return 0;
}