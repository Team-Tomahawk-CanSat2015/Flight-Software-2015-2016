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
  location+=EEPROM_readAnything(location,initialize_time);
  location+=EEPROM_readAnything(location,prevtrans_Time);
  location+=EEPROM_readAnything(location,liftoff_time);
  location+=EEPROM_readAnything(location,ground_alt);
  location+=EEPROM_readAnything(location,alt_buffer);
  location+=EEPROM_readAnything(location,alt_buffer_time);
  
  Serial.print("\n"); Serial.println ("---***Booting from***---");
  Serial.print("State="); Serial.println(state);
  Serial.print("PacketCount="); Serial.println(packet_count);
  Serial.print("InitializeTime=");Serial.println(initialize_time);
  Serial.print("PreviousTransmitTime=");Serial.println(prevtrans_Time);
  Serial.print("liftoffTime=");Serial.println(liftoff_time);
  Serial.print("LiftoffAltitude=");Serial.println(ground_alt);
  Serial.println ("---***Boot Sucess***---"); Serial.print("\n");
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
  location+=EEPROM_writeAnything(location,initialize_time);
  location+=EEPROM_writeAnything(location,prevtrans_Time);
  location+=EEPROM_writeAnything(location,liftoff_time);
  location+=EEPROM_writeAnything(location,ground_alt);
  location+=EEPROM_writeAnything(location,alt_buffer);
  location+=EEPROM_writeAnything(location,alt_buffer_time);
}
