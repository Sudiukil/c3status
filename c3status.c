#include <stdio.h>
#include <unistd.h>

#include "src/general.h"
#include "src/display.h"
#include "src/time.h"
#include "src/battery.h"
#include "src/volume.h"
#include "src/fs.h"
#include "src/mem.h"
#include "src/cpu.h"
#include "src/temp.h"
#include "src/moc.h"

int main(int argc, char *argv[]) {

	printf("{\"version\":1}\n");
	printf("[[],\n");

	while(1) {
		sleep(1);
		fflush(stdout);
		printf("[\n");

		display(
				"moc",
				"moc",
				"MOC",
				get_moc_infos(),
				"#767676",
				NULL,
				0,
				0
		);

		int cpu_load_pcent = get_cpu_load_pcent();
		display(
				"cpu",
				"load",
				"CPU",
				normalize(cpu_load_pcent, '%'),
				"#767676",
				NULL,
				test_value(cpu_load_pcent, 75, 90),
				0
		);

		int cpu_temp = get_cpu_temp();
		display(
				"temp",
				"cpu",
				NULL,
				normalize(cpu_temp, 'C'),
				"#767676",
				NULL,
				test_value(cpu_temp, 50, 75),
				0
		);

		int mem_usage_pcent = get_mem_usage_pcent();
		display(
				"mem",
				"mem",
				"MEM",
				normalize(mem_usage_pcent, '%'),
				"#767676",
				NULL,
				test_value(mem_usage_pcent, 50, 75),
				0
		);

		int root_usage_pcent = get_fs_usage_pcent("/");
		display(
				"disk",
				"root",
				"/",
				normalize(root_usage_pcent, '%'),
				"#767676",
				NULL,
				test_value(root_usage_pcent, 75, 90),
				0
		);

		int usr_usage_pcent = get_fs_usage_pcent("/usr");
		display(
				"disk",
				"usr",
				"/usr",
				normalize(usr_usage_pcent, '%'),
				"#767676",
				NULL,
				test_value(usr_usage_pcent, 75, 90),
				0
		);

		int home_usage_pcent = get_fs_usage_pcent("/home");
		display(
				"disk",
				"home",
				"/home",
				normalize(home_usage_pcent, '%'),
				"#767676",
				NULL,
				test_value(home_usage_pcent, 75, 90),
				0
		);

		int battery_pcent = get_battery_pcent();
		display(
				"battery",
				"bat0",
				"BAT",
				gen_battery_str_pcent(battery_pcent),
				"#767676",
				NULL,
				test_battery_pcent(battery_pcent),
				0
		);

		int *alsa_infos = get_alsa_infos("Master");
		display(
				"volume",
				"master",
				"VOL",
				gen_alsa_str_volume_pcent(alsa_infos),
				"#767676",
				NULL,
				test_alsa_volume_pcent(alsa_infos, 50),
				0
		);

		display(
				"time",
				"local",
				NULL,
				get_time("%d/%m/%Y - %H:%M:%S"),
				NULL,
				NULL,	
				0,
				1
		);

		printf("],\n");
	}

	return 0;
}
