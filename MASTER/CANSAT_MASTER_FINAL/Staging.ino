void UpdateStaging (){
  #ifdef USE_INTEEPROM
  EEPROM.get(EEPROM_StageAdress, StageNumber);
  #endif
  
  switch (StageNumber){
      //.STAGE 1.Ascent stage:: Stage tasks: Do nothing
    case(1):
        //Just Transmits data, Nothing secial here
      //Transition condition, If altitude ever exceeds release altitude go to next stage
      //if (SensorData[0]>ReleaseAltitude && abs(SensorData[0]-ReleaseAltitude)>AltitudeFilterOffset){
      if (pre>ReleaseAltitude && abs(pre-ReleaseAltitude)>AltitudeFilterOffset){
        ++StageNumber;
      }
    break;

    //.STAGE 2. Transition Stage:: Stage tasks: Do nothing
    case(2): 
      //Transition condition, If altitude ever goes below release altitude Burn that Nichrome
      if (pre<ReleaseAltitude && abs(pre-ReleaseAltitude)>AltitudeFilterOffset){
        ++StageNumber;
        NichromeBurnBaBBY();
        //TakePicture();
      }
    break;

    
    //.STAGE 3. second Below 400m again ,Released stage
    case(3): 
      //Transition condition, If altitude ever exceeds release altitude
      if (abs(pre) < GroundAproximationAltitude ){
        ++StageNumber;
      }
    break;

    
    // .STAGE 2. Stable on ground, Landed stage
    case(4):  
      Buzzer();
      //No transition
    break;
    
    
    default: 
      StageNumber = 0;
    break;
  }
  #ifdef USE_INTEEPROM
  EEPROM.update(EEPROM_StageAdress, StageNumber); //Save stage back
  #endif USE_INTEEPROM
}
