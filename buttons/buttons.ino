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

#define NEOPIXEL_PIN {?, ?, ?}  // ?? Pins connected to the NeoPixel strip
#define NUM_PIXELS 5   // Total number of NeoPixels (5x3 matrix)

Adafruit_NeoPixel strip_1 = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN[1], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_2 = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN[2], NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_3 = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN[3], NEO_GRB + NEO_KHZ800);


double row1, row2, row3, col1, col2, col3, col4, col5;

int touchedRow, touchedCol, oldRow, oldCol;

bool newCol = false;

bool newRow = false;

int sender = 25;

int row_pin_1 = 14; 

int row_pin_2 = 13;

int row_pin_3 = 12;

int col_pin_1 = 21;  

int col_pin_2 = 19;

int col_pin_3 = 18;

int col_pin_4 = 17;

int col_pin_5 = 16;

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

  // Strip 1
  strip_1.begin();
  strip_1.show();  // Initialize all pixels to 'off'

  // Strip 2
  strip_2.begin();
  strip_2.show();  // Initialize all pixels to 'off'

  // Strip 3
  strip_3.begin();
  strip_3.show();  // Initialize all pixels to 'off'
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
    touchedCol = 1;
  } else if(col2 > 30){
    oldCol = touchedCol;
    touchedCol = 2;
  } else if(col3 > 30){
    oldCol = touchedCol;
    touchedCol = 3;
  } else if(col4 > 20){
    oldCol = touchedCol;
    touchedCol = 4;
  } else if(col5 > 30){
    oldCol = touchedCol;
    touchedCol = 5;
  }

  // Find the row that is touched, assign it to the variable
  if (row1 > 60){
    oldRow = touchedRow;
    touchedRow = 1;
  } else if (row2 > 60){
    oldRow = touchedRow;
    touchedRow = 2;
  } else if (row3 > 60){
    oldRow = touchedRow;
    touchedRow = 3;
  }

  if (oldRow != touchedRow){
    newRow = true;
  } else if(oldCol != touchedCol){
    newCol = true;
  }

  // Print the pair to serial monitor when the number change
  if (newRow || newCol){
    Serial.print(touchedRow);
    Serial.print(",");
    Serial.print(touchedCol);
    Serial.println(";");
    newRow = false;
    newCol = false;
  }

  // Light up corresponding LED in strip 1
  if(touchedRow == 1){
    strip_1.setPixelColor(touchedCol, strip.Color(255, 255, 255)); // White color
    strip_1.show();
    delay(10000); // Keep the LED on for 10 second
    strip_1.setPixelColor(touchedCol, strip.Color(0, 0, 0)); // No color
  } 
  // Light up corresponding LED in strip 2
  else if (touchedRow == 2){
    strip_2.setPixelColor(touchedCol, strip.Color(255, 255, 255)); // White color
    strip_2.show();
    delay(10000); // Keep the LED on for 10 second
    strip_2.setPixelColor(touchedCol, strip.Color(0, 0, 0)); // No color
  } 
  // Light up corresponding LED in strip 3
  else if (touchedRow == 3){
    strip_3.setPixelColor(touchedCol, strip.Color(255, 255, 255)); // White color
    strip_3.show();
    delay(10000); // Keep the LED on for 10 second
    strip_3.setPixelColor(touchedCol, strip.Color(0, 0, 0)); // No color
  }

  delay(2);
}
