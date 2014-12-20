// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "all.h"
#include "config.h"

int main(int argc, char *argv[]) {

	struct timeval t1, t2;
	float elapsed_time;
	int refresh_interval;

	if(argc>1 && argv[1]!=NULL) {
		sscanf(argv[1], "%d", &refresh_interval);
		refresh_interval = refresh_interval*1000;
	}
	else refresh_interval = 1000;

	printf("{\"version\":1}\n");
	printf("[[],\n");

	conf();

	while(1) {
		gettimeofday(&t1, NULL);

		fflush(stdout);
		printf("[\n");

		update();

		printf("{\"full_text\":\"\"}");

		printf("],\n");

		gettimeofday(&t2, NULL);
		elapsed_time = ((t2.tv_sec-t1.tv_sec)*1000)+((t2.tv_usec-t1.tv_usec)/1000);
		if(elapsed_time<refresh_interval) usleep((refresh_interval-elapsed_time)*1000);
	}

	return 0;
}
