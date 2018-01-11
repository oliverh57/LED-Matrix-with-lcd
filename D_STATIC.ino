void static_animation(int pram){
  if(pram == 0){setall(255, 0, 0);} //red 
  if(pram == 1){setall(0, 255, 0);} //green
  if(pram == 2){setall(0, 0 , 255);} ///blue
  if(pram == 3){setall(255, 0 , 255);} //purple
  if(pram == 4){setall(255, 255, 0);} //yellow
    
  FastLED.show(); //update LEDs
}

void setall(int r, int g, int b){
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = CRGB(r,g,b); 
  }
}
