void EEPROMReadAll() {
  float value;
  int eeAddress_R =0;
  int numValues = 256;
  for (int i = 0; i < numValues; i++) {
    if (eeAddress_R + sizeof(float) >= EEPROM.length()){
      eeAddress_R = 0;
    }
    EEPROM.get(eeAddress_R, value);
    Serial.println(value);
    eeAddress_R += sizeof(float);
  }
}


void extEEPROMReadAll() {
  float value;
  int eeAddress_R =0;
  int numValues = 256;
  for (int i = 0; i < numValues; i++) {
    if (eeAddress_R + sizeof(float) >= EEPROM.length()){
      eeAddress_R = 0;
    }
    byte data;
  Wire.beginTransmission(EEPROM_ID);
  Wire.write((int)highByte(eeAddress_R) );
  Wire.write((int)lowByte(eeAddress_R) );
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ID,(int)1);
  while(Wire.available() == 0) // wait for data
    ;
  value = Wire.read();

    Serial.println(value);
    eeAddress_R += sizeof(float);
  }
}
//void EEPROMRead(float values[], int numValues) {
//  int eeAddress_R =0;
//  for (int i = 0; i < numValues; i++) {
//    if (eeAddress_R + sizeof(float) >= EEPROM.length()){
//      eeAddress_R = 0;
//    }
//    EEPROM.get(eeAddress_R, values[i]);
//    Serial.println(values[i]);
//    eeAddress_R += sizeof(float);
//  }
//}
//
//void EEPROMRead(float values[]) {
//  int eeAddress_R =0;
//  int numValues = 256;
//  for (int i = 0; i < numValues; i++) {
//    if (eeAddress_R + sizeof(float) >= EEPROM.length()){
//      eeAddress_R = 0;
//    }
//    EEPROM.get(eeAddress_R, values[i]);
//    Serial.println(values[i]);
//    eeAddress_R += sizeof(float);
//  }
//}


