#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//uncoment for serial debuing
#define SERIAL_DEBUG

#define pot A0 //brightnes pot

#define DT 3 //pin for rot encoder
#define CLK 4 //pin for rot encoder

unsigned short int encoder0POS = 0; //value for rot encoder mode A
unsigned short int encoder1POS = 0; //value for rot encoder mode B

int encoder0PinALast = LOW;

#define switch_pin  2// pin 

#define I2C_ADDR 0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

String programs[] = {"wave", "static", "rainbow", "droplets", "random"};
/*                     |        |          |          |           |
                       |        |          |          |           \---*/ String modes_4[] = {"1", "2", "3", "4", "5"}; /*
                       |        |          |          |
                       |        |          |          \--- */ String mode_3[] = {"mono cromatic", "colourful", "rising", "dense", "sparse"}; /*
                       |        |          |
                       |        |          \--- */ String mode_2[] = {"pulse", "vertical", "horizontal", "whole colour", "random"}; /*
                       |        |
                       |        \---- */ String mode_1[] = {"red", "green", "blue", "purple", "yellow"}; /*
                       |
                       \---- */ String mode_0[] = {"static 1", "static 2", "moveing 1", "moving 2", "moving 3"}; /*
                       
*/
#define numprograms 5


//uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

volatile bool turndetected;
volatile bool up;

void encoderisr ()  {
  turndetected = true;
  up = (digitalRead(CLK) == digitalRead(DT));
}

volatile bool switchstate = false;

void switchisr ()  {
  /*
  if (switchstate == true){
    switchstate = false;
  }else{
    switchstate = true;
  }*/
}
//get value from pot and map to 8 bit value (0 -> 255)
void setup() {

  setupLED(); //run all setup for fast LED
  
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  pinMode(switch_pin, INPUT_PULLUP);
  pinMode(pot, INPUT); //declare brihgtnes pot as input

  lcd.begin(16, 2); //begin LCD

  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();  // go home

  #if defined(SERIAL_DEBUG)
    Serial.begin(9600); //begin serial comunication at 57600 baud 
  #endif

  attachInterrupt (digitalPinToInterrupt(3),encoderisr,FALLING); //rotary encoder isr
  attachInterrupt (digitalPinToInterrupt(2),switchisr,RISING); //switch isr

}

void loop() {
  encoderREFRESH(); //refresh encder
  lcdREFRESH(); //refresh lcd
  
  lcd.print(programs[encoder0POS % numprograms]);

  lcd.setCursor(1, 1);
  
  switch(encoder0POS % numprograms){
    case 0://wave
      wave_animation(encoder1POS % numprograms); //if mode = wave ->  run wave function with option as pram and update lcd
      break;
    case 1://static
      static_animation(encoder1POS % numprograms); //if mode = static -> run static function with option as pram and update lcd
      break;
    case 2:
      //static_animation(encoder1POS % numprograms); //if mode = static, run static function with option as pram
      lcd.print(mode_2[encoder1POS % numprograms]);//update lcd
      break;
    case 3:
      //static_animation(encoder1POS % numprograms); //if mode = static, run static function with option as pram
      lcd.print(mode_2[encoder1POS % numprograms]);//update lcd
      break;
    case 4:
      //static_animation(encoder1POS % numprograms); //if mode = static, run static function with option as pram
      lcd.print(mode_3[encoder1POS % numprograms]);//update lcd
      break;
  }
  
  updateBrightnes(); //update brightnes from pot

  delay(10); //relay to prevent lcd flicker from onstannt refresh 

}
