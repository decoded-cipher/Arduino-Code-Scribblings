//Defining board
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif

//Asynchronous Web Server library
//asynchronous network means that you can handle more than one connection at the same time
#include <ESPAsyncWebServer.h>

//AccessPoint
const char* accesspoint_name = "ESP-ACCESSPOINT";
const char* accesspoint_password = "0123456789";

//Initilizing server at port 80(HTTP)
//https://github.com/me-no-dev/ESPAsyncWebServer
AsyncWebServer server(80);

//Page not found function
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not Found");
}

void setup() {
  Serial.begin(115200);

  //Setting the ESP as an access point
  //Here we are using the softAP(soft Access Point)
  //https://randomnerdtutorials.com/esp32-access-point-ap-web-server/

  WiFi.softAP(accesspoint_name, accesspoint_password);
  delay(10000);
  Serial.println("AccessPoint Created");
  Serial.print("Name: ");
  Serial.println(accesspoint_name);
  Serial.print("IP: ");
  //Print the softAP IP Address
  Serial.println(WiFi.softAPIP());

  //Define mDNS
  //Multicast DNS (mDNS) is a protocol that resolves hostnames to IP addresses in small networks without a local name server
  // if (MDNS.begin("esp")) {
  //   Serial.println("MDNS responder started");
  // }

  server.on("/", [](AsyncWebServerRequest * request)
  { 
    String message = "hello world"; 
    request->send(200, "text/plain", message);
  });

  server.on("/page1",HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    String message = "Page One"; 
    request->send(200, "text/plain", message);
  });

  server.onNotFound(notFound);

  //Begin the webserver
  server.begin();
}

void loop() {

}
