/*
 * Watch.cpp
 */
#include <Eventually.h>
#include "Listeners.h"
#include "Watch.h"
#include "WIFI.h"
#include "EventActions.h"

Watch::Watch() { }

void Watch::begin(std::shared_ptr<Configuration> config, std::shared_ptr<State> state) {
	Serial.println("Begin Watch");

	this->configuration = config;
	this->state = state;

	pinMode(BUTTON_UP, INPUT_PULLUP);
	pinMode(BUTTON_DOWN, INPUT_PULLUP);
	pinMode(BUTTON_SELECT, INPUT_PULLUP);

	this->display.begin(this->configuration, this->state);
	this->wifi.begin(this->configuration, this->state);

	this->display.showSplash();

	// setup initial event listeners
	this->eventMgr.resetContext();

	this->eventMgr.addListener(new EvtTimeListener(1000, true, (EvtAction)&EventActions::clockTick));
	this->eventMgr.addListener(new EvtTimeListener((*this->configuration).Splash_Timeout * 1000, false, (EvtAction)&EventActions::clearSplash));

//	// catch button clicks
	this->eventMgr.addListener(new EvtPinListener(BUTTON_UP, 100, LOW, (EvtAction)&EventActions::buttonPress));
	this->eventMgr.addListener(new EvtPinListener(BUTTON_DOWN, 100, LOW, (EvtAction)&EventActions::buttonPress));
	this->eventMgr.addListener(new EvtPinListener(BUTTON_SELECT, 100, LOW, (EvtAction)&EventActions::buttonPress));

	this->eventMgr.addListener(new EvtWifiStateListener((EvtAction)&EventActions::wifiStatusChange));

	this->displayTimer = new EvtTimeListener(((*this->configuration).Splash_Timeout + (*this->configuration).Display_Timeout) * 1000, false, (EvtAction)&EventActions::displayTimeout);
	this->eventMgr.addListener(this->displayTimer);
}

void Watch::clockTick(EvtListener lstn){
	(*this->state).now = now();
	localtime_r(&(*this->state).now, &(*this->state).localNow);

	this->display.showClock((*this->state).localNow);

	this->display.render();
}

void Watch::buttonPress(EvtPinListener lstn){
	// cancel the display off timer
	if (this->displayTimer)
		this->eventMgr.removeListener(this->displayTimer);

	switch(lstn.pin){
		default:
			Serial.printf("Unrecognised pin press %d\n", lstn.pin);
			break;
	}

	if ( !(*this->state).displayOn)
		this->display.on();

	// start a new display off timer
	this->displayTimer = new EvtTimeListener((*this->configuration).Display_Timeout * 1000, false, (EvtAction)&EventActions::displayTimeout);
	this->eventMgr.addListener(this->displayTimer);
}

void Watch::loop() {
//	Serial.println("Watch loop");

	this->eventMgr.loopIteration();
}