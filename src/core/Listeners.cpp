/*
 * Listeners.cpp
 */

#include <ESP8266WiFi.h>
#include "Listeners.h"

EvtWifiStateListener::EvtWifiStateListener(EvtAction action) {
	this->triggerAction = action;
};

bool EvtWifiStateListener::isEventTriggered() {
	if (this->currentState != WiFi.status()) {
		this->previousState = this->currentState;
		this->currentState = WiFi.status();

		return true;
	}

	return false;
}

char* EvtWifiStateListener::getStatusName(int code) {
	switch(code) {
		case 255:
			return (char*) "WL_NO_SHIELD";
			break;
		case 0:
			return (char*) "WL_IDLE_STATUS";
			break;
		case 1:
			return (char*) "WL_NO_SSID_AVAIL";
			break;
		case 2:
			return (char*) "WL_SCAN_COMPLETED";
			break;
		case 3:
			return (char*) "WL_CONNECTED";
			break;
		case 4:
			return (char*) "WL_CONNECT_FAILED";
			break;
		case 5:
			return (char*) "WL_CONNECTION_LOST";
			break;
		case 6:
			return (char*) "WL_WRONG_PASSWORD";
			break;
		case 7:
			return (char*) "WL_DISCONNECTED";
			break;
		default:
			return (char*) "unknown";
	}
}

void EvtWifiStateListener::setupListener() {
	this->currentState = WiFi.status();
}
