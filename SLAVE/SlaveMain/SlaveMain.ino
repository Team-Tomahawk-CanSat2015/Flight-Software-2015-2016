/* 
* ---Team Tomahawk Flight Software for Slave Processor---
* File contains the Slave Processor Tasks
* ---We shall flash the stars!!---
*/

//Libary inclisions
#include <Wire.h>


//Global Variables
int voltageMeasurementPin=0; //Analog pin A0 for BUS voltage on Slave
float voltage;
byte voltage1;
byte voltage2; 
byte voltagesplit[2];
byte data[] = {0, 1, 2, 3, 4, 5, 6, 7};//Data string to send to Master
//VOLTAGE,GPSLATITUDE,GPSLONGITUDE,GPSALTITUDE,GPSSATNUM,GPSSPEED,ServoPOS

void setup(){
  Serial.begin(115200);
  Wire.begin(19);  // join I2C bus with address #19
  Wire.onReceive(receiveEvent);//"recieveevent" is called when slave recives data from master 
  Wire.onRequest(requestEvent);//"requestenevt" is called master requests data from this slave device.
}

void loop(){
  //Loop function for Slave is not really needed.
  //Slave is only Active when Master Requests data from it.
  //Slave is simply a I2C module.
}
