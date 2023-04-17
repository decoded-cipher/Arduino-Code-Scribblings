void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
   {     
      char data= Serial.read(); // reading the data received from the bluetooth module
      switch(data)
      {
        case '1': 
        {
          digitalWrite(LED_BUILTIN, HIGH);
          break;
        }
        case '2': 
        {
          digitalWrite(LED_BUILTIN, LOW);
          break;
        }
        default : break;
      }
      Serial.println(data);
   }
   delay(50);     
}
