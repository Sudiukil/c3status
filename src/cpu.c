// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "cpu.h"
#include "general.h"
#include "display.h"

int get_cpu_load_pcent(void) {

	const char *statfile_path;
	FILE *statfile;
	long user, nice, system, idle, total;
	int diff_idle, diff_total;

	statfile_path = "/proc/stat";

	if(!(statfile = fopen(statfile_path, "r"))) {
		fprintf(stderr, "Error: Can't get CPU infos: %s: %s\n", statfile_path, strerror(errno));
		return -1;
	}

	fscanf(statfile, "cpu %ld %ld %ld %ld", &user, &nice, &system, &idle);

	fclose(statfile);

	total = user+nice+system+idle;
	diff_idle = idle-prev_idle;
	diff_total = total-prev_total;

	prev_idle = idle;
	prev_total = total;

	if(diff_total!=total) return((1000*(diff_total-diff_idle)/diff_total+5)/10);
	else return 0;
}

int get_cpu_temp(const char *current_temp_file_path) {

	FILE *current_temp_file;
	int current_temp;

	if(!(current_temp_file = fopen(current_temp_file_path, "r"))) {
		fprintf(stderr, "Error: Can't get CPU temperature: %s: %s\n", current_temp_file_path, strerror(errno));
		return -1;
	}

	fscanf(current_temp_file, "%d", &current_temp);

	fclose(current_temp_file);

	return current_temp/1000;
}

void update_cpu(cpu *c) {

	if(c->initialized==0) {
		if(!(c->warning_load_pcent)) c->warning_load_pcent = 75;
		if(!(c->critical_load_pcent)) c->critical_load_pcent = 90;
		if(!(c->current_temp_file_path)) c->current_temp_file_path = "/sys/class/hwmon/hwmon0/temp1_input";
		if(!(c->warning_temperature)) c->warning_temperature = 60;
		if(!(c->critical_temperature)) c->critical_temperature = 75;
		if(!(c->label)) c->label = "CPU";
		c->initialized = 1;
	}

	if(c->load_pcent_enable) {
		c->load_pcent = get_cpu_load_pcent();
		c->load_pcent_status = test_value(c->load_pcent, c->warning_load_pcent, c->critical_load_pcent);
	}

	if(c->temperature_enable) {
		c->temperature = get_cpu_temp(c->current_temp_file_path);
		c->temperature_status = test_value(c->temperature, c->warning_temperature, c->critical_temperature);
	}
}

void display_cpu(cpu *c) {	

	char *cpu_load_pcent;
	char *cpu_temperature;

	update_cpu(c);

	if(c->load_pcent_enable) {
		cpu_load_pcent = normalize(c->load_pcent, '%');
		display("cpu", "load_pcent", c->label, cpu_load_pcent, c->load_pcent_status);
		free(cpu_load_pcent);
	}

	if(c->temperature_enable) {
		cpu_temperature = normalize(c->temperature, 'C');
		if(c->load_pcent_enable) display("cpu", "temperature", NULL, cpu_temperature, c->temperature_status);
		else display("cpu", "temperature", c->label, cpu_temperature, c->temperature_status);
		free(cpu_temperature);
	}
}
