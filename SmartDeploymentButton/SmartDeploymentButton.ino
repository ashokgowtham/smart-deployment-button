#include "ESP8266WiFi.h"
#include <PubSubClient.h>

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

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

#define BUTTON_PIN  D2
#define FASTLED_PIN 1

#define NUM_LEDS    1
#define BRIGHTNESS  255
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

#define UPDATES_PER_SECOND 100

WiFiClient espClient;
PubSubClient client(espClient);
CRGB leds[NUM_LEDS];


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

  if(strncmp((char*)payload, "Building", length)==0) {
    leds[0] = CRGB::Yellow;
  }

  if(strncmp((char*)payload, "Passed", length)==0) {
    leds[0] = CRGB::Lime;
  }

  if(strncmp((char*)payload, "Failed", length)==0) {
    leds[0] = CRGB::Red;
  }
}


void setup() {
  delay( 3000 ); // power-up safety delay

  setupWifi();

  Serial.begin(9600);

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  client.subscribe(MQTT_SUBSCRIBE_TOPIC);

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(TEAMID, mqttUsername, mqttPassword)) {
      Serial.println("MQTT connected");
    }
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  FastLED.addLeds<LED_TYPE, FASTLED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
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

