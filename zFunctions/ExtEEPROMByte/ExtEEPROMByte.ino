#include <Wire.h>    
 
#define EEPROM_ID 0x50
 
void setup(void)
{
  Serial.begin(9600);
  Wire.begin();  
 
  unsigned int address = 0;
 
  EXTwriteEEPROM_byte(EEPROM_ID, address, 255);
  Serial.print(EXTreadEEPROM_byte(EEPROM_ID, address), DEC);
}
 
void loop(){}
 
void EXTwriteEEPROM_byte(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); 
  Wire.write((int)(eeaddress & 0xFF)); 
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte EXTreadEEPROM_byte(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); 
  Wire.write((int)(eeaddress & 0xFF));
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}

