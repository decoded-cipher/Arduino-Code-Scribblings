#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "............................................."     // WiFi SSID
#define WIFI_PASSWORD "............................................."     //WiFi Password

#define FIREBASE_HOST "............................................."     // my-realtime-database.firebaseio.com
#define FIREBASE_AUTH "............................................."     // Firebase Authentication Token

#define LIGHT_PIN 0

int lum=0;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }
  Serial.println();
  Serial.print("Connected, ip: ");
  Serial.println(WiFi.localIP());
  pinMode(LIGHT_PIN, INPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  lum = analogRead(LIGHT_PIN);
  Serial.println(lum);
  Firebase.pushInt("light", lum);

  if(Firebase.failed()){
    Serial.println("Failed:");
  }

  delay(30000);
}
