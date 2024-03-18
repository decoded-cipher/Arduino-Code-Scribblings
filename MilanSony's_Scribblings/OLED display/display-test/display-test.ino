#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
Pin Connections

If you’re using a different Arduino board, make sure you check the correct I2C pins:

Nano: SDA (A4); SCL (A5);
MEGA: SDA (20); SCL (21);
Leonardo: SDA (20); SCL (21);
*/

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
/*
initialize a display object with the width and height defined earlier with I2C communication protocol (&Wire).
*/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/*
The (-1) parameter means that your OLED display doesn’t have a RESET pin. 
If your OLED display does have a RESET pin, it should be connected to a GPIO. 
In that case, you should pass the GPIO number as a parameter.
*/

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);
  display.clearDisplay(); //All pixels are off

  // Display static text
  display.setTextSize(1); //Set the font size, support sizes from 1 to 8
  display.setTextColor(WHITE); // Set the coordinates to start writing text
  // display.setTextColor(BLACK, WHITE); // Inverted
  display.setCursor(0, 10); //Set the coordinates to start writing text
  display.println("Hello World");//Prints the characters at location x,y
  display.display(); // Call this method for the changes to make effect
}

void loop() {
  
}