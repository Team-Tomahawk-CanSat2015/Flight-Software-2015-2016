/**
* EEPROM functions
* including CanSat Boot and SaveState
**/
#include <EEPROM.h>
#include "EEPROMAnything.h"

void ClearEEPROMMemory()
{
  for (int i = 0; i < 512; i++)
  {
    EEPROM.write(i, 0);
  }
}

/**
* Boot Sequence Method
* Loads flight software state from memory
* Loads:
* - State
* - PacketCount
**/
void boot()
{
  byte location = 0;
  location+=EEPROM_readAnything(location,state);
  location+=EEPROM_readAnything(location,packet_count);
  
 //Serial.println ("--***Boot***--");
 //Serial.print("\n");Serial.println ("---***Booting from***---");
 //Serial.print("State="); Serial.println(state);
 //Serial.print("PacketCount="); Serial.println(packet_count);
 //Serial.println ("---***Boot Sucess***---");
}

/**
* Save the Flight Software state to memory
* currently Saving:
* - Flight State
* - packetCount
*/
void saveStatetoEEPROM()
{ byte location = 0;
  location+=EEPROM_writeAnything(location,state);
  location+=EEPROM_writeAnything(location,packet_count);
  
}
