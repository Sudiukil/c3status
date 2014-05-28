#include <time.h>
#include <stdlib.h>
#include <string.h>

//get the system time (format : HH:MM:SS (assuming separator is ':'))
char *get_time(char separator) {
	
	time_t now = time(NULL);
	struct tm* tm = localtime(&now);
	char *str_time = calloc(16, sizeof(char));

	if(tm->tm_hour<10) strcat(str_time, "0");
	strcat(str_time, itoa(tm->tm_hour));

	str_time[strlen(str_time)] = separator;
	str_time[strlen(str_time)] = '\0';

	if(tm->tm_min<10) strcat(str_time, "0");
	strcat(str_time, itoa(tm->tm_min));

	str_time[strlen(str_time)] = separator;
	str_time[strlen(str_time)] = '\0';

	if(tm->tm_sec<10) strcat(str_time, "0");
	strcat(str_time, itoa(tm->tm_sec));

	return str_time;
}

//get the system date (format : DD/MM/YYYY (assuming separator is '/'))
char *get_date(char separator) {

	time_t now = time(NULL);
	struct tm* tm = localtime(&now);
	char *str_date = calloc(16, sizeof(char));

	if(tm->tm_mday<10) strcat(str_date, "0");
	strcat(str_date, itoa(tm->tm_mday));

	str_date[strlen(str_date)] = separator;
	str_date[strlen(str_date)] = '\0';

	if(tm->tm_mon+1<10) strcat(str_date, "0");
	strcat(str_date, itoa(tm->tm_mon+1));

	str_date[strlen(str_date)] = separator;
	str_date[strlen(str_date)] = '\0';

	strcat(str_date, itoa(tm->tm_year+1900));

	return str_date;
}

//get the system date and time (format : DD/MM/YYYY - HH:MM:SS (assuming separator1 is '/' and separator2 is ':'))
char *get_date_time(char separator1, char separator2) {

	char *str = calloc(32, sizeof(char));

	strcat(str, get_date(separator1));
	strcat(str, " - ");
	strcat(str, get_time(separator2));

	return str;
}
