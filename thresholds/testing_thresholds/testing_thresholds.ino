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

  bool ledState[NUM_LEDS][3]; //2D array to keep track of which led is on or off

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

  int rows = 3;
  int cols = 5;

  int threshold_col[][5] = {
    {20, 30, 20, 18, 18},
    {18, 45, 10, 20, 18},
    {65, 45, 10, 10, 18}
  };

  int threshold_rows[][5] = {
    {200, 200, 200, 200, 200},
    {160, 155, 160, 160, 170},
    {160, 165, 165, 165, 165}
  };

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

    FastLED.setBrightness(20); //0-255

    for (int i = 0; i < NUM_LEDS; i++) {
      ledState[i][0] = false;
      ledState[i][1] = false;
      ledState[i][2] = false;
    }

    for(int i = 0; i<NUM_LEDS; i++){
      leds_1[i] = CRGB::Blue;
      leds_2[i] = CRGB::Blue;
      leds_3[i] = CRGB::Blue;
      FastLED.show();
    }
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

  Serial.print("[");
  Serial.print(row1);
  Serial.print(", ");
  Serial.print(col1);
  Serial.print("], [");
  Serial.print(row1);
  Serial.print(", ");
  Serial.print(col2);
  Serial.print("], [");
  Serial.print(row1);
  Serial.print(", ");
  Serial.print(col3);
  Serial.print("], [");
  Serial.print(row1);
  Serial.print(", ");
  Serial.print(col4);
  Serial.print("], [");
  Serial.print(row1);
  Serial.print(", ");
  Serial.print(col5);
  Serial.println("] //");

  Serial.print("[");
  Serial.print(row2);
  Serial.print(", ");
  Serial.print(col1);
  Serial.print("], [");
  Serial.print(row2);
  Serial.print(", ");
  Serial.print(col2);
  Serial.print("], [");
  Serial.print(row2);
  Serial.print(", ");
  Serial.print(col3);
  Serial.print("], [");
  Serial.print(row2);
  Serial.print(", ");
  Serial.print(col4);
  Serial.print("], [");
  Serial.print(row2);
  Serial.print(", ");
  Serial.print(col5);
  Serial.println("] //");

  Serial.print("[");
  Serial.print(row3);
  Serial.print(", ");
  Serial.print(col1);
  Serial.print("], [");
  Serial.print(row3);
  Serial.print(", ");
  Serial.print(col2);
  Serial.print("], [");
  Serial.print(row3);
  Serial.print(", ");
  Serial.print(col3);
  Serial.print("], [");
  Serial.print(row3);
  Serial.print(", ");
  Serial.print(col4);
  Serial.print("], [");
  Serial.print(row3);
  Serial.print(", ");
  Serial.print(col5);
  Serial.println("] //");

  Serial.println();
  Serial.println();

    //find some way to read seperate, time multiplexing?? not working because of the overlap Isolation with air and foam tape

    // find the row that is touched and the col that is touched and print it in the format x,y;
    
    int col_values[] = {col1, col2, col3, col4, col5};
    int row_values[] = {row1, row2, row3};

    // Iterate through the columns
    for (int col = 0; col < cols; col++) {
      if (col_values[col] > threshold_col[touchedRow][col]) {
        oldCol = touchedCol;
        touchedCol = col;
        newCol = true;
        break;
      }
    }

    // Iterate through the rows
    for (int row = 0; row < rows; row++) {
      if (row_values[row] > threshold_rows[row][touchedCol]) {
        oldRow = touchedRow;
        touchedRow = row;
        newRow = true;
        break;
      }
    }

    // Check for changes
    if (oldRow == touchedRow && oldCol == touchedCol) {
      newRow = false;
      newCol = false;
    }


    // Print the pair to serial monitor when the number change
    if (newRow || newCol){
      Serial.print("[");
      Serial.print(paperNumber);
      Serial.print(";");
      Serial.print(touchedRow);
      Serial.print(",");
      Serial.print(touchedCol);
      Serial.print("]");
      Serial.println();


      if (touchedRow == 0) {
        ledState[touchedCol][touchedRow] = !ledState[touchedCol][touchedRow];
      } else if (touchedRow == 1) {
        ledState[touchedCol][touchedRow] = !ledState[touchedCol][touchedRow];
      } else if (touchedRow == 2) {
        ledState[touchedCol][touchedRow] = !ledState[touchedCol][touchedRow];
      }

      // Update LED strips based on the LED state
      for (int i = 0; i < NUM_LEDS; i++) {
        if (!ledState[i][0]) {
          leds_1[i] = CRGB::Black; // Turn off LED
        } else {
          leds_1[i] = CRGB::White; // Turn on LED
        }

        if (!ledState[i][1]) {
          leds_2[i] = CRGB::Black; // Turn off LED
        } else {
          leds_2[i] = CRGB::White; // Turn on LED
        }

        if (!ledState[i][2]) {
          leds_3[i] = CRGB::Black; // Turn off LED
        } else {
          leds_3[i] = CRGB::White; // Turn on LED
        }
      }

      FastLED.show();
      
      newRow = false;
      newCol = false;
    }
    

    /*
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

      delay(10000); // Keep the LED on for 10 second
      leds_1[touchedCol] = CRGB::Black; // Turn LED off
      FastLED.show();
      
    } 
    // Light up corresponding LED in strip 2
    else if (touchedRow == 1){
      leds_2[touchedCol] = CRGB::White; // Turn LED on
      FastLED.show();
  /*
      delay(10000); // Keep the LED on for 10 second
      leds_2[touchedCol] = CRGB::Black; // Turn LED off
      FastLED.show();
      
    } 
    // Light up corresponding LED in strip 3
    else if (touchedRow == 2){
      leds_3[touchedCol] = CRGB::White; // Turn LED on

      FastLED.show();

      delay(10000); // Keep the LED on for 10 second
      leds_3[touchedCol] = CRGB::Black; // Turn LED off
      
      
    }
    */

    FastLED.show();
    delay(2);
  }
