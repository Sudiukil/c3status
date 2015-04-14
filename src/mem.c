// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "mem.h"
#include "general.h"
#include "display.h"

int get_mem_usage_pcent(void) {

	const char *meminfo_path;
	FILE *meminfo;
	char *buffer;
	unsigned long total, avail, used;

	meminfo_path = "/proc/meminfo";

	if(!(meminfo = fopen(meminfo_path, "r"))) {
		fprintf(stderr, "Error: Can't get memory usage pcent: %s: %s", meminfo_path, strerror(errno));
		return -1;
	}

	buffer = malloc(128*sizeof(char));

	fgets(buffer, 128, meminfo);
	sscanf(buffer, "MemTotal: %ld kB", &total);
	fgets(buffer, 128, meminfo);
	fgets(buffer, 128, meminfo);
	sscanf(buffer, "MemAvailable: %ld kB", &avail);

	fclose(meminfo);
	free(buffer);

	used = total-avail;

	return((int)round((float)used/(float)total*100));
}

void update_mem(mem *m) {

	if(!(m->initialized)) {
		if(!(m->warning_usage_pcent)) m->warning_usage_pcent = 75;
		if(!(m->critical_usage_pcent)) m->critical_usage_pcent = 90;
		if(!(m->label)) m->label = "MEM";
		m->initialized = 1;
	}

	m->usage_pcent = get_mem_usage_pcent();
	m->usage_pcent_status = test_value(m->usage_pcent, m->warning_usage_pcent, m->critical_usage_pcent);
}

void display_mem(mem *m) {

	char *mem_usage_pcent;

	update_mem(m);

	mem_usage_pcent = normalize(m->usage_pcent, '%');

	display("memory", "ram", m->label, mem_usage_pcent, m->usage_pcent_status);

	free(mem_usage_pcent);
}
