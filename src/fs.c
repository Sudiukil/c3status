// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "fs.h"
#include "general.h"
#include "display.h"

int get_fs_usage_pcent(const char *mount_point) {

	struct statvfs buf;
	unsigned long block_size, total, avail, used;

	if(!statvfs(mount_point, &buf)) {
		block_size = buf.f_bsize;

		total = buf.f_blocks*block_size;
		avail = buf.f_bavail*block_size;
		used = total-avail;

		return((int)round((float)used/(float)total*100));
	}
	else {
		fprintf(stderr, "Error: Can't get %s usage percentage\n", mount_point);
		return -1;
	}
}

void update_fs(fs *f) {

	if(!(f->initialized)) {
		if(!(f->mount_point)) f->mount_point = "/";
		if(!(f->warning_usage_pcent)) f->warning_usage_pcent = 75;
		if(!(f->critical_usage_pcent)) f->critical_usage_pcent = 90;
		if(!(f->label)) f->label = f->mount_point;
	}

	f->usage_pcent = get_fs_usage_pcent(f->mount_point);
	f->usage_pcent_status = test_value(f->usage_pcent, f->warning_usage_pcent, f->critical_usage_pcent);
}

void display_fs(fs *f) {

	char *fs_usage_pcent;

	update_fs(f);

	fs_usage_pcent = normalize(f->usage_pcent, '%');

	display("fs", f->mount_point, f->label, fs_usage_pcent, f->usage_pcent_status);

	free(fs_usage_pcent);
}
