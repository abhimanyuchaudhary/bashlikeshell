#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

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
int main(int argc, char *argv[]){//make flags -d: deleted directory if expty; -i confirms before delting

	// if(remove(argv[1])) {
	// 	printf("%s\n", "no");
	// }
	// return 0;
	if(argc == 2) {
		if(isFile(argv[1])) {
			// remove(argv[1]);
			if(remove(argv[1])) {
				printf("%s\n", "file doesn't exist");
			}
		}
		else {
			printf("%s\n", "Can't delete directory");
		}
	}
	else if(argc == 3) {
		if(!strcmp(argv[1], "-d")) {
			if(remove(argv[2])) {
				printf("%s\n", "Unable to delete file");
			}
		}
		else if(!strcmp(argv[1], "-i")) {
			char in[10];
			printf("%s\n", "Are you sure you want to delete y/n");
			scanf("%s", in);
			if(!isFile(argv[2])) {
				printf("%s\n", "This is a directory use -d");
				return 0;
			}
			if(!strcmp(in, "y") || !strcmp(in, "Y") || !strcmp(in, "yes")) {
				if(remove(argv[2])) {
					printf("%s\n", "File doesn't exist");
				}
			}
			else if(!strcmp(in, "n") || !strcmp(in, "N") || !strcmp(in, "no")) {
				return 0;
			}
			else {
				printf("%s\n", "invalid option");
				return 0;
			}
		}
		else {
			printf("%s\n", "Invalid usage: rm [-i] [-d] [filename]");
		}
	}
	else if(argc == 4) {
		if(!( (!strcmp(argv[1], "-d") || !strcmp(argv[1], "-i")) && (!strcmp(argv[2], "-d") || !strcmp(argv[2], "-i")) ) ) {
			printf("%s\n", "Invalid usage: rm [-i] [-d] [filename]");
		}
		else {
			char in[10];
			printf("%s\n", "Are you sure you want to delete y/n");
			scanf("%s", in);
			if(!strcmp(in, "y") || !strcmp(in, "Y") || !strcmp(in, "yes")) {
				if(remove(argv[3])) {
					printf("%s\n", "Unable to delete file");
				}
			}
			else if(!strcmp(in, "n") || !strcmp(in, "N") || !strcmp(in, "no")) {
				return 0;
			}
			
		}
	}

	printf("\n");
	return 0;
}