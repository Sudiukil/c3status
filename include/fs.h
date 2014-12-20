// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef FS_H_INCLUDED
#define FS_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <sys/statvfs.h>

typedef struct fs {
	const char *mount_point;

	int usage_pcent;
	int usage_pcent_status;
	int warning_usage_pcent;
	int critical_usage_pcent;

	const char *label;
	int initialized;
} fs;

// Calculates a filesystem usage percentage
int get_fs_usage_pcent(const char *mount_point);

// Updates a filesystem infos
void update_fs(fs *f);

// Displays a filesystem infos on the status bar
void display_fs(fs *f);

#endif
