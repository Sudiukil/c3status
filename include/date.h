// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <stdlib.h>
#include <time.h>

typedef struct date {
	const char *format;

	time_t now;

	const char *label;
	int initialized;
} date;

// Updates a date
void update_date(date *d);

// Returns a date as a string
char *gen_date(date *d);

// Displays a date on the status bar
void display_date(date *d);

#endif
