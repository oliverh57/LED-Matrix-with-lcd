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
