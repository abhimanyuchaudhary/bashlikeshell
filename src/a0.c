#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
int max(int a, int b) {
	if (a > b)
		return a;
	return b;
}
int main(){

	int numCommands = 0;
	char cwd[1000];
	getcwd(cwd, sizeof(cwd));
	char history[1000][1000];
	char homedir[1000];
	strcpy(homedir, cwd);

	char pathToRm[100];
	char pathToMkdir[100];
	char pathToLs[100];
	char pathToCat[100];
	char pathToDate[100];

	strcpy(pathToDate, cwd);
	strcpy(pathToRm, cwd);
	strcpy(pathToMkdir, cwd);
	strcpy(pathToLs, cwd);
	strcpy(pathToCat, cwd);

	strcat(pathToDate, "/");
	strcat(pathToRm, "/");
	strcat(pathToMkdir, "/");
	strcat(pathToLs, "/");
	strcat(pathToCat, "/");

	strcat(pathToDate, "date.out");
	strcat(pathToRm, "rm.out");
	strcat(pathToMkdir, "mkdir.out");
	strcat(pathToLs, "ls.out");
	strcat(pathToCat, "cat.out");


	while(1){

		//Reading the input//
		printf("%s ", "$");
		char input[1000];
		gets(input);
		if(!strcmp(input, "")){
			continue;
		}
		strcpy(history[numCommands++], input);
		char *command[1000];
		int temp = 0;
		char *pch;
		
		pch = strtok (input," ");
		int numArg = 0;
	    while (pch != NULL)
	    {
	        command[temp++] = pch;
	        pch = strtok (NULL, " ");
	        numArg ++;
	    }
	    command[temp] = NULL;
	    // printf("%d\n %s %s", numArg, command[0], command[1]);

		//----Finished Reading the input ------//
		
		//Executing the commands//
		if(!strcmp(command[0], "quit")) {
			break;
		}
		else if(!strcmp(command[0], "cd")) {//implement home directory
			// printf("%d\n", numArg);
			if(numArg > 2) {
				printf("%s\n", "Invalid format");
			}
			else {
				if(numArg == 1 || !strcmp(command[1], "~")) {
					chdir(homedir);
					getcwd(cwd, sizeof(cwd));
				}
				else if(!strcmp(command[1], "-")) {
					printf("%s\n", homedir);
					chdir(homedir);
					getcwd(cwd, sizeof(cwd));
				}
				else {
					int x = chdir(command[1]);
					if(errno == ENOENT){
						printf("%s\n", "Directory doesn't exist");
					}
					else if(errno == ENOTDIR) {
						printf("%s\n", "Not a directory");
					}
					else{
						getcwd(cwd, sizeof(cwd));
					}
				}
				
			}
			

		}
		else if(!strcmp(command[0], "echo")) { // do -e
			int flag = 1;
			if(!strcmp(command[1], "-n")) {
				flag = 2;
			}
			for(int i = flag; i < temp; i++) {
				printf("%s ", command[i]);
			}
			if(flag == 1)
				printf("\n");
			
		}
		else if(!strcmp(command[0], "history")) {
			int start = 10000;
			if(numArg > 2) {
				printf("%s\n", "Incorrect usage: history [-c] [offset]");
			}
			else if(command[1] != NULL) {
				if(!strcmp(command[1], "-c")) {
					numCommands = 1;
					strcpy(history[0], "history");
				}
				else {
					start = atoi(command[1]);
					if(start < 1) {
						printf("%s\n", "Incorrect usage: history [-c] [offset]");
					}
				}
			}
			start = max(0, numCommands - start);
			for(int i = start; i < numCommands; i++) {
				printf("%s\n", history[i]);
			}
			
		}
		else if(!strcmp(command[0], "pwd")) { // -L and -P idk what they do
			// printf("%s\n", cwd);
			printf("%s\n", cwd);
		}
		else if(!strcmp(command[0], "cat")){
			int flag = fork();
			if(!flag){
				// char temp[10000];
				// strcpy(temp, cwd);
				// strcat(temp, "/");
				// strcat(temp, command[numArg - 1]);
				// strcpy(command[numArg - 1], temp);
				execv(pathToCat, command);
			}
			wait(0);
		}
		else if(!strcmp(command[0], "date")){
			int flag = fork();
			if(!flag){
				execv(pathToDate, command);
			}
			wait(0);
			
		}
		else if(!strcmp(command[0], "mkdir")){
			int flag = fork();
			if(!flag){
				// char temp[1000];
				// strcpy(temp, cwd);
				// strcat(temp, "/");
				// strcat(temp, command[numArg - 1]);
				// strcpy(command[numArg - 1], temp);
				execv(pathToMkdir, command);
			}
			wait(0);

		}
		else if(!strcmp(command[0], "rm")){// check if it needs to be implemented like mkdir and cat the prefix ting
			int flag = fork();
			if(!flag){
				// char temp[1000];
				// strcpy(temp, cwd);
				// strcat(temp, "/");
				// strcat(temp, command[numArg - 1]);
				// strcpy(command[numArg - 1], temp);
				execv(pathToRm, command);
			}
			wait(0);
			
		}
		else if(!strcmp(command[0], "ls")){
			int flag = fork();
			if(!flag){
				execv(pathToLs, command);
			}
			wait(0);
			
		}

		else {
			printf("%s\n", "Invalid command");
			continue;
		}

	}
	
	return 0;
}