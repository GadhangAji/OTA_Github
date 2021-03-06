#include <OTA_Github.h>
const char* host = "raw.githubusercontent.com";

#define httpsPort 443

void OTA::updateFirmware(const String& URL_fw_Version, const String& URL_fw_Bin, const String& version) {
  WiFiClientSecure clientHUB;
  clientHUB.setInsecure();
  if (!clientHUB.connect(host, httpsPort)){
    Serial.println(F("Connection failed"));
    return;
  }
  clientHUB.print(String("GET ") + URL_fw_Version + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" +
                  "User-Agent: BuildFailureDetectorESP32\r\n" +
                  "Connection: close\r\n\r\n");
  while (clientHUB.connected()) {
    String line = clientHUB.readStringUntil('\n');
    if (line == "\r") {
      Serial.println(F("Headers received"));
      break;
    }
  }
  String payload = clientHUB.readStringUntil('\n');
  payload.trim();
  Serial.println(payload);

  if (payload.equals(version)) {
    Serial.println(F("Device already on latest firmware version"));
    return;
  }
  else {
    Serial.println(F("New firmware detected"));
    #if defined(ESP8266)
      ESPhttpUpdate.setLedPin(2, LOW);
      t_httpUpdate_return ret = ESPhttpUpdate.update(clientHUB, "https://" + String(host) + URL_fw_Bin);
    
    #else
      httpUpdate.setLedPin(33, LOW);
      t_httpUpdate_return ret = httpUpdate.update(clientHUB, "https://" + String(host) + URL_fw_Bin);
    #endif

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        #if defined(ESP8266)
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        #else
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
        #endif
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println(F("HTTP_UPDATE_NO_UPDATES"));
        break;

      case HTTP_UPDATE_OK:
        Serial.println(F("HTTP_UPDATE_OK"));
        break;
    }
  }
}