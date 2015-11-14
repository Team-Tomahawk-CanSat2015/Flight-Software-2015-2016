/* 
* ---Team Tomahawk Flight Software for Slave Processor---
* File contains the Slave Processor Tasks
* ---We shall flash the stars!!---
*/

//Libary inclisions
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VC0706.h>
#include <SoftwareSerial.h> 


File myFile;
char curr_picfile;

#define Active_LED 8
#define chipSelect 10
#define RstPin 9
#define slaveusingSDPin 7

//Global Variables
byte Master_msg; //Message from Master
int lastImgNum;
int voltageMeasurementPin=0; //Analog pin A0 for BUS voltage on Slave
float voltage;
byte voltage1;
byte voltage2; 
byte voltagesplit[2];


void setup(){
  Serial.begin(115200);
  Serial.println ("--Slave Start...--");
  pinMode (slaveusingSDPin, OUTPUT);
  digitalWrite(slaveusingSDPin, LOW);
  Setup_RSTpin();
  Wire.begin(19);  // join I2C bus with address #19
  Wire.onReceive(receiveEvent);//"recieveevent" is called when slave recives data from master 
  Wire.onRequest(requestEvent);//"requestenevt" is called master requests data from this slave device.
}

unsigned long p_time = 0;
bool takepic = false;
void loop(){
  if (takepic == true){
     digitalWrite(slaveusingSDPin, HIGH);
     takepicture ("1.JPG");
     delay (1000);
     
     unsigned long t = millis ();
     SendPictureonSerial();
     Serial.println(millis()-t);
     
     for (int i = 10;i<=13;++i){digitalWrite(i,LOW);}
     soft_RST();
    }
     
}





