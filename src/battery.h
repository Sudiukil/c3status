// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Calculates the battery percentage
int get_battery_pcent(char *battery_name) {

    char *energy_full_file_path = calloc(64, sizeof(char));
    char *energy_now_file_path = calloc(64, sizeof(char));

    FILE *energy_full_file, *energy_now_file;
    unsigned long energy_full, energy_now;

    snprintf(energy_full_file_path, 64, "/sys/class/power_supply/%s/energy_full", battery_name);
    snprintf(energy_now_file_path, 64, "/sys/class/power_supply/%s/energy_now", battery_name);

    if(!(energy_full_file = fopen(energy_full_file_path, "r")) || !(energy_now_file = fopen(energy_now_file_path, "r"))) return -1;

    fscanf(energy_full_file, "%lu", &energy_full);
    fscanf(energy_now_file, "%lu", &energy_now);

    fclose(energy_full_file);
    fclose(energy_now_file);

    return((int)round((float)energy_now/(float)energy_full*100));
}

// Gets the battery status (battery, charging or absent)
char *get_battery_status(char *battery_name) {

    char *status_file_path = calloc(64, sizeof(char));
    FILE *status_file;
    char status[8];

    snprintf(status_file_path, 64, "/sys/class/power_supply/%s/status", battery_name);

    if(!(status_file = fopen(status_file_path, "r"))) return "ABS";

    fgets(status, sizeof(status), status_file);

    fclose(status_file);

    if(status[0]=='C') return "CHR";
    return "BAT";
}

// Tests the battery percentage compaired to user defined max, warning and critical values
int test_battery_pcent(int battery_pcent, int max, int warning, int critical) {

    if(battery_pcent>critical && battery_pcent<=warning) return 1;
    if(battery_pcent<=critical) return 2;
    if(battery_pcent>=max) return 3;
    if(battery_pcent==-1) return 2;
    return 0;
}

// Generates the battery infos as a string (xy% (status))
char *gen_battery_str_infos(int battery_pcent, char *battery_status) {

    char *str_pcent = calloc(16, sizeof(char));

    if(battery_pcent!=-1) {
	if(battery_pcent<10) snprintf(str_pcent, 16, "0%d%% (%s)", battery_pcent, battery_status);
	else snprintf(str_pcent, 16, "%d%% (%s)", battery_pcent, battery_status);
    }
    else snprintf(str_pcent, 16, "No battery");

    return str_pcent;
}
