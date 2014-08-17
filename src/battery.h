// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int get_battery_pcent() {

	FILE *energy_full_file, *energy_now_file;
	unsigned long energy_full, energy_now;

	if(!(energy_full_file = fopen("/sys/class/power_supply/BAT0/energy_full", "r")) || !(energy_now_file = fopen("/sys/class/power_supply/BAT0/energy_now", "r"))) return -1;

	fscanf(energy_full_file, "%lu", &energy_full);
	fscanf(energy_now_file, "%lu", &energy_now);

	fclose(energy_full_file);
	fclose(energy_now_file);

	return((int)round((float)energy_now/(float)energy_full*100));
}

char *get_battery_status() {

	FILE *status_file;
	char status[8];

	if(!(status_file = fopen("/sys/class/power_supply/BAT0/status", "r"))) return "ABS";

	fgets(status, sizeof(status), status_file);

	fclose(status_file);

	if(status[0]=='C') return "CHR";
	return "BAT";
}

int test_battery_pcent(int battery_pcent) {

	if(battery_pcent>10 && battery_pcent<=25) return 1;
	if(battery_pcent<=10) return 2;
	if(battery_pcent>=95) return 3;
	if(battery_pcent==-1) return 2;
	return 0;
}

char *gen_battery_str_pcent(int battery_pcent) {

	char *str_pcent = calloc(16, sizeof(char));
	char *status = get_battery_status();

	if(battery_pcent!=-1) {
		if(battery_pcent<10) snprintf(str_pcent, 16, "0%d%% (%s)", battery_pcent, status);
		else snprintf(str_pcent, 16, "%d%% (%s)", battery_pcent, status);
	}
	else strcpy(str_pcent, "No battery");
	
	return str_pcent;
}
