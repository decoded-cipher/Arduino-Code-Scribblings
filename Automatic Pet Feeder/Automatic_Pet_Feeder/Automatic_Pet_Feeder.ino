#include <Servo.h>
#include <SoftwareSerial.h>

const int ProxSensor=2;
int inputVal = 0;
int flag = 0;
int prevStatus = 0;
int feedCount = 0;
int feedStatus;

Servo myservo; 
int pos = 0;

SoftwareSerial espSerial(5, 6);
String str;

void setup() 
{                
  pinMode(13, OUTPUT);
  pinMode(ProxSensor,INPUT);
  myservo.attach(9);
  
  Serial.begin(115200);
  espSerial.begin(115200);
}

void loop() 
{
  feedStatus = 0;
  detectPetPresence();
  if(flag==1 && prevStatus!=1)
  {
    prevStatus = flag;
    detectOverFeeding();
  }
  
  inputVal = digitalRead(ProxSensor);
//  Serial.println(inputVal);
  espSerial.println(feedStatus);
  delay(2000);
}


void feedFood() {
  for (pos = 0; pos <= 90; pos += 5) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 90; pos >= 0; pos -= 5) {
    myservo.write(pos);
    delay(15);
  }
}


void detectOverFeeding() {
  if (feedCount >= 2) {
    str = String("Overfeeding Prevented! Paused for the next 1 minute...");
    Serial.println(str);
    delay(30000);
  } else {
    feedFood();
    feedStatus = 1;
    feedCount++;
    str = String("Doggy was fed just now! #0" )+String(feedCount);
    Serial.println(str);
    delay(5000);
  }
}


void detectPetPresence() {
  if (digitalRead(ProxSensor) == HIGH)
  {
    digitalWrite(13, HIGH);
    flag = 1;
    str = String("Presence of Dog detected!");
    Serial.println(str);
  }
  else
  {
    digitalWrite(13, LOW);
    prevStatus = flag;
    flag = 0;
    str = String("Dog went away!");
    Serial.println(str);
  }
}
