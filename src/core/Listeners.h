/*
 * Listeners.h
 */

#ifndef DSTIKE_EVENTS_LISTENERS_H
#define DSTIKE_EVENTS_LISTENERS_H

#include <Eventually.h>

class EvtWifiStateListener : public EvtListener {
public:
	EvtWifiStateListener(EvtAction action);

	char* getStatusName(int code);
	int previousState;
	int currentState;
	void setupListener();

	bool isEventTriggered();
};


#endif //DSTIKE_EVENTS_LISTENERS_H
