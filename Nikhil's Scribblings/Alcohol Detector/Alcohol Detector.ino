
float sensorValue;
float sensorVolts;
 
void setup()
{
 Serial.begin(9600);      // sets the serial port to 9600
 delay(20000);    // allow the MQ-6 to warm up
 pinMode(11, OUTPUT);
}
 
void loop()
{
 
 for(int i = 0; i < 100; i++){
     sensorValue = sensorValue + analogRead(0);       // read analog input pin 0
 }
 
 sensorValue = sensorValue / 100;                  // get average reading
 sensorVolts = sensorValue/1024*5.0;   //convert to voltage
 if(sensorVolts > 1.4){
 digitalWrite(11, HIGH);
 delay(300);
 digitalWrite(11, LOW);
 delay(1000);
 }
 Serial.println(sensorVolts);  // prints the value read
 delay(1000);                        // wait 100ms for next reading
}