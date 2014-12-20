// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef WIRELESS_H_INCLUDED
#define WIRELESS_H_INCLUDED

#include <stdio.h>
#include <iwlib.h>
#include <string.h>
#include <errno.h>

typedef struct wireless {
	const char *interface;

	const char *label;
	int initialized;
} wireless;

// Gets the current wireless ESSID on specified interface
char *gen_wireless_ssid(const char *interface);

// Updates a wireless network infos
void update_wireless(wireless *w);

// Displaus a wireless infos on the status bar
void display_wireless(wireless *w);

#endif
