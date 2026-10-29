#include <WiFi.h>
const char *ssid = "AETHER_TX_MK-1"; 

void setup() {
  Serial.begin(115200);
  
   
  WiFi.softAP(ssid); 
  
  Serial.println("\n[SYSTEM] AETHER Illuminator Powered On.");
  Serial.print("[SYSTEM] Broadcasting Radar Tripwire as: ");
  Serial.println(ssid);
}

void loop() {
  delay(1000);
}
