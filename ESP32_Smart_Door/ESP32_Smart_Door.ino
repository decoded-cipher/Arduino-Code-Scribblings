#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Cipher Den";
const char* password = "Ak@152epv";
const char* webhook_url = "https://discord.com/api/webhooks/1128190625200738424/RhR6nM5pXIYgZcN3IVYuAqKwV9N7DUDlCqrad3S-SSmgG7RVqB-iyS-A3AyHo517eNtR";



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




void sendDiscordWebhook() {
  HTTPClient http;
  http.begin(webhook_url);
  http.addHeader("Content-Type", "application/json");
  
  String json = "{\"content\":null,\"embeds\":[{\"title\":\":warning:  Alert! Inovus Smart Door  :warning:\",\"description\":\"Hey, did you know!\\nSomeone just opened our **RFID Secured Door** !\\n\\n> Door Status : **Not Available**\\n> Tag ID : **Not Available**\\n> Tag Owner : **Not Available**\\n.\",\"color\":10381369,\"footer\":{\"text\":\"Note : Please ignore this activity if the act is legit.\"}}],\"attachments\":[]}";
  
  int http_code = http.POST(json);
  if (http_code == 204) {
    Serial.println("Discord Webhook Sent...");
  } else {
    Serial.println("Error sending webhook...");
  }
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

    if (response) {
      sendDiscordWebhook();
    }
  }
}
