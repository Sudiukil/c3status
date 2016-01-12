// Copyright (c) 2014-2016, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef BATTERY_H_INCLUDED
#define BATTERY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

typedef struct battery {
	// User-defined data
	const char *name;
	const char *label;

	int show_remaining_time;

	int charged_pcent;
	int warning_pcent;
	int critical_pcent;

	// Intermediary data
	char *status_fp;
	char *capacity_fp;
	char *energy_full_fp;
	char *energy_now_fp;
	char *power_now_fp;

	// Collected data
	char status;
	int capacity;
	int remaining_time;
	int state;

	int initialized;
} battery;

// Initializes a battery
void init_battery(battery *b);

// Frees a battery
void free_battery(battery *b);

// Updates a battery infos
int update_battery(battery *b);

// Returns a battery infos as a string
char *str_battery(battery *b);

// Tests a battery capacity
int test_battery(battery *b);

// Displays a battery infos on the status bar
void display_battery(battery *b);

#endif
