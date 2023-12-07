
#include <FastLED.h>
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

#define SS_PIN 5 // ESP32 pin GPIO5
#define RST_PIN 0 // ESP32 pin GPIO27

#define RXD2 16
#define TXD2 17

#define LED_PIN_1 27  // LED Pins
#define LED_PIN_2 0
#define LED_PIN_3 2
#define NUM_LEDS 5   // Total number of LEDs (5x3 matrix)

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];

bool ledState[NUM_LEDS][3]; //2D array to keep track of which led is on or off

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

int col_pin_3 = 18;

int col_pin_4 = 19;

int col_pin_5 = 21;

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
  Serial.begin(115200);
  Serial.println("Started the sender (white board");
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

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
  if (row1 > 70){
    oldRow = touchedRow;
    touchedRow = 0;
  } else if (row2 > 70){
    oldRow = touchedRow;
    touchedRow = 1;
  } else if (row3 > 70){
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
    Serial2.print(touchedRow);
    Serial2.print(",");
    Serial2.print(touchedCol);
    Serial2.println();
    newRow = false;
    newCol = false;
  }

  delay(2);
}