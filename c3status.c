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
