//Purpose: This function is called whenever slave recives data from master 
void receiveEvent(int numBytes) {
}

/*Purpose: This requestEvent function is called whenever slave recives data from master
* When Master askes slaves Slaves 
* 1. Update Voltage data
* 2. Update GPS data
* 3. Compile bytes to send to Master
* 4. Send data to I2C Master
* Data = [voltage, LAT, Long, Alt, SatNum, GPSSpeed, Servopos]
*/
void requestEvent() {
  readBUSVoltage(&voltage);
  data[0] = voltage;
  for (int i=0; i<=sizeof(data); ++i){
    Wire.write(data[i]);  //send all bytes to Master
  }
}



