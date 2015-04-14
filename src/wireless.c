// Copyright (c) 2014-2015, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "wireless.h"
#include "display.h"

void update_wireless(wireless *w) {

	if(!(w->initialized)) {
		if(!(w->interface)) w->interface = "wlan0";
		if(!(w->label)) w->label = "WIFI";
		w->initialized = 1;
	}
}

char *gen_wireless_ssid(const char *interface) {

	wireless_scan_head head;
	wireless_scan *result;
	iwrange range;
	int sock = iw_sockets_open();
	char *ssid = malloc(32*sizeof(char));

	if(iw_get_range_info(sock, (char*)interface, &range) < 0) {
		fprintf(stderr, "Error: Can't get %s wireless ssid: %s\n", interface, strerror(errno));
		snprintf(ssid, 32, "Error");
		return ssid;
	}

	if(iw_scan(sock, (char*)interface, range.we_version_compiled, &head) < 0) {
		fprintf(stderr, "Error: Can't get %s wireless ssid: %s\n", interface, strerror(errno));
		snprintf(ssid, 32, "No Wifi");
		return ssid;
	}

	result = head.result;
	while(result) {
		snprintf(ssid, 32, "%s", result->b.essid);
		result = result->next;
	}

	close(sock);
	free(head.result);

	if(strlen(ssid)==0) {
		snprintf(ssid, 32, "%s", "No Wifi");
		return ssid;
	}

	return ssid;
}

void display_wireless(wireless *w) {

	char *wireless_ssid;

	update_wireless(w);

	wireless_ssid = gen_wireless_ssid(w->interface);

	display("wireless", w->interface, w->label, wireless_ssid, 0);

	free(wireless_ssid);
}
