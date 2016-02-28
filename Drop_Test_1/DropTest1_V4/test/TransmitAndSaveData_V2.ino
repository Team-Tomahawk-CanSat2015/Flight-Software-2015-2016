void TransmitAndSaveData() {
  while ((millis() - TeleTime) < (long) 1000) {}
  TeleArray[0] = packetCount;
  TeleArray[1] = gpsData.satTime;
  TeleArray[2] = gpsData.lat_degrees;
  TeleArray[3] = gpsData.lon_degrees;
  TeleArray[4] = gpsData.velocity;
  TeleArray[5] = dofData.Altitude;
  TeleArray[6] = dofData.Pressure;
  TeleArray[7] = dofData.Temperature;
  TeleArray[8] = dofData.x_accel;
  TeleArray[9] = dofData.y_accel;
  TeleArray[10] = dofData.z_accel;
  TeleArray[11] = dofData.x_alpha;
  TeleArray[12] = dofData.y_alpha;
  TeleArray[13] = dofData.z_alpha;

temp="";
  for (int i = 0; i <= 13; ++i) {
    temp+= (String) TeleArray[i] + ",";
  }


  TeleTime = millis();
  packetCount++;

}

/*
void ReceiveRadioData() {
  if (Serial.available()) {
    TeleCommand = Serial.read();
  }
}
*/



