/*
Display infos formated as JSON for i3bar.
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

void display(char *prefix, char *data, int priority, int last) { //display an info formated as JSON
	char jsonStr[256] = "{\"full_text\":\"";
	strcat(jsonStr, prefix); //add a optionnal prefix to the info
	strcat(jsonStr, data);
	switch(priority) { //colorize the output according to the priority
		case 0:
			strcat(jsonStr, "\"}"); //no color for low priority
			break;
		case 1:
			strcat(jsonStr, "\",\"color\":\"#ffff00\"}"); //yellow for important
			break;
		case 2:
			strcat(jsonStr, "\",\"color\":\"#ff0000\"}"); //red for very important
			break;
	}
	if(last==0) strcat(jsonStr, ","); //append a last "," only if the info is not the last to be diplayed
	printf("%s", jsonStr);
}
