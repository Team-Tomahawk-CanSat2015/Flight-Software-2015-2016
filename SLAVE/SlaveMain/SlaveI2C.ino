/*Purpose: This requestEvent function is called whenever slave recives data from master
* When Master askes slaves Slaves 
* 1. Update Voltage data
* 2. Update GPS data
* 3. Compile bytes to send to Master
* 4. Send data to I2C Master
* Data = [voltage, LAT, Long, Alt, SatNum, GPSSpeed, Servopos]
*/
void requestEvent() {
  Wire.write(&curr_picfile, 1);
}



//Called when Slaves recieve command from Master
void receiveEvent (int howMany){
  if (Wire.available() > 0) { 
    Master_msg = Wire.read(); 
    Serial.print("Command recived from MAster -> ");
    Serial.println(Master_msg);        
  }
  switch (Master_msg){
  case 10: {//Take picture case
  Serial.println ("--Taking Snapshot!--");
  byte num_by = (byte)random (62, 122);
  char buff;
  String num = String(random (1, 9));
  num += ".JPG";
  const char* filestr = num.c_str();
  takepic = true;
  break;
  }
  
 }



}



