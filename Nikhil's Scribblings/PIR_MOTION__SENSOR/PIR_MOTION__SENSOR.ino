int Buzz= 8; // Define Buzzer pin
int LED= 13; // Define LED pin
int PIR= 2; // Define PIR pin
int val= 0; // Initializing the value as zero at the beginning
  
void setup() {
  
pinMode(Buzz, OUTPUT);
pinMode(LED, OUTPUT);
pinMode(PIR, INPUT);
Serial.begin(9600);
}

void loop() {
            
val = digitalRead(PIR); // The value read from PIR pin 3 will be assigned to 'val'
if(val == HIGH){
  digitalWrite(LED, HIGH); // Turn LED ON
  digitalWrite(Buzz, HIGH); // Turn Buzzer ON
  Serial.println("Movement Detected"); // Print this text in Serial Monitor
}
else 
{
  digitalWrite(LED, LOW);
  digitalWrite(Buzz, LOW);
  Serial.println("Movement not Detected");
}
}
