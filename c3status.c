// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>
#include <unistd.h>

#include "src/general.h"
#include "src/display.h"

#include "src/time.h"

int main(int argc, char *argv[]) {

    char *str_data;

    printf("{\"version\":1}\n");
    printf("[[],\n");

    while(1) {
	sleep(1);
	fflush(stdout);
	printf("[\n");

	str_data = get_time("%d/%m/%Y - %H:%M:%S");
	display(
		"time",
		"local",
		NULL,
		str_data,
		NULL,
		NULL,	
		0,
		1
	       );
	free(str_data);

	printf("],\n");
    }

    return 0;
}
