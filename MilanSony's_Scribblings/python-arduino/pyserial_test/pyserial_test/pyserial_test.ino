// Define variables
int data;
int LEDPin = 10;

void setup() 
{ 
  pinMode(LEDPin, OUTPUT);
  Serial.begin(9600);  
//  Initially setting LED to low
//  digitalWrite(LEDPin, LOW);
}
 
void loop() 
{
  // see if there is any incoming serial data
  if (Serial.available() > 0)
  {
    data = Serial.read();
    if (data == 'y'){
      digitalWrite (LEDPin, HIGH);
    }else if (data == 'n'){
       digitalWrite (LEDPin, LOW);
    }
}
