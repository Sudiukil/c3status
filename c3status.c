/*
 * Main part of c3status, get and display all infos.
 * Copyright (C) 2013 Quentin Sonrel (Sudiukil).
 *
 * This file is part of c3status.
 *
 * c3status is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * c3status is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with c3status.  If not, see <http://www.gnu.org/licenses/>.
 * */

#include <stdio.h>
#include <unistd.h>

#include "src/vtoa.h"

#include "src/display.h"
#include "src/time.h"
#include "src/volume.h"
#include "src/fs.h"
#include "src/battery.h"

int main(int argc, char *argv[]) {

	printf("{\"version\":1}");
	printf("[[],");

loop:
	sleep(1);
	fflush(stdout);
	printf("[");

	int root_usage_pcent = get_fs_usage_pcent("/");
	display("/: ", gen_fs_str_usage_pcent(root_usage_pcent), test_fs_usage_pcent(root_usage_pcent), 0);

	int home_usage_pcent = get_fs_usage_pcent("/home");
	display("/home: ", gen_fs_str_usage_pcent(home_usage_pcent), test_fs_usage_pcent(home_usage_pcent), 0);

	if(argc>1 && argv[1][0]=='-' && argv[1][1]=='b') {
		int battery_pcent = get_battery_pcent();
		display(get_battery_status(), gen_battery_str_pcent(battery_pcent), test_battery_pcent(battery_pcent), 0);
	}

	display(NULL, get_date_time('/', ':'), 0, 0);

	int *alsa_infos = get_alsa_infos("Master");
	display(NULL, gen_alsa_str_volume_pcent(alsa_infos), test_alsa_volume_pcent(alsa_infos, 50), 1);

	printf("],");
	goto loop;

	return 0;
}
