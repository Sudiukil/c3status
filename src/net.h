// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int loop_nb_dl = 0, loop_nb_ul = 0;
static char format_dl[16], format_ul[64];
static unsigned long prev_received = 0;
static unsigned long prev_transmitted = 0;

// Calculates the download speed on specified interface
unsigned long get_dl_speed(char *interface) {

    FILE *file;
    char buffer[256], target[8], found[8];
    unsigned long received, diff;

    if(!(file = fopen("/proc/net/dev", "r"))) return -1;

    snprintf(target, 8, "%s:", interface);
    while(strcmp(found, target)!=0) {
	if(loop_nb_dl<10) loop_nb_dl++;
	else return -1;
	fgets(buffer, 256, file);
	sscanf(buffer, "%s:", found);
    }

    if(strlen(format_dl)==0) {
	snprintf(format_dl, 16, "%s: %%lu", interface);
    }

    sscanf(buffer, format_dl, &received);

    pclose(file);

    diff = received-prev_received;

    prev_received = received;
    loop_nb_dl = 0;

    if(diff!=received) return diff;
    else return 0;
}

// Calculates the upload speed on specified interface
unsigned long get_ul_speed(char *interface) {

    FILE *file;
    char buffer[256], target[8], found[8];
    unsigned long d, transmitted, diff;

    if(!(file = fopen("/proc/net/dev", "r"))) return -1;

    snprintf(target, 8, "%s:", interface);
    while(strcmp(found, target)!=0) {
	if(loop_nb_ul<10) loop_nb_ul++;
	else return -1;
	fgets(buffer, 256, file);
	sscanf(buffer, "%s", found);
    }

    if(strlen(format_ul)==0) {
	snprintf(format_ul, 64, "%s: %%lu %%lu %%lu %%lu %%lu %%lu %%lu %%lu %%lu", interface);
    }

    sscanf(buffer, format_ul, &d, &d, &d, &d, &d, &d, &d, &d, &transmitted);

    pclose(file);

    diff = transmitted-prev_transmitted;

    prev_transmitted = transmitted;
    loop_nb_ul = 0;

    if(diff!=transmitted) return diff;
    else return 0;
}

// Generates the download or upload infos as a string (x unit/s)
char *gen_str_speed(unsigned long speed, char unit, char precision_mode) {

    char *str_speed = calloc(16, sizeof(char));

    if(speed!=-1) {
	if(speed>1024) {
	    snprintf(str_speed, 16, "%lu Ki%c/s", speed/1024, unit);
	}
	else if(speed>1048576) {
	    snprintf(str_speed, 16, "%lu Mi%c/s", speed/1024/1024, unit);
	}
	else {
	    if(precision_mode) snprintf(str_speed, 16, "%lu %c/s", speed, unit);
	    else snprintf(str_speed, 16, "0 Ki%c/s", unit);
	}
    }
    else snprintf(str_speed, 16, "Error");

    return str_speed;
}
