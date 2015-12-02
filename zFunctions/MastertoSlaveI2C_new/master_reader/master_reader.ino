#include <Wire.h>

// Declaring global variables for GPS telemetry. altitude, satnum, velocity, lon_deg, lat_deg
volatile float a, b, c, d, e;

// Constants:
    const byte slaveAddress = 8;
    const byte dataCount = 20; // [bytes] (max:32)

// Variables:
    union alt {byte b[20]; float f;} alt; // a
    union satnum {byte b[20]; float f;} satnum; // b
    union vel {byte b[20]; float f;} vel; // c
    union lon_deg {byte b[20]; float f;} lon_deg; // d
    union lat_deg {byte b[20]; float f;} lat_deg; // e

void readValues() // Requests GPS Data from the slave.
{
  if (Wire.requestFrom(slaveAddress, dataCount) == dataCount)
  {
    for (byte i = 0; i < dataCount; i++)
    {
      alt.b[i] = Wire.read();
      satnum.b[i] = Wire.read();
      vel.b[i] = Wire.read();
      lon_deg.b[i] = Wire.read();
      lat_deg.b[i] = Wire.read();
    }
    a = alt.f;
    b = satnum.f;
    c = vel.f;
    d = lon_deg.f;
    e = lat_deg.f;
    Serial.print("Altutude: "); Serial.println(a);
    Serial.print("Satellite Number: "); Serial.println(b);  
    Serial.print("Velocity: "); Serial.println(c);
    Serial.print("Longitude Degrees: "); Serial.println(d);
    Serial.print("Latitude Degrees: "); Serial.println(e);
  }
  else
  {
    while (Wire.available()) {byte del = Wire.read();} // Delete any data on wire.
  }
}

void setup()
{
  // I2C BUS:
  Wire.begin(); // Join I2C Bus as a Master Device
  Serial.begin(9600);
  delay(200);
}

void loop(){
  readValues();
  delay(4000);
}
