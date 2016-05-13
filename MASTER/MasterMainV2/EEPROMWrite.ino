void EEPROMWrite(float data[], int dataSize){
  for (int i = 0; i < dataSize; i++){
    if (eeAddress_W + sizeof(float) >= EEPROM.length()){
      eeAddress_W = 0;
    }
    EEPROM.put(eeAddress_W, data[i]);
    eeAddress_W += sizeof(float); 
  }
}

void extEEPROMWrite(float data[], int dataSize){
  for (int i = 0; i < dataSize; i++){
    if (EXTeeAddress_W + sizeof(float) >= EEPROM.length()){
      EXTeeAddress_W = 0;
    }
    Wire.beginTransmission(EEPROM_ID);
    Wire.write((int)highByte(EXTeeAddress_W) );
    Wire.write((int)lowByte(EXTeeAddress_W) );
    Wire.write(data[i]);
    Wire.endTransmission();
    delay(5); // wait for the I2C EEPROM to complete the write cycle
    eeAddress_W += sizeof(float); 
  }
}


