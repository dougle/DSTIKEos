/*
 * Configuration.h
 */

#ifndef DSTIKEOS_STATE_H
#define DSTIKEOS_STATE_H

#include <Time.h>

class State {
public:
	unsigned long display_duration;
	bool display_on = true;

	time_t now;
	tm local_now;
	tm rendered_time;

	unsigned int wifi_state = 0;
};

#endif //DSTIKEOS_STATE_H
