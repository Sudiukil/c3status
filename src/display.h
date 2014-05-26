#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void display(char *prefix, char *string, int priority, int is_last) {

	char *json_str = calloc(256, sizeof(char));

	strcat(json_str, "{\"full_text\":\"");
	if(prefix) strcat(json_str, prefix);
	strcat(json_str, string);

	switch(priority) {
		case 0:
			strcat(json_str, "\"}");
			break;
		case 1:
			strcat(json_str, "\", \"color\":\"#ffff00\"}");
			break;
		case 2:
			strcat(json_str, "\", \"color\":\"#ff0000\"}");
			break;
	}

	if(!is_last) strcat(json_str, ",");
	printf("%s", json_str);
}
