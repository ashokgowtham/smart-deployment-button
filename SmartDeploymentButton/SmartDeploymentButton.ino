#include "ESP8266WiFi.h"

const char* wifi_ssid = FILL_SSID_HERE;
const char* wifi_password = FILL_PASSWORD_HERE;

WiFiClient espClient;


void setupWifi() {
  delay(100);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tries++;
    if (tries>20) {
      Serial.print("Connection failed. Rebooting...");
      ESP.restart();
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  delay( 3000 ); // power-up safety delay

  setupWifi();

  Serial.begin(9600);

  Serial.println(WiFi.localIP().toString());
}


void loop()
{

}
