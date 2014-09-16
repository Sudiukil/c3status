// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <time.h>
#include <stdlib.h>

// Gets the current system time in the given format
char *get_time(char *format) {

    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char *str_time = calloc(32, sizeof(char));

    if(!(strftime(str_time, 32, format, tm))) return "Error";

    return str_time;
}
