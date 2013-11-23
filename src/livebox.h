/*
Get public IP for Livebox owners.
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

char *getLiveboxIp() { //get public ip from Livebox, may work for some other router but not made for it
	FILE *curlStdout = popen("curl -s 192.168.1.1 | grep \"90.\" | cut -d '>' -f 2 | cut -d '<' -f 1", "r");
	fgets(buffer, sizeof(buffer), curlStdout);
	pclose(curlStdout);
	buffer[strlen(buffer)-1] = '\0';
	return buffer;
}
