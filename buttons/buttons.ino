/*
 * 
 * 
 */

/*******************************************************************************
* Capacitive Sensing for Touch and Proximity
*
* Prints the values of a capacitive sensor.
*
*******************************************************************************/
#include <CapacitiveSensor.h>
//#include <MFRC522.h>
#include <FastLED.h>

/*
#define SS_PIN 5 // ESP32 pin GPIO5
#define RST_PIN 27 // ESP32 pin GPIO27
*/

#define LED_PIN_1 0  // LED Pins
#define LED_PIN_2 22
#define LED_PIN_3 32
#define NUM_LEDS 5   // Total number of LEDs (5x3 matrix)
CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];

//Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN[1], NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN[2], NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN[3], NEO_GRB + NEO_KHZ800);

//MFRC522 rfid(SS_PIN, RST_PIN);

// Define a mapping table for NFC tags
struct TagMapping {
  byte tagUID[7]; // UID of the NFC tag
  int tagNumber;  // Number associated with the tag
};

int paperNumber = 0;

// Define the mapping table with respective NFC tag UIDs and numbers
TagMapping tagMappings[] = {
  {{0x04, 0xB1, 0x61, 0x3E, 0xB9, 0x2A, 0x81}, 1},
  {{0x04, 0x8E, 0x61, 0x3E, 0xB9, 0x2A, 0x81}, 2},
  {{0x04, 0xA8, 0x61, 0x3E, 0xB9, 0x2A, 0x81}, 3}
};


double row1, row2, row3, col1, col2, col3, col4, col5;

int touchedRow, touchedCol, oldRow, oldCol;

bool newCol = false;

bool newRow = false;

int sender = 25;

int row_pin_1 = 14; 

int row_pin_2 = 13;

int row_pin_3 = 12;

int col_pin_1 = 15;  

int col_pin_2 = 4;

int col_pin_3 = 21;

int col_pin_4 = 16;

int col_pin_5 = 17;

int samples_touch = 10;

CapacitiveSensor sensor1 = CapacitiveSensor(sender, row_pin_1);
CapacitiveSensor sensor2 = CapacitiveSensor(sender, row_pin_2);
CapacitiveSensor sensor3 = CapacitiveSensor(sender, row_pin_3);
CapacitiveSensor sensor4 = CapacitiveSensor(sender, col_pin_1);
CapacitiveSensor sensor5 = CapacitiveSensor(sender, col_pin_2);
CapacitiveSensor sensor6 = CapacitiveSensor(sender, col_pin_3);
CapacitiveSensor sensor7 = CapacitiveSensor(sender, col_pin_4);
CapacitiveSensor sensor8 = CapacitiveSensor(sender, col_pin_5);


void setup()
{
  Serial.begin(9600);
  
  //rfid.PCD_Init(); // Init MFRC522

  FastLED.addLeds<NEOPIXEL,LED_PIN_1>(leds_1,NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,LED_PIN_2>(leds_2,NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,LED_PIN_3>(leds_3,NUM_LEDS);

}

void loop()
{
  /*
  if (rfid.PICC_IsNewCardPresent()) { // New tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been read
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      //Serial.print("RFID/NFC Tag Type: ");
      //Serial.println(rfid.PICC_GetTypeName(piccType)); // Print UID in Serial Monitor in the hex format
      //Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        //Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
        //Serial.print(rfid.uid.uidByte[i], HEX);
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
          //Serial.print("Mapped Number: ");
          //Serial.println(tagMappings[j].tagNumber);
          paperNumber = tagMappings[j].tagNumber;
          break;
        }
      }

      rfid.PICC_HaltA(); // Halt PICC
      rfid.PCD_StopCrypto1(); // Stop encryption on PCD
    }
  }
  */
  // Send row values
  row1 = sensor1.capacitiveSensor(samples_touch);
  row2 = sensor2.capacitiveSensor(samples_touch);
  row3 = sensor3.capacitiveSensor(samples_touch);

  // Send col values
  col1 = sensor4.capacitiveSensor(samples_touch);
  col2 = sensor5.capacitiveSensor(samples_touch);
  col3 = sensor6.capacitiveSensor(samples_touch);
  col4 = sensor7.capacitiveSensor(samples_touch);
  col5 = sensor8.capacitiveSensor(samples_touch);

  //find some way to read seperate, time multiplexing?? not working because of the overlap Isolation with air and foam tape

  // find the row that is touched and the col that is touched and print it in the format x,y;
  
  // Find the col that is touched, assign it to the variable
  if (col1 > 30){
    oldCol = touchedCol;
    touchedCol = 0;
  } else if(col2 > 30){
    oldCol = touchedCol;
    touchedCol = 1;
  } else if(col3 > 30){
    oldCol = touchedCol;
    touchedCol = 2;
  } else if(col4 > 20){
    oldCol = touchedCol;
    touchedCol = 3;
  } else if(col5 > 30){
    oldCol = touchedCol;
    touchedCol = 4;
  }

  // Find the row that is touched, assign it to the variable
  if (row1 > 60){
    oldRow = touchedRow;
    touchedRow = 0;
  } else if (row2 > 60){
    oldRow = touchedRow;
    touchedRow = 1;
  } else if (row3 > 60){
    oldRow = touchedRow;
    touchedRow = 2;
  }

  if (oldRow != touchedRow){
    newRow = true;
  } else if(oldCol != touchedCol){
    newCol = true;
  }

  // Print the pair to serial monitor when the number change
  if (newRow || newCol){
    Serial.print("[");
    Serial.print(paperNumber);
    Serial.println(";");
    Serial.print(touchedRow);
    Serial.print(",");
    Serial.print(touchedCol);
    Serial.print("]");
    Serial.println();
    newRow = false;
    newCol = false;
  }

  for(int i = 0; i<NUM_LEDS; i++){
    leds_1[i] = CRGB::Red;
    leds_2[i] = CRGB::Red;
    leds_3[i] = CRGB::Red;
    FastLED.show();
  }

  // Light up corresponding LED in strip 1
  if(touchedRow == 0){
    leds_1[touchedCol] = CRGB::White; // Turn LED on
    FastLED.show();
/*
    delay(10000); // Keep the LED on for 10 second
    leds_1[touchedCol] = CRGB::Black; // Turn LED off
    FastLED.show();
    */
  } 
  // Light up corresponding LED in strip 2
  else if (touchedRow == 1){
    leds_2[touchedCol] = CRGB::White; // Turn LED on
    FastLED.show();
/*
    delay(10000); // Keep the LED on for 10 second
    leds_2[touchedCol] = CRGB::Black; // Turn LED off
    FastLED.show();
    */
  } 
  // Light up corresponding LED in strip 3
  else if (touchedRow == 2){
    leds_3[touchedCol] = CRGB::White; // Turn LED on
    FastLED.show();
/*
    delay(10000); // Keep the LED on for 10 second
    leds_3[touchedCol] = CRGB::Black; // Turn LED off
    FastLED.show();
    */
  }

  delay(2);
}
