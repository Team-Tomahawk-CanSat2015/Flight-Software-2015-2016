/*This is the Cansat Flight software for 2015/2016.
 * AD lucem MUTAFUKA!!
 */
//Libaries
#include <SFE_BMP180.h>
#include <Wire.h> 
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include"GPS.h"
SoftwareSerial GpsSerial(7, 8); // RX, TX


//Marcos
#define TEAMID 6643
#define NichromeBurnPin 10
#define BuzzerPin 9
#define VoltagePin A0
#define TMP36Pin A3
#define DS1307_I2C_ADDRESS 0x68  // the I2C address of Tiny RTC
#define CommunicationPin 9 //High when Slave is using it else low
#define EEPROM_ID 0x50
#define EEPROM_LocationAddress 0 //0 to 31


//Global Variables
//Telemetery variables
unsigned long MissionTime;
unsigned long PacketCount;
const int SensorDataSize = 12;
float SensorData[SensorDataSize];
long eeAddress_W = 0;
bool NichromeActive = false;
int NichromeActiveCount = 0;
int NichromeBurnDuration = 15;

unsigned long PreviousSendTime = 0;
int StageNumber;
int ReleaseAltitude = 450; //450 meters
int GroundAproximationAltitude = 50; //50meters 
/*
//TELEMETERY FORMAT
 * 1. Team ID.
 * 2. Mission time.
 * 3. Packet Count.
 * 5. Altitude sensor Data.[0]
 * 6. Pressure sensor data.[1]
 * 7. Pitot Speed.[2]
 * 8. Temperature.[3]
 * 9. Battery voltage.[4]
 * 10. GPS latitude[5]
 * 11. GPS longitude.[6]
 * 12. GPS Altitude.[7]
 * 13. GPS Satlite number.[8]
 * 14. GPS speed.[9]
 * 15. Command time.[10]
 * 16. Command count[11]
 */

void setup() {
  Serial.println("Begin...");
  Serial.begin(19200); //Begin Serial
  delay(500);

  //Initialize BMP 180 Pressure and Temperature sensor
  Wire.begin();
  initialize_BMP180();

  //Initialize GPS
  GpsSerial.begin(9600);
  GpsSerial.setTimeout(400);

  //Initialize output pins
  pinMode(NichromeBurnPin,OUTPUT);
  digitalWrite(NichromeBurnPin,LOW);

  //Gets External EEPROM Location
  EEPROM.get(EEPROM_LocationAddress, eeAddress_W);

  //Buzzer FeedBack
  Buzzer_feedback();  
}

void loop() {
  UpdateTelemetery ();
  UpdateStaging();
  
  if(millis()-PreviousSendTime>1000){
    digitalWrite(CommunicationPin,HIGH);
    SendTelemetery ();
    //SaveTelemetery(); //Commented our to preserver write cycle
    PreviousSendTime=millis();
    ++NichromeActiveCount;
    digitalWrite(CommunicationPin,LOW);
  }
  
  if (Serial.available()){PerformRadioTask();}
  if (NichromeActive==true&&NichromeActiveCount>NichromeBurnDuration){NichromeStopBaBBY();}
  
}


/*************************
 * MORE USER DEFINED FUNCTIONS *
 * **********************/
void SendTelemetery(){
  Serial.print(TEAMID); Serial.print(",");
  Serial.print(MissionTime);Serial.print(",");
  Serial.print(++PacketCount);Serial.print(",");
  
  for (int i=0; i<SensorDataSize; ++i){
    Serial.print(SensorData[i]);Serial.print(",");
  }
  Serial.println();
    
}

void UpdateTelemetery (){
  UpdateBMP180();
  UpdateMissionTime();
  UpdatePitotSensor();
  UpdateBatteryVoltage();
  UpdateGPSData();
}

void PerformRadioTask(){
  SensorData[11] = SensorData[11] + 1.00;
  SensorData[10] =(float) MissionTime;
  String RadioRecieve = Serial.readString();

  if (RadioRecieve.indexOf("%") != -1){//Nichrome burn Command recoeved
    NichromeBurnBaBBY();
    }

   if (RadioRecieve.indexOf("$") != -1){//Take snap shot command recieved
    TakeSnapshot();
   }  

    
  
  }

void SaveTelemetery(){
  extEEPROMWrite(SensorData,SensorDataSize);
  }

  void UpdateBatteryVoltage(){
   float R1 = 7500;
   float R2 = 10000;
   SensorData[4] =  ((analogRead(VoltagePin)/1024.00)*(R1+R2)* 5.00)/R2;
 }



 void NichromeBurnBaBBY (){
  NichromeActiveCount = 0;
  digitalWrite(NichromeBurnPin,HIGH);
  NichromeActive = true;
  }

 void NichromeStopBaBBY (){
  SensorData[11] = SensorData[11] + 1.00;
  SensorData[10] =(float) MissionTime;
  
  NichromeActiveCount = 0;
  digitalWrite(NichromeBurnPin,LOW);
  NichromeActive = false;
  }

  void TakeSnapshot(){}

  void UpdateGPSData () {
    if (GpsSerial.available ()){
      callGPS(&gpsData);
      //printStuff(&gpsData);
      assignGPS(&gpsData);   
      }
  }









