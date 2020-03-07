void setup() {
 pinMode(13,OUTPUT);
 pinMode(12,OUTPUT);
 Serial.begin(9600);
}

void loop() {
  int VAL=analogRead(A0);
  if(VAL>400)
  {
    digitalWrite(13,1);
    digitalWrite(12,0);
    Serial.println("GAS IS HIGH");
    delay(170);  
  }
  else
  {
    digitalWrite(13,0);
    digitalWrite(12,0);
  }

}
