#ifndef OTA_Github_h
#define OTA_Github_h

#include <WiFiClientSecure.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
const int led = 2;
#else
#include <WiFi.h>
#include <HTTPUpdate.h>
const int led = 33;
#endif

class OTA {
public:
	void updateFirmware(const String& URL_fw_Version, const String& URL_fw_Bin, const String& version);
private:
	;
};
#endif