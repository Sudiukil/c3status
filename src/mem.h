// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>
#include <math.h>

int get_mem_usage_pcent() {

	FILE *meminfo;
	char buffer[128];
	unsigned long total, avail, used;

	if(!(meminfo = fopen("/proc/meminfo", "r"))) return -1;

	fgets(buffer, 128, meminfo);
	sscanf(buffer, "MemTotal: %ld kB", &total);
	fgets(buffer, 128, meminfo);
	fgets(buffer, 128, meminfo);
	sscanf(buffer, "MemAvailable: %ld kB", &avail);

	fclose(meminfo);

	used = total-avail;

	return((int)round((float)used/(float)total*100));
}
