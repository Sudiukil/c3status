// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef BATTERY_H_INCLUDED
#define BATTERY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

typedef struct battery {
	const char *name;

	int pcent;
	int pcent_status;
	int max_pcent;
	int warning_pcent;
	int critical_pcent;

	char status;

	const char *label;
	int initialized;
} battery;

// Calculates the battery percentage
int get_battery_pcent(const char *battery_name);

// Gets the battery status (battery or charging)
char get_battery_status(const char *battery_name);

// Tests the battery percentage compaired to user defined max, warning and critical values
int test_battery_pcent(int battery_pcent, int max, int warning, int critical);

// Updates a battery infos
void update_battery(battery *b);

// Returns a battery infos as a string
char *gen_battery_infos(battery *b);

// Displays a battery infos on the status bar
void display_battery(battery *b);

#endif
