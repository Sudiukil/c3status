// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "music.h"
#include "display.h"

char *gen_ncmpcpp_infos() {

	char *infos = malloc(256*sizeof(char));

	FILE *ncmpcpp_stdout = popen("ncmpcpp --now-playing \"{%n. }{%t}|{%f}{ - %a}{ (%b)}\"", "r");

	if(fgets(infos, 256, ncmpcpp_stdout)) infos[strlen(infos)-1] = '\0';
	else snprintf(infos, 256, "stopped");

	pclose(ncmpcpp_stdout);

	return infos;
}

int is_moc_music_played() {

	char infos;

	FILE *mocp_stdout = popen("mocp -Q \"%state\" 2> /dev/null", "r");

	fscanf(mocp_stdout, "%c", &infos);

	pclose(mocp_stdout);

	if(infos!='S') return 1;
	else return 0;
}

char *gen_moc_infos() {

	char *infos = malloc(256*sizeof(char));

	FILE *mocp_stdout = popen("mocp -Q \"%n. %t - %a (%A)\" 2> /dev/null", "r");

	if(fgets(infos, 256, mocp_stdout) && is_moc_music_played()) infos[strlen(infos)-1] = '\0';
	else snprintf(infos, 256, "stopped");

	pclose(mocp_stdout);
	return infos;
}

void update_music(music *m) {

	if(!(m->initialized)) {
		if(!(m->label)) m->label = "MUSIC";
		m->initialized = 1;
	}
}

void display_music(music *m) {

	char *infos;

	update_music(m);

	if(m->ncmpcpp) {
		infos = gen_ncmpcpp_infos();
		display("music", "ncmpcpp", m->label, infos, 0);
		free(infos);
	}
	else if(m->moc) {
		infos = gen_moc_infos();
		display("music", "moc", m->label, infos, 0);
		free(infos);
	}
}
