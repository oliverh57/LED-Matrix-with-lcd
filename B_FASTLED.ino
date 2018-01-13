#include <FastLED.h> //include fastled.h

#define NUM_LEDS 88 //number of LEDS in stop
#define DATA_PIN 8 //pin led strip is connected to

#define rows 11
#define coloums 8 

CRGB leds[NUM_LEDS];

void setupLED() { 
  LEDS.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
  LEDS.setBrightness(255);
}

void updateBrightnes(){
  int readval = map(analogRead(pot), 0, 1023, 0, 255); //get value from pot and map to 8 bit value (0 -> 255)
  if(readval < 20){ //if less than 20 turn off to prevent flicker
    LEDS.setBrightness(0);
  }else{
   LEDS.setBrightness(readval); //set to maped 8 bit value
  }
  #if defined(SERIAL_DEBUG)
    Serial.println("BRIGHTNES UPDATES");
  #endif
}

