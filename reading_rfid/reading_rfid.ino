#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5 // ESP32 pin GPIO5
#define RST_PIN 0 // ESP32 pin GPIO27

MFRC522 rfid(SS_PIN, RST_PIN);

// Define a mapping table for NFC tags
struct TagMapping {
  byte tagUID[7]; // UID of the NFC tag
  int tagNumber;  // Number associated with the tag
};

// Define the mapping table with respective NFC tag UIDs and numbers
TagMapping tagMappings[] = {
  {{0x04, 0x86, 0x61, 0x3E, 0xB9, 0x2A, 0x81}, 1},
  {{0x04, 0x92, 0x97, 0x3E, 0xB9, 0x2A, 0x81}, 2},
  {{0x04, 0x93, 0x97, 0x3E, 0xB9, 0x2A, 0x81}, 3}
};

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) { // New tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been read
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType)); // Print UID in Serial Monitor in the hex format
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      // Search the mapping table for the matching NFC tag and its number
      for (int j = 0; j < sizeof(tagMappings) / sizeof(tagMappings[0]); j++) {
        bool matched = true;
        for (int k = 0; k < sizeof(tagMappings[j].tagUID); k++) {
          if (tagMappings[j].tagUID[k] != rfid.uid.uidByte[k]) {
            matched = false;
            break;
          }
        }
        if (matched) {
          Serial.print("Mapped Number: ");
          Serial.println(tagMappings[j].tagNumber);
          break;
        }
      }

      rfid.PICC_HaltA(); // Halt PICC
      rfid.PCD_StopCrypto1(); // Stop encryption on PCD
    }
  }
}
