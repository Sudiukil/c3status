// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "general.h"

void print_usage(int is_err) {

	if(is_err) fprintf(stderr, "Usage: c3status [-c CONFIG_FILE] [-t REFRESH_INTERVAL]\n");
	else printf("Usage: c3status [-c CONFIG_FILE] [-t REFRESH_INTERVAL]\n");
}

char *normalize(int value, char appendix) {

	char *str = malloc(8*sizeof(char));

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
				fprintf(stderr, "Bad argument, possible values : '%%' or '°'\n");
				free(str);
				exit(1);
				break;
		}
	}
	else snprintf(str, 8, "Error");

	return str;
}

int test_value(int value, int warning, int critical) {

	if(value>=warning && value<critical) return 1;
	if(value>=critical) return 2;
	if(value==-1) return 2;
	return 0;
}
