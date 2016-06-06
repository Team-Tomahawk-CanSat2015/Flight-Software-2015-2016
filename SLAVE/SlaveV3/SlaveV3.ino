#include <Adafruit_VC0706.h>
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h> 

//-----------------Global Variable---------------------------
SoftwareSerial cameraconnection =SoftwareSerial(4,3);
Adafruit_VC0706 cam = Adafruit_VC0706(&Serial);
int latestPicNum = 0;
int lastPicNum = -1;
int segment = 1;
int numSegments = 0;
char fileName[16];
char readName[16];
int SERIAL_FREE_PIN = 5;//Change this to the correct PIN-----------------------------------------------------------------------------------------------
int transStartBit = 0;
int transEndBit = 0;
int imgPacketSize = 1600;
int transLength_1;
int transLength_2;
//-----------------------------------------------------------


void setup() {

  
  Serial.begin(19200);
  //Camera Setup
  if (cam.begin()) {
    Serial.println("Camera Found:");
  } else {
    Serial.println("No camera found?");
    return;
  }
  delay(100);
  char *reply = cam.getVersion();
  if (reply == 0) {
    Serial.print("Failed to get version");
  } else {
    Serial.println("-----------------");
    Serial.print(reply);
    Serial.println("-----------------");
  }
  

  cam.setImageSize(VC0706_640x480);
  delay(100);
  uint8_t imgsize = cam.getImageSize();
  Serial.print("Image size: ");
  if (imgsize == VC0706_640x480) Serial.println("640x480");
  if (imgsize == VC0706_320x240) Serial.println("320x240");
  if (imgsize == VC0706_160x120) Serial.println("160x120");
  //Pin Initialization
  pinMode(SERIAL_FREE_PIN, INPUT);//HIGH = Serial in Use, LOW = Serial Free


  //SD Setup
  if (!SD.begin(10)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }  

  //Take Picture on Start
  TakePicture();
  SetFileName();
  WriteFileToSD();



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
  }

  
  
}











