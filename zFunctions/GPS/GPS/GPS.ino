
//Functions and data types***************
struct gpsDataUnit {
  float satTime[3];//    0: Hours  1: Minutes 2: Seconds
  float latitudeDMD[3];//   0: Degree 1: Minutes 2: Direction
  float latitude;
  char latDir;
  float longitudeDMD[3];//  0: Degree 1: Minutes 2: Direction
  float longitude;
  char longDir;
  float altitude;
  char altUnit;
  float satNum;
  float velocity;
} gpsData;

void callGPS(gpsDataUnit* Unit);
void printStuff(gpsDataUnit* Unit);
//***************************************


//Global Variabes************************
//gpsDataUnit gpsData;
const short HOUR = 0, MIN = 1, SEC = 2, DEGREE = 0, DIRECTION = 2; 
//***************************************


//Default Arduino Code*******************
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
}

void loop() {
  callGPS(&gpsData);
  printStuff(&gpsData);

  delay (3000);
}
//***************************************

void callGPS(struct gpsDataUnit* unit) {
  String data = Serial.readString();
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
  unit->latitudeDMD[DEGREE] = int(temp)/ 100;
  unit->latitudeDMD[MIN]= temp - unit->latitudeDMD[DEGREE] * 100;
  GGA.remove(0, GGA.indexOf(",")+1);
  unit->latDir = GGA.charAt(0);
  if (unit->latDir == 'N'){
  unit->latitudeDMD[DIRECTION] = 1;
  } else if (unit->latDir == 'E'){
   unit->latitudeDMD[DIRECTION] = 2;
  } else if (unit->latDir == 'S'){
   unit->latitudeDMD[DIRECTION] = 3;
  } else if (unit->latDir == 'W'){
   unit->latitudeDMD[DIRECTION] = 4;
  }
  
  GGA.remove(0, GGA.indexOf(",")+1);
  temp = GGA.toFloat();
  unit->longitudeDMD[DEGREE] = (int) temp /100;
  unit->longitudeDMD[MIN] = temp - unit->longitudeDMD[DEGREE]*100;
  GGA.remove(0, GGA.indexOf(",")+1);
  unit->longDir = GGA.charAt(0);
   if (unit->longDir == 'N'){
   unit->longitudeDMD[DIRECTION] = 1;
  } else if (unit->longDir == 'E'){
   unit->longitudeDMD[DIRECTION] = -1;
  } else if (unit->longDir == 'S'){
   unit->longitudeDMD[DIRECTION] = 1;
  } else if (unit->longDir == 'W'){
   unit->longitudeDMD[DIRECTION] = -1;
  }

  //Convert Lat/Long
  unit->longitude = unit->longitudeDMD[DIRECTION] * (unit->longitudeDMD[DEGREE] + (unit->longitudeDMD[MIN])/60.0);
  unit->latitude = unit->latitudeDMD[DIRECTION] * (unit->latitudeDMD[DEGREE] + (unit->latitudeDMD[MIN])/60.0);
  
  
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
  unit->velocity = VTG.toFloat();
}

//Time/Position/Fix Information Parsing Function
void printStuff(struct gpsDataUnit* unit) {

  Serial.print("Time: ");
  Serial.print(unit -> satTime[HOUR]);
  Serial.print(" : ");
  Serial.print(unit -> satTime[MIN]);
  Serial.print(" : ");
  Serial.println(unit -> satTime[SEC]);

  Serial.print("longitudeDMD: ");
  Serial.print(unit->longitudeDMD[DEGREE]);
  Serial.print("'");
  Serial.print(unit->longitudeDMD[MIN]);
  Serial.print(" ");
  Serial.println(unit -> longDir);

  Serial.print("latitudeDMD: ");
  Serial.print(unit->latitudeDMD[DEGREE]);
  Serial.print("'");
  Serial.print(unit->latitudeDMD[MIN]);
  Serial.print(" ");
  Serial.println(unit -> latDir);

   Serial.print("Altitude: ");
   Serial.print(unit->altitude);
   Serial.print(" ");
   Serial.println(unit->altUnit);

   Serial.print("Number of Satalite Connections: ");
   Serial.println(unit->satNum);

   Serial.print("Velocity (km/h): ");
   Serial.println(unit->velocity);

   Serial.println();
   Serial.println();
}













