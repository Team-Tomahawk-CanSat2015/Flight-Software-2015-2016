//Functions and data types***************
struct gpsDataUnit {
  long altitude;     //Units is always mmeters          
  long satNum;       //## of Satlites connected to
  float velocity;    //Units is always m/s
  float lon_degrees; //
  float lat_degrees; //
} gpsData;

//Default Arduino Code*******************
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
  gpsData.altitude = 889;
  gpsData.satNum = 3;
  gpsData.velocity = 23.1;
  gpsData.lon_degrees = 4.33;
  gpsData.lat_degrees = -70.2;
   
}

void loop() {
}














