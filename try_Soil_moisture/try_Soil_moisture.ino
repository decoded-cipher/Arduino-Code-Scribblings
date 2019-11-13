const int probe = 0;
const int level = 250;
void setup() {
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(probe);
  Serial.println(x);
  if(x > 250){
    digitalWrite(11, HIGH);
    delay(300);
    digitalWrite(11, LOW);
    delay(300);
    }
  delay(100);  
}
