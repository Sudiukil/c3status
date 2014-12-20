// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "display.h"

void display(const char *name, const char *instance, const char *label, char *data, int priority) {

	char *json_label = malloc(512*sizeof(char));
	char *json_data = malloc(512*sizeof(char));
	char *json_global = malloc(1024*sizeof(char));
	char *end_string = malloc(32*sizeof(char));

	if(label) {
		if(label_color) snprintf(end_string, 32, ", \"color\":\"%s\"},", label_color);
		else snprintf(end_string, 32, "},");

		snprintf(
				json_label,
				512,
				"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\", \"separator\":false%s",
				name,
				instance,
				label,
				end_string
				);
	}

	switch(priority) {
		case 0:
			if(data_color) snprintf(end_string, 32, ", \"color\":\"%s\"},", data_color);
			else snprintf(end_string, 32, "},");
			break;
		case 1:
			if(warning_color) snprintf(end_string, 32, ", \"color\":\"%s\"},", warning_color);
			else snprintf(end_string, 32, ", \"color\":\"#ffff00\"},");
			break;
		case 2:
			if(critical_color) snprintf(end_string, 32, ", \"color\":\"%s\"},", critical_color);
			else snprintf(end_string, 32, ", \"color\":\"#ff0000\"},");
			break;
		case 3:
			if(ok_color) snprintf(end_string, 32, ", \"color\":\"%s\"},", ok_color);
			else snprintf(end_string, 32, ", \"color\":\"#00ff00\"},");
			break;
	}

	snprintf(
			json_data,
			512,	
			"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\"%s",
			name,
			instance,
			data,
			end_string
			);

	if(label) snprintf(json_global, 1024, "%s%s", json_label, json_data);
	else snprintf(json_global, 1024, "%s", json_data);

	printf("%s\n", json_global);

	free(end_string);
	free(json_label);
	free(json_data);
	free(json_global);
}
