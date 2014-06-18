#include <time.h>
#include <stdlib.h>

char *get_time(char *format) {

	time_t now = time(NULL);
	struct tm *tm = localtime(&now);
	char *str_time = calloc(32, sizeof(char));

	if(!(strftime(str_time, 32, format, tm))) return "Error";

	return str_time;
}
