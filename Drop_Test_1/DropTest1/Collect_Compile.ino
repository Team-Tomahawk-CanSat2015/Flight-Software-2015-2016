
/*void CompileData(){
 //TeleData = "";
  TeleData = (String) TeamID;
  TeleData += ",";
  
  TeleData +=  packetCount;
  TeleData += ",";
  TeleData +=  dofData.Altitude;
  TeleData += ",";
  TeleData +=  dofData.Pressure;
  TeleData += ",";
  TeleData +=  dofData.Temperature;
  TeleData += ",";
  TeleData +=  gpsData.lat_degrees;
  TeleData += ",";
  TeleData +=  gpsData.lon_degrees;
  TeleData += ",";
  TeleData +=  gpsData.altitude;
  TeleData += ",";
  TeleData +=  gpsData.satNum;
  TeleData += ",";
  TeleData +=  gpsData.velocity;
  TeleData += ",";
  TeleData +=  TeleCommand;

  Serial.println(TeleData);
}
*/

/*void up (){
  TeleArray[0] = TeamID;
  
  TeleArray[1] = packetCount;
  
  TeleArray[2] =  dofData.Altitude;
  
  TeleArray[3] =  dofData.Pressure;
  
  TeleArray[4] =  dofData.Temperature;
  
  TeleArray[5] =  gpsData.lat_degrees;
  
  TeleArray[6] =  gpsData.lon_degrees;
  
  TeleArray[7] =  gpsData.altitude;
  
  TeleArray[8] =  gpsData.satNum;
  
  TeleArray[9] =  gpsData.velocity;
  
  TeleArray[10] =  TeleCommand;

   TeleData = "";
   
  for (int i=0; i<11; ++i){
    TeleData += TeleArray[i];
    TeleData += ",";
    }

  
  Serial.println(TeleData);
  
  }*/



