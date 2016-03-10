

//Functions, data types and Constants***************
void callGPS(gpsDataUnit* Unit);
const short HOUR = 0, MIN = 1, SEC = 2, DEGREE = 0, DIRECTION = 2;
//***************************************




void callGPS(struct gpsDataUnit* unit) {
 

GPS.begin(9600);
if (GPS.fix){
unit->lat_degrees = GPS.latitudeDegrees;
unit->lon_degrees = GPS.longitudeDegrees;
unit->velocity = GPS.speed;
} else {
unit->lat_degrees = 999;
unit->lon_degrees = 999;
unit->velocity = 999;
  
}
  
}















