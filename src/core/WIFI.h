/*
 * WIFI.h
 */

#ifndef DSTIKEOS_WIFI_H
#define DSTIKEOS_WIFI_H

#include <memory>
#include <Eventually.h>
#include "Configuration.h"
#include "State.h"
#include "Listeners.h"

class WIFI {
public:
	WIFI();
	void connect(const char *ssid, const char *password);
	void begin(std::shared_ptr<Configuration> config, std::shared_ptr<State> state);
	bool openAP();
	void loop();
	void status_change(EvtWifiStateListener lstn, EvtContext ctx);

	unsigned int current_ssid_index = 0;

private:
	std::shared_ptr<Configuration> configuration;
	std::shared_ptr<State> state;
};


#endif //DSTIKEOS_WIFI_H
