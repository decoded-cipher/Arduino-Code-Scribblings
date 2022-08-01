#define BLYNK_TEMPLATE_ID "TMPLM0RapqLo"
#define BLYNK_DEVICE_NAME "Pet Feeder"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"

int s0;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  BlynkEdgent.begin();
}

void loop() 
{
  if (Serial.available())
  {
    s0 = Serial.read();
    Serial.write(s0);
  }
  Blynk.virtualWrite(V1, s0);
  
  BlynkEdgent.run();
  }
