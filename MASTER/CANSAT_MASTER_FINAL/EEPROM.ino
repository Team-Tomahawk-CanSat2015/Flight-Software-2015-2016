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

 void EEPROMWrite(float data[], int dataSize){
   for (int i = 0; i < dataSize; i++){
     if (eeAddress_W + sizeof(float) >= EEPROM.length()){
       eeAddress_W = 0;
     }
     EEPROM.put(eeAddress_W, data[i]);
     eeAddress_W += sizeof(float); 
   }
 }
