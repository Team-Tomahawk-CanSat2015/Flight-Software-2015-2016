void Setup_RSTpin(){
digitalWrite (RstPin, HIGH);
pinMode(RstPin, INPUT);
}

void soft_RST(){
Serial.flush();
pinMode(RstPin, OUTPUT);
digitalWrite (RstPin, LOW);
}

void saveGPSonSD(struct gpsDataUnit* unit){
  String toSD = "";
  toSD += unit->lat_degrees; toSD += ",";
  toSD += unit->lon_degrees; toSD += ",";
  toSD += unit->altitude; toSD += ",";
  toSD += unit->satNum; toSD += ",";  
  toSD += unit->velocity; 

  if (!SD.begin(10)){Serial.println("SD Error");}
  SD.remove("GPS.txt");
  File GPSfile = SD.open("GPS.txt", FILE_WRITE);
  GPSfile.println(toSD);
  }
