/*Purpose: This requestEvent function is called whenever slave recives data from master
* When Master askes slaves Slaves 
* 1. Update Voltage data
* 2. Update GPS data
* 3. Compile bytes to send to Master
* 4. Send data to I2C Master
* Data = [voltage, LAT, Long, Alt, SatNum, GPSSpeed, Servopos]
*/
void requestEvent() {
  readBUSVoltage();
  //Wire.write(voltagesplit, 2);
  Wire.write(I2Cpacket, 28);
}



//Called when Slaves recieve command from Master
void receiveEvent (int howMany){
  if (Wire.available() > 0) { 
    Master_msg = Wire.read(); 
    Serial.println(Master_msg);        
  }
  switch (Master_msg){
  case 10:
  Serial.println ("--Taking Snapshot!--");
  char fiel = char(rand());
  SavetoSD("So picture string here 2", strcat(&fiel, ".txt"));
  for (int i = 10;i<=13;++i){digitalWrite(i,LOW);}
  Wire.write(&fiel, 1);
  break;
  
  }



}



