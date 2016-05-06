#include <Adafruit_VC0706.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h> 

//-----------------Global Variable---------------------------
SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);
int latestPicNum = 0;
int lastPicNum = -1;
int segment = 1;
int numSegments = 0;
char fileName[16];
char readName[16];
int SERIAL_FREE_PIN = 5;//Change this to the correct PIN-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------


void setup() {
  Serial.begin(19200);
  //Camera Setup
  cam.begin();
  cam.setImageSize(VC0706_640x480);
  //Pin Initialization
  pinMode(SERIAL_FREE_PIN, INPUT);//HIGH = Serial in Use, LOW = Serial Free
}

void loop() {
  
  //Checks for signal to take picture (*)
  if (Serial.available() > 0 && Serial.read() == '*'){
    TakePicture();
    SetFileName();
    WriteFileToSD();
  }

  //Transmits File Segments
  if (latestPicNum > 0 && digitalRead(SERIAL_FREE_PIN) == LOW) {
    TransmitSegment();
    lastPicNum = latestPicNum;
    
    delay(30);//We need some kind of a delay here so that is doesn't try to
  //transmit another image segment before the Master has the chance to
  //transmit another telemetry packet. There's definitly a better way to 
  //do this than a delay, but I threw this in as a place holder until 
  //monday.
  
  }

  
  
}











