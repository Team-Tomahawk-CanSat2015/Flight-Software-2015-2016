/* 
* ---Team Tomahawk Flight Software for Master Processor---
* File contains the core flight software loop
* ---We shall pierce the skies!!---
*/

//Libaries inclusion
#include <Wire.h>

/**
* Flight Software state variable:
*  0 - initialize
*  1 - Launch Wait
*  2 - Ascent
*  3 - Rocket Deployment / Stabilization
*  4 - Seperation
*  5 - Descent (Main Payload Action Stage)
*  6 - Landed -> Buzzer Activater
**/
//Telemertery data
unsigned int TeamID = 1086; //1. Done
unsigned long packetID = 0;//2.
float pressure_Alt;//3.
float pitot_speed;//4.
float temp;//5.
float voltage;//6.
float GPS_lat;//7.
float GPS_lon;//8.
float GPS_alt;//9.
float GPS_satnum;//10.
float GPS_speed;//11.
float CMD_time;//12.
float CMD_count;//13.
unsigned int ServoPos; //14
unsigned int state;

float all_data [13]; //just to store all data for manipulation ease




void setup(){
  Serial.begin(115200);
  Setup_I2C(); //Setup I2C bus for slave
  //boot();
}

/**
* Main Software Loop:
* 1. Collect data from sensors and Slave Processor.
* 2. Preform State-specific functions (actions and transitions check).
* 3. Save State to memory.
* 4. If a second has elapsed, Transmit and Save data to SD.
* 5. Perform Radio data task 
**/
void loop(){
  
  //1. Collect data from sensors and slave Processor and fill Sensor_Data array
  //Collect_Sensor_Data();
  Collect_Slave_Data();
  
  //2. Preform State-specific functions
  switch (state){
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
      //packetID
     //Transmit_data();
     //Store_Data_inSD();
   
  //5. Perform Radio data task
       //bool did_RadioRecieve = getdatafromRadio();  
       //PerformRadiotask(did_RadioRecieve);
     
     


}
