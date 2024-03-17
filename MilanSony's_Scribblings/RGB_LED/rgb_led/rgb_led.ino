// Arduino digital pins that control red, green and blue colors
const int LED_R = 2;
const int LED_G = 3;
const int LED_B = 4;

void setup() {
  // Configure pins connected to LED R, G and B as output
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  digitalWrite(LED_R, HIGH); //Red ON
  delay(1000);
  digitalWrite(LED_R, LOW); //Red OFF
  digitalWrite(LED_G, HIGH); //Green ON
  delay(1000);
  digitalWrite(LED_G, LOW); //Green OFF
  digitalWrite(LED_B, HIGH);  //Blue ON
  delay(1000);
  digitalWrite(LED_B, LOW); //Blue OFF
  delay(1000);
}