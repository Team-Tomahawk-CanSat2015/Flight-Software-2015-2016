//THIS CODE IS FOR THE ADAFRUIT 10 DOF SENSOR------
  //CHECK BUTTOM FOR FUNCTIONS
  #include <Adafruit_Sensor.h>            
  #include <Adafruit_BMP085_U.h>          
  sensors_event_t bmp_event;   
  
  Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);

  
  
  
  
  //***********************************************************************************************************************************
  //***********************************************************************************************************************************
  //***********************************************************************************************************************************
  //***********************************************************************************************************************************
  //***********************************************************************************************************************************
  //ADD YOUR FUNCTIONS HERE--ADD YOUR FUNCTIONS HERE--ADD YOUR FUNCTIONS HERE
  /*--DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS--*/
  void  initilize_Adafruit_10_DOF_Sensors()
  {
    if(!bmp.begin())
    { Serial.println("ERROR Pressure Sensor");}
  }
  void adafruit_function () //Input Variables are global now!!
  {   
    bmp.getEvent(&bmp_event);
    if (bmp_event.pressure)
    {//float Temp; //Tele_data [2];
     bmp.getTemperature(&Tele_data[2]); //bmp.getTemperature(&Temp);
     //float seaLevelPressure = 1013; //units = hpa
     Tele_data[0]=bmp.pressureToAltitude(1013, bmp_event.pressure, Tele_data[2]); 
     
    }
  }

