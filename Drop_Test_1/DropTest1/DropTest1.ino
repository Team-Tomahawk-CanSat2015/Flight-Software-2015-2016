#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
//#include <SPI.h>
//#include <SD.h>
#include <SoftwareSerial.h>

#define TeamID 1086

//Structure Definition
struct gpsDataUnit {
  float altitude;
  char altUnit;
  float satNum;
  float velocity;
  float lon_degrees;
  float lat_degrees;
} gpsData;

struct dofDataUnit {
  float y_alpha, x_alpha, z_alpha;
  float z_rollrate;
  float Altitude;
  float Temperature;
  float Pressure;
} dofData;

//GlobalVariables
//File myFile;
int packetCount = 1;
//String TeleData;
char TeleCommand;
unsigned long TeleTime = 0;
float TeleArray[11];
SoftwareSerial softSer(4,5);
//DOF Variables
Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;


void setup() {
  Serial.begin(19200);
  //SD Setup
  //SD.begin(10);
  //myFile = SD.open("Data.txt", FILE_WRITE);
  //GPS Setup
  softSer.setTimeout(500);
  //DOF Setup
  Wire.begin();
  gyro.enableAutoRange(true);
  initilize_Adafruit_10_DOF_Sensors();

}

void loop() {

  //CollectData();
 adafruit_function (&dofData.y_alpha, &dofData.x_alpha, &dofData.z_alpha, &dofData.z_rollrate, &dofData.Altitude, &dofData.Temperature, &dofData.Pressure);


  callGPS(&gpsData);
  //callDOF(&dofData);
  //up ();

  //CompileData();

  TransmitAndSaveData();

  ReceiveRadioData();

}




















