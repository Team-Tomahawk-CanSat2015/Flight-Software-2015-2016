/* 
* ---Team Tomahawk Flight Software for Master Processor---
* File contains the core flight software loop
* We shall pierce the skies!!
*/

/**
* Flight Software state variable:
*  0 - initialize
*  1 - Launch Wait
*  2 - Ascent
*  3 - Rocket Deployment / Stabilization
*  4 - Seperation
*  5 - Descent (Main Payload Action Stage)
*  6 - Landed -> Buzzer Activater
*  Data array Format:
*  [TeamID,Missiontime,Packetcount,PAlt,Pressure,Speed,Temp,Voltage,Lati,Longi,
*  GPSAlt,SatNum,GPSSpeed,CMDTIME,CAMSERVPOS
**/
byte State;

void Setup(){
  Serial.begin(115200);
  //boot();
}

/**
* Main Software Loop:
* 1. Collect data from sensors and Slave Processor.
* 2. Preform State-specific functions (actions and transitions check).
* 3. Save State to memory.
* 4. Transmit and Save data to SD.
* 5. Perform Radio data task 
**/
Void loop(){
  
  //1. Collect data from sensors and slave Processor and fill Sensor_Data array
  //Collect_Sensor_Data();
  //Collect_Slave_Data();
  
  //2. Preform State-specific functions
  switch (state)
  {
    case 0:
      //initialize();
      break;
    case 1:
      //launch_wait();
      break;
    case 2:
      //ascent();
      break;
    case 3:
      //rocketDeployment_Stabilization();
      break;
    case 4:
      //seperation();
      break;
    case 5:
      //descent();
      break;
    case 6:
      //landed();
      break;
    default:
      //boot();
  }

  //3. Save State to memory
  //saveState();
  
  //4. Transmit and Save data to SD.
     //Transmit_data();
     //Store_Data_inSD();
   
  //5. Perform Radio data task
       //bool did_RadioRecieve = getdatafromRadio();  
       //PerformRadiotask(did_RadioRecieve);
     
     


}
