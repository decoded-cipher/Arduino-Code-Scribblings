float temp;
 float farh;
 int tempPin = A0;
 void setup()
 {
 Serial.begin(9600);
 }
 void loop()
 {
 temp = analogRead(tempPin);
 temp = temp * 0.48828125;
 farh= (temp*9)/5 + 32;
 Serial.print("TEMPRATURE = ");
 Serial.print(temp);
 Serial.print(" C\t");
 Serial.print("TEMPRATURE = ");
 Serial.print(farh);
 Serial.print(" F");
 Serial.println();
 delay(1000);
 } ﻿
