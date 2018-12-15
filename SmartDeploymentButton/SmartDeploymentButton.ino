#include "ESP8266WiFi.h"
#include <PubSubClient.h>

const char* wifi_ssid = FILL_SSID_HERE;
const char* wifi_password = FILL_PASSWORD_HERE;
const char* mqttServer = FILL_MQTT_SERVER_HERE;
const int   mqttPort = FILL_MQTT_PORT_HERE;
const char* mqttUsername = FILL_MQTT_USERNAME_HERE;
const char* mqttPassword = FILL_MQTT_PASSWORD_HERE;

// FILL your team ID here:
#define TEAMID "TeamX"

#define MQTT_PUBLISH_TOPIC "build/" TEAMID "/command"
#define MQTT_SUBSCRIBE_TOPIC ("build/" TEAMID "/state")

#define BUTTON_PIN  d2

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
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.println("message: ");
  Serial.println((char*)payload);

  if(strcmp((char*)payload, "Building")==0) {
    Serial.println("Red");
  }

  if(strcmp((char*)payload, "Passed")==0) {
    Serial.println("Green");
  }

  if(strcmp((char*)payload, "Failed")==0) {
    Serial.println("Amber");
  }
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
      Serial.println("MQTT connected");
    }
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

int lastButtonState = HIGH;

void loop()
{
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(TEAMID, mqttUsername, mqttPassword)) {
      Serial.println("MQTT reconnected");
    }
  }

  int buttonState = digitalRead(BUTTON_PIN);
  if(buttonState != lastButtonState) {
      lastButtonState = buttonState;
      if (buttonState == HIGH)
      {
        client.publish(MQTT_PUBLISH_TOPIC, "Deploy");
      }
  }

}

