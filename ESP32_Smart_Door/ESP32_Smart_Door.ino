#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Cipher Den";
const char* password = "Ak@152epv";



void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi...");
}



String sendGetRequest(const char* path) {
  HTTPClient http;
  String response = "";
  http.begin(path);
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    response = http.getString();
  } else {
    Serial.print("Error - HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return response;
}



String processRequest(String tagId) {
  String path = "https://firestore.googleapis.com/v1/projects/inovus-smart-door/databases/(default)/documents/tags/" + tagId;
  Serial.println(path);
  
  String response = sendGetRequest(path.c_str());
  if (response.length() > 0) {
    Serial.println("Verified Tag ID...");
  } else {
    Serial.println("Invalid Tag ID...");
  }
  return response;
}



void setup() {
  Serial.begin(9600);
  connectToWiFi();
}



void loop() {
  if (Serial.available()) {
    String tagId = Serial.readStringUntil('\n');
    tagId.trim();
    Serial.println("User input: " + tagId);
    String response = processRequest(tagId);
  }
}
