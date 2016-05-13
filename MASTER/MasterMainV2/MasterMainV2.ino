

/* 
* ---Team Tomahawk Flight Software for Master Processor---
* File contains the core flight software loop
* ---We shall pierce the skies!!---
*/

//Libaries inclusion
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>            
#include <Adafruit_BMP085_U.h>
#include <EEPROM.h>
File myFile;

//Physical pin and adress setups in software
#define RstPin 9
#define TeamID 1086
#define buzzerpin 6 
#define memoryresetpin 8
#define NichromePin 5
#define DS1307_I2C_ADDRESS 0x68  // the I2C address of RTC
#define slaveusingSDPin 7
#define Slave_I2C_Adress 19
#define EEPROM_ID 0x50

unsigned long packet_count = 0;
int state = 0;
unsigned long m_time;
int Slave_Array_Size = 3;
byte Slave_data[3]; //See MAster_Slave_I2C for meaning


//---------------Telemertery data
int Tele_Array_Size = 19;
float Tele_data[19]; 
//float pressure_Alt;//0.
//float pressure;//1.
//float pitot_speed;//2.
//float temp;//3.
//float voltage;//4.
//float GPS_lat;//5.
//float GPS_lon;//6.
//float GPS_alt;//7.
//float GPS_satnum;//8.
//float GPS_speed;//9.
//float CMD_time;//10.
//float CMD_count;//11.
//float ServoPos; //12.
//float x_alpha; //xx.
//float y_alpha; //xx.
//float z_alpha; //xx.
//float z_rollrate; //xx.

//-------------Extra variables
unsigned long a_time, a_date; //Actual time and date
unsigned long initialize_time = 0;
unsigned long prevtrans_Time =0, liftoff_time = 0;
byte previous_slaveusingSDPin = 0;
int eeAddress_W = 0;
int EXTeeAddress_W = 0;

//Structure Definition
struct gpsDataUnit {
  long satTime[3];//0: Hours  1: Minutes 2: Seconds
  long latitude[3];//0: Degree 1: Minutes 2: Direction
  char latDir;
  long longitude[3];//0: Degree 1: Minutes 2: Direction
  char longDir;
  long altitude;
  char altUnit;
  long satNum;
  long velocity;
  //----------------
  long lon_degrees;
  long lat_degrees;
} gpsData;

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
  Setup_RSTpin(); //Setup pin used for soft reset
  Serial.begin(115200); 
  pinMode(slaveusingSDPin, INPUT); //Setup pin indicator if slave is using SD card BUS
  Wire.begin(); //Setup I2C bus for slave
  boot();
  Serial.println ("--Master Start--");
}

/**
* Main Software Loop:
* 1. Collect data from sensors and Slave Processor.
* 2. Preform State-specific functions (actions and transitions check).
* 3. Save State to memory.
* 4. If a second has elapsed,Check what transmission protocol to perform (4a or 4b)
*    4a. Transmit standard packet without pic and Save data to SD.
*    4b. Transmit Packet with image property attached, save standard packet to SD
* 5. Perform Radio data task 
**/
void loop(){
  if (digitalRead(memoryresetpin) == HIGH){ //If reset button is pressed
    delay (200);
    ClearEEPROMMemory();
    boot(); //Reboot
  }
  
  //1. Collect data from sensors and slave Processor and fill Sensor_Data array
   // Update_Sensor_Data();
   // Update_Slave_data();
  
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
   // saveStatetoEEPROM();
  
  //4. Transmit and Save data to SD.
    if (millis() - prevtrans_Time >= (1) *1000){ // 1 second telemetery transfer rate
      prevtrans_Time = millis ();
      ++packet_count;
      
      if (!(digitalRead(slaveusingSDPin)==LOW && previous_slaveusingSDPin==HIGH)){
  //4a. Standard packet Transmission and save
        TransmitandSave_data(1, "0");}
      else{
  //4b. Image packet transmission loop
        RunImageTransmissionSequence();}
    }

   
  //5. Perform Radio data task
     bool did_RadioRecieve = getdatafromRadio(); 
     if  (did_RadioRecieve)  PerformRadiotask();


    //----- Extra Variable Updates
     previous_slaveusingSDPin = digitalRead(slaveusingSDPin);
     
}
