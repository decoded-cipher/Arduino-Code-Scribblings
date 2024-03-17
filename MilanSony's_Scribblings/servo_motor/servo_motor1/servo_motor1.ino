// servo library
#include <Servo.h>

// defining variables
int servoPin = 9;

// creates an object of Servo
Servo servo1;

void setup() {
  servo1.attach(servoPin);
}

void loop() {
  // move servo to 0 degree
  servo1.write(0);
  delay(2000);

  // move servo to 90 degree
  servo1.write(90);
  delay(2000);

  // move the servos to 180 degree
  servo1.write(180);
  delay(2000);

  // move servo to 90 degree
  servo1.write(90);
  delay(2000);
}
