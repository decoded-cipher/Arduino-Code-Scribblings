#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

//fauxmoESP library
#include <fauxmoESP.h>

#include <ESPAsyncTCP.h>

fauxmoESP fauxmo;

const char* ssid = "Edayady";
const char* password = "mynameismilanmilosh";

//Pin's
#define led_one  5 //D1 or GPIO5
#define led_two 14  //D5 or GPIO14

void setup() {
  Serial.begin(115200);
  delay(5000);

  pinMode(led_one, OUTPUT);
  pinMode(led_two, OUTPUT);

  //Initially turning off all led's
  digitalWrite(led_one, LOW);
  digitalWrite(led_two, LOW);

  //WiFi Connection
  
  //Set WiFi module to STA mode
  WiFi.mode(WIFI_STA);

  //Connecting to the WiFi network
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  //Begin WiFi connection
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
    
  //Adding device names
  fauxmo.addDevice("led one");
  fauxmo.addDevice("led two");

  fauxmo.setPort(80); // required for gen3 devices
  fauxmo.enable(true);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {

    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

    if (strcmp(device_name, "led one")==0) {
      digitalWrite(led_one, state ? HIGH : LOW);
    } else if (strcmp(device_name, "led two")==0) {
      digitalWrite(led_two, state ? HIGH : LOW);
    }

  });

}

void loop() {
  fauxmo.handle();
}
