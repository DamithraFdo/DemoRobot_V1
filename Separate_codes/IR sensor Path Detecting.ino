void ModeD(){
 
  showOnOLED("Mode D");

  val0=digitalRead(ir0); // Left sensor
  val4=digitalRead(ir4); // Right sensor
  
  if(!val0 && !val4) 
  {
    bool x=true;
    InALine(x); 
  }
  else if(val0 && !val4) 
  {
    bool y=true;
    Turn(y);
  }
  else if(!val0 && val4) 
  {
    bool y=false;
    Turn(y);
  }
  else if(val0 && val4) 
  {
    stop();
    delay(200);
    
  }
  
  delay(100); 
}