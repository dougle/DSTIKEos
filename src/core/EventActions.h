/*
 * EventActions.h
 */

#ifndef DSTIKEOS_EVENTACTIONS_H
#define DSTIKEOS_EVENTACTIONS_H

#include "Watch.h"

class EventActions {
public:
	static bool clock_tick(EvtListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.clock_tick(lstn);
		return false;
	}

	static bool clear_splash(EvtListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.display.clearSplash();
		return false;
	}

	static bool wifi_status_change(EvtWifiStateListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.wifi.status_change(lstn, ctx);
		return false;
	}

	static bool button_press(EvtPinListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.button_press(lstn);
		return false;
	}

	static bool display_timeout(EvtTimeListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.display.off();

		return false;
	}
};

#endif //DSTIKEOS_EVENTACTIONS_H
