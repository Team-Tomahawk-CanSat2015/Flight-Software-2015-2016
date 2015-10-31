//Used to compile string and send string to radio serial
void TransmitandSave_data (){
  String toradio = "";
  toradio += TeamID;
  toradio += ",";
  toradio += packet_count;
  toradio += ",";
  toradio += pressure_Alt;
  toradio += ",";
  toradio += pitot_speed;
  toradio += ",";
  toradio += temp;
  toradio += ",";
  toradio += voltage;
  toradio += ",";
  toradio += GPS_lat;
  toradio += ",";
  toradio += GPS_lon;
  toradio += ",";
  toradio += GPS_alt;
  toradio += ",";
  toradio += GPS_satnum;
  toradio += ",";
  toradio += GPS_speed;
  toradio += ",";
  toradio += CMD_time;
  toradio += ",";
  toradio += CMD_count;
  toradio += ",";
  toradio += ServoPos;
  toradio += ",";
  toradio += state;
  //EXTRA data Starts here, Could possibly comment out but Naaa
      toradio += ",";
      toradio += x_alpha;
      toradio += ",";
      toradio += y_alpha;
      toradio += ",";
      toradio += z_alpha;
      toradio += ",";
      toradio += z_rollrate;
 
  Serial.println (toradio); //Print to radio
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
    digitalWrite (NichromePin, HIGH); 
    break;
    
    default:
    1+1; //Hope that's Tough enough?
    break;
    }
}


void Collect_Sensor_Data(){
   adafruit_function (&y_alpha, &x_alpha, &z_alpha, &z_rollrate, &pressure_Alt, &temp); //Update Adafruit 10 DOF IMU data
   geta_time (&a_time, &a_date); //Update all time variable
   
}


void Createnewlogfile(){
    //Serial.print (" CreatingNew Log file Named");
    geta_time(&a_time, &a_date);
    Serial.print( "Date = ");
    Serial.print(a_date);
    Serial.print( "      Time = ");
    Serial.println(a_time);
}









