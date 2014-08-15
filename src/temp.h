// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>

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