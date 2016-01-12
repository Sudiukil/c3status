// Copyright (c) 2014-2016, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "battery.h"
#include "display.h"

void init_battery(battery *b) {

	if(!(b->name)) b->name = "BAT0";
	if(!(b->label)) b->label = "BAT";
	if(!(b->show_remaining_time)) b->show_remaining_time = 0;

	if(!(b->charged_pcent)) b->charged_pcent = 95;
	if(!(b->warning_pcent)) b->warning_pcent = 25;
	if(!(b->critical_pcent)) b->critical_pcent = 10;

	b->status_fp = malloc(64*sizeof(char));
	b->capacity_fp = malloc(64*sizeof(char));
	b->energy_full_fp = malloc(64*sizeof(char));
	b->energy_now_fp = malloc(64*sizeof(char));	
	b->power_now_fp = malloc(64*sizeof(char));

	snprintf(b->status_fp, 64, "/sys/class/power_supply/%s/status", b->name);
	snprintf(b->capacity_fp, 64, "/sys/class/power_supply/%s/capacity", b->name);
	snprintf(b->energy_full_fp, 64, "/sys/class/power_supply/%s/energy_full", b->name);
	snprintf(b->energy_now_fp, 64, "/sys/class/power_supply/%s/energy_now", b->name);
	snprintf(b->power_now_fp, 64, "/sys/class/power_supply/%s/power_now", b->name);

	b->initialized = 1;
}

void free_battery(battery *b) {

	free(b->status_fp);
	free(b->capacity_fp);
	free(b->energy_full_fp);
	free(b->energy_now_fp);
	free(b->power_now_fp);
}

int update_battery(battery *b) {

	FILE *status_f, *capacity_f, *energy_full_f, *energy_now_f, *power_now_f;
	float energy_full, energy_now, power_now;

	if(!(b->initialized)) init_battery(b);

	if(!(status_f = fopen(b->status_fp, "r"))) {
		fprintf(stderr, "Error: Can't get %s percentage: %s: %s\n", b->name, b->status_fp, strerror(errno));
		return 0;
	}

	if(!(capacity_f = fopen(b->capacity_fp, "r"))) {
		fprintf(stderr, "Error: Can't get %s percentage: %s: %s\n", b->name, b->capacity_fp, strerror(errno));
		return 0;
	}

	if(!(energy_full_f = fopen(b->energy_full_fp, "r"))) {
		fprintf(stderr, "Error: Can't get %s percentage: %s: %s\n", b->name, b->energy_full_fp, strerror(errno));
		return 0;
	}

	if(!(energy_now_f = fopen(b->energy_now_fp, "r"))) {
		fprintf(stderr, "Error: Can't get %s percentage: %s: %s\n", b->name, b->energy_now_fp, strerror(errno));
		return 0;
	}

	if(!(power_now_f = fopen(b->power_now_fp, "r"))) {
		fprintf(stderr, "Error: Can't get %s percentage: %s: %s\n", b->name, b->power_now_fp, strerror(errno));
		return 0;
	}

	fscanf(status_f, "%c", &(b->status));
	fscanf(capacity_f, "%d", &(b->capacity));
	fscanf(energy_full_f, "%f", &energy_full);
	fscanf(energy_now_f, "%f", &energy_now);
	fscanf(power_now_f, "%f", &power_now);

	fclose(status_f);
	fclose(capacity_f);
	fclose(energy_full_f);
	fclose(energy_now_f);
	fclose(power_now_f);

	if(b->capacity > b->charged_pcent) b->state = 3;
	else if(b->capacity > b->critical_pcent && b->capacity < b->warning_pcent) b->state = 1;
	else if(b->capacity <= b->critical_pcent) b->state = 2;
	else b->state = 0;

	switch(b->status) {
		case 'C':
			b->remaining_time = (int)(((energy_full-energy_now)/power_now)*60);
			break;
		case 'D':
			b->remaining_time = (int)((energy_now/power_now)*60);
			break;
		default:
			b->remaining_time = 0;
			break;
	}

	return 1;
}

char *str_battery(battery *b) {

	const char *status;
	char *str_battery, *str_remaining_time;

	str_battery = malloc(32*sizeof(char));

	switch(b->status) {
		case 'C':
			status = "CHR";
			break;
		case 'D':
			status = "BAT";
			break;
		case 'F':
			status = "FULL";
			break;
		default:
			status = "UNK";
			break;
	}

	str_remaining_time = malloc(16*sizeof(char));

	if(b->show_remaining_time) snprintf(str_remaining_time, 16, " (%02d:%02d)", b->remaining_time/60, b->remaining_time%60);
	else snprintf(str_remaining_time, 16, "");

	snprintf(str_battery, 32, "%02d%% (%s)%s", b->capacity, status, str_remaining_time);

	free(str_remaining_time);

	return str_battery;
}

void display_battery(battery *b) {

	char *battery_str;

	if(update_battery(b)) {
		battery_str = str_battery(b);
		display("battery", b->name, b->label, battery_str, b->state);
	}
	else {
		battery_str = malloc(16*sizeof(char));
		snprintf(battery_str, 16, "No battery");
		display("battery", b->name, b->label, battery_str, 2);
	}

	free(battery_str);
}
