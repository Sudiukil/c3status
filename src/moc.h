/*
Get MOC infos.
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

int testMocState() { //test if moc is running
	FILE *psStdout = popen("ps -e | grep mocp > /dev/null; echo $?", "r");
	fgets(buffer, sizeof(buffer), psStdout);
	pclose(psStdout);
	if(buffer[0]=='0') return 0;
	else return 1;
}

char *getMocInfos(int returnCode) { //get music infos from moc only if it is running
	if(returnCode==0) {
		char command[46] = "mocp -Q %state:\\ %title\\ %ct\\/%tl\\ \\[%tt]";
		FILE *mocpStdout = popen(command, "r");
		fgets(buffer, sizeof(buffer), mocpStdout);
		pclose(mocpStdout);
		if(buffer[0]=='S') return "STOP";
		else {
			buffer[strlen(buffer)-1] = '\0';
			return buffer;
		}
	}
	else return "STOP";
}
