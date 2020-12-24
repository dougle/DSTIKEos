/*
 * Watch.h
 */

#ifndef DSTIKEOS_WATCH_H
#define DSTIKEOS_WATCH_H

#include <memory>
#include <Eventually.h>

#include "Configuration.h"
#include "State.h"
#include "Display.h"
#include "WIFI.h"

// Button pin definitions
#define BUTTON_UP 12
#define BUTTON_DOWN 13
#define BUTTON_SELECT 14

class Watch {
public:
	Watch();
	Display display = Display();
	WIFI wifi = WIFI();

	void begin(std::shared_ptr<Configuration> config, std::shared_ptr<State> state);
	void loop();

	void clockTick(EvtListener lstn);
	void buttonPress(EvtPinListener lstn);

private:
	std::shared_ptr<Configuration> configuration;
	std::shared_ptr<State> state;
	EvtManager eventMgr;
	EvtTimeListener *displayTimer;
};

#endif //DSTIKEOS_WATCH_H
