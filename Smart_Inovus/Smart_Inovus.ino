
#define BLYNK_TEMPLATE_ID "----------"
#define BLYNK_DEVICE_NAME "----------"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG

#include "BlynkEdgent.h"
#include <DHT.h>

#define DHT11_PIN 15
#define DHT11_TYPE DHT11
DHT dht(DHT11_PIN, DHT11_TYPE);

BlynkTimer timer;

BLYNK_WRITE(V0) {
  int Light01 = param.asInt();
  digitalWrite(16, Light01);
}

BLYNK_WRITE(V1) {
  int Light02 = param.asInt();
  digitalWrite(5, Light02);
}

//BLYNK_WRITE(V2) {
//  int Light03 = param.asInt();
//  digitalWrite(4, Light03);
//}
//
//BLYNK_WRITE(V3) {
//  int Light04 = param.asInt();
//  digitalWrite(0, Light04);
//}

BLYNK_WRITE(V4) {
  int Fan01 = param.asInt();
  digitalWrite(2, Fan01);
}

BLYNK_WRITE(V5) {
  int Fan02 = param.asInt();
  digitalWrite(14, Fan02);
}

BLYNK_WRITE(V6) {
  int Fan03 = param.asInt();
  digitalWrite(12, Fan03);
}

BLYNK_WRITE(V7) {
  int Fan04 = param.asInt();
  digitalWrite(13, Fan04);
}
//
//BLYNK_WRITE(V8) {
//  int Fan05 = param.asInt();
//  digitalWrite(15, Fan05);
//}

BLYNK_WRITE(V14) {
  int Light01 = param.asInt();
  int Light02 = param.asInt();
  int Fan01 = param.asInt();
  int Fan02 = param.asInt();
  int Fan03 = param.asInt();
  int Fan04 = param.asInt();
//  int Fan05 = param.asInt();
//  int Fan06 = param.asInt();
  
  digitalWrite(16, Light01);
  digitalWrite(5, Light02);
  digitalWrite(2, Fan01);
  digitalWrite(14, Fan02);
  digitalWrite(12, Fan03);
  digitalWrite(13, Fan04);
//  digitalWrite(15, Fan05);
}

//BLYNK_WRITE(V10) {
//  int Fan07 = param.asInt();
//  digitalWrite(1, Fan07);
//}

//BLYNK_WRITE(V11) {
//  int Fan08 = param.asInt();
//  digitalWrite(10, Fan08);
//}



void sendSensorValue () {
  float Temp = dht.readTemperature(DHT11_PIN);
  float Hum = dht.readHumidity(DHT11_PIN);

//  if (isnan(Temp) || isnan(Hum)) {
//    Serial.println("DHT Sensor value - Not Reading!");
//    return;
//  }
  Blynk.virtualWrite(V12, Temp);
  Blynk.virtualWrite(V13, Hum);
}



void setup()
{
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
//  pinMode(4, OUTPUT);
//  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
//  pinMode(15, OUTPUT);
//  pinMode(3, OUTPUT);
//  pinMode(1, OUTPUT);
//  pinMode(10, OUTPUT);
//  pinMode(9, INPUT);
  
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();

  dht.begin();
  timer.setInterval(2000L, sendSensorValue);
}

void loop() {
  BlynkEdgent.run();
   timer.run();
}
