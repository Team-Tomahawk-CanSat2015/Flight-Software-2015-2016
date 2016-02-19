/*****************************************************/
/* Stage transition Alogorithms/
**********Sensor Telemeterydata reference************
[0]  - 
[1]  - 
[2]  - 
[3]  - 
[4]  - 
[5]  - 
[6]  - 
[7]  - 
[8]  - 
[9]  - 
[10] - 
[11] -
/*************Relevant Transition reference **************
*
*
/**********************************************************/



//Declaration (May be moved elsewhere for cleaner code)
unsigned long stateStartTime;
float ascentTransitionAlt  = 3; //Tayo, you can change this, I just figure 3m would be safe
#define rocketBurnTime 2
#define rocketDelayTime 1
#define nichromeBurnTime 1
float groundAlt = 0;
float prevAlt;
long landCheckTime = 0;

void initialize(){
  //FUNCTION TASK
  //TRANSITION CHECK
  if (gpsData.altitude != -999){
    groundAlt = gpsData.altitude;
    state = 1;
  }
  
}

void launch_wait() {
  //FUNCTION TASK
  //TRANSITION CHECK

  
  if (gpsData.altitude > (groundAlt + ascentTransitionAlt)){ //Last Year's code also checked that the altitude is increasing. Is this really nessesairy? Especially since we're not explicitly measuring descnet rate
    state = 2;
    stateStartTime = a_time;
    
    
  }
}

void ascent() {
  //FUNCTION TASK
  //TRANSITION CHECK
  if ((a_time - stateStartTime) > (rocketBurnTime + rocketDelayTime) ){
    state = 3;
    stateStartTime = a_time;
  }
  
}

void rocketDeployment_Stabilization() {
  //FUNCTION TASK
  //TRANSITION CHECK

 if (gpsData.altitude <= (groundAlt + 450)){
    state = 4;
    stateStartTime = a_time;
 }
  
}


void seperation() {
  //FUNCTION TASK
  digitalWrite(NichromePin, HIGH);  
  //TRANSITION CHECK
  if ((a_time - stateStartTime) > nichromeBurnTime){
    state = 5;
    digitalWrite(NichromePin, LOW);  
    //stateStartTime = a_time;
  }
}

void descent() {
  //FUNCTION TASK
  //TRANSITION CHECK
  if (gpsData.altitude < (prevAlt + .25) && gpsData.altitude > (prevAlt - .25) && landCheckTime == 0){
    landCheckTime = a_time;
  }else{
    landCheckTime = 0;
  }

  if( (a_time - landCheckTime) >= 5){
    state = 6;
    //stateStartTime = a_time;
  }
}

void landed() {
  //FUNCTION TASK :  
  //1. Acivate Buzzer at certain Intervals!!! 
      tone (buzzerpin, 262);
      delay (4000);
      noTone (buzzerpin);
      delay (5000);
      
  //TRANSITION CHECK
  //0. No Transition here, until reset button is pressed.
      //End State :)
}





