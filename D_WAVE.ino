  float hue = 1;
  float incrment_hue = 1;
  int hue_delta = 4;

  CRGB temp[88]; //aray for diffrent modes
  
void wave_animation(int pram){
  
  lcd.print(mode_0[encoder1POS % numprograms]);//update lcd
  Serial.print(mode_0[encoder1POS % numprograms]);
  
  switch(pram){ 
    case 0: //static 1
      fill_rainbow(leds, NUM_LEDS, hue, hue_delta);
      hue = hue + incrment_hue;
      break;
    case 1://static 2
      //setall(20, 0, 0);
      fill_rainbow(temp, 80, hue, 1);
      hue = hue + incrment_hue;
      for(int n=0; n < 8; n++){ 
        for (int i=0; i < rows; i++){
          leds[(i*8)+n] = temp[i*n];
          }
      }
      Serial.println(hue);
      
      break;
    case 2: //moving 1
      //setall(70, 40, 255); 
      break;
    case 3: //moving 2
      //setall(210, 40, 255);
      break;
    case 4://moving 3
      ///setall(200, 255, 10);
      break;
    default://default -> white
      setall(255, 255, 255);
      break;
  }//end switch
  
  FastLED.show(); //update LEDs
}

