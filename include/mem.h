// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef MEM_H_INCLUDED
#define MEM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

typedef struct mem {
	int usage_pcent;

	int usage_pcent_status;
	int warning_usage_pcent;
	int critical_usage_pcent;

	const char *label;
	int initialized;
} mem;

// Calculates the memory usage percentage
int get_mem_usage_pcent(void);

// Updates the memory infos
void update_mem(mem *m);

// Displays the memory infos on the status bar
void display_mem(mem *m);

#endif
