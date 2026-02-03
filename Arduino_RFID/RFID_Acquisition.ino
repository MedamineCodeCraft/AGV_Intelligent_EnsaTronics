#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); // Communication avec l'ESP32
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  // Vérifier la présence d'un nouveau tag [cite: 14, 47]
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  String uidString = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidString += (rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    uidString += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) uidString += " ";
  }
  
  uidString.toUpperCase();
  Serial.println(uidString); // Envoi de l'UID à l'ESP32 [cite: 41, 49]

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000); // Éviter les lectures multiples
}