// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

const char *label_color;
const char *data_color;
const char *ok_color;
const char *warning_color;
const char *critical_color;

void display(const char *name, const char *instance, const char *label, char *data, int priority);

#endif
