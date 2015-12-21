/* 
* ---Team Tomahawk Flight Software for Slave Processor---
* File contains the Slave Processor Tasks
* ---We shall flash the stars!!---
*/

//Libary inclisions
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h> 
#include <Adafruit_VC0706.h>
#include <Servo.h>

File myFile;
Servo camserv;

char curr_picfile;

#define Active_LED 8
#define chipSelect 10
#define RstPin 9
#define slaveusingSDPin 7

//Global Variables
byte Master_msg; //Message from Master
int lastImgNum;


struct gpsDataUnit {
  float satTime[3];//0: Hours  1: Minutes 2: Seconds
  float latitude[3];//0: Degree 1: Minutes 2: Direction
  char latDir;
  float longitude[3];//0: Degree 1: Minutes 2: Direction
  char longDir;
  float altitude;
  char altUnit;
  float satNum;
  float velocity;
  //----------------
  float lon_degrees;
  float lat_degrees;
} gpsData;

void setup(){
  Serial.begin(9600);
  Serial.setTimeout(500); //Setup for Gps
  Serial.println ("--Slave Start...--");
  pinMode (slaveusingSDPin, OUTPUT);
  digitalWrite(slaveusingSDPin, LOW);
  Setup_RSTpin();
  Wire.begin(19);  // join I2C bus with address #19
  Wire.onReceive(receiveEvent);//"recieveevent" is called when slave recives data from master 
  Wire.onRequest(requestEvent);//"requestenevt" is called master requests data from this slave device.
  camserv.attach (6);
}

unsigned long pU_time = 0;
bool takepic = false, slavedataUpdate = false;

void loop(){
  if (takepic == true){
     digitalWrite(slaveusingSDPin, HIGH);
     takepicture ("1.JPG");
     delay (1000);
     
     unsigned long t = millis ();
     //SendPictureonSerial();
     Serial.println(millis()-t);
     
     for (int i = 10;i<=13;++i){digitalWrite(i,LOW);}
     soft_RST();
     takepic = false;
     digitalWrite(slaveusingSDPin, LOW);
    }
     
}





