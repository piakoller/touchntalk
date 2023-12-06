/*
 * I[1;3,5] like[1;1,4] you[1;2,5]
 * 
 * Are[1;3,4] you[1;2,5] excited[3;3,4] ?[3;1,1]
 * 
 * I[1;3,5] want[1;2,3] relax[2;3,1] after[2;3,2] the[3;3,1] exam[3;2,5]
 * 
 * I[1;3,5] want[1;2,3] beer[2;1,3] please[1;2,2]
 */

#include <FastLED.h>

#define LED_PIN_1 0  // LED Pins
#define LED_PIN_2 22
#define LED_PIN_3 32
#define NUM_LEDS 5   // Total number of LEDs (5x3 matrix)
CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL,LED_PIN_1>(leds_1,NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,LED_PIN_2>(leds_2,NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,LED_PIN_3>(leds_3,NUM_LEDS);

  FastLED.setBrightness(200): //0-255

  for(int i = 0; i<NUM_LEDS; i++){
    leds_1[i] = CRGB::Red;
    leds_2[i] = CRGB::Red;
    leds_3[i] = CRGB::Red;
    FastLED.show();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //I like you
  Serial.println("[1;2,4]"); //I
  leds_3[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[4] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[1;0,3]"); //like
  leds_1[3] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_1[3] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[1;1,4]"); //you
  leds_2[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_2[4] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20)
  
  //Are you excited ?
  Serial.println("[1;2,3]"); //Are
  leds_3[3] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[3] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[1;1,4]"); //you
  leds_2[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_2[4] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20);
  Serial.println("[3;2,3]"); //excited
  leds_3[3] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[3] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[3;0,0]"); //?
  leds_1[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_1[0] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20);

  //I want relax after the exam
  Serial.println("[1;2,4]"); //I
  leds_3[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[4] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[1;1,2]"); //want
  leds_2[2] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_2[2] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20);
  Serial.println("[2;2,0]]"); //relax
  leds_3[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[0] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[2;2,1]");//after
  leds_3[1] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[1] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20);
  Serial.println("[3;2,0]");//the
  leds_3[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[0] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[3;1,4]");//exam
  leds_2[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_2[4] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20);

  //Yes I want beer please
  Serial.println("[1;2,1]"); //Yes
  leds_3[1] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[1] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[1;2,4]"); //I
  leds_3[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_3[4] = CRGB::Red; // Turn LED off
  FastLED.show();
  Serial.println("[1;1,2]"); //want
  leds_2[2] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_2[2] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20);
  Serial.println("[2;0,2]"); //beer
  leds_1[2] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_1[2] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20);
  Serial.println("[1;1,1]"); //please
  leds_2[1] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(10);
  leds_2[1] = CRGB::Red; // Turn LED off
  FastLED.show();
  delay(20);
}
