#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

char bt = 'S';
void setup()
{
  Serial.begin(9600);

  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  Stop();
}


void loop() {

  bt = Serial.read();

  if (bt == 'F')
  {
    forward();
    Serial.print("FORWARD \n");
  }

  if (bt == 'B')
  {
    backward();
    Serial.print("BACKWARD \n");
  }

  if (bt == 'L')
  {
    left();
    Serial.print("LEFT \n");

  }

  if (bt == 'R')
  {
    right();
    Serial.print("RIGHT \n");

  }

  if (bt == 'S')
  {
    Stop();
  }

}
void forward()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void backward()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void left()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void right()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
