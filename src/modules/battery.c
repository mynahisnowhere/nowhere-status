#include <math.h>
#include "nowhere_status.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef BAT0
#define BAT0 "/sys/class/power_supply/BAT0/"
#endif

#ifndef DIS
#define DIS "Discharging\n"
#endif

#ifndef CHR
#define CHR "Charging\n"
#endif

#ifndef FUL
#define FUL "Full\n"
#endif

#ifndef NOT_CHR
#define NOT_CHR "Not charging\n"
#endif

int nowhere_battery(struct node *_node) {
	char buffer[4096];

	if (nowhere_device_read(buffer, 4096, BAT0"capacity") == -1) return -1;
	int capacity = (int)strtol(buffer, NULL, 0);
	
	if (nowhere_device_read(buffer, 4096, BAT0"status") == -1) return -1;

	char status[4] = "UNK";

	// Assuming implementation of /sys/class/power_supply/BAT0/status
	// prints "Discharging", "Charging", "Full", and "Not charging"
	switch (buffer[0]) {
	case 'D':
		snprintf(status, 4, "DIS");
		break;
	case 'C':
		snprintf(status, 4, "CHR");
		break;
	case 'F':
		snprintf(status, 4, "FUL");
		break;
	case 'N':
		snprintf(status, 4, "INH");
		break;
	}

	float normal = 1.0 - log(1.0 + ((float)capacity / 100.0f));

	int red = normal * 255.0f;
	int green = (1.0f - normal) * 255.0f;

	snprintf(_node->name, NOWHERE_NAMSIZ, "bat");
	snprintf(_node->full_text, NOWHERE_TXTSIZ, "BAT0 %d%% %s", capacity, status);
	_node->alt_text[0] = '\0';
	_node->color.r = red;
	_node->color.g = green;
	_node->color.b = 0;

	return 0;
}
