//Used to compile string and send string to radio serial
void Transmit_data (){
  String toradio = "";
  toradio += TeamID;
  toradio += ", ";
  toradio += packet_count;
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

//Returns True if radio recived data from Ground station or serial port
bool getdatafromRadio () {
  if (!Serial.available())
    return false;
    else
    return true;
}

//Either adjusts servo angle on slave or takes a SHOT on Master
void PerformRadiotask(){
  String recv = Serial.readString();
  
    switch (recv.charAt(0)){
    case '#': //#160 to change servo angle
    Serial.println ("Recived Servo Command");
    break;
    
    case'*': //* to take snapshot of camera
    Serial.println ("Recived Camera Command");
    ++CMD_count;
    CMD_time = millis();//need to change this to mission time
    //TakeSnapShot(); 
    break;
    
    case'&': //& For instant Nichrome Burn Baby!!!!!!
    Serial.println ("Recived Nichrome Burn Command");
    digitalWrite (nichrome_pin, HIGH); 
    break;
    
    default:
    1+1; //Hope that's Tough enough?
    break;
    }
}









