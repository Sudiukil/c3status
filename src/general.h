// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdlib.h>
#include <stdio.h>

// Appends the unit to a percentage or temperature value
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
    else snprintf(str, 8, "Error");

    return str;
}

// Tests a value compaired to user defined warning and critical values
int test_value(int value, int warning, int critical) {

    if(value>=warning && value<critical) return 1;
    if(value>=critical) return 2;
    if(value==-1) return 2;
    return 0;
}
