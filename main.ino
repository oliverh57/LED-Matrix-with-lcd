#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


int val;
int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;


#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

char* progrmas[]={"static colours", "wave", "pulse", "rainbow", "drops","random"};

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
 
  lcd.begin (16,2);
  
// Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home

}

void loop()
{
    n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }
    lcd.clear();
    lcd.print(encoder0Pos);
   
  }
  encoder0PinALast = n;
 
}


void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  lcd.setCursor ( 0, 1 ); 
  lcd.print("R:" + String(red) + " " + "G:" + String(green) + " " + "B:" + String(blue));

  //  "G:" + String(green) + "B:" + String(blue)
}

