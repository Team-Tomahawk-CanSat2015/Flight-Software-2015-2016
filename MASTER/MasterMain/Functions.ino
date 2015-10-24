void Transmit_data (){
  String toradio = "";
  toradio += TeamID;
  toradio += ", ";
  toradio += packetID;
  toradio += ", ";
  toradio += pressure_Alt;
  toradio += ", ";
  toradio += pitot_speed;
  toradio += ", ";
  toradio += temp;
  toradio += ", ";
  toradio += voltage1;
  toradio += ".";
  if (voltage2 > 10)
  toradio += voltage2;
  else{
  toradio += "0";
  toradio += voltage2; 
  }
  toradio += ", ";
  toradio += GPS_lat;
  toradio += ", ";
  toradio += GPS_lon;
  toradio += ", ";
  toradio += GPS_alt;
  toradio += ", ";
  toradio += GPS_satnum;
  toradio += ", ";
  toradio += GPS_speed;
  toradio += ", ";
  toradio += CMD_time;
  toradio += ", ";
  toradio += CMD_count;
  toradio += ", ";
  toradio += ServoPos;
  toradio += ", ";
  toradio += state;
  Serial.println (toradio);
}
