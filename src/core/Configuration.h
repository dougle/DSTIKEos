/*
 * Configuration.h
 */

#ifndef DSTIKEOS_CONFIGURATION_H
#define DSTIKEOS_CONFIGURATION_H

#include <NtpClientLib.h>

class Configuration {
public:
	Configuration();

	char* WiFI_Connections[1][2] = {{WIFI_SSID, WIFI_PASS}};
	unsigned int WiFi_Connect_Timeout = 10000;

	char* AP_SSID = (char *)"dstike";
	char* AP_Password = (char *)"";
	bool AP_Hidden = false;

	char* NTP_Server_Host = (char *)DEFAULT_NTP_SERVER;
	unsigned int NTP_Interval = 1500;
	unsigned int NTP_Timeout = 1500;
	unsigned int Display_Timeout = 30;
	unsigned int Splash_Timeout = 15;
	bool Display_Timeout_Enabled = true;

	// https://www.cplusplus.com/reference/ctime/strftime/
	char* Time_Format = (char *)"%H:%M:%S";
	char* Date_Format = (char *)"%a %e %b %Y";
private:
};

#endif //DSTIKEOS_CONFIGURATION_H
