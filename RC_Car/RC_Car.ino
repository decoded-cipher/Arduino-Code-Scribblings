int motorA1 = 5; // Pin  2 of L293
int motorA2 = 6; // Pin  7 of L293
int motorB1 = 9; // Pin 10 of L293
int motorB2 = 10; // Pin 14 of L293
int vel = 255; // Speed Of Motors (0-255)
int state = '0'; // Initialise Motors

void setup() { 
Serial.begin(9600); // Initialize serial communication at 9600 bits per second
   // Set pins as outputs
pinMode(motorA1, OUTPUT);
pinMode(motorA2, OUTPUT);
pinMode(motorB1, OUTPUT);
pinMode(motorB2, OUTPUT);
} 

void loop() { 

if(Serial.available()>0){ // Reads from bluetooth and stores its value
state = Serial.read();
}
if(state=='f'){ // Forward
  Serial.println(state);
analogWrite(motorA1, vel); 
analogWrite(motorA2, 0); 
analogWrite(motorB1, vel); 
analogWrite(motorB2, 0); 
}
if(state=='R'){ // Reverse
    Serial.println(state);
analogWrite(motorA1, 0); 
analogWrite(motorA2, vel);
analogWrite(motorB1, 0); 
analogWrite(motorB2, vel); 
}
if(state=='r'){ // Right
    Serial.println(state);
analogWrite(motorA1, vel); 
analogWrite(motorA2, 0); 
analogWrite(motorB1, 0); 
analogWrite(motorB2, vel); 
}
if(state=='l'){ // Left
    Serial.println(state);
analogWrite(motorA1, 0); 
analogWrite(motorA2, vel);
analogWrite(motorB1, vel);
analogWrite(motorB2, 0); 
} 
if(state=='s'){ // Stop
    Serial.println(state);
analogWrite(motorA1, 0); 
analogWrite(motorA2, 0); 
analogWrite(motorB1, 0); 
analogWrite(motorB2, 0); 

}

}
