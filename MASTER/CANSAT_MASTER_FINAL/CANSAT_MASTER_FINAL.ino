/*This is the Cansat Flight software for 2015/2016.
 * AD lucem!!
 */
//Libaries
#include <SFE_BMP180.h>
#include <Wire.h> 
#include <EEPROM.h>
#include <Adafruit_GPS.h> 
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

SoftwareSerial mySerial(7, 8); // RX, TX
Adafruit_GPS GPS(&mySerial); 
#define GPSECHO  true 



//Marcos
#define USE_INTEEPROM //To activate Internal EEPROM, //Commented out to preserve write cycle
#define USE_EXTEEPROM //To activate Internal EEPROM, //Commented out to preserve write cycle
#define TEAMID 6643
#define NichromeBurnPin 10
#define BuzzerPin 9
#define VoltagePin A0
#define PitotPin A1
#define TMP36Pin A3
#define DS1307_I2C_ADDRESS 0x68  // the I2C address of Tiny RTC
#define CommunicationPin 9 //High when Slave is using it else low
#define EEPROM_ID 0x50
#define EEPROM_LocationAddress 0 //0 to 31
#define EEPROM_StageAdress 40
#define SnapshotPin 5


//Global Variables
//Telemetery variables
int MissionTime;
unsigned long PacketCount;
const int SensorDataSize = 12;
float SensorData[SensorDataSize];
long eeAddress_W = 0;
bool NichromeActive = false;
int NichromeActiveCount = 0;
int NichromeBurnDuration = 15;

unsigned long PreviousSendTime=0;
byte StageNumber;
byte ReleaseAltitudeaddr = 99;
int ReleaseAltitude = 450;
int GroundAproximationAltitude = 50; //50meters 
int AltitudeFilterOffset=3;
byte MissionTimeaddr= 199;
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
  SetupNichrome();//Initialize NichromePin
  Serial.begin(19200); //Begin Serial

  //Initialize BMP 180 Pressure and Temperature sensor
  Wire.begin();
  initialize_BMP180();

  //Initialize GPS
  setupGPS();

  //Setup EEPROM logging
  //eeAddress_W = 0; //To Start From The Begining, Use When testing
  EEPROM.get(EEPROM_LocationAddress, eeAddress_W);//Gets External EEPROM Location//Uncomment for actual Flight
  //extEEPROMRead(2*900);while (1==1){}  //If you want to read first 1000 digits in External EEPROM
  SaveTelemetery();SaveTelemetery();
  

  //Buzzer FeedBack
  Buzzer_feedback(); 
 


  //Setup SnapSHot Pin
  pinMode(SnapshotPin, OUTPUT);
  digitalWrite(SnapshotPin, LOW); 



  //Release altitude
  EEPROM.get(ReleaseAltitudeaddr, ReleaseAltitude);
  //Serial.print("Release Altitude");Serial.println(ReleaseAltitude);
  
}

void loop() {
  UpdateTelemetery ();
  UpdateStaging();

  if(millis()-PreviousSendTime>1000){
    UpdateMissionTime();
    digitalWrite(CommunicationPin,HIGH);
    SendTelemetery ();
    SaveTelemetery(); 
    PreviousSendTime=millis();
    ++NichromeActiveCount;
    digitalWrite(CommunicationPin,LOW);
    if (MissionTime - SensorData[10] > 10){digitalWrite(SnapshotPin, LOW); }
  }
  
  if (Serial.available()){PerformRadioTask();}
  if (NichromeActive==true&&NichromeActiveCount>NichromeBurnDuration){NichromeStopBaBBY();}
  
}


/***********************************
 * USER DEFINED FUNCTIONS ARE BELOW*
 * *********************************/
void SendTelemetery(){ //To compile and Send Telemetery on Main Serial
  Serial.print(TEAMID); Serial.print(",");
  Serial.print(MissionTime);Serial.print(",");
  Serial.print(++PacketCount);Serial.print(",");
  
  for (int i=0; i<SensorDataSize; ++i){
    if (i==5||i==6||i==7 ){ //Print to 6 decimal places for GPS presicion
      Serial.print(SensorData[i],8);Serial.print(",");
     }
     else{
       Serial.print(SensorData[i],3);Serial.print(",");
     }
  }
  Serial.println();
    
}

void UpdateTelemetery (){ //Updates all sensor data that are required for telemetery
  //UpdateBMP180();
  //UpdatePitotSensor();
  //UpdateBatteryVoltage();
  //UpdateGPSData();
}

void PerformRadioTask(){ //Performs Tasks Recived of serial which is connected to Radio
  SensorData[11] = SensorData[11] + 1.00;
  SensorData[10] =(float) MissionTime;
  String RadioRecieve = Serial.readString();

  if (RadioRecieve.indexOf("%") != -1){//Nichrome burn Command recoeved
    NichromeBurnBaBBY();
   }
  else if (RadioRecieve.indexOf("*") != -1){//Take snap shot command recieved
    TakeSnapshot();
  }  
  else if (RadioRecieve.indexOf("@") != -1){//Take snap shot command recieved
    Buzzer_Command();
  }
   else if (RadioRecieve.indexOf("^") != -1){//Adjust release altitude
    ReleaseAltitude = RadioRecieve.substring(RadioRecieve.indexOf("^") + 1).toFloat();
    EEPROM.update(ReleaseAltitudeaddr,ReleaseAltitude);
    EEPROM.get(ReleaseAltitudeaddr, ReleaseAltitude);
    Serial.print("Release Altitude = ");Serial.println(ReleaseAltitude);    
  }
  else if (RadioRecieve.indexOf("+") != -1){//Take snap shot command recieved
    SendLatestFileSD();
  }

  
  Serial.println (RadioRecieve);
    
  
  }

void SaveTelemetery(){ //Compiles and Saves Telemetery data to External EEPROM
  #ifdef USE_EXTEEPROM
  float DatatoExtEEPROM [SensorDataSize+3];
  DatatoExtEEPROM[0] = TEAMID;
  DatatoExtEEPROM[1] = MissionTime;
  DatatoExtEEPROM[2] = PacketCount;
  for (int k=0;k<SensorDataSize;++k){
    DatatoExtEEPROM[k+3] = SensorData[k]; 
  }
  extEEPROMWrite(DatatoExtEEPROM,SensorDataSize+3);
  #endif
  }

 void UpdateBatteryVoltage(){ //Battery Voltage divider measurment Sensor Calculation
   float R1 = 7500;
   float R2 = 10000;
   SensorData[4] =  ((analogRead(VoltagePin)/1024.00)*(R1+R2)* 5.00)/R2;
 }



 void NichromeBurnBaBBY (){ //Start A Nichrome burn
  Buzzer_Command();
  SensorData[11] = SensorData[11] + 1.00;
  SensorData[10] =(float) MissionTime;
  NichromeActiveCount = 0;
  digitalWrite(NichromeBurnPin,HIGH);
  NichromeActive = true;
  }

 void NichromeStopBaBBY (){ //Stop A nichrome Burn
  SensorData[11] = SensorData[11] + 1.00;
  SensorData[10] =(float) MissionTime;
  NichromeActiveCount = 0;
  digitalWrite(NichromeBurnPin,LOW);
  NichromeActive = false;
  Buzzer_Command();
  }

  void TakeSnapshot(){
    digitalWrite(SnapshotPin, HIGH); 
    }


  void SetupNichrome(){
    //Initialize output pins
    pinMode(NichromeBurnPin,OUTPUT);
    digitalWrite(NichromeBurnPin,LOW);
  }








