
//Functions and data types***************

void callGPS(gpsDataUnit* Unit);
void printStuff(gpsDataUnit* Unit);
//***************************************


//Global Variabes************************
//gpsDataUnit gpsData;
const short HOUR = 0, MIN = 1, SEC = 2, DEGREE = 0, DIRECTION = 2; 
//***************************************


//Default Arduino Code*******************
/*
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
}

void loop() {
  callGPS(&gpsData);
  printStuff(&gpsData);

  delay (3000);
}
*/
//***************************************

void callGPS(struct gpsDataUnit* unit) {
  String data = Serial.readString();
  Serial.print (data);
  Serial.flush();
  int index1 = data.indexOf("$GPGGA");
  int index2 = data.indexOf("$", index1 +1);
  float temp;
  
  //ParseGGA
  String GGA = data.substring(index1, index2);
  GGA.remove(0, 7);

  
  //ParseTime
  /*
  temp = GGA.toFloat();
  unit->satTime[HOUR] = (int) temp / 10000;
  temp -= unit->satTime[HOUR] *10000;
  unit->satTime[MIN] = (int)temp / 100;
  temp -= unit-> satTime[MIN] * 100;
  unit->satTime[SEC] = temp;
  */


  //Lat+Long
  GGA.remove(0,GGA.indexOf(",")+1);
  temp = GGA.toFloat();
  unit->latitude[DEGREE] = int(temp)/ 100;
  unit->latitude[MIN]= temp - unit->latitude[DEGREE] * 100;
  
  GGA.remove(0, GGA.indexOf(",")+1);
  unit->latDir = GGA.charAt(0);
  if (unit->latDir == 'N'){
  unit->latitude[DIRECTION] = 1;
  } else if (unit->latDir == 'E'){
   unit->latitude[DIRECTION] = 2;
  } else if (unit->latDir == 'S'){
   unit->latitude[DIRECTION] = 3;
  } else if (unit->latDir == 'W'){
   unit->latitude[DIRECTION] = 4;
  }
  
  GGA.remove(0, GGA.indexOf(",")+1);
  temp = GGA.toFloat();
  unit->longitude[DEGREE] = (int) temp /100;
  unit->longitude[MIN] = temp - unit->longitude[DEGREE]*100;
  GGA.remove(0, GGA.indexOf(",")+1);
  unit->longDir = GGA.charAt(0);
   if (unit->longDir == 'N'){
   unit->longitude[DIRECTION] = 1;
  } else if (unit->longDir == 'E'){
   unit->longitude[DIRECTION] = 2;
  } else if (unit->longDir == 'S'){
   unit->longitude[DIRECTION] = 3;
  } else if (unit->longDir == 'W'){
   unit->longitude[DIRECTION] = 4;
  }

  //Gps latitude and longitude to degrees
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
  Serial.println(VTG);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  VTG.remove(0, VTG.indexOf(",")+1);
  Serial.println(VTG);
  unit->velocity = VTG.toFloat()*0.27777772;// to m/s

  if (unit->satNum == 0){
    unit-> lat_degrees = 999;
    unit-> lon_degrees = 999;
    unit-> velocity = 999;
    unit-> altitude = -999;
    }
}

//Time/Position/Fix Information Parsing Function
void printStuff(struct gpsDataUnit* unit) {

  /*Serial.print("Time: ");
  Serial.print(unit -> satTime[HOUR]);
  Serial.print(" : ");
  Serial.print(unit -> satTime[MIN]);
  Serial.print(" : ");
  Serial.println(unit -> satTime[SEC]);*/

  Serial.print("Longitude: ");
  Serial.println(unit->lon_degrees);
  /*Serial.print(unit->longitude[DEGREE]);
  Serial.print("'");
  Serial.print(unit->longitude[MIN]);
  Serial.print(" ");
  Serial.println(unit -> longDir);*/

  Serial.print("Latitude in deg: "); 
   Serial.println(unit->lat_degrees);
  /*Serial.print(unit->latitude[DEGREE]);
  Serial.print("'");
  Serial.print(unit->latitude[MIN]);
  Serial.print(" ");
  Serial.println(unit -> latDir);*/

   Serial.print("Altitude: ");
   Serial.print(unit->altitude);
   Serial.print(" ");
   Serial.println(unit->altUnit);

   Serial.print("Number of Satalite Connections: ");
   Serial.println(unit->satNum);

   Serial.print("Velocity (m/s): ");
   Serial.println(unit->velocity);

   Serial.println();
   Serial.println();
}













