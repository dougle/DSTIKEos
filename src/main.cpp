/**************************************************************************
 * DSTRIKE ESP8266 Watch 2 Base OS
 * 
 * https://google.github.io/styleguide/cppguide.html#General_Naming_Rules
 *
 * rst cause Values
 * rst cause : 1
 * 	Power-on-reset, indicates that the ESP8266 went through a power cycle and rebooted as a result of that.
 * 	Often seen randomly if your power supply is dodgy.
 * rst cause : 2
 * 	External reset is triggered by the reset pin of the ESP8266. This is the reason you would see when the ESP8266 is reset explicitly via the pin or when the ESP8266 wakes up from deep sleep (because that involves a GPIO driving the reset pin).
 * rst cause : 4
 * 	Hardware watchdog reset, triggered when your code is stuck or malfunctioning. This is usually a result of improper loading of watchdog timer, which is enabled by default on the SDKs provided by Espressif.
 *
 * no warranty is given.
**************************************************************************/

#include <Arduino.h>
#include <memory>
#include <Eventually.h>

#include "core/Configuration.h"
#include "core/State.h"
#include "core/Watch.h"
#include "core/EventActions.h"

Watch watch = Watch();
auto configuration = std::shared_ptr<Configuration>(new Configuration());
auto state = std::shared_ptr<State>(new State());

void setup() {
	Serial.begin(115200);
	Serial.flush();
	delay(500);

	watch.begin(configuration, state);
}


void loop() {
	watch.loop();
	delay(10); // required for watchdog
}