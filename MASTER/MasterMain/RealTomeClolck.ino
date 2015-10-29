/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////**************RTC functions below**************************************/////////////////////
#define DS1307_I2C_ADDRESS 0x68  // the I2C address of Tiny RTC


 // Used to Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)        {return ( (val/10*16) + (val%10) );}

// Used to Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)        {return ( (val/16*10) + (val%16) );}


void geta_time(unsigned long *a_time, unsigned long *a_date)
{
  byte seconds, minutes, hours;
  byte dayinWeek, dayinmonth, months, years;
 // Reset the register pointer
 Wire.beginTransmission(DS1307_I2C_ADDRESS);
 Wire.write(decToBcd(0));
 Wire.endTransmission();
 Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
 
 // Need to change this if 12 hour am/pm
 seconds     = bcdToDec(Wire.read() & 0x7f);
 minutes     = bcdToDec(Wire.read());
 hours       = bcdToDec(Wire.read() & 0x3f);  
 
  dayinWeek  = bcdToDec(Wire.read());
  dayinmonth = bcdToDec(Wire.read());
  months      = bcdToDec(Wire.read());
  years       = bcdToDec(Wire.read());
  
 *a_time = ((hours * 60 * 60) + (minutes * 60) + (seconds));
 *a_date = (30*months)+dayinmonth+years;
}
 
