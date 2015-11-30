/*Flight tasks that are important but cannot be really clasified are held in this file*/


//Used to compile string and send string to radio serial
void TransmitandSave_data (byte save){
  String radio = "";
  radio += TeamID; radio += ",";
  radio += packet_count; radio += ",";
  for (int i=0; i<19; ++i){
  radio += Tele_data[i];
  radio += "," ;
  }
  Serial.println (radio);
  if (save == 1 && digitalRead(slaveusingSDPin) == LOW){
  //Extra stuff to save
  radio += a_time; radio += ",";
  radio += a_date; radio += ",";
  SavetoSD(radio, "M.txt");
   }
}

//Returns True if radio recived data from Ground station or serial port
bool getdatafromRadio () {
  if (!Serial.available())
    return false;
    else
    return true;
}

//Either adjusts servo angle on slave or takes a SHOTs
void PerformRadiotask(){
  String recv = Serial.readString();
  
    switch (recv.charAt(0)){
    case '#':{ //#160 to change servo angle
    Serial.println ("--Recived Servo Command!!--");
    recv.remove (0, 1);
    int serv_pos = recv.toInt();
    CamServ.write (serv_pos);
    break;}
    
    case'*':{ //* to take snapshot of camera
    Serial.println ("Recived Camera Command from GCS");
    ++Tele_data[11];//++CMD_count;
    Tele_data[10] = millis (); //CMD_time = millis();//need to change this to mission time
    AsktoTakeSnapShot();
    break;}
    
    case'&':{ //& For instant Nichrome Burn Baby!!!!!!
    //Serial.println ("Recived Nichrome Burn Command");
    digitalWrite (NichromePin, HIGH); 
    break;}
    
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
void AsktoTakeSnapShot(){
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
Serial.flush();
pinMode(RstPin, OUTPUT);
digitalWrite (RstPin, LOW);
}





