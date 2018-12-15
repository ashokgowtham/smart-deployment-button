#include "ESP8266WiFi.h"
#include <PubSubClient.h>

const char* wifi_ssid = "FILL_SSID_HERE";
const char* wifi_password = "FILL_PASSWORD_HERE";
const char* mqttServer = "FILL_MQTT_SERVER_HERE";
const int   mqttPort = 12345;
const char* mqttUsername = "FILL_MQTT_USERNAME_HERE";
const char* mqttPassword = "FILL_MQTT_PASSWORD_HERE";

// FILL your team ID here:
#define TEAMID "TeamX"

#define MQTT_PUBLISH_TOPIC "iot-workshop/echo"
#define MQTT_SUBSCRIBE_TOPIC "iot-workshop/#"

WiFiClient espClient;
PubSubClient client(espClient);


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

void callback(char* topic, byte* payload, unsigned int length) {
  //handle incoming messages here
}


void setup() {
  delay( 3000 ); // power-up safety delay

  setupWifi();

  Serial.begin(9600);

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(TEAMID, mqttUsername, mqttPassword)) {
      client.publish(MQTT_PUBLISH_TOPIC, TEAMID " connected");
    }
  }
}


void loop()
{

}


