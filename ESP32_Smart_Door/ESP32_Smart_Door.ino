#include <WiFi.h>
#include <HTTPClient.h>

const char* webhook_url = "https://discord.com/api/webhooks/1128190625200738424/RhR6nM5pXIYgZcN3IVYuAqKwV9N7DUDlCqrad3S-SSmgG7RVqB-iyS-A3AyHo517eNtR";

void setup() {
  Serial.begin(115200);
  WiFi.begin("Cipher Den", "Ak@152epv");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  HTTPClient http;
  http.begin(webhook_url);
  http.addHeader("Content-Type", "application/json");
  
  
  String json = "{\"content\":null,\"embeds\":[{\"title\":\":warning:  Alert! Inovus Smart Door  :warning:\",\"description\":\"Hey, did you know!\\nIt seems someone is accessing our **RFID Secured Door**!\\n\\n> Status : **Open**\\n> Tag ID : **6E 4A 2C**\\n> Tag Owner : **Arjun Krishna**\\n.\",\"color\":10381369,\"footer\":{\"text\":\"Note : Please ignore this activity if the act is legit.\"}}],\"attachments\":[]}";
  
  
  int http_code = http.POST(json);
  if (http_code == 204) {
    Serial.println("Message sent");
  } else {
    Serial.println("Error sending message");
  }
  delay(10000);
}
