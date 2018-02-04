#include <stdio.h>
#include <time.h>
#include <string.h>
int main(int argc, char *argv[]){ // make flags +%b +%B -> returns month, +%D mmddyy +%f yymmdd

	time_t t = time(NULL);

	struct tm tm = *localtime(&t);

	char *monthsFull[13] = {"Invalid", "January", "Febuary", "March", "April", "May", "June", "July",
							"August", "September", "October", "November", "December"};
	char *monthsHalf[13] = {"Invalid", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug"
							"Sep", "Oct", "Nov", "Dec"};
	char *weekday[7] = {"Sun", "Mon", "Tue", "Wed", "Thur", "Fri", "Sat"};


	if(argc == 1) {
		printf("%s-%d-%d-%d-%d %d:%d:%d\n",  weekday[tm.tm_wday], tm.tm_wday, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	}
	if(argc == 3) {
		printf("%s\n", "Invalid usage: date [+%b / +%B] [+%D] [+%F]");
		return 0;
	}
	if(!strcmp(argv[1], "+%b")) {
		printf("%s\n", monthsHalf[tm.tm_mon + 1]);
		return 0;
	}
	else if(!strcmp(argv[1], "+%B")) {
		printf("%s\n", monthsFull[tm.tm_mon + 1]);
		return 0;
	}
	else if(!strcmp(argv[1], "+%D")) {
		printf("%d/%d/%d\n", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900 - 2000);

	}
	else if(!strcmp(argv[1], "+%F")) {
		printf("%d-%d-%d\n",tm.tm_year + 1900,  tm.tm_mday, tm.tm_mon + 1);
	}
	else {
		printf("%s\n", "Invalid usage: date [+%b / +%B] [+%D] [+%F]");
		return 0;
	}
	return 0;
}