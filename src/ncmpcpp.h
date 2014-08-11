#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_ncmpcpp_infos() {

	char *infos = calloc(256, sizeof(char));

	FILE *ncmpcpp_stdout = popen("ncmpcpp --now-playing \"{%n. %t}|{%f} - {%a} {(%b)}\"", "r");

	fgets(infos, 256, ncmpcpp_stdout);

	infos[strlen(infos)-1] = '\0';

	pclose(ncmpcpp_stdout);

	if(strlen(infos)!=0) return infos;
	else {
		strcpy(infos, "stopped");
		return infos;
	}
}
