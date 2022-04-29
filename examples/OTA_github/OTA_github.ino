#include <OTA_Github.h>
OTA ota;

String Firmware_Version = "1.0.0";
String URL_Version = "/EXON/xxx/main/xx/xxx/Version.txt";
String URL_Source = "/EXON/xxx/main/xxx/xxxx/xxx/Source.ino.bin";

void setup() {
  Serial.begin(115200);
  WiFi.begin("EXON","exon_hd");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
}
void loop() {
  ota.updateFirmware(URL_Version, URL_Source, Firmware_Version);
  delay(500000);
}
