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

#define shortWait 2000
#define longWait 5000

#define LED_PIN_1 27  // LED Pins
#define LED_PIN_2 0
#define LED_PIN_3 2

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

  FastLED.setBrightness(100); //0-255

  for(int i = 0; i<NUM_LEDS; i++){
    leds_1[i] = CRGB::Black;
    leds_2[i] = CRGB::Black;
    leds_3[i] = CRGB::Black;
    FastLED.show();
  }

}

void loop() {
  delay(shortWait);
  // put your main code here, to run repeatedly:
  //I like you
  Serial.println("[1;0,0]"); //I
  leds_3[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[0] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[1;2,1]"); //like
  leds_1[1] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_1[1] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[1;1,0]"); //you
  leds_2[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_2[0] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(shortWait);
  for(int i = 0; i<NUM_LEDS; i++){
    leds_1[i] = CRGB::Black;
    leds_2[i] = CRGB::Black;
    leds_3[i] = CRGB::Black;
    FastLED.show();
  }
  delay(longWait);
  
  //Are you excited ?
  Serial.println("[1;0,1]"); //Are
  leds_3[1] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[1] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[1;1,0]"); //you
  leds_2[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_2[0] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(longWait);
  Serial.println("[3;0,1]"); //excited
  leds_3[1] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[1] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[3;2,4]"); //?
  leds_1[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_1[4] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(shortWait);
  for(int i = 0; i<NUM_LEDS; i++){
    leds_1[i] = CRGB::Black;
    leds_2[i] = CRGB::Black;
    leds_3[i] = CRGB::Black;
    FastLED.show();
  }
  delay(longWait);

  //I want relax after the exam
  Serial.println("[1;0,0]"); //I
  leds_3[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[0] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[1;1,2]"); //want
  leds_2[2] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_2[2] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(longWait);
  Serial.println("[2;0,4]"); //relax
  leds_3[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[4] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[2;0,3]");//after
  leds_3[3] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[3] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(longWait);
  Serial.println("[3;0,4]");//the
  leds_3[4] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[4] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[3;1,0]");//exam
  leds_2[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_2[0] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(shortWait);
  for(int i = 0; i<NUM_LEDS; i++){
    leds_1[i] = CRGB::Black;
    leds_2[i] = CRGB::Black;
    leds_3[i] = CRGB::Black;
    FastLED.show();
  }
  delay(longWait);

  //Yes I want beer please
  Serial.println("[1;0,3]"); //Yes
  leds_3[3] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[3] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[1;0,0]"); //I
  leds_3[0] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_3[0] = CRGB::Green; // Turn LED off
  FastLED.show();
  Serial.println("[1;1,2]"); //want
  leds_2[2] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_2[2] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(longWait);
  Serial.println("[2;2,2]"); //beer
  leds_1[2] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_1[2] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(longWait);
  Serial.println("[1;1,3]"); //please
  leds_2[3] = CRGB::White; // Turn LED on
  FastLED.show();
  delay(shortWait);
  leds_2[3] = CRGB::Green; // Turn LED off
  FastLED.show();
  delay(shortWait);
  for(int i = 0; i<NUM_LEDS; i++){
    leds_1[i] = CRGB::Black;
    leds_2[i] = CRGB::Black;
    leds_3[i] = CRGB::Black;
    FastLED.show();
  }
  delay(longWait);
}
