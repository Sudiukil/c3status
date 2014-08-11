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
#include "src/net.h"
//#include "src/moc.h"
#include "src/ncmpcpp.h"

int main(int argc, char *argv[]) {

	int num_data;
	char *str_data;

	printf("{\"version\":1}\n");
	printf("[[],\n");

	while(1) {
		sleep(1);
		fflush(stdout);
		printf("[\n");

		str_data = get_ncmpcpp_infos();
		display(
				"ncmpcpp",
				"ncmpcpp",
				"♪",
				str_data,
				"#767676",
				NULL,
				0,
				0
		);
		free(str_data);

		str_data = gen_str_speed(get_dl_speed("enp4s0"), 'o', 0);
		display(
				"net",
				"download",
				"NET",
				str_data,
				"#767676",
				NULL,
				0,
				0
		);
		free(str_data);

		str_data = gen_str_speed(get_ul_speed("enp4s0"), 'o', 0);
		display(
				"net",
				"upload",
				NULL,
				str_data,
				"#767676",
				NULL,
				0,
				0
		);
		free(str_data);

		num_data = get_cpu_load_pcent();
		str_data = normalize(num_data, '%');
		display(
				"cpu",
				"load",
				"CPU",
				str_data,
				"#767676",
				NULL,
				test_value(num_data, 75, 90),
				0
		);
		free(str_data);

		num_data = get_cpu_temp();
		str_data = normalize(num_data, 'C');
		display(
				"temp",
				"cpu",
				NULL,
				str_data,
				"#767676",
				NULL,
				test_value(num_data, 50, 75),
				0
		);
		free(str_data);

		num_data = get_mem_usage_pcent();
		str_data = normalize(num_data, '%');
		display(
				"mem",
				"load",
				"MEM",
				str_data,
				"#767676",
				NULL,
				test_value(num_data, 50, 75),
				0
		);
		free(str_data);

		num_data = get_fs_usage_pcent("/");
		str_data = normalize(num_data, '%');
		display(
				"disk",
				"root",
				"/",
				str_data,
				"#767676",
				NULL,
				test_value(num_data, 75, 90),
				0
		);
		free(str_data);

		num_data = get_fs_usage_pcent("/usr");
		str_data = normalize(num_data, '%');
		display(
				"disk",
				"usr",
				"/usr",
				str_data,
				"#767676",
				NULL,
				test_value(num_data, 75, 90),
				0
		);
		free(str_data);

		num_data = get_fs_usage_pcent("/home");
		str_data = normalize(num_data, '%');
		display(
				"disk",
				"home",
				"/home",
				str_data,
				"#767676",
				NULL,
				test_value(num_data, 75, 90),
				0
		);
		free(str_data);

		num_data = get_battery_pcent();
		str_data = gen_battery_str_pcent(num_data);
		display(
				"battery",
				"bat0",
				"BAT",
				str_data,
				"#767676",
				NULL,
				test_battery_pcent(num_data),
				0
		);
		free(str_data);

		int *alsa_infos = get_alsa_infos("Master");
		str_data = gen_alsa_str_volume_pcent(alsa_infos);
		display(
				"volume",
				"master",
				"VOL",
				str_data,
				"#767676",
				NULL,
				test_alsa_volume_pcent(alsa_infos, 75),
				0
		);
		free(alsa_infos);
		free(str_data);

		str_data = get_time("%d/%m/%Y - %H:%M:%S");
		display(
				"time",
				"local",
				NULL,
				str_data,
				NULL,
				NULL,	
				0,
				1
		);
		free(str_data);

		printf("],\n");
	}

	return 0;
}
