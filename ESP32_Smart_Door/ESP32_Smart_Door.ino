#include <WiFi.h>
#include <HTTPClient.h>

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   5
#define SS_PIN    21

MFRC522 mfrc522(SS_PIN, RST_PIN);

unsigned long previousMillis = 0;
unsigned long interval = 30000;

const char* ssid = "Cipher Den";
const char* password = "Ak@152epv";
const char* webhook_url = "https://discord.com/api/webhooks/1128190625200738424/RhR6nM5pXIYgZcN3IVYuAqKwV9N7DUDlCqrad3S-SSmgG7RVqB-iyS-A3AyHo517eNtR";

String door = "Not Available";
String uid = "";
String owner = "";
String json = "";
bool autoLock = false;


void connect_WiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}



void connect_MFRC() {
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("\nReady to read RFID tags...");
}



void sendDiscordWebhook() {
  HTTPClient http;
  http.begin(webhook_url);
  http.addHeader("Content-Type", "application/json");


  if(autoLock == true ) {
    
    json = "{\"content\":null,\"embeds\":[{\"title\":\":butterfly:   Info! Inovus Smart Door   :butterfly:\",\"description\":\"Hey, did you know!\\nOur **Inovus Smart Door** just triggered an auto-lock.!\\n\\n> Door Status : **Locked**\\n> Agent : **Magnetic Switch**\\n.\",\"color\":5614830,\"footer\":{\"text\":\"Note : Please ignore this activity if the act is legit.\"}}],\"attachments\":[]}";
    
  } else {  

    if(owner != "") {
  
      json = "{\"content\":null,\"embeds\":[{\"title\":\":white_check_mark:   Log! Inovus Smart Door   :white_check_mark:\",\"description\":\"Hey, did you know!\\nSomeone just opened our **RFID Secured Door** !\\n\\n> Door Status : **";
      json += door;
      json += "**\\n> Tag ID : **";
      json += uid;
      json += "**\\n> Tag Owner : **";
      json += owner;
      json += "**\\n.\",\"color\":7844437,\"footer\":{\"text\":\"Note : Please ignore this activity if the act is legit.\"}}],\"attachments\":[]}";
    
    } else {
      json = "{\"content\":null,\"embeds\":[{\"title\":\":warning:   Alert! Inovus Smart Door   :warning:\",\"description\":\"Hey, did you know!\\nSomeone just opened our **RFID Secured Door** !\\n\\n> Door Status : **";
      json += door;
      json += "**\\n> Tag ID : **";
      json += uid;
      json += "**\\n> Tag Owner : **";
      json += "Not Registered";
      json += "**\\n.\",\"color\":10381369,\"footer\":{\"text\":\"Note : Please ignore this activity if the act is legit.\"}}],\"attachments\":[]}";
      
    }
  }
  Serial.println(json);
  
  int http_code = http.POST(json);
  if (http_code == 204) {
    Serial.println("Discord Webhook Sent...");
  } else {
    Serial.println("Error sending webhook...");
  }
}



void setup() {
  Serial.begin(9600);
  
  connect_WiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
  
  connect_MFRC();
}



void loop() {

  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
  
  
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      uid.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    
    Serial.print("RFID tag detected: ");
    Serial.println(uid);


    if(uid == "22987321") {
      owner = "Arjun Krishna";
    } else {
      owner = "";
    }


    if(owner == "") {
      Serial.println("Owner not found...");
    } else {
      Serial.print("Owner Name: ");
      Serial.println(owner);
    }

    sendDiscordWebhook();

    uid = "";
    owner = "";
        
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }




  if (Serial.available()) {
    String userInput = Serial.readStringUntil('\n');
    userInput.trim();
    Serial.println("User input: " + userInput);

    if (userInput == "ON") {
      autoLock = true;
      sendDiscordWebhook();
    } else {
      autoLock = false;
    }
  }
}
