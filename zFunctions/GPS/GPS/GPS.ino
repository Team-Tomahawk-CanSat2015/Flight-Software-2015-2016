#include <string.h>



//Functions and data types***************
struct gpsDataUnit {
  float satTime[3];
  float latitude;
  float longitude;
  float altitude;
  float satNum;
  float velocity;
} gpsData;

void callGPS(gpsDataUnit* Unit);
void parseGGA(gpsDataUnit* Unit);
void parseGSA(gpsDataUnit* Unit);
void parseGSV(gpsDataUnit* Unit);
void parseRMC(gpsDataUnit* Unit);
void parseVTG(gpsDataUnit* Unit);
//***************************************


//Global Variabes************************
//gpsDataUnit gpsData;
const short HOUR = 0, MIN = 1, SEC = 2;
const short GPGAA = 1, GPGSA = 2;
//***************************************


//Default Arduino Code*******************
void setup() {
  Serial.begin(9600);
}

void loop() {
  callGPS(&gpsData);
  delay(10);
}
//***************************************





void callGPS(struct gpsDataUnit* unit) {
  //Variable declaration
  bool GGA = false, GSA = false, GSV = false, RMC = false, VTG = false;
  bool updated = false;
  char readChar;
  char NMEA[5];

  
  while (updated == false) {

    //Initate new NMEA
    
    
    readChar = Serial.read();
    if (readChar == '$') {

      //Read NMEA CODE
      readChar = Serial.read();
      int charNo = 0;
      while (readChar != ',') {
        NMEA[charNo] = readChar;
        charNo++;
        readChar = Serial.read();
      }
      printf("a");
      //Serial.write(NMEA);
        if (strcmp("GPGGA", NMEA)==0){
        parseGGA(unit); GGA = true;
        } else if (strcmp("GPGSA", NMEA)==0){
        //parseGSA(unit); GSA = true;
        } else if (strcmp("GPGSV", NMEA)==0){
        //parseGSV(unit); GSV = true;
        } else if (strcmp("GPRMC", NMEA)==0){
        //parseRMC(unit); RMC = true;
        } else if (strcmp("GPVTG", NMEA)==0){
        //parseVTG(unit); VTG = true;
        }
      

      //Check if All data feild updated
      if (GGA == true &&
          GSA == true &&
          GSV == true &&
          RMC == true &&
          VTG == true) {
        updated = true;
        GGA = false;
        GSA = false;
        GSV = false;
        RMC = false;
        VTG = false;
      }
    }
  }
}

//Time/Position/Fix Information Parsing Function
void parseGGA(struct gpsDataUnit* unit){
  float rawTime = Serial.parseFloat();
  unit->satTime[HOUR] = (int) rawTime / 10000;
  unit->satTime[MIN] = (int)(rawTime - unit->satTime[HOUR]*10000)/100;
  unit->satTime[SEC] = rawTime - unit->satTime[HOUR]*10000 - unit->satTime[MIN]*100;

  Serial.print(unit -> satTime[SEC], DEC);
}













