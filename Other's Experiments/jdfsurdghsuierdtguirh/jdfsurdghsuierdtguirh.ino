void setup()
{
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int val = analogRead(A0);
    if(val>200)
    {
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    Serial.println(val);
    delay(500);
    }
    else {
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);
    Serial.println(val);
    delay(500);
     }
  }
