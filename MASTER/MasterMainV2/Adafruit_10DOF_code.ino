//THIS CODE IS FOR THE ADAFRUIT 10 DOF SENSOR------
//Freedom to ***e the stars!!
sensors_event_t bmp_event;    
  
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(18001);

void initilize_Adafruit_10_DOF_Sensors(){
  if(!bmp.begin())    Serial.println("ERROR Pressure Sensor");
  }
  
void adafruit_function () {//Input Variables are global now!!   
  bmp.getEvent(&bmp_event);
  if (bmp_event.pressure) {
     bmp.getTemperature(&Tele_data[2]); //Temp->Tele_data [2];
     Tele_data[1] = bmp_event.pressure;//pressure->Tele_data[1]
     //float seaLevelPressure = 1013; //units = hpa
     Tele_data[0]=bmp.pressureToAltitude(1013, Tele_data[1], Tele_data[2]); //pressure_alt->Tele_data[0];
    }
  }

