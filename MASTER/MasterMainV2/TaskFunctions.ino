//Used to compile string and send string to radio serial
void TransmitandSave_data (byte save){
  String radio = "";
  radio += TeamID; radio += ",";
  for (int i=0; i<19; ++i){
  radio += Tele_data[i];
  radio += "," ;
  }
  Serial.println (radio);
  if (save == 1){
  //Extra stuff to save
  radio += a_time; radio += ",";
  radio += a_date; radio += ",";
  SavetoSD(radio, "M_tele.txt");
   }
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
    //Serial.println ("Recived Servo Command");
    break;
    
    case'*': //* to take snapshot of camera
    Serial.println ("Recived Camera Command from GCS");
    ++Tele_data[11];//++CMD_count;
    Tele_data[10] = millis (); //CMD_time = millis();//need to change this to mission time
    TakeSnapShot(); 
    break;
    
    case'&': //& For instant Nichrome Burn Baby!!!!!!
    //Serial.println ("Recived Nichrome Burn Command");
    digitalWrite (NichromePin, HIGH); 
    break;
    
    default:
    1+1; //Hope that's Tough enough?
    break;
    }
}


void Update_Sensor_Data(){
  // adafruit_function (&Tele_data[14], &Tele_data[13], &Tele_data[15], &Tele_data[16], &Tele_data[0], &Tele_data[2]); //Update Adafruit 10 DOF IMU data
   geta_time (&a_time, &a_date); //Update all time variable
   
}

   //Ask slave to take snapshot and store in SD fro Master retrival
void TakeSnapShot(){
    Wire.beginTransmission(19);
    byte toSlave_msg = 10;
    Wire.write(toSlave_msg);
    Wire.endTransmission(); 
    soft_RST();     
}

void Setup_RSTpin(){
digitalWrite (RstPin, HIGH);
pinMode(RstPin, INPUT);
}

void soft_RST(){
delay (200);
pinMode(RstPin, OUTPUT);
digitalWrite (RstPin, LOW);
}





