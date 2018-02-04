#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdlib.h>
int isFile(char *name) {
    DIR* fname = opendir(name);
    if(fname != NULL) {
        closedir(fname);
        return 0;
    }
    else {
        return 1;
    }
}
int main(int argc, char *argv[]){

	
	int fileStart = 1;
	for( ; fileStart < argc; fileStart++) {
		if(strcmp(argv[fileStart], "-n") && strcmp(argv[fileStart], "-b")) {
			break;
		}
	}
	if(fileStart == 3) {
		printf("%s\n", "Invalid usage: cat [-n] or [-b] but not both");
		return 0;
	}
	for(int i = fileStart; i < argc; i++) {
		// char temp[10000];
		// strcpy(temp, cwd);
		// strcat(temp, "/");
		// strcat(temp, command[i]);
		// strcpy(command[i], temp);
		if(!isFile(argv[i])) {
			printf("%s\n", "Not a file");
		}
		else {
			int counter = 0;
			char str[1000];
			FILE *file;
			file = fopen(argv[i], "rt");
			// printf("%s\n", argv[argc - 1]);
			if(file){
				while(fgets(str, 1000, file) != NULL){
					if(!strcmp(argv[1], "-n"))
						printf("%d %s", ++counter, str);
					else if(!strcmp(argv[1], "-b")) {
						if(strcmp(str, "\n")) {
							printf("%d %s", ++counter, str);
						}
						else {
							printf("\n");
						}
					}

					else {
						printf("%s", str);
					}
				}
			}
			else{
				printf("%s\n", "Error: File not found");
			}
		}
		

	}
	
	
	printf("\n");
	return 0;
}