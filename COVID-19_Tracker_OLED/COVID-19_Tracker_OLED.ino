/*  Corona Virus Tracker OLED Display
 *  Corona Data: https://www.worldometers.info/coronavirus/
 *  ThingSpeak: https://thingspeak.com/
 *  Library: https://github.com/ThingPulse/esp8266-oled-ssd1306
 */
 
 #include <ESP8266WiFi.h>        //Use ESP8266 functions                                              
 #include <ESP8266HTTPClient.h>
 #include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
 #include "SSD1306Wire.h" 
 #include "OLEDDisplayUi.h" // Include the UI lib
 #include "images.h"  // Include custom images
  SSD1306Wire  display(0x3c, D2, D1); //  D2 -> SDA and D1 -> SCL
  SSD1306Spi display(D0, D2, D8);
  OLEDDisplayUi ui ( &display );

  const char* ssid = "Decoded_Cipher";              //WIFI SSID Name                             
  const char* password =  "170021095090";        //WIFI Password
  const char* host = "api.thingspeak.com";  //We read the data from this host                                   
  const int httpPortRead = 80;                                           
                                                  
  const char* url1 = "/apps/thinghttp/send_request?api_key=U0S4MKJOIPCF2970";     //Change this URL Cases
  const char* url2 = "/apps/thinghttp/send_request?api_key=EB107NSJHQ6X6ZY1";   //Deaths
  const char* url3 = "/apps/thinghttp/send_request?api_key=KZRL9X4T1N74PZCI";   //Recovered
  int To_remove;      //There are some irrelevant data on the string and here's how I keep the index
                      //of those characters 
  String Cases,Deaths,Recovered,Data_Raw,Data_Raw_1,Data_Raw_2,Data_Raw_3;  //Here I keep the numbers that I got

  WiFiClient client;      //Create a WiFi client and http client                                                     
  HTTPClient http; 

  void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
    
      display->drawXbm(x + 34, y + 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
      
      display->clear();
      display->drawXbm(0 , 0 , covid19_width, covid19_height, covid19_bits);
    }
  
  void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
    display->clear();
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_16);
    display->drawString(64, 10, "COVID -19");
    display->drawString(64, 35, "INDIA");   //Change Country name
   }
  
  void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
    display->clear();
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_16);
    display->drawString(64,15, "CASES"); 
    display->drawString(64,35, String(Cases));
  }
  
  void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
   
   display->clear();
   display->setTextAlignment(TEXT_ALIGN_CENTER);
   display->setFont(ArialMT_Plain_16);
   display->drawString(64,15, "DEATHS");
   display->drawString(64,35, String(Deaths));
    
  }
  
  void drawFrame5(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
   display->clear();
   display->setTextAlignment(TEXT_ALIGN_CENTER);
   display->setFont(ArialMT_Plain_16);
   display->drawString(64,15, "RECOVERED");
   display->drawString(64,35, String(Recovered));
   }
  
    FrameCallback frames[] = { drawFrame2, drawFrame3, drawFrame4, drawFrame5 }; 
    int frameCount = 5;
    int overlaysCount = 1;
    
  void setup() {
    Serial.begin(115200);
    WiFi.disconnect();             //Disconnect and reconnect to the Wifi you set                                                 
    delay(1000);                                                                  
    WiFi.begin(ssid, password);                                                   
    Serial.println("Connected to the WiFi network");   //Display feedback on the serial monitor                                        
    Serial.println(WiFi.localIP());
    ui.setTargetFPS(60);
    ui.setActiveSymbol(activeSymbol);
    ui.setInactiveSymbol(inactiveSymbol);
  
    // You can change this to
    ui.setIndicatorPosition(BOTTOM); // TOP, LEFT, BOTTOM, RIGHT
    ui.setIndicatorDirection(LEFT_RIGHT);
    ui.setFrameAnimation(SLIDE_LEFT); // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
    ui.setFrames(frames, frameCount);
    ui.init();
    display.flipScreenVertically();
    }


void loop() {
  int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0) {
    delay(remainingTimeBudget);
  }

   //Reading 1: Reading of cases
    if( http.begin(host,httpPortRead,url1))        //Connect to the host and the url                                      
      {
        int httpCode = http.GET();                //Check feedback if there's a response                                                  
        if (httpCode > 0)                                                              
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {                
              
              Data_Raw = http.getString();   //Here we store the raw data string
            
              
              Data_Raw_1 = Data_Raw;                                    
              To_remove = Data_Raw_1.indexOf(">");                      //I look for the position of this symbol ">"                                 
              Data_Raw_1.remove(0,To_remove+1);                        //I remove it and everything that's before
              To_remove = Data_Raw_1.indexOf("<");                     //I look for the position of this symbol ">"                                
              Data_Raw_1.remove(To_remove,Data_Raw_1.length());          //I remove it and everything that's after
                                                                     //Example: This is the raw data received <td style="font-weight: bold; text-align:right">63,927</td>
                                                                     //First we look for ">" and we remove everything before it including it
                                                                     //We stay with this 63,927</td>
                                                                     //We look for "<" symbol and we remove it + everything after
                                                                     //We keep only this 63,927 as string
              Cases=Data_Raw_1;
              Serial.print("Cases: ");  //I choosed to display it on the serial monitor to help you debug
              Serial.println(Cases); 
              
              Data_Raw_2=Data_Raw;
              To_remove = Data_Raw_2.indexOf("<span>");
              Data_Raw_2.remove(0,To_remove+6);
              Data_Raw_3=Data_Raw_2;
              To_remove = Data_Raw_2.indexOf("</span>");
              Data_Raw_2.remove(To_remove,Data_Raw_2.length());

              Deaths=Data_Raw_2;
              Serial.print("Deaths: ");
              Serial.println(Deaths);
            
              To_remove = Data_Raw_3.indexOf("<span>");
              Data_Raw_3.remove(0,To_remove+6);

              To_remove = Data_Raw_3.indexOf("<");
              Data_Raw_3.remove(To_remove,Data_Raw_3.length());

              Recovered=Data_Raw_3;
              
              Serial.print("Recovered: ");
              Serial.println(Recovered);    
                                                                                       
            }
        }
        else //If we can't get data
        {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        
        http.end();                                                                 
      } 
    else //If we can't connect to the HTTP
      {
        Serial.printf("[HTTP} Unable to connect\n");
      }

    while (WiFi.status() != WL_CONNECTED)     //In case the Wifi connexion is lost                                    
      { 
        
        WiFi.disconnect();                                                        
        delay(1000);                                                             
        
        WiFi.begin(ssid, password);                                              
        Serial.println("Reconnecting to WiFi..");       
        delay(10000);                                                             
      }
}
