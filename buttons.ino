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

  delay(2);
}
