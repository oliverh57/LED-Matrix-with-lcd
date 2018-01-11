#include "FastLED.h" //include fastled.h
#define NUM_LEDS 88

#define DATA_PIN 8
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void setup_LED() { 
  LEDS.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
  LEDS.setBrightness(84);
}

