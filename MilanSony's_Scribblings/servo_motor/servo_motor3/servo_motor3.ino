// servo library
#include <Servo.h>

// defining servo pin
int ServoPin = 2;

// creating servo object
Servo servo;

// temporary setting the angle value as 0
int angle = 0;  

void setup() {
    servo.attach(ServoPin);
}

void loop() {
    // scan from 0 to 180 degree
    for(angle = 0; angle < 180; angle++) {
        servo.write(angle);
        delay(15);
    }
    // scan back from 180 to 0 degree
    for(angle = 180; angle > 0; angle--) {
        servo.write(angle);
        delay(15);
    }
}
