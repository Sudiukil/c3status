// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void display(char *name, char *instance, char *label, char *data, char *label_color, char *data_color, int priority, int is_last) {

	char *json_label = calloc(512, sizeof(char));
	char *json_data = calloc(512, sizeof(char));
	char *json_global = calloc(1024, sizeof(char));

	if(label) {
		if(label_color) {
			snprintf(
					json_label,
					512,
					"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\", \"separator\":false, \"color\":\"%s\"},",
					name,
					instance,
					label,
					label_color
			);
		}
		else {
			snprintf(
					json_label,
					512,
					"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\", \"separator\":false},",
					name,
					instance,
					label
			);
		}
	}

	switch(priority) {
		case 0:
			if(data_color) {
				snprintf(
						json_data,
						512,	
						"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\", \"color\":\"%s\"}",
						name,
						instance,
						data,
						data_color
				);
			}
			else {
				snprintf(
						json_data,
						512,
						"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\"}",
						name,
						instance,
						data
				);
			}
			break;
		case 1:
			snprintf(
					json_data,
					512,
					"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\", \"color\":\"%s\"}",
					name,
					instance,
					data,
					"#ffff00"
			);
			break;
		case 2:
			snprintf(
					json_data,
					512,
					"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\", \"color\":\"%s\"}",
					name,
					instance,
					data,
					"ff0000"
			);
			break;
		case 3:
			snprintf(
					json_data,
					512,
					"{\"name\":\"%s\", \"instance\":\"%s\", \"full_text\":\"%s\", \"color\":\"%s\"}",
					name,
					instance,
					data,
					"00ff00"
			);
			break;
	}

	if(label) strcat(json_global, json_label);
	strcat(json_global, json_data);
	if(!is_last) strcat(json_global, ",");

	free(json_label);
	free(json_data);

	printf("%s\n", json_global);

	free(json_global);
}
