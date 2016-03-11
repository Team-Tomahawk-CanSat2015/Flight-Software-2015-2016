

//Functions, data types and Constants***************
void callGPS(gpsDataUnit* Unit);
const short HOUR = 0, MIN = 1, SEC = 2, DEGREE = 0, DIRECTION = 2;
//***************************************




void callGPS(struct gpsDataUnit* unit) {

  if (softSer.available()) {

    float latitude[3], longitude[3];
    char latDir, longDir;

    String data = softSer.readString();
    softSer.flush();
    int index1 = data.indexOf("$GPGGA");
    int index2 = data.indexOf("$", index1 + 1);
    float temp;

    //ParseGGA
    String GGA = data.substring(index1, index2);
    GGA.remove(0, 7);

    
    //ParseTime
    unit->satTime = GGA.toFloat();
 
    
    //Lat+Long
    GGA.remove(0, GGA.indexOf(",") + 1);
    temp = GGA.toFloat();
    latitude[DEGREE] = int(temp) / 100;
    latitude[MIN] = temp - latitude[DEGREE] * 100;

    GGA.remove(0, GGA.indexOf(",") + 1);
    latDir = GGA.charAt(0);
    if (latDir == 'N') {
      latitude[DIRECTION] = 1;
    } else if (latDir == 'E') {
      latitude[DIRECTION] = 2;
    } else if (latDir == 'S') {
      latitude[DIRECTION] = 3;
    } else if (latDir == 'W') {
      latitude[DIRECTION] = 4;
    }

    GGA.remove(0, GGA.indexOf(",") + 1);
    temp = GGA.toFloat();
    longitude[DEGREE] = (int) temp / 100;
    longitude[MIN] = temp - longitude[DEGREE] * 100;
    GGA.remove(0, GGA.indexOf(",") + 1);
    longDir = GGA.charAt(0);
    if (longDir == 'N') {
      longitude[DIRECTION] = 1;
    } else if (longDir == 'E') {
      longitude[DIRECTION] = 2;
    } else if (longDir == 'S') {
      longitude[DIRECTION] = 3;
    } else if (longDir == 'W') {
      longitude[DIRECTION] = 4;
    }

    //Gps latitude and longitude to degrees
    unit->lon_degrees = latitude[DEGREE] + (0.0166666 * latitude[MIN] );
    unit->lat_degrees = longitude[DEGREE] + (0.0166666 * longitude[MIN] );


    //Number of Satalites
    GGA.remove(0, GGA.indexOf(",") + 1);
    GGA.remove(0, GGA.indexOf(",") + 1);
    unit->satNum = GGA.toFloat();

    //Altitude
    GGA.remove(0, GGA.indexOf(",") + 1);
    GGA.remove(0, GGA.indexOf(",") + 1);
    unit->altitude = GGA.toFloat();
    GGA.remove(0, GGA.indexOf(",") + 1);
    unit->altUnit = GGA.charAt(0);

    //ParseVTG
    index1 = data.indexOf("$GPVTG");
    index2 = data.indexOf("$", index1 + 1);
    String VTG = data.substring(index1, index2);

    for (int i = 0; i< 8; i++){
    VTG.remove(0, VTG.indexOf(",") + 1);
    }/*
    VTG.remove(0, VTG.indexOf(",") + 1);
    VTG.remove(0, VTG.indexOf(",") + 1);
    VTG.remove(0, VTG.indexOf(",") + 1);
    VTG.remove(0, VTG.indexOf(",") + 1);
    VTG.remove(0, VTG.indexOf(",") + 1);
    VTG.remove(0, VTG.indexOf(",") + 1);
    */
    unit->velocity = VTG.toFloat() * 0.27777772; // to m/s

    if (unit->satNum == 0) {
      unit-> lat_degrees = 999;
      unit-> lon_degrees = 999;
      unit-> velocity = 999;
      unit-> altitude = -999;
    }
  }
  
}















