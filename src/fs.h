#include <sys/statvfs.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int get_fs_usage_pcent(char *mount_point) {

	struct statvfs buf;
	unsigned long blocks, block_size, avail_blocks, total, avail, used;

	if(!statvfs(mount_point, &buf)) {
		blocks = buf.f_blocks;
		block_size = buf.f_bsize;
		avail_blocks = buf.f_bavail;

		total = blocks*block_size;
		avail = avail_blocks*block_size;
		used = total-avail;
	}
	else return -1;

	return((int)round((float)used/(float)total*100));
}

char *gen_fs_str_usage_pcent(int disk_usage_pcent) {

	if(disk_usage_pcent!=-1) {
		char *str_pcent = calloc(8, sizeof(char));

		strcat(str_pcent, itoa(disk_usage_pcent));
		str_pcent[strlen(str_pcent)] = '%';
		str_pcent[strlen(str_pcent)] = '\0';

		return str_pcent;
	}
	else return "Error";
}

int test_fs_usage_pcent(int disk_usage_pcent) {

	if(disk_usage_pcent>=75 && disk_usage_pcent<90) return 1;
	if(disk_usage_pcent>=90) return 2;
	if(disk_usage_pcent==-1) return 2;
	return 0;
}
