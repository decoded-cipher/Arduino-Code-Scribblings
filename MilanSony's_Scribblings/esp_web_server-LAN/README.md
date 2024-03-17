# esp_webserver-LAN

Here we make an HTML page then deploy that HTML page on the web server running on the ESP board. Using this you will be able to control the devices attached to the ESP board from your web browser

> In this we are using the softAP (soft Access Point)


- In ESPAsyncWebServer, the <a href="https://github.com/me-no-dev/ESPAsyncWebServer">ESPAsyncWebServer</a> library is used and send's plain text as a message to clients connected to the ESP web server
  
- In websockets the <a href="https://github.com/Links2004/arduinoWebSockets">WebSocketsServer</a> library is used and send's HTML page to clients connected to the ESP web server. `connection.send("LED one is ON");` is used to sent data to the server. `websockets.onEvent(webSocketEvent);` receive's the data from the client.

### Read Documents

<a href="https://randomnerdtutorials.com/esp32-access-point-ap-web-server/">Read about Access Point</a>

<a href="https://developerinsider.co/difference-between-http-and-http-2-0-websocket/">Read the diff b/w http and websocket</a>

<a href="https://www.w3schools.com/js/js_json_intro.asp">JSON</a>
