// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

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

int is_moc_music_played() {

	char *infos = calloc(8, sizeof(char));

	FILE *mocp_stdout = popen("mocp -Q \"%state\" 2> /dev/null", "r");

	fgets(infos, 8, mocp_stdout);

	pclose(mocp_stdout);

	if(infos[0]!='S') return 1;
	else return 0;
}

char *get_moc_infos() {

	char *infos = calloc(256, sizeof(char));

	FILE *mocp_stdout = popen("mocp -Q \"%n. %t - %a (%A)\" 2> /dev/null", "r");

	fgets(infos, 256, mocp_stdout);

	infos[strlen(infos)-1] = '\0';

	pclose(mocp_stdout);

	if(strlen(infos)!=0 && is_moc_music_played()) return infos;
	else {
		strcpy(infos, "stopped");
		return infos;
	}
}
