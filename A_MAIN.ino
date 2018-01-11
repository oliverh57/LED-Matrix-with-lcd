#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

Bounce debouncer = Bounce(); // Instantiate a Bounce object

#define DT 3
#define CLK 4

unsigned short int encoder0POS = 0;
unsigned short int encoder1POS = 0;

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
                       \---- */ String mode_0[] = {"wavey", "really wavey", "supper wavey", "something", "something"}; /*
                       
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

volatile bool switchstate;

void switchisr ()  {
  
  if (switchstate == true){
    switchstate = false;
  }else{
    switchstate = true;
  }
}

void setup() {
  debouncer.attach(switch_pin);
  debouncer.interval(5); // interval in ms

  setup_LED(); //run all setup for fast LED
  
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  pinMode(switch_pin, INPUT_PULLUP);

  lcd.begin(16, 2);

  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();  // go home

  Serial.begin(57600);

  attachInterrupt (digitalPinToInterrupt(3),encoderisr,FALLING); //rotary encoder isr
  attachInterrupt (digitalPinToInterrupt(2),switchisr,RISING); //switch isr

}

void loop() {
  if (turndetected) {
    if(switchstate){
      if (up) {
        encoder0POS++;
      } else {
        encoder0POS--;
      }
    }else{
      if (up) {
        encoder1POS++;
      } else {
        encoder1POS--;
      }
    }
    turndetected = false; //rest isr flag
  }
  
  lcd.clear(); //refresh lcd

  if(switchstate){ //button mode
    lcd.setCursor(0, 0);
    lcd.write(126);  
  }else{
    lcd.setCursor(0, 1);
    lcd.write(126); 
  }
  
  lcd.setCursor(1, 0);
  lcd.print(programs[encoder0POS % numprograms]);

  lcd.setCursor(1, 1);
  lcd.print(mode_1[encoder1POS % numprograms]);

  if(encoder0POS % numprograms == 1){static_animation(encoder1POS % numprograms);} //if mode = static, run static function with option as pram

  delay(100); //relay to prevent lcd flicker from onstannt refresh 

}
