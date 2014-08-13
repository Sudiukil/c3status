// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <sys/statvfs.h>
#include <math.h>

int get_fs_usage_pcent(char *mount_point) {

	struct statvfs buf;
	unsigned long block_size, total, avail, used;

	if(!statvfs(mount_point, &buf)) {
		block_size = buf.f_bsize;

		total = buf.f_blocks*block_size;
		avail = buf.f_bavail*block_size;
		used = total-avail;

		return((int)round((float)used/(float)total*100));
	}
	else return -1;
}
