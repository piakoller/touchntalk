#include <MFRC522.h>
//#include <FastLED.h>
#include <SPI.h>

#define RXD2 16
#define TXD2 17

#define SS_PIN 5 // ESP32 pin GPIO5
#define RST_PIN 0 // ESP32 pin GPIO27

#define LED_PIN_1 33  // LED Pins
#define LED_PIN_2 27
#define LED_PIN_3 22
#define NUM_LEDS 5   // Total number of LEDs (5x3 matrix)

/*
CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];
*/

int touchedRow, touchedCol, oldRow, oldCol;

bool ledState[NUM_LEDS][3]; //2D array to keep track of which led is on or off

MFRC522 rfid(SS_PIN, RST_PIN);

// Define a mapping table for NFC tags
struct TagMapping {
  byte tagUID[7]; // UID of the NFC tag
  int tagNumber;  // Number associated with the tag
};

int paperNumber;

// Define the mapping table with respective NFC tag UIDs and numbers
TagMapping tagMappings[] = {
  {{0x04, 0x86, 0x61, 0x3E, 0xB9, 0x2A, 0x81}, 1},
  {{0x04, 0x92, 0x97, 0x3E, 0xB9, 0x2A, 0x81}, 2},
  {{0x04, 0x93, 0x97, 0x3E, 0xB9, 0x2A, 0x81}, 3}
};

int myInts[3]; // Array to store three integers

void setup() {
  Serial.begin(9600);
  Serial.println("Started the sender (white board");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  SPI.begin(); 
  rfid.PCD_Init(); // Init MFRC522

/*
  FastLED.addLeds<NEOPIXEL,LED_PIN_1>(leds_1,NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,LED_PIN_2>(leds_2,NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,LED_PIN_3>(leds_3,NUM_LEDS);

  FastLED.setBrightness(20); //0-255
*/
/*
  for (int i = 0; i < NUM_LEDS; i++) {
    ledState[i][0] = false;
    ledState[i][1] = false;
    ledState[i][2] = false;
  }

  //set all LED to red for tests
  for(int i = 0; i<NUM_LEDS; i++){
    leds_1[i] = CRGB::Blue;
    leds_2[i] = CRGB::Blue;
    leds_3[i] = CRGB::Blue;
    FastLED.show();
  }
*/
}

void loop() { 

  if (rfid.PICC_IsNewCardPresent()) { // New tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been read
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      //Serial.print("RFID/NFC Tag Type: ");
      //Serial.println(rfid.PICC_GetTypeName(piccType)); // Print UID in Serial Monitor in the hex format
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
          Serial2.print("Mapped Number: ");
          Serial2.println(tagMappings[j].tagNumber);
          break;
        }
      }

      rfid.PICC_HaltA(); // Halt PICC
      rfid.PCD_StopCrypto1(); // Stop encryption on PCD
    }
  }

  delay(2);
  
}