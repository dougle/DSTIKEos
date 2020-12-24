/*
 * WIFI.cpp
 */

#include <ESP8266WiFi.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <Eventually.h>

#include "WIFI.h"
#include "Configuration.h"

WIFI::WIFI() { }

void WIFI::begin(std::shared_ptr<Configuration> config, std::shared_ptr<State> state) {
	Serial.println("Begin WIFI");
	this->configuration = config;
	this->state = state;

	this->connect((*this->configuration).WiFI_Connections[this->current_ssid_index][0], (*this->configuration).WiFI_Connections[this->current_ssid_index][1]);
}

/**
 *
 * https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/include/wl_definitions.h#L50
 *
 * @param ssid
 * @param password
 * @return
 */
void WIFI::connect(const char *ssid, const char *password) {
	Serial.printf("Attempting to connect to %s wifi network\n", ssid);

	WiFi.begin(ssid, password);
}

void WIFI::loop() {
	Serial.println("WIFI loop");
}

bool WIFI::openAP() {
	char* ssid = (*this->configuration).AP_SSID;
	unsigned int channel = (rand()%12) + 1;

	Serial.printf("Bringing up AP on channel: %d with ssid: %s\n", channel, ssid);

	// generate a password
	if ((*this->configuration).AP_Password == (char *)"") {
		Serial.println("Generating AP password");
		(*this->configuration).AP_Password = (char *)"generated-password";
	}

	return WiFi.softAP(ssid, (*this->configuration).AP_Password, channel, (*this->configuration).AP_Hidden?1:0);
}

void WIFI::status_change(EvtWifiStateListener lstn, EvtContext ctx) {
	Serial.printf("WiFi status changed from %s to %s\n", lstn.getStatusName(lstn.previousState), lstn.getStatusName(lstn.currentState));

//	clear_wifi_symbol();
//
//	draw_wifi_symbol(lstn);
//
//	if (lstn.currentState != WL_CONNECTED) {
//		if (!blink_wifi_listener) {
//			blink_wifi_listener = new EvtTimeListener(1000, true, (EvtAction) blink_wifi);
//			mgr.addListener(blink_wifi_listener);
//		}
//	} else {
//		if(blink_wifi_listener)
//			mgr.removeListener(blink_wifi_listener);
//	}
//
//	OLED.display();

	// move on to next wifi
	unsigned int number_of_networks = sizeof((*this->configuration).WiFI_Connections) / sizeof((*this->configuration).WiFI_Connections[0]);

	switch (lstn.currentState) {
		case WL_IDLE_STATUS:
		case WL_CONNECTION_LOST:
		case WL_DISCONNECTED:
		case WL_NO_SSID_AVAIL:
			(*this->state).wifi_state = 0;

			this->current_ssid_index = (this->current_ssid_index+1)%number_of_networks;

			this->connect((*this->configuration).WiFI_Connections[this->current_ssid_index][0], (*this->configuration).WiFI_Connections[this->current_ssid_index][1]);
			break;
		case WL_CONNECTED:
			(*this->state).wifi_state = 1;

			Serial.printf("Setting up NTP %s\n", (*this->configuration).NTP_Server_Host);
			NTP.setInterval(63);
			NTP.setNTPTimeout((*this->configuration).NTP_Timeout);
			NTP.begin((*this->configuration).NTP_Server_Host, 0, true, 0);
			break;
	}
}