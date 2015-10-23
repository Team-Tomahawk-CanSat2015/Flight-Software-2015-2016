//Purpose: Function Must be call In Setup to initaliza Masters I2C Bus
void Setup_I2C (){
  Wire.begin(); // create I2C bus address 
  delay(100);
}

void Collect_Slave_Data(){
  Wire.requestFrom(8, 8, true);//request 20 bytes from slave device #11
  while (Wire.available() == 0 && count < 1000){++count;} //wait till we get first data
  if (Wire.available() > 0){
  voltage = Wire.read ();
  GPS_lat = Wire.read ();
  GPS_lon = Wire.read ();
  GPS_alt = Wire.read ();
  GPS_satnum = Wire.read ();
  GPS_speed = Wire.read ();
  }


}






