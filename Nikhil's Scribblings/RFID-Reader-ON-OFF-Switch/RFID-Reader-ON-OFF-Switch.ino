#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

int j=0;

String RFIDKey1 = "D3:5F:2C:2E"; //assign accepted RFID Tag 1 
String RFIDKey2 = "C1:FA:84:19"; //assign accepted RFID Tag 2

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Tap card key: ");
  Serial.println(strID);

  //check RFID keys
  if(strID.indexOf(RFIDKey1)>=0 or strID.indexOf(RFIDKey2)>=0){
    
    if(j==2){j=0;}
    if(j==0){
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      }

    if(j==1){
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      }  
      j++;
    }
    else{
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
    }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
