/* 
* ---Team Tomahawk Flight Software for Master Processor---
* File contains the core flight software loop
* ---We shall pierce the skies!!---
*/

//Libaries inclusion
#include <Wire.h>
//#include <SPI.h>
//#include <SD.h>

//File for Telemetery and picture
//File Mfile;

//Physical pin setups in software
#define TeamID 1086
#define buzzerpin 6 
#define memoryresetpin 8
#define NichromePin 5
#define DS1307_I2C_ADDRESS 0x68  // the I2C address of RTC

//---------------Telemertery data
float Tele_data[19];
//TeamID = 1086; //0. 
//unsigned long packet_count = 0;//1.
//float pressure_Alt;//2.
//float pitot_speed;//3.
//float temp;//4.
//float voltage;//5.
//float GPS_lat;//6.
//float GPS_lon;//7.
//float GPS_alt;//8.
//float GPS_satnum;//9.
//float GPS_speed;//10.
//float CMD_time;//11.
//int CMD_count;//12.
//unsigned int ServoPos; //13.
//unsigned int state = 0;//14.
//unsigned long m_time; //15.

//-------------Extra variables
//float x_alpha; //16.
//float y_alpha; //17.
//float z_alpha; //18.
//float z_rollrate; //19.
byte voltage1, voltage2;
unsigned long a_time, a_date; //Actual time and date
unsigned long initialize_time = 0;
unsigned long prevtrans_Time =0, liftoff_time = 0;
float ground_alt;
float alt_buffer[5]; //used for descent rate calculation
unsigned long alt_buffer_time[5]; //stores last 5 altitudes measured with timestamp

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

void setup(){
  Serial.begin(115200); Serial.println ("--Start...--");
  Setup_I2C(); //Setup I2C bus for slave
  //Createnewlogfile();
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
  
  if (digitalRead(memoryresetpin) == HIGH){ //If reset button is pressed
    Serial.println ("---Reseting Memory..."); delay (500);
    ClearEEPROMMemory(); //Clear and reset memory 
    Serial.println ("---Reseting Memory Sucess!");
    boot(); //Reboot
  }
  
  //1. Collect data from sensors and slave Processor and fill Sensor_Data array
 // Collect_Sensor_Data();
 // Collect_Slave_Data();
  
  //2. Preform State-specific functions
  switch (state){
    case 0:
      initialize();
      break;
    case 1:
      launch_wait();
      break;
    case 2:
      ascent();
      break;
    case 3:
      rocketDeployment_Stabilization();
      break;
    case 4:
      seperation();
      break;
    case 5:
      descent();
      break;
    case 6:
      landed();
      break;
    default:
      boot();
  }

  //3. Save State to memory
    //saveStatetoEEPROM();
  
  //4. Transmit and Save data to SD.
    if (prevtrans_Time - a_time >= (1)*1000){ // 1 second telemetery transfer rate
    prevtrans_Time = a_time;
    ++packet_count;
    TransmitandSave_data();
    }
   
  //5. Perform Radio data task
     bool did_RadioRecieve = getdatafromRadio(); 
     if  (did_RadioRecieve)
     PerformRadiotask();
     
}
