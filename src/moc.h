#include <stdio.h>
#include <stdlib.h>

int is_moc_running() {

	FILE *pgrep_stdout = popen("pgrep moc > /dev/null; echo $?", "r");
	char return_code[4];

	fgets(return_code, sizeof(return_code), pgrep_stdout);

	pclose(pgrep_stdout);

	if(return_code[0]=='0') return 1;
	return 0;
}

char *get_moc_infos() {

	if(is_moc_running()) {
		char *infos = calloc(256, sizeof(char));
		FILE *mocp_stdout = popen("mocp -Q \"%state: %title %ct/%tl [%tt]\" | sed -e 's/\\/ \\[\\]//g'", "r");

		fgets(infos, 256, mocp_stdout);

		infos[strlen(infos)-1] = '\0';

		pclose(mocp_stdout);

		if(infos[0]=='S') return "STOP";
		return infos;
	}
	else return "STOP";
}
