/*
Get disks infos.
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

char *getDiskUsage(char *disk) { //get disk usage percentage
	char command[111] = "disk=";
	strcat(command, disk);
	strcat(command, " && df -h --output=target,source,pcent | grep $disk | sed -e 's/ //g' -e 's/\\/dev\\/'\"$disk\"'/: /'");
	FILE *dfStdout = popen(command, "r");
	fgets(buffer, sizeof(buffer), dfStdout);
	pclose(dfStdout);
	buffer[strlen(buffer)-1] = '\0';
	return buffer;
}

int testDiskUsage(char *disk) { //check a disk usage percentage to colorize the output
	char command[103] = "disk=";
	strcat(command, disk);
	strcat(command, " && df -h --output=pcent,source | grep $disk | sed -e 's/ //g' -e 's/%\\/dev\\/'\"$disk\"'//'");
	FILE *dfStdout = popen(command, "r");
	fgets(buffer, sizeof(buffer), dfStdout);
	pclose(dfStdout);
	if(strlen(buffer)==3) {
		if((int)buffer[0]<55) return 0; //default color under 70%
		else if((int)buffer[0]>=55 && (int)buffer[0]<57) return 1; //yellow between 75% and 90%
		else return 2; //red over 90%
	}
	else if(strlen(buffer)==2) return 0;
	else return 2;
}
