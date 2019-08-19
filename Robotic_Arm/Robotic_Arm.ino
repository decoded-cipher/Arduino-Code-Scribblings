///////Arm Control/////////
#include<Servo.h>
//// Object Creation ////
Servo myservo0;
Servo myservo1;
Servo myservo2;
Servo myservo3;
//// Initialization ////
int input0=A0;
int input1=A1;
int input2=A2;
int input3=A3;
int val0;
int val1;
int val2;
int val3;
void setup()ś
{
myservo0.attach(5); //Pins to which servo is attached
myservo1.attach(6);
myservo2.attach(10);
myservo3.attach(11);
Serial.begin(9600);
}
//// run again and again ////
void loop()
{
val0=analogRead(input0); //Read Analog value as value between 0 and 1023
Serial.println(val0);
delay(200);
val0=map(val0,0,1023,0,180); //Scale the values between 0 and 180
myservo0.write(val0); //Sets the values of servo to the scaled value
delay(15); //waits for the servo to get there
val1=analogRead(input1);
val1=map(val1,0,1023,0,180);
myservo1.write(val1);
delay(15);
val2=analogRead(input2);
val2=map(val2,0,1023,0,180);
myservo2.write(val2);
delay(15);
val3=analogRead(input3);
val3=map(val3,0,1023,0,180);
myservo3.write(val3);
delay(15);
}
