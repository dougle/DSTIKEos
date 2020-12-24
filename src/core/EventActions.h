/*
 * EventActions.h
 */

#ifndef DSTIKEOS_EVENTACTIONS_H
#define DSTIKEOS_EVENTACTIONS_H

#include "Watch.h"

class EventActions {
public:
	static bool clockTick(EvtListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.clockTick(lstn);
		return false;
	}

	static bool clearSplash(EvtListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.display.clearSplash();
		watch.display.showStatusIcons();
		return false;
	}

	static bool wifiStatusChange(EvtWifiStateListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.wifi.statusChange(lstn, ctx);
		watch.display.showStatusIcons();
		return false;
	}

	static bool buttonPress(EvtPinListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.buttonPress(lstn);
		return false;
	}

	static bool displayTimeout(EvtTimeListener lstn, EvtContext ctx) {
		extern Watch watch;
		watch.display.off();

		return false;
	}
};

#endif //DSTIKEOS_EVENTACTIONS_H
