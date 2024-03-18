//NodeMCU/ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//ESP32
// #include <WiFi.h>
// #include <WebServer.h>

#include <DNSServer.h>
#include <WiFiManager.h>

//WiFi Credentials
const char* ssid = "MilanSony";
const char* password = "27022001";

//Access Point Credentials
const char* accesspointname = "NodeMCU"; //Access Point Name
const char* accesspointpswd  = "0123456789";  //Access Point Password

void setup(){

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  WiFi.mode(WIFI_STA); //Set WiFi to station + AP

  WiFi.begin(ssid, password); //Begin the WiFi Connection

  WiFiManager wifimanager;  //Creating an object for WiFiManager
  Serial.println("Waiting for a WiFi Connection...");
  bool res = wifimanager.autoConnect(accesspointname, accesspointpswd);
  if(!res){
    Serial.println("WiFi not Connected to an Access Point");
  }else{
    Serial.println("WiFi Connected to an Access Point");
  }

  if(WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi Connected");
    delay(1000);
    for(int i=0; i<3; i++)
    {
      digitalWrite(LED_BUILTIN, LOW);  //Turn the LED ON (By default the LED is OFF in ESP)
      delay(1000);                    //Wait for a second
      digitalWrite(LED_BUILTIN, HIGH);  //Turn the LED OFF
      delay(1000);
    }
  }
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); //Turn the LED OFF
}