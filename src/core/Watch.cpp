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
	this->event_mgr.resetContext();

	this->event_mgr.addListener(new EvtTimeListener(1000, true, (EvtAction)&EventActions::clock_tick));
	this->event_mgr.addListener(new EvtTimeListener((*this->configuration).Splash_Timeout * 1000, false, (EvtAction)&EventActions::clear_splash));

//	// catch button clicks
	this->event_mgr.addListener(new EvtPinListener(BUTTON_UP, 100, LOW, (EvtAction)&EventActions::button_press));
	this->event_mgr.addListener(new EvtPinListener(BUTTON_DOWN, 100, LOW, (EvtAction)&EventActions::button_press));
	this->event_mgr.addListener(new EvtPinListener(BUTTON_SELECT, 100, LOW, (EvtAction)&EventActions::button_press));

	this->event_mgr.addListener(new EvtWifiStateListener((EvtAction)&EventActions::wifi_status_change));

	this->displayTimer = new EvtTimeListener(((*this->configuration).Splash_Timeout + (*this->configuration).Display_Timeout) * 1000, false, (EvtAction)&EventActions::display_timeout);
	this->event_mgr.addListener(this->displayTimer);
}

void Watch::clock_tick(EvtListener lstn){
	(*this->state).now = now();
	localtime_r(&(*this->state).now, &(*this->state).local_now);

	this->display.showClock((*this->state).local_now);

	this->display.render();
}

void Watch::button_press(EvtPinListener lstn){
	// cancel the display off timer
	if (this->displayTimer)
		this->event_mgr.removeListener(this->displayTimer);

	switch(lstn.pin){
		default:

			break;
	}

	this->display.on();

	// start a new display off timer
	this->displayTimer = new EvtTimeListener((*this->configuration).Display_Timeout * 1000, false, (EvtAction)&EventActions::display_timeout);
	this->event_mgr.addListener(this->displayTimer);
}

void Watch::loop() {
//	Serial.println("Watch loop");

	this->event_mgr.loopIteration();
}