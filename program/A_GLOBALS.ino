#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define DT 3 //for rot
#define CLK 4 //for rot

#define switch  2

#define I2C_ADDR 0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN 3 //defs for lcd
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4}; //custom char for lcd



String programs[] = {"wave", "static", "rainbow", "droplets", "random"};
/*                     |        |          |          |           |
                       |        |          |          |           \---*/ String random_modes[] = {"1", "2", "3", "4", "5"}; /*
                       |        |          |          |
                       |        |          |          \--- */ String droplets_mode[] = {"mono cromatic", "colourful", "rising", "dense", "sparse"}; /*
                       |        |          |
                       |        |          \--- */ String rainbow_mode[] = {"pulse", "vertical", "horizontal", "whole colour", "random"}; /*
                       |        |
                       |        \---- */ String static_mode[] = {"red", "green", "blue", "purple", "yellow"}; /*
                       |
                       \---- */ String wave_mode[] = {"wavey", "really wavey", "supper wavey", "something", "something"}; /*
                       
*/
const int numprograms = 5;


volatile bool turndetected; //var for rot isr
volatile bool up; //var for rot idr
unsigned short int encoderPOS = 0; //total possision for rot 

volatile bool switchstate; //ver for switch isr
