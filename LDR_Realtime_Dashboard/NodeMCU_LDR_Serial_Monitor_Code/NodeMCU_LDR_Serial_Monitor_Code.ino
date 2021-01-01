const int LDR = A0; // Defining LDR PIN 
int input_val = 0;  // Varible to store Input values

void setup() {
   Serial.begin(9600); 
}

void loop() {  
   input_val = analogRead(LDR);      // Reading Input
   Serial.print("LDR value is : " );                        
   Serial.println(input_val);        // Writing input on serial monitor.
   delay(1000);       
}
