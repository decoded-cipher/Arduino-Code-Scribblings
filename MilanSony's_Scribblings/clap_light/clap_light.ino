int sound_sensor = 4;
int ledPinG1 = 10;

int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPinG1, OUTPUT);
  pinMode(sound_sensor, INPUT);
}
 
void loop() {
  int status_sensor = digitalRead(sound_sensor);
  Serial.println(status_sensor);
//  delay(1000);
  if (status_sensor == 0)
  {
    if (clap == 0)
    {
      detection_range_start = detection_range = millis();
      clap++;
//      Serial.print("Detection Range: ");
//      Serial.println(detection_range);
    }
    else if (clap > 0 && millis()-detection_range >= 50)
    {
      detection_range = millis();
      Serial.print("Detection Range: ");
      Serial.println(detection_range);
      clap++;
    }
  }
  if (millis()-detection_range_start >= 400)
  {
    if (clap == 2)
    {
      if (!status_lights)
        {
          status_lights = true;
          digitalWrite(ledPinG1, HIGH);
        }
        else if (status_lights)
        {
          status_lights = false;
          digitalWrite(ledPinG1, LOW);
        }
    }
    clap = 0;
  }
}
