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

//WebSockets Server library
#include <WebSocketsServer.h>

//Arduino JSON library
#include <ArduinoJson.h>

//AccessPoint
const char* accesspoint_name = "ESP-ACCESSPOINT";
const char* accesspoint_password = "0123456789";

//LED pins
#define LED1 14
#define LED2 15

//Initilizing server at port 80(HTTP)
//https://github.com/me-no-dev/ESPAsyncWebServer
AsyncWebServer server(80);

//Initilizing WebSocketsServer at port 81
WebSocketsServer websockets(81);

//Write your webpage here (Raw String Literal)
/*
Here we are storing the webpage in the program memory, the data is stored inside the flash memory
If we have not stored the webpage in program memory it is stored in RAM
The amount of flash memory is more than of RAM
*/
char webpage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP Web Server</title>
</head>

<!-- CSS -->
<style>
    .main-head{
        color: red;
    }
    .head-one{
        padding-top: 20px;
    }
    .head-two{
        padding-top: 40px;
    }
    button{
        margin-left: 40px;
        margin-right: 40px;
        padding: 10px;
    }
</style>

<!-- JS -->
<script>
    var connection = new WebSocket('ws://'+location.hostname+':81/'); //Establish websocket connection at port 81

    var button_one_status = 0;
    var button_two_status = 0;

    // let status = document.getElementById("status");

    //LED ONE
    function button_one_on()
    {
        button_one_status = 1;
        console.log("LED one is ON");
        document.getElementById("status").innerText = ": ON";
        send_data();
    }

    function button_one_off()
    {
        button_one_status = 0;
        console.log("LED one is OFF");
        document.getElementById("status").innerText = ": OFF";
        send_data();
    }
    
    //LED TWO
    function button_two_on()
    {
        button_two_status = 1
        console.log("LED two is ON");
        document.getElementById("status2").innerText = ": ON";
        send_data();
    }

    function button_two_off()
    {
        button_two_status = 0;
        console.log("LED two is OFF");
        document.getElementById("status2").innerText = ": OFF";
        send_data();
    }

    //Send the data formated  in JSON form
    function send_data()
    {
        var json_data = '{"LED1" :'+button_one_status+',"LED2":'+button_two_status+'}';
        connection.send(json_data);
    }
</script>
<body>
    <center>
        <h1 class="main-head">ESP WEB SERVER</h1>

        <!-- LED ONE -->
        <h3 class="head-one">LED ONE <span id="status"></span></h3>
        <button onclick="button_one_on()">ON</button>
        <button onclick="button_one_off()">OFF</button>

        <!-- LED TWO -->
        <h3 class="head-two">LED TWO <span id="status2"></span></h3>
        <button onclick="button_two_on()">ON</button>
        <button onclick="button_two_off()">OFF</button>
    </center>
</body>
</html>

)=====";

//Page not found function definition --> server.onNotFound(notFound);
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not Found");
}

//Function definition of onEvent --> websockets.onEvent(webSocketEvent);
/*
num: automatically assign number to the connected client (same as of giving an ID to the user) 0,1,2...
type: websocket type - WStype_DISCONNECTED, WStype_CONNECTED, WStype_TEXT
payload: data receiving from the client side(actual data)
length: length of the payload
*/
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) 
  {
    case WStype_DISCONNECTED: //If any of the client disconnected
      Serial.printf("Client [%u] Disconnected\n", num);
      break;
    case WStype_CONNECTED: { //If new client connected
        IPAddress ip = websockets.remoteIP(num); //Save client IP Address
        Serial.printf("Client [%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // Send's a message to the client if connected
        websockets.sendTXT(num, "Connected with server");
      }
      break;
    case WStype_TEXT: //This function is called if any message comes from the client
      Serial.printf("Client [%u] Get Text: %s\n", num, payload); //Payload
      String message = String((char*)( payload)); //Converts the payload into string format
      Serial.println(message);

      //Creating an object for JSON
      DynamicJsonDocument doc(200);

      //Deserialize the JSON data using deserializeJson() and saving all the JSON data in the doc object
      DeserializationError error = deserializeJson(doc, message);
      //Checking if there is any error 
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      int LED1_status = doc["LED1"]; //Fetch/parse the data from the JSON --> doc
      digitalWrite(LED1, LED1_status);
      int LED2_status = doc["LED2"];
      digitalWrite(LED2, LED2_status);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

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
    request->send_P(200, "text/html", webpage); //send_P - If you are reading anything from flash memory you have to use send_P
  });

  server.on("/page1",HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    String message = "Page One"; 
    request->send(200, "text/plain", message);
  });

  //Page not found
  server.onNotFound(notFound);

  //Begin the webserver
  server.begin();

  //Begin WebSocketsServer
  websockets.begin();

  //Receiving the data from the client
  websockets.onEvent(webSocketEvent);
}

void loop() {
  websockets.loop(); //for looping the websockets
}