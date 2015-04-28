// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef NET_H_INCLUDED
#define NET_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct net {
	const char *interface;

	long dl_speed;
	long ul_speed;

	char unit;

	const char *label;
	int initialized;
} net;

long prev_received;
long prev_transmitted;

// Calculates the download and upload speeds on specified interface
unsigned long long *get_dl_ul_speed(const char *interface);

// Generates the download or upload infos as a string (x unit/s)
char *gen_str_speed(long speed, char unit);

// Updates net infos
void update_net(net *n);

// Displays net infos on the status bar
void display_net(net *n);

#endif
