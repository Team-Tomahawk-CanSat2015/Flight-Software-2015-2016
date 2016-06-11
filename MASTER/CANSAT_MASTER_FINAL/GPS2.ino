void setupGPS_2(){
  GpsSerial.begin(9600);
  GpsSerial.setTimeout(400);
  }

void callGPS(struct gpsDataUnit* unit) {
  if (!GpsSerial.available ()) return;
  String data = GpsSerial.readString();
  //Serial.println (data);
 
  GpsSerial.flush();
  int index1 = data.indexOf("$GPGGA");
  int index2 = data.indexOf("$", index1 +1);
  float temp;
  
  //ParseGGA
  String GGA = data.substring(index1, index2);
  GGA.remove(0, 7);

  //Lat+Long
  GGA.remove(0,GGA.indexOf(",")+1);
  temp = GGA.toFloat();
  unit->latitude[DEGREE] = int(temp)/ 100;
  unit->latitude[MIN]= temp - unit->latitude[DEGREE] * 100.00;
  GGA.remove(0, GGA.indexOf(",")+1);
  /*unit->latDir = GGA.charAt(0);
  if (unit->latDir == 'N'){
  unit->latitude[DIRECTION] = 1;
  } else if (unit->latDir == 'E'){
   unit->latitude[DIRECTION] = 2;
  } else if (unit->latDir == 'S'){
   unit->latitude[DIRECTION] = 3;
  } else if (unit->latDir == 'W'){
   unit->latitude[DIRECTION] = 4;
  }*/
  
  GGA.remove(0, GGA.indexOf(",")+1);
  temp = GGA.toFloat();
  unit->longitude[DEGREE] = (int) temp /100;
  unit->longitude[MIN] = temp - unit->longitude[DEGREE]*100.00;
  GGA.remove(0, GGA.indexOf(",")+1);
  /*unit->longDir = GGA.charAt(0);
   if (unit->longDir == 'N'){
   unit->longitude[DIRECTION] = 1;
  } else if (unit->longDir == 'E'){
   unit->longitude[DIRECTION] = 2;
  } else if (unit->longDir == 'S'){
   unit->longitude[DIRECTION] = 3;
  } else if (unit->longDir == 'W'){
   unit->longitude[DIRECTION] = 4;
  }*/

  //Gps latitude and longitude to degrees
  if (unit->latitude[DEGREE]+ (0.0166666 * unit->latitude[MIN] ) == 0){return;}
  unit->lon_degrees = unit->latitude[DEGREE]+ (0.0166666 * unit->latitude[MIN] );
  unit->lat_degrees = unit->longitude[DEGREE]+(0.0166666 * unit->longitude[MIN] );

  
  //Number of Satalites
  GGA.remove(0, GGA.indexOf(",")+1);
  GGA.remove(0, GGA.indexOf(",")+1);
  unit->satNum = GGA.toFloat(); 

  //Altitude
  GGA.remove(0,GGA.indexOf(",")+1);
  GGA.remove(0,GGA.indexOf(",")+1);
  unit->altitude = GGA.toFloat();
  GGA.remove(0, GGA.indexOf(",")+1);
  unit->altUnit = GGA.charAt(0);

  //ParseVTG
  index1 = data.indexOf("$GPVTG");
  index2 = data.indexOf("$", index1 +1);
  String VTG = data.substring(index1, index2);
  //Serial.println(VTG);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  //Serial.println(VTG);
  unit->velocity = VTG.toFloat()*0.27777772;// to m/s
  
  SensorData[5] = unit-> lat_degrees;//* 10. GPS latitude[5]
  SensorData[6] = unit-> lon_degrees;//* 11. GPS longitude.[6]
  SensorData[7] = unit->altitude;//* 12. GPS Altitude.[7]
  SensorData[8] = unit->satNum;//* 13. GPS Satlite number.[8]
  SensorData[9] = unit->velocity;//* 14. GPS speed.[9]

  /*if (unit->satNum == 0){
    SensorData[5] = 0;
    SensorData[6] = 0;
    SensorData[7] = 0;
    SensorData[8] = 0;
    SensorData[9] = 0;
    }*/
    
    

    
}
