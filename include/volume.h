// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef VOLUME_H_INCLUDED
#define VOLUME_H_INCLUDED

#include <stdlib.h>
#include <math.h>
#include <alsa/asoundlib.h>

typedef struct volume {
	const char *selem;

	int volume;
	int status;

	int limit;

	const char *label;
	int initialized;
} volume;

// Gets infos (volume percentage and status (muted or not)) from ALSA API
int *get_alsa_infos(const char *selem_name);

// Generates the volume infos as a string (xy% ([M] if muted))
char *gen_alsa_str_volume_infos(int pcent, int is_active);

// Tests the volume percentage compaired to the user defined limit
int test_alsa_volume_pcent(int pcent, int is_active, int limit);

// Updates volume infos
void update_volume(volume *v);

// Displays volume infos on the status bar
void display_volume(volume *v);

#endif
