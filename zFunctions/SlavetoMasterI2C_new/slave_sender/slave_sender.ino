#include <Wire.h>

// Declaring global variables for GPS telemetry. altitude, satnum, velocity, lon_deg, lat_deg
volatile float a, b, c, d, e;

// Constants:
const byte myAddress = 8;
const byte dataCount = 20; // [bytes] (max:32)

// union variables:
union alt {byte b[20]; float f;} alt;
union satnum {byte b[20]; float f;} satnum;
union vel {byte b[20]; float f;} vel;
union lon_deg {byte b[20]; float f;} lon_deg;
union lat_deg {byte b[20]; float f;} lat_deg;

// Creating Fake GPS Data (in actuality, we will get realtime GPS telemetry)
struct gpsDataUnit {
  float altitude;     //Units is always mmeters          
  float satNum;       //## of Satlites connected to
  float velocity;    //Units is always m/s
  float lon_degrees; //
  float lat_degrees; //
} gpsData;

void writeValues(){ // The function that executes whenever data is requested by master.
  a = gpsData.altitude; b = gpsData.satNum; 
  c = gpsData.velocity; d = gpsData.lon_degrees;
  e = gpsData.lat_degrees;
  
  alt.f = a; satnum.f = b; vel.f = c;
  lon_deg.f = d; lat_deg.f = e;
  
  byte data[dataCount];
  byte j;

  for (byte i = 0; i < 4; i++) {
    j = i * 5; // dataCount / 4 = 5
    data[j]     = alt.b[i];
    data[j + 1] = satnum.b[i];
    data[j + 2] = vel.b[i];
    data[j + 3] = lon_deg.b[i];
    data[j + 4] = lat_deg.b[i];
  }

  Wire.write(data, dataCount);
}

void setup()
{
  // I2C BUS:
  Wire.begin(myAddress); // Join I2C Bus as a Slave Device with address #myAddress
  Wire.onRequest(writeValues); // Interrupt handler for when data is requested.
  
  Serial.begin(9600);

   

  //Set Fake GPS Data here
  gpsData.altitude = 77.22;
  gpsData.satNum = 4;
  gpsData.velocity = 33.1;
  gpsData.lon_degrees = 49.33;
  gpsData.lat_degrees = -79.2;
  delay(200);
}

void loop()
{
}
