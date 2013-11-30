/*
Get battery infos.
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

#include <stdlib.h>
#include <string.h>

float getBatteryDecim() { //get the battery percentage as a float
	char buffer1[256];
	char buffer2[256];

	FILE *batteryFull = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
	FILE *batteryNow = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
	fgets(buffer1, sizeof(buffer1), batteryFull);
	fgets(buffer2, sizeof(buffer2), batteryNow);
	
	float batteryDecim = atof(buffer2)/atof(buffer1);
	batteryDecim *= 100;
	
	return batteryDecim;
}

char *getBatteryPcent(float batteryDecim) { //convert the battery percentage into a string
	sprintf(buffer, "%.f", batteryDecim);
	strcat(buffer, "%");
	return buffer;
}

char *getBatteryState() { //check if the battery is charging or discharging
	FILE *batteryState = fopen("/sys/class/power_supply/BAT0/status", "r");
	if(fgetc(batteryState)=='C') return "CHR: ";
	else return "BAT: ";
}

int testBatteryPcent(float batteryDecim) { //test the battery percent to colorize the output
	if(batteryDecim>25 || batteryDecim<95) return 0; //default color between 25% and 95%
	else return 1; //yellow under (or equal to) 25% and over (or equal to) 95%
}
