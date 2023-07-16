#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   5   // Reset Pin
#define SS_PIN    21  // Slave Select Pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600); // Initialize serial communication
  SPI.begin();        // Initialize SPI communication
  mfrc522.PCD_Init(); // Initialize MFRC522 RFID reader
  Serial.println("Ready to read RFID tags...");
}

void loop() {
  // Check if a new RFID tag is detected
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Get the UID of the tag
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      uid.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    
    Serial.print("RFID tag detected: ");
    Serial.println(uid);
    
    // Reset the RFID reader to prepare for the next tag
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
