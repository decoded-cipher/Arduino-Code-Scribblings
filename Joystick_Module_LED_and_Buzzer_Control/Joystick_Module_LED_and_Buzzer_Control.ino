const int buzzer = 4;
const int ledleft = 13;
const int ledright = 8;
const int ledbehind = 7;
const int ledfront = 12;
const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

void setup() {
  
  pinMode(buzzer, OUTPUT);
  pinMode(ledleft, OUTPUT);
  pinMode(ledright, OUTPUT);
  pinMode(ledbehind, OUTPUT);
  pinMode(ledfront, OUTPUT);
 
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  
  int position_x = analogRead(X_pin);
  int position_y = analogRead(Y_pin);
  int switch_status = digitalRead(SW_pin);
  
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  delay(1);

 if (switch_status == 0){
  digitalWrite (buzzer, HIGH);
 }
 else {
  digitalWrite (buzzer, LOW);
 }
 if (position_x <= 470) {
  digitalWrite (ledbehind, HIGH); 
 }
 else {
  digitalWrite (ledbehind, LOW);
 }
 if (position_x >= 530) {
  digitalWrite (ledfront, HIGH);
 }
 else {
  digitalWrite (ledfront, LOW); 
 }
if (position_y >= 530) {
  digitalWrite (ledright, HIGH);
}
else {
  digitalWrite (ledright, LOW);
}
 if (position_y <= 470) {
  digitalWrite (ledleft, HIGH);
 }
 else {
  digitalWrite (ledleft, LOW);
 }
}
