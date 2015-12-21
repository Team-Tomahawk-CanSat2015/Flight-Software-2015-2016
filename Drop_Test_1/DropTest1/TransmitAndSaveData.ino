void TransmitAndSaveData() {
  while ((millis() - TeleTime) < (long) 1000){}
  
  TeleArray[0] = TeamID;
  TeleArray[1] = packetCount;
  TeleArray[2] = dofData.Altitude;
  TeleArray[3] = dofData.Pressure;
  TeleArray[4] = dofData.Temperature;
  TeleArray[5] = gpsData.lat_degrees;
  TeleArray[6] = gpsData.lon_degrees;
  TeleArray[7] = gpsData.altitude;
  TeleArray[8] = gpsData.satNum; 
  TeleArray[9] = gpsData.velocity;
  TeleArray[10] = TeleCommand;

//String  TeleData = "";
   
  for (int i=0; i<11; ++i){
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
    if (Serial.available()){
      TeleCommand = Serial.read();
    }
}

