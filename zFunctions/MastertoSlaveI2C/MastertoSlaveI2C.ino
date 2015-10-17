/*
#    The functions below enable the master to send Strings of data to slave.
#      1. init_MasterI2C(Master's address)- To initilize master to slave communication and give master an adress.
#      2. SendtoSlave(Slave's address, dataString)- To send data to slave's adress
#
#    Current format of String data:
#    ("177")
#    (Cam_Servopos)
#
#*/

#include <Wire.h>

int MasterI2Caddress = 11, SlaveI2Caddress = 12;
int cam_servopos = 180;
int datatoSlave[1], datafromslave[1]; //array of {cam_servopos}


void setup() {
  Serial.begin(9600);
  init_MasterI2C(MasterI2Caddress); //Initilize masters I2C
}

byte x = 0;

void loop() {
  datatoSlave [0] =  cam_servopos; //Build string to send to slave
  SendtoSlave(SlaveI2Caddress, datatoSlave, sizeof(datatoSlave)); //Send data to slave
  delay(2000);
}


void init_MasterI2C(int address){
    Wire.begin(); // create I2C bus address 
    delay(100);
}


void SendtoSlave(int address, int data[], int data_size){
  Wire.beginTransmission(address); // transmit to slave's address
  Serial.println (""); Serial.print ("Sending to Slave I2C: ");
  for (int i=0; i<data_size-1; ++i){
  Wire.write(data[i]);        // send data
  Serial.print (data[i]); Serial.print (", ");
  delay(10);}
  Wire.endTransmission();// stop transmitting
  delay(50);
  
  Wire.requestFrom(address, 1, true);// request 1 bytes from slave device #8
  while (0 < Wire.available()) { 
  int k = Wire.read (); 
  Serial.println ("");Serial.print ("Data from Slave : ");
  Serial.println (k);
  }

}



