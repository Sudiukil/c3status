#include <stdlib.h>
#include <stdio.h>

int is_moc_running() {

	char *return_code = calloc(2, sizeof(char));	
	FILE *pgrep_stdout = popen("pgrep moc > /dev/null; echo $?", "r");

	fgets(return_code, sizeof(return_code), pgrep_stdout);

	pclose(pgrep_stdout);

	if(return_code[0]=='0') return 1;
	return 0;
}

char *get_moc_infos() {

	if(is_moc_running()) {
		char *infos = calloc(128, sizeof(char));
		FILE *mocp_stdout = popen("mocp -Q \"%state: %title %ct/%tl [%tt]\"", "r");

		fgets(infos, 128, mocp_stdout);

		pclose(mocp_stdout);

		infos[strlen(infos)-1] = '\0';

		if(infos[0]=='S') return "STOP";
		return infos;
	}
	else return "STOP";
}
