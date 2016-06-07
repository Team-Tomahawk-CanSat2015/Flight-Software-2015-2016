//Functions and data types***************
struct gpsDataUnit {
  float satTime[3];//0: Hours  1: Minutes 2: Seconds
  float latitude[3];//0: Degree 1: Minutes 2: Direction
  char latDir;
  float longitude[3];//0: Degree 1: Minutes 2: Direction
  char longDir;
  float altitude;
  char altUnit;
  float satNum;
  float velocity;
  //----------------
  float lon_degrees;
  float lat_degrees;
} gpsData;

void callGPS(gpsDataUnit* Unit);
void printStuff(gpsDataUnit* Unit);
//***************************************


//Global Variabes************************
//gpsDataUnit gpsData;
const short HOUR = 0, MIN = 1, SEC = 2, DEGREE = 0, DIRECTION = 2; 
//***************************************
