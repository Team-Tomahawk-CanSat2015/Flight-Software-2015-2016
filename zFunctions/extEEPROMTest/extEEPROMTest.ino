#include <Wire.h>
#define EEPROM_ID 0x50

int EXTeeAddress_W = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("start");
  float data[3] = {27, 34, 8};

  //extEEPROMWrite(data, 3);

  extEEPROMReadAll();
;
}

void loop() {
  // put your main code here, to run repeatedly:

}

void extEEPROMWrite(float data[], int dataSize){
  for (int i = 0; i < dataSize; i++){
    if (EXTeeAddress_W + sizeof(float) >= 256000){
      EXTeeAddress_W = 0;
    }
    
    Wire.beginTransmission(EEPROM_ID);
    Wire.write((int)highByte(EXTeeAddress_W) );
    Wire.write((int)lowByte(EXTeeAddress_W) );
    
    Wire.write((byte)data[i]);
    Serial.println("write1");
    Wire.endTransmission();
    Serial.println("write2");
    delay(5); // wait for the I2C EEPROM to complete the write cycle
    EXTeeAddress_W += sizeof(float); 
  }
}

void extEEPROMReadAll() {
  float value;
  int eeAddress_R =0;
  int numValues = 256;
  for (int i = 0; i < numValues; i++) {
    if (eeAddress_R + sizeof(float) >= 256000){
      eeAddress_R = 0;
    }
    byte data;
    
  Wire.beginTransmission(EEPROM_ID);
  Wire.write((int)highByte(eeAddress_R) );
  Wire.write((int)lowByte(eeAddress_R) );
  
  //Wire.endTransmission();
  
  Wire.requestFrom(EEPROM_ID,(int)1);
  Serial.println("write1");
  while(Wire.available() == 0) // wait for data
    Serial.println("a");
    ;
  value = Wire.read();

    Serial.println(value);
    eeAddress_R += sizeof(float);
  }
}
