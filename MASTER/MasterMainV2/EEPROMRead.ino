void EEPROMRead() {
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


