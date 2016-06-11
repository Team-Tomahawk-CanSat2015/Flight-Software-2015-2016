/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////**************RTC functions below**************************************/////////////////////
/*
 // Used to Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)        {return ( (val/10*16) + (val%10) );}
// Used to Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)        {return ( (val/16*10) + (val%16) );}
unsigned long geta_time(){
  byte second, minute, hour;
 // Reset the register pointer
 Wire.beginTransmission(DS1307_I2C_ADDRESS);
 Wire.write(decToBcd(0));
 Wire.endTransmission();
 Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
 second     = bcdToDec(Wire.read() & 0x7f);
 minute     = bcdToDec(Wire.read());
 hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
 
 //Serial.print("The Time is: ");
 //Serial.print(hour); Serial.print(":");
 //Serial.print(minute); Serial.print(":");
 //Serial.println(second);
 return((hour * 60 * 60) + (minute * 60) + (second));
}
*/
void UpdateMissionTime (){
  intEEPROM_readAnything(MissionTimeaddr, MissionTime);
  //MissionTime =(int)MissionTime + ((int)millis()/1000);
  ++MissionTime;
  intEEPROM_writeAnything(MissionTimeaddr,MissionTime);

  
}



