//Purpose: Function Must be call In Setup to initaliza Masters I2C Bus
void Setup_I2C (){
  Wire.begin(); // create I2C bus address 
  delay(1000);
}

void Collect_Slave_Data(){
  Wire.requestFrom(19, 2, true);//request 8 bytes from slave device #19
  Serial.println ("Asking Slave for data"); 
  int timeoutcount = 0;
  //while (Wire.available() == 0 && timeoutcount < 1000){++timeoutcount;} //wait till we get first data
  while (Wire.available()>0){
  voltage1 = Wire.read ();
  voltage2 = Wire.read ();
  //GPS_lat = Wire.read ();
  //GPS_lon = Wire.read ();
  //GPS_alt = Wire.read ();
  //GPS_satnum = Wire.read ();
  //GPS_speed = Wire.read ();
  }
  //Serial.print("DatefromSlave: ");


}






