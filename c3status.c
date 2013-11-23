/*
Main part of c3status, get and display all infos.
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>

char buffer[256]; //buffer used in most functions

#include "src/time.h"
#include "src/volume.h"
#include "src/disk.h"
#include "src/battery.h"
#include "src/livebox.h"
#include "src/moc.h"
#include "src/display.h"

int main() {
	printf("{\"version\":1}");
	printf("[[],");
	while(1) {
		sleep(1); //refresh c3status all every second
		fflush(stdout);
		printf("[");
		//display("MOC: ", getMocInfos(testMocState()), 0, 0);
		//display("IP Publique: ", getLiveboxIp(), 0, 0);
		//display("", getDiskUsage("sda6"), testDiskUsage("sda6"), 0);
		//display("", getDiskUsage("sda7"), testDiskUsage("sda7"), 0);
		//display("", getDiskUsage("sda8"), testDiskUsage("sda8"), 0);
		//display("", getDiskUsage("sda9"), testDiskUsage("sda9"), 0);
		//display("", getDiskUsage("sda10"), testDiskUsage("sda10"), 0);
		//display("", getBattery(), testBatteryPcent(), 0);
		display("", getTime(), 0, 0);
		display("", getVolume(), testVolumeState(),1);
		printf("],");
	}
	return 0;
}
