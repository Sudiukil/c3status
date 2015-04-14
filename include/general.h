// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Appends the unit to a percentage or temperature value
char *normalize(int value, char appendix);

// Tests a value compaired to user defined warning and critical values
int test_value(int value, int warning, int critical);

#endif
