#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

int val;
#define DT 3
#define CLK 4
unsigned short int encoderPOS = 0;
int encoder0PinALast = LOW;
int n = LOW;

#define switch  2

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

uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

LiquidCrystal_I2C
    lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);


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
  lcd.createChar(0, retarrow);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  pinMode(switch, INPUT_PULLUP);

  lcd.begin(16, 2);

  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();  // go home

  attachInterrupt (digitalPinToInterrupt(3),encoderisr,FALLING); //rotary encoder isr
  attachInterrupt (digitalPinToInterrupt(2),switchisr,RISING); //switch isr

}

void loop() {
  if (turndetected) {
    if (up) {
      encoderPOS++;
    } else {
      encoderPOS--;
    }
    turndetected = false;
  }
  
  lcd.clear();

  if(switchstate == HIGH){ //button mode
    lcd.setCursor(0, 0);
    lcd.write(126);  
  }else{
    lcd.setCursor(0, 1);
    lcd.write(126); 
  }
  
  lcd.setCursor(1, 0);
  lcd.print(programs[encoderPOS % numprograms]);

  delay(10);
}
