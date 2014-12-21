// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct music {
	int ncmpcpp;
	int moc;

	const char *label;
	int initialized;
} music;

// Gets the current playing infos from ncmpcpp
char *gen_ncmpcpp_infos();

// Checks if MOC is playing music
int is_moc_music_played();

// Gets the current playing infos from mocp
char *gen_moc_infos();

// Updates a music player infos
void update_music(music *m);

// Displays a music player infos on the status bar
void display_music(music *m);

#endif