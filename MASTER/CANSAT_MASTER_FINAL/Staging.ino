void UpdateStaging (){
  switch (StageNumber){
    
    //.STAGE 1.Ascent stage:: Stage tasks: Do nothing
    case(1):   
    //Transition condition, If altitude ever exceeds release altitude
    if (abs(SensorData[0]) > abs(ReleaseAltitude) ){
      ++StageNumber;
     }
    break;
    //.STAGE 2. Transition Stage:: Stage tasks: Do nothing
    case(2): 
    //Transition condition, If altitude ever goes below release altitude
    if (abs(SensorData[0]) < abs(ReleaseAltitude) ){
      ++StageNumber;
     }
    break;
    //.STAGE 2. second Below 400m again ,Release stage
    case(3): 
    //Transition condition, If altitude ever exceeds release altitude
    if (abs(SensorData[0]) < GroundAproximationAltitude ){
      ++StageNumber;
     }
    break;
    // .STAGE 2. Stable on ground, Landed stage
    case(4):  
    Buzzer();
    //No transition
    break;
    
    
    default: 
      1+1; //Do Nothing
    break;
    
    
    
 
  }
  
  
}
