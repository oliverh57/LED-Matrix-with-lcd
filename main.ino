#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

int val;
#define DT 3
#define CLK 4
unsigned short int encoderPOS = 0;
int encoder0PinALast = LOW;
int n = LOW;

#define switch  8

#define I2C_ADDR 0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

String programs[] = {"colours", "static", "rainbow!", "droplets", "random"};
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

  attachInterrupt (digitalPinToInterrupt(3),encoderisr,FALLING);

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
  lcd.home();
  lcd.write(126);
  //lcd.write(' ');
  lcd.print(programs[encoderPOS % numprograms]);

  delay(10);
  /*
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoderPOS--;
    } else {
      encoderPOS++;
    }

    lcd.clear();
    lcd.print(">" + progrmas[encoderPOS]);
    lcd.setCursor(0, 1);
    lcd.print(" hello");
  }
  encoder0PinALast = n;
  */
}
