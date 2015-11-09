/* 
* ---Team Tomahawk Flight Software for Slave Processor---
* File contains the Slave Processor Tasks
* ---We shall flash the stars!!---
*/

//Libary inclisions
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
File myFile;
char curr_picfile;

#define Active_LED 9

//Global Variables
byte Master_msg; //Message from Master
int voltageMeasurementPin=0; //Analog pin A0 for BUS voltage on Slave
float voltage;
byte voltage1;
byte voltage2; 
byte voltagesplit[2];
byte I2Cpacket[7*4] = {0, 0, 0, 0, //Voltage
                       1, 1, 1, 1,
                       2, 2, 2, 2,
                       3, 3, 3, 3,
                       4, 4, 4, 4,
                       5, 5, 5, 5,
                       6, 6, 6, 6};//Data string to send to Master
//VOLTAGE,GPSLATITUDE,GPSLONGITUDE,GPSALTITUDE,GPSSATNUM,GPSSPEED,ServoPOS

String c_picfile;

void setup(){
  Serial.begin(115200);
  Serial.println ("--Slave Start...--");
  Wire.begin(19);  // join I2C bus with address #19
  Wire.onReceive(receiveEvent);//"recieveevent" is called when slave recives data from master 
  Wire.onRequest(requestEvent);//"requestenevt" is called master requests data from this slave device.
}
void loop(){
  //Loop function for Slave is not really needed.
  //Slave is only Active when Master Requests data from it.
  //Slave is simply a I2C module.
}


//Converts a 4 byte float to a byte array
void floattobytes (float f, int I2Carray ){
  long faddr = * (long *) &f;
  I2Cpacket[I2Carray+0] = (faddr >> 0) & (0xFF);
  I2Cpacket[I2Carray+1] = (faddr >> 8) & (0xFF);
  I2Cpacket[I2Carray+2] = (faddr >> 16) & (0xFF);
  I2Cpacket[I2Carray+3] = (faddr >> 32) & (0xFF);
}

float bytetofloat (byte bytes[4]){
float conv = *(float *)&bytes;
return conv;
}






