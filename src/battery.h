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

char *getBattery() { //get the battery percentage and the state (Charging/Discharging)
	FILE *acpiStdout = popen("acpi -b | cut -d ' ' -f 3,4,5 | sed -e 's/Charging,/CHR:/' -e 's/Discharging,/BAT:/' -e 's/,//g'", "r");
	fgets(buffer, sizeof(buffer), acpiStdout);
	pclose(acpiStdout);
	buffer[strlen(buffer)-1] = '\0';
	return buffer;
}

int testBatteryPcent() { //test the battery percent to colorize the output
	FILE *acpiStdout = popen("acpi -b | cut -d ' ' -f 4 | sed -e 's/%,//'", "r");
	fgets(buffer, sizeof(buffer), acpiStdout);
	pclose(acpiStdout);
	if(strlen(buffer)==3) {
		if((int)buffer[0]>=52 && (int)buffer[0]<56) return 0; //default color between 40% and 80%
		else if((int)buffer[0]<52) return 1; //yellow under 40%...
		else if((int)buffer[0]>=56) return 1; //... and over 80%
		else return 2; //red under 10% and at 100%
	}
	else return 2;
}
