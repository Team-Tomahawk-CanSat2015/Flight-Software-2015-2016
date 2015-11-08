////////////**************RTC functions below*********************/////////////////////

// Used to Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val) {return ( (val/10*16) + (val%10) );}
// Used to Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val) {return ( (val/16*10) + (val%16) );}


void geta_time(unsigned long *a_time, unsigned long *a_date)
{
  byte second, minute, hour;
  byte dayinWeek, dayinmonth, months, years;
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(decToBcd(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  second = bcdToDec(Wire.read() & 0x7f);
  minute = bcdToDec(Wire.read());
  hour   = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  *a_time = ((hour * 60 * 60) + (minute * 60) + (second));
 
  dayinWeek  = bcdToDec(Wire.read());
  dayinmonth = bcdToDec(Wire.read());
  months      = bcdToDec(Wire.read());
  years       = bcdToDec(Wire.read());
 *a_date = (30*months)+dayinmonth+years;
}
 
