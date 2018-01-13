void encoderREFRESH(){ //function to update encoder
  if (turndetected) {//if isr flag is set
    if(switchstate){//if in mode 1
      if (up) {
        encoder0POS++;
      } else {
        encoder0POS--;
      }
    }else{//mode 2
      if (up) {
        encoder1POS++;
      } else {
        encoder1POS--;
      }
    }
    turndetected = false; //rest isr flag
    
    #if defined(SERIAL_DEBUG)
      Serial.println("ENCODER REFRESHED");
    #endif
  }
}//end encoderREFRESH 

void lcdREFRESH(){
  lcd.clear(); //refresh lcd
  
  if(switchstate){ //button mode
    lcd.setCursor(0, 0);
    lcd.write(126);  
  }else{
    lcd.setCursor(0, 1);
    lcd.write(126); 
  }
  lcd.setCursor(1, 0);// set lcd to "home"
  
}

