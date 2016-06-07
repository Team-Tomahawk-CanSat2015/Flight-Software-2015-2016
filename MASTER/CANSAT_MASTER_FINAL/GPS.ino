/*boolean usingInterrupt = false;
void useInterrupt(boolean);
SoftwareSerial mySerial(7, 8); // RX, TX
Adafruit_GPS GPS(&mySerial);

void setupGPS(){ //To Set up GPS as Just like the ada fruit libary 
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
}


SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  #ifdef UDR0
    if (GPSECHO)
      float useless_value = 1;  //if (c) UDR0 = c;<--TO PRINT OUT FULL NNMEA SENTENCE--PLS DO NOT DELETE  
  #endif
}
void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}


void UpdateGPSData(){
  GPS.newNMEAreceived();
  GPS.parse(GPS.lastNMEA());
  if (GPS.fix >= 1) {
    SensorData[5] = GPS.latitudeDegrees;//* 10. GPS latitude[5]
    SensorData[6] = GPS.longitudeDegrees;//* 11. GPS longitude.[6]
    SensorData[7] = GPS.satellites;//* 12. GPS Altitude.[7]
    SensorData[8] = GPS.fix;//* 13. GPS Satlite number.[8]
    SensorData[9] = GPS.speed;//* 14. GPS speed.[9]
  }
  else 
  {
  SensorData[5] = 0;
  SensorData[6] = 0;
  SensorData[7] = 0;
  SensorData[8] = 0;
  SensorData[9] = 0;
  
  }
   
}
*/

/*void UpdateGPSData1 (){
  SoftwareSerial mySerial(7, 8); // RX, TX
  Adafruit_GPS GPS(&mySerial);
  //////////////////////////////////////////////////////////////
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   
  // useInterrupt(true);/////////////////////////////////////////
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  usingInterrupt = true;
  ///////////////////////////////////////////
  GPS.newNMEAreceived();
  GPS.parse(GPS.lastNMEA());
  if (GPS.fix >= 1) {
    SensorData[5] = GPS.latitudeDegrees;//* 10. GPS latitude[5]
    SensorData[6] = GPS.longitudeDegrees;//* 11. GPS longitude.[6]
    SensorData[7] = GPS.satellites;//* 12. GPS Altitude.[7]
    SensorData[8] = GPS.fix;//* 13. GPS Satlite number.[8]
    SensorData[9] = GPS.speed;//* 14. GPS speed.[9]
  }
  else 
  {
  SensorData[5] = 0;
  SensorData[6] = 0;
  SensorData[7] = 0;
  SensorData[8] = 0;
  SensorData[9] = 0;
  }
  mySerial.end();
  
  }*/
