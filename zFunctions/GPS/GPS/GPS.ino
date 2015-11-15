#include <string.h>

//Functions and data types***************
struct gpsDataUnit {
  float satTime[3];
  float latitude[2];
  char latDir;
  float longitude[2];
  char longDir;
  float altitude;
  char altUnit;
  float satNum;
  float velocity;
} gpsData;

void callGPS(gpsDataUnit* Unit);
void printStuff(gpsDataUnit* Unit);
void parseGSA(gpsDataUnit* Unit);
void parseGSV(gpsDataUnit* Unit);
void parseRMC(gpsDataUnit* Unit);
void parseVTG(gpsDataUnit* Unit);
//***************************************


//Global Variabes************************
//gpsDataUnit gpsData;
const short HOUR = 0, MIN = 1, SEC = 2, DEGREE = 0; 
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

  //ParseGGA
  String GGA = data.substring(index1, index2);
  GGA.remove(0, 7);

  
  //ParseTime
  float temp = GGA.toFloat();
  unit->satTime[HOUR] = (int) temp / 10000;
  temp -= unit->satTime[HOUR] *10000;
  unit->satTime[MIN] = (int)temp / 100;
  temp -= unit-> satTime[MIN] * 100;
  unit->satTime[SEC] = temp;

  

  //Lat+Long
  GGA.remove(0,GGA.indexOf(",")+1);
  temp = GGA.toFloat();
  unit->latitude[DEGREE] = int(temp)/ 100;
  unit->latitude[MIN]= temp - unit->latitude[DEGREE] * 100;
  GGA.remove(0, GGA.indexOf(",")+1);
  unit->latDir = GGA.charAt(0);
  

  GGA.remove(0, GGA.indexOf(",")+1);
  temp = GGA.toFloat();
  unit->longitude[DEGREE] = (int) temp /100;
  unit->longitude[MIN] = temp - unit->longitude[DEGREE]*100;
  GGA.remove(0, GGA.indexOf(",")+1);
  unit->longDir = GGA.charAt(0);

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

  Serial.print("Longitude: ");
  Serial.print(unit->longitude[DEGREE]);
  Serial.print("'");
  Serial.print(unit->longitude[MIN]);
  Serial.print(" ");
  Serial.println(unit -> longDir);

  Serial.print("Latitude: ");
  Serial.print(unit->latitude[DEGREE]);
  Serial.print("'");
  Serial.print(unit->latitude[MIN]);
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













