#ifndef __GPS_H__
#define __GPS_H__

struct gpsDataUnit {
  long satTime[3];//0: Hours  1: Minutes 2: Seconds
  long latitude[3];//0: Degree 1: Minutes 2: Direction
  char latDir;
  long longitude[3];//0: Degree 1: Minutes 2: Direction
  char longDir;
  long altitude;
  char altUnit;
  long satNum;
  long velocity;
  //----------------
  long lon_degrees;
  long lat_degrees;
} gpsData;

//void callGPS(gpsDataUnit* Unit);
//void printStuff(gpsDataUnit* Unit);



#endif
