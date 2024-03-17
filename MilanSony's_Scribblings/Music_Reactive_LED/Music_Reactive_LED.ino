const int ledPinG1 = 10;
const int ledPinG2 = 9;
const int ledPinY1 = 8;
const int ledPinY2 = 7;
const int ledPinR1 = 6;
const int ledPinR2 = 5;
const int soundSensor = A2;
const int thresholdValueL1 = 30; 
const int thresholdValueL2 = 35; 
const int thresholdValueM1 = 40; 
const int thresholdValueM2 = 45; 
const int thresholdValueH1 = 50; 
const int thresholdValueH2 = 55; 
const int timeDelay = 62;
void setup() {
  Serial.begin(9600);
  pinMode(ledPinG1, OUTPUT);
  pinMode(ledPinG2, OUTPUT);
  pinMode(ledPinY1, OUTPUT);
  pinMode(ledPinY2, OUTPUT);
  pinMode(ledPinR1, OUTPUT);
  pinMode(ledPinR2, OUTPUT);
  pinMode(soundSensor, INPUT);
}

void loop() {
  int soundValue = analogRead(soundSensor);
  Serial.println(soundValue);
  if(soundValue == thresholdValueL1){
    digitalWrite(ledPinG1, HIGH);
    delay(timeDelay);
    }else if(soundValue == thresholdValueL2){
      digitalWrite(ledPinG1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinG2, HIGH);
    }else if(soundValue == thresholdValueM1){
      delay(timeDelay);
      digitalWrite(ledPinG1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinG2, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinY1, HIGH);
    }else if(soundValue == thresholdValueM2){
      delay(timeDelay);
      digitalWrite(ledPinG1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinG2, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinY1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinY2, HIGH);
    }else if(soundValue == thresholdValueH1){
      delay(timeDelay);
      digitalWrite(ledPinG1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinG2, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinY1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinY2, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinR1, HIGH);
    }else if(soundValue == thresholdValueH2){
      delay(timeDelay);
      digitalWrite(ledPinG1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinG2, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinY1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinY2, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinR1, HIGH);
      delay(timeDelay);
      digitalWrite(ledPinR2, HIGH);
      delay(timeDelay);
    }else{
      digitalWrite(ledPinG1, LOW);
      digitalWrite(ledPinG2, LOW);
      digitalWrite(ledPinY1, LOW);
      digitalWrite(ledPinY2, LOW);
      digitalWrite(ledPinR1, LOW);
      digitalWrite(ledPinR2, LOW);
    }
}
