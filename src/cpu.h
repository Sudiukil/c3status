// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>

static int prev_idle = 0;
static int prev_total = 0;

int get_cpu_load_pcent() {

	FILE *statfile;
	long user, nice, system, idle, total;
	int diff_idle, diff_total;

	if(!(statfile = fopen("/proc/stat", "r"))) return -1;

	fscanf(statfile, "cpu %ld %ld %ld %ld", &user, &nice, &system, &idle);

	fclose(statfile);

	total = user+nice+system+idle;
	diff_idle = idle-prev_idle;
	diff_total = total-prev_total;

	prev_idle = idle;
	prev_total = total;

	if(diff_total!=total) return((1000*(diff_total-diff_idle)/diff_total+5)/10);
	else return 0;
}
