// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_moc_running() {

	FILE *pgrep_stdout = popen("pgrep moc > /dev/null; echo $?", "r");
	char return_code[4];

	fgets(return_code, sizeof(return_code), pgrep_stdout);

	pclose(pgrep_stdout);

	if(return_code[0]=='0') return 1;
	return 0;
}

char *get_moc_infos() {

	char *infos = calloc(256, sizeof(char));
			
	if(is_moc_running()) {
		FILE *mocp_stdout = popen("mocp -Q \"%state: %title %ct/%tl [%tt]\" | sed -e 's/\\/ \\[\\]//g'", "r");

		fgets(infos, 256, mocp_stdout);

		infos[strlen(infos)-1] = '\0';

		pclose(mocp_stdout);

		if(infos[0]=='S') strcpy(infos, "STOP");
	}
	else strcpy(infos, "STOP");

	return infos;
}
