void TransmitAndSaveData() {
  while ((millis() - TeleTime) < (long) 1000) {}

  
  TeleArray[0] = packetCount;
  TeleArray[1] = gpsData.satTime;
  TeleArray[2] = gpsData.lat_degrees;
  TeleArray[3] = gpsData.lon_degrees;
  TeleArray[4] = gpsData.altitude;
  TeleArray[5] = gpsData.velocity;
  TeleArray[6] = dofData.Altitude;
  TeleArray[7] = dofData.Pressure;
  TeleArray[8] = dofData.Temperature;
  TeleArray[9] = dofData.x_accel;
  TeleArray[10] = dofData.y_accel;
  TeleArray[11] = dofData.z_accel;
  TeleArray[12] = dofData.x_alpha;
  TeleArray[13] = dofData.y_alpha;
  TeleArray[14] = dofData.z_alpha;
  TeleArray[15] = TeleCommand;

  for (int i = 0; i <= 15; ++i) {
    //TeleData += TeleArray[i];
    //TeleData += ",";
    Serial.print((String) TeleArray[i]);
    Serial.print(",");
    //SavetoSD((String)TeleArray[i] + ",");
  }
  Serial.print("\n");
  //SavetoSD("/n");
  TeleTime = millis();
  //SavetoSD(TeleData);
  packetCount++;

}


void ReceiveRadioData() {
  if (Serial.available()) {
    TeleCommand = Serial.read();
  }
}


void printLegend() {
  Serial.println("Legend:");
  Serial.println("Packet Count");
  Serial.println("GPS - Time");
  Serial.println("GPS - Latitude");
  Serial.println("GPS - Longitude");
  Serial.println("GPS - Altitude");
  Serial.println("GPS - Velocity");
  Serial.println("IMU - Altitude");
  Serial.println("IMU - Pressure");
  Serial.println("IMU - Temperature");
  Serial.println("IMU - X Acceleration");
  Serial.println("IMU - Y Acceleration");
  Serial.println("IMU - Z Acceleration");
  Serial.println("IMU - X Orientation");
  Serial.println("IMU - Y Orientation");
  Serial.println("IMU - Z Orientation");
  Serial.println("Char Received");
  Serial.println();
}


