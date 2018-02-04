#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
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
	DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    int mflag = 0;
    int pflag = 0; 
    int invalidFile = 0;
    if(argc == 1){
        char temp[100];
        getcwd(temp, sizeof(temp));
        mydir = opendir(temp);
    }
    else if(argc == 2) {
        if(!strcmp(argv[1], "-m")) {
            mflag = 1;
            char temp[100];
            getcwd(temp, sizeof(temp));
            mydir = opendir(temp);
        }
        else if(!strcmp(argv[1], "-p")) {
            pflag = 1;
            char temp[100];
            getcwd(temp, sizeof(temp));
            mydir = opendir(temp);
        }
        else {
            mydir = opendir(argv[1]);
            if(mydir == NULL) {
                printf("%s\n", "Can't open directory/file");
                return 0;
            }
        }
    }
    else if(argc == 3) {
        
        if( !strcmp(argv[1], "-p") && strcmp(argv[2], "-m")) {
            pflag = 1;
            mydir = opendir(argv[2]);
            if(mydir == NULL) {
                printf("%s %s\n", "Can't open directory/file", argv[2]);
                return 0;
            }

        }
        else if( !strcmp(argv[1], "-m") && strcmp(argv[2], "-p")) {
            mflag = 1;
            mydir = opendir(argv[2]);
            if(mydir == NULL) {
                printf("%s %s\n", "Can't open directory/file", argv[2]);
                return 0;
            }
        }
        else if( (strcmp(argv[1], "-p") && strcmp(argv[1], "-m") ) || ( strcmp(argv[2], "-p") && strcmp(argv[2], "-m") )) {
            printf("%s\n", "Invalid usage: use ls [-p] [-m] [directory]");
            return 0;
        }
        else {
            pflag = 1;
            mflag = 1;
            char temp[100];
            getcwd(temp, sizeof(temp));
            mydir = opendir(temp);
        }
    }
    else if(argc == 4) {
        if( (strcmp(argv[1], "-p") && strcmp(argv[1], "-m") ) || ( strcmp(argv[2], "-p") && strcmp(argv[2], "-m") )) {
            printf("%s\n", "Invalid usage: use ls [-p] [-m] [directory]");
            return 0;
        }
        else {
            pflag = 1;
            mflag = 1;
            mydir = opendir(argv[3]);
            if(mydir == NULL) {
                printf("%s\n", "Can't open directory/file");
                return 0;
            }
            
        }

    }
    else {
        printf("%s\n", "Invalid usage: use ls [-p] [-m] [directory]");
    }
    char fileName[1000][1000];
    int counter = 0;
    while((myfile = readdir(mydir)) != NULL)
    {
        strcpy(fileName[counter], myfile -> d_name);
        counter++;
    }
    qsort(fileName, counter, sizeof(fileName[0]), (int (*)(const void*, const void*))strcmp);
    for(int i = 0; i < counter; i++) {
        // printf("%d, %d\n", mflag, pflag);
        if(mflag == 1 && pflag == 1) {
            if(!isFile(fileName[i]))
                printf("%s/, ", fileName[i]);
            else
                printf("%s, ", fileName[i]);
        } 
        else if(pflag == 1) {
            if(!isFile(fileName[i]))
                printf("%s/\n", fileName[i]);
            else
                printf("%s\n", fileName[i]);
        }
        else if(mflag == 1) {
            printf("%s, ", fileName[i]);
        }
        else
            printf("%s\n", fileName[i]);

    }
    if(mflag == 1 || mflag + pflag == 0) {
        printf("\n");
    }
    closedir(mydir);
	return 0;
}