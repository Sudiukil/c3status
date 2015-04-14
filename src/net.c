// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "net.h"
#include "display.h"

long get_dl_speed(const char *interface) {

	const char *net_dev_file_path;
	FILE *net_dev_file;
	char *buffer, *target, *found;
	int is_found;
	long received, diff;

	net_dev_file_path = "/proc/net/dev";

	if(!(net_dev_file = fopen(net_dev_file_path, "r"))) {
		fprintf(stderr, "Error: Can't get %s download speed: %s: %s\n", interface, net_dev_file_path, strerror(errno));
		return -1;
	}

	buffer = malloc(256*sizeof(char));
	target = malloc(8*sizeof(char));
	found = malloc(8*sizeof(char));

	snprintf(target, 8, "%s:", interface);
	is_found = 0;
	while(!(is_found) && fgets(buffer, 256, net_dev_file)) {
		sscanf(buffer, "%s:", found);
		if(strcmp(found, target)==0) is_found = 1;
	}

	free(target);
	free(found);
	fclose(net_dev_file);

	if(!(is_found)) {
		fprintf(stderr, "Error: Can't get %s download speed: %s not found in %s\n", interface, interface, net_dev_file_path);
		free(buffer);
		return -1;
	}

	if(strlen(format_dl)==0) {
		snprintf(format_dl, 16, "%s: %%ld", interface);
	}

	sscanf(buffer, format_dl, &received);

	free(buffer);

	diff = received-prev_received;

	prev_received = received;

	if(diff!=received) return diff;
	else return 0;
}

long get_ul_speed(const char *interface) {

	const char *net_dev_file_path;
	FILE *net_dev_file;
	char *buffer, *target, *found;
	int is_found;
	long transmitted, diff, d;

	net_dev_file_path = "/proc/net/dev";

	if(!(net_dev_file = fopen(net_dev_file_path, "r"))) {
		fprintf(stderr, "Error: Can't get %s upload speed: %s: %s\n", interface, net_dev_file_path, strerror(errno));
		return -1;
	}

	buffer = malloc(256*sizeof(char));
	target = malloc(8*sizeof(char));
	found = malloc(8*sizeof(char));

	snprintf(target, 8, "%s:", interface);
	is_found = 0;
	while(!(is_found) && fgets(buffer, 256, net_dev_file)) {
		sscanf(buffer, "%s:", found);
		if(strcmp(found, target)==0) is_found = 1;
	}

	free(target);
	free(found);
	fclose(net_dev_file);

	if(!(is_found)) {
		fprintf(stderr, "Error: Can't get %s upload speed: %s not found in %s\n", interface, interface, net_dev_file_path);
		free(buffer);
		return -1;
	}

	if(strlen(format_ul)==0) {
		snprintf(format_ul, 64, "%s: %%ld %%ld %%ld %%ld %%ld %%ld %%ld %%ld %%ld", interface);
	}

	sscanf(buffer, format_ul, &d, &d, &d, &d, &d, &d, &d, &d, &transmitted);

	free(buffer);

	diff = transmitted-prev_transmitted;

	prev_transmitted = transmitted;

	if(diff!=transmitted) return diff;
	else return 0;
}

char *gen_str_speed(long speed, char unit) {

	char *str_speed = malloc(16*sizeof(char));

	if(speed!=-1) {
		if(speed>1048576) {
			snprintf(str_speed, 16, "%.1f Mi%c/s", (float)speed/1024/1024, unit);
		}
		else {
			snprintf(str_speed, 16, "%ld Ki%c/s", speed/1024, unit);
		}
	}
	else snprintf(str_speed, 16, "Error");

	return str_speed;
}

void update_net(net *n) {

	if(!(n->initialized)) {
		if(!(n->interface)) n->interface = "eth0";
		if(!(n->unit)) n->unit = 'B';
		if(!(n->label)) n->label = "NET";
		n->initialized = 1;
	}

	n->dl_speed = get_dl_speed(n->interface);
	n->ul_speed = get_ul_speed(n->interface);
}

void display_net(net *n) {

	char *dl_speed, *ul_speed;

	update_net(n);

	dl_speed = gen_str_speed(n->dl_speed, n->unit);
	ul_speed = gen_str_speed(n->ul_speed, n->unit);

	display("net", "download", n->label, dl_speed, 0);
	display("net", "upload", NULL, ul_speed, 0);

	free(dl_speed);
	free(ul_speed);
}
