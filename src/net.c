// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "net.h"
#include "display.h"

unsigned long long *get_dl_ul_speed(const char *interface) {

	const char *net_dev_file_path;
	FILE *net_dev_file;
	char *buffer, *stripped_line, *found_iface;
	int done, i, j;
	char last_char;
	unsigned long long received_bytes, transmitted_bytes, diff;
	unsigned long long *dl_ul;

	net_dev_file_path = "/proc/net/dev";
	dl_ul = malloc(2*sizeof(unsigned long long));

	if(!(net_dev_file = fopen(net_dev_file_path, "r"))) {
		fprintf(stderr, "Error: Can't get %s upload speed: %s: %s\n", interface, net_dev_file_path, strerror(errno));
		dl_ul[0] = -1;
		dl_ul[1] = -1;
		return dl_ul;
	}

	buffer = calloc(256, sizeof(char));
	stripped_line = malloc(256*sizeof(char));
	found_iface = malloc(16*sizeof(char));
	done = 0;
	j = 0;
	last_char = ' ';

	fgets(buffer, 256, net_dev_file);
	fgets(buffer, 256, net_dev_file);
	while(!done && fgets(buffer, 256, net_dev_file)) {

		for(i=0; i<256; i++) {
			if(buffer[i]!=' ') {
				if(buffer[i]==':') {
					stripped_line[j] = ' ';
					j++;
				}
				stripped_line[j] = buffer[i];
				j++;
				last_char = buffer[i];
			}
			else {
				if(last_char!=' ') {
					stripped_line[j] = buffer[i];
					j++;
					last_char = ' ';
				}
			}
		}

		sscanf(stripped_line, "%s : %Ld %Ld %Ld %Ld %Ld %Ld %Ld %Ld %Ld", found_iface, &received_bytes, &transmitted_bytes, &transmitted_bytes, &transmitted_bytes, &transmitted_bytes, &transmitted_bytes, &transmitted_bytes, &transmitted_bytes, &transmitted_bytes);

		if(strcmp(interface, found_iface)==0) done = 1;

		stripped_line[j] = '\0';
		j = 0;
		last_char = ' ';
	}

	fclose(net_dev_file);
	free(buffer);
	free(stripped_line);
	free(found_iface);

	dl_ul[0] = 0;
	dl_ul[1] = 0;

	diff = received_bytes-prev_received;
	prev_received = received_bytes;
	if(diff!=received_bytes) dl_ul[0] = diff;

	diff = transmitted_bytes-prev_transmitted;
	prev_transmitted = transmitted_bytes;
	if(diff!=transmitted_bytes) dl_ul[1] = diff;

	return dl_ul;
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

	unsigned long long *dl_ul;

	if(!(n->initialized)) {
		if(!(n->interface)) n->interface = "eth0";
		if(!(n->unit)) n->unit = 'B';
		if(!(n->label)) n->label = "NET";
		n->initialized = 1;
	}

	dl_ul = get_dl_ul_speed(n->interface);

	n->dl_speed = dl_ul[0];
	n->ul_speed = dl_ul[1];

	free(dl_ul);
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
