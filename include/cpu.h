// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct cpu {
	int load_pcent_enable;
	int load_pcent;
	int load_pcent_status;
	int warning_load_pcent;
	int critical_load_pcent;

	int temperature_enable;
	const char *current_temp_file_path;
	int temperature;
	int temperature_status;
	int warning_temperature;
	int critical_temperature;

	const char *label;
	int initialized;
} cpu;

int prev_idle;
int prev_total;

// Calculates the CPU usage percentage
int get_cpu_load_pcent(void);

// Calculates the CPU temperature
int get_cpu_temp(const char *current_temp_file_path);

// Updates a CPU infos
void update_cpu(cpu *c);

// Displays a CPU infos on the status bar
void display_cpu(cpu *c);

#endif
