#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *normalize(int value, char appendix) {

	char *str = calloc(8, sizeof(char));

	if(value!=-1) {
		switch(appendix) {
			case '%':
				if(value<10) snprintf(str, 8, "0%d%%", value);
				else snprintf(str, 8, "%d%%", value);
				break;
			case 'C':
				if(value<10) snprintf(str, 8, "0%d°C", value);
				else snprintf(str, 8, "%d°C", value);
				break;
			default:
				printf("Bad argument, possible values : '%%' or '°'");
				exit(1);
				break;
		}
	}
	else strcpy(str, "Error");

	return str;
}

int test_value(int value, int max, int critical) {

	if(value>=max && value<critical) return 1;
	if(value>=critical) return 2;
	if(value==-1) return 2;
	return 0;
}
