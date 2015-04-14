// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "date.h"
#include "display.h"

void update_date(date *d) {

	if(!(d->initialized)) {
		if(!(d->format)) d->format = "%d/%m/%Y - %H:%M";
		d->initialized = 1;
	}

	d->now = time(NULL);
}

char *gen_date(date *d) {

	char *date = malloc(32*sizeof(char));

	if(!(strftime(date, 32, d->format, localtime(&(d->now))))) {
		fprintf(stderr, "Error getting date\n");
		snprintf(date, 32, "Error");
	}

	return date;
}

void display_date(date *d) {

	char *date;

	update_date(d);

	date = gen_date(d);

	display("date", "localtime", d->label, date, 0);

	free(date);
}
