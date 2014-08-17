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

int get_cpu_temp() {

	FILE *current_temp_file;
	int current_temp;

	if(!(current_temp_file = fopen("/sys/class/hwmon/hwmon0/device/temp1_input", "r"))) {
		if(!(current_temp_file = fopen("/sys/class/hwmon/hwmon0/temp1_input", "r"))) {
			return -1;
		}
	}

	fscanf(current_temp_file, "%d", &current_temp);

	pclose(current_temp_file);

	return current_temp/1000;
}
