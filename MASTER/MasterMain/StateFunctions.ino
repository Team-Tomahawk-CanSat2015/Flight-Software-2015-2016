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
//
void initialize(){
  //FUNCTION TASK
  //TRANSITION CHECK
}

void launch_wait() {
  //FUNCTION TASK
  //TRANSITION CHECK
}

void ascent() {
  //FUNCTION TASK
  //TRANSITION CHECK
}

void rocketDeployment_Stabilization() {
  //FUNCTION TASK
  //TRANSITION CHECK
}

void seperation() {
  //FUNCTION TASK
  //TRANSITION CHECK
}

void descent() {
  //FUNCTION TASK
  //TRANSITION CHECK
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





