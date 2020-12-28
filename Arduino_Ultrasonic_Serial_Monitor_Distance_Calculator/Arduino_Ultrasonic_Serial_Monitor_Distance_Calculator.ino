int trigPin=9;
int echoPin=10;
int led=7;
void setup()
{ 
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}
void loop()
{
  long duration,distance;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(1000);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  duration=pulseIn(echoPin,HIGH);
  distance=(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(10);

 if((distance<=10))
 {
  digitalWrite(led,HIGH);
  
 }
 else if(distance>10)
 {delay(500);
  digitalWrite(led,LOW);
 }
  
}
