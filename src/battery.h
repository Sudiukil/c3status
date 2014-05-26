#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int get_battery_pcent() {

	char *energy_full = calloc(16, sizeof(char));
	char *energy_now = calloc(16, sizeof(char));

	FILE *energy_full_file = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
	FILE *energy_now_file = fopen("/sys/class/power_supply/BAT0/energy_now", "r");

	fgets(energy_full, sizeof(energy_full)+1, energy_full_file);
	fgets(energy_now, sizeof(energy_now)+1, energy_now_file);

	fclose(energy_full_file);
	fclose(energy_now_file);

	return (int)round(atof(energy_now)/atof(energy_full)*100);
}

char *get_battery_status() {

	char *status = calloc(16, sizeof(char));

	FILE *status_file = fopen("/sys/class/power_supply/BAT0/status", "r");

	fgets(status, sizeof(status), status_file);

	fclose(status_file);

	if(status[0]=='C') return "CHR: ";
	return "BAT: ";
}

char *gen_battery_str_pcent(int battery_pcent) {

	char *str_pcent = calloc(8, sizeof(char));

	strcat(str_pcent, itoa(battery_pcent));
	str_pcent[strlen(str_pcent)] = '%';
	str_pcent[strlen(str_pcent)] = '\0';

	return str_pcent;
}

int test_battery_pcent(int battery_pcent) {

	if(battery_pcent>10 && battery_pcent<=25) return 1;
	if(battery_pcent<=10) return 2;
	return 0;
}
