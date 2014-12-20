// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "battery.h"
#include "display.h"

int get_battery_pcent(const char *battery_name) {

	char *energy_full_file_path, *energy_now_file_path;
	FILE *energy_full_file, *energy_now_file;
	long energy_full, energy_now;

	energy_full_file_path = malloc(64*sizeof(char));
	energy_now_file_path = malloc(64*sizeof(char));

	snprintf(energy_full_file_path, 64, "/sys/class/power_supply/%s/energy_full", battery_name);
	snprintf(energy_now_file_path, 64, "/sys/class/power_supply/%s/energy_now", battery_name);

	if(!(energy_full_file = fopen(energy_full_file_path, "r"))) {
		fprintf(stderr, "Error: Can't get %s percentage: %s: %s\n", battery_name, energy_full_file_path, strerror(errno));
		free(energy_full_file_path);
		free(energy_now_file_path);
		return -1;
	}

	if(!(energy_now_file = fopen(energy_now_file_path, "r"))) {
		fprintf(stderr, "Error: Can't get %s percentage: %s: %s\n", battery_name, energy_now_file_path, strerror(errno));
		free(energy_full_file_path);
		free(energy_now_file_path);
		return -1;
	}

	free(energy_full_file_path);
	free(energy_now_file_path);

	fscanf(energy_full_file, "%ld", &energy_full);
	fscanf(energy_now_file, "%ld", &energy_now);

	fclose(energy_full_file);
	fclose(energy_now_file);

	return (int)round((float)energy_now/(float)energy_full*100);
}

char get_battery_status(const char *battery_name) {

	char *status_file_path;
	FILE *status_file;
	char status;

	status_file_path = malloc(64*sizeof(char));

	snprintf(status_file_path, 64, "/sys/class/power_supply/%s/status", battery_name);

	if(!(status_file = fopen(status_file_path, "r"))) {
		fprintf(stderr, "Error: Can't get %s status: %s: %s\n", battery_name, status_file_path, strerror(errno));
		free(status_file_path);
		return 'U';
	}

	free(status_file_path);

	fscanf(status_file, "%c", &status);

	fclose(status_file);

	return status;
}

int test_battery_pcent(int battery_pcent, int max, int warning, int critical) {

	if(battery_pcent>critical && battery_pcent<=warning) return 1;
	if(battery_pcent<=critical) return 2;
	if(battery_pcent>=max) return 3;
	if(battery_pcent==-1) return 2;
	return 0;
}

void update_battery(battery *b) {

	if(!(b->initialized)) {
		if(!(b->name)) b->name = "BAT0";
		if(!(b->max_pcent)) b->max_pcent = 95;
		if(!(b->warning_pcent)) b->warning_pcent = 25;
		if(!(b->critical_pcent)) b->critical_pcent = 10;
		if(!(b->label)) b->label = b->name;
		b->initialized = 1;
	}

	b->pcent = get_battery_pcent(b->name);
	b->pcent_status = test_battery_pcent(b->pcent, b->max_pcent, b->warning_pcent, b->critical_pcent);
	b->status = get_battery_status(b->name);
}

char *gen_battery_infos(battery *b) {

	const char *status;
	char *battery_infos;

	battery_infos = malloc(16*sizeof(char));

	switch(b->status) {
		case 'C':
			status = "CHR";
			break;
		case 'D':
			status = "BAT";
			break;
		default:
			status = "UNK";
			break;
	}

	if(b->pcent!=-1) {
		if(b->pcent<10) snprintf(battery_infos, 16, "0%d%% (%s)", b->pcent, status);
		else snprintf(battery_infos, 16, "%d%% (%s)", b->pcent, status);
	}
	else snprintf(battery_infos, 16, "No battery");

	return battery_infos;
}

void display_battery(battery *b) {

	char *battery_infos;

	update_battery(b);

	battery_infos = gen_battery_infos(b);

	display("battery", b->name, b->label, battery_infos, b->pcent_status);

	free(battery_infos);
}
