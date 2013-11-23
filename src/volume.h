/*
Get volume from ALSA.
Copyright (C) 2013 Quentin Sonrel (Sudiukil).

This file is part of c3status.

c3status is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

c3status is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with c3status.  If not, see <http://www.gnu.org/licenses/>.
*/

char *getVolume() { //get the volume from alsa
	FILE *amixerStdout = popen("amixer get Master | grep \"Mono:\" | cut -d '[' -f 2 | sed -e 's/ //g' -e 's/]//'", "r");
	fgets(buffer, sizeof(buffer), amixerStdout);
	pclose(amixerStdout);
	buffer[strlen(buffer)-1] = '\0';
	return buffer;
}

int testVolumeState() { //test the volume to colorize the output
	FILE *amixerStdout = popen("amixer get Master | grep \"Mono:\" | cut -d '[' -f 4 | sed -e 's/on]/1/' -e 's/off]/0/'", "r");
	fgets(buffer, sizeof(buffer), amixerStdout);
	pclose(amixerStdout);
	if(buffer[0]=='1') return 0; //default color if not muted
	else return 1; //yellow if muted
}
