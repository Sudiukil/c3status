// Copyright (c) 2014-2016, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "display.h"

void display(const char *name, const char *instance, const char *label, char *data, int priority) {

	const char *color;

	if(first_run) {
		if(!label_color) label_color = "#ffffff";
		if(!data_color) data_color = "#ffffff";
		if(!ok_color) ok_color = "#00ff00";
		if(!warning_color) warning_color = "#ffff00";
		if(!critical_color) critical_color = "#ff0000";
		first_run = 0;
	}

	if(!label) label = "";

	switch(priority) {
		case 0:
			color = data_color;
			break;
		case 1:
			color = warning_color;
			break;
		case 2:
			color = critical_color;
			break;
		case 3:
			color = ok_color;
			break;
		default:
			color = data_color;
			break;
	}

	printf("{\"full_text\":\"%s\", \"color\":\"%s\", \"separator\":false},\n{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\", \"color\":\"%s\", \"separator\":true},\n\n",
			label,
			label_color,
			name,
			instance,
			data,
			color
		  );
}
