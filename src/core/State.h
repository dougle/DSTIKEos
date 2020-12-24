/*
 * Configuration.h
 */

#ifndef DSTIKEOS_STATE_H
#define DSTIKEOS_STATE_H

#include <Time.h>

class State {
public:
	bool displayOn = true;

	time_t now;
	tm localNow;
	tm renderedTime;

	unsigned int wifiState = 0;
};

#endif //DSTIKEOS_STATE_H
