void static_animation(int pram){
  lcd.print(mode_1[encoder1POS % numprograms]);//update lcd
  switch(pram){ //small amounts of other colours mixed in to some coluors to make them look nicer
    case 0://red
      setall(255, 10, 50); 
      break;
    case 1://Green
      setall(70, 225, 40); 
      break;
    case 2://Blue
      setall(70, 40, 255); 
      break;
    case 3://Purple
      setall(210, 40, 255);
      break;
    case 4://Yelllow
      setall(200, 255, 10);
      break;
    default://default -> white
      setall(255, 255, 255);
      break;
  }//end switch
  
  FastLED.show(); //update LEDs
}

void setall(int r, int g, int b){
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = CRGB(r,g,b); 
  }
}

