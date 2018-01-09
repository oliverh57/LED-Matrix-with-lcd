void switchisr ()  { //interrupt service routine for switch
  if (switchstate == true){
    switchstate = false;
  }else{
    switchstate = true;
  }
}

void encoderisr ()  { //interrupt service routine for rot encoder
  turndetected = true;
  up = (digitalRead(CLK) == digitalRead(DT));
}
