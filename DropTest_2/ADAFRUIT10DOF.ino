float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;  /* Update this with the correct SLP for accurate altitude measurements */
  
//float y_alpha, x_alpha, z_alpha, z_rollrate, Altitude, Temperature;
//adafruit_function (&y_alpha, &x_alpha, &z_alpha, &z_rollrate, &Altitude, &Temperature);
  
  
  //***********************************************************************************************************************************
  //***********************************************************************************************************************************
  //***********************************************************************************************************************************
  //***********************************************************************************************************************************
  //***********************************************************************************************************************************
  //ADD YOUR FUNCTIONS HERE--ADD YOUR FUNCTIONS HERE--ADD YOUR FUNCTIONS HERE
  /*--DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS----DO NOT CROSS--*/
  void  initilize_Adafruit_10_DOF_Sensors(){
    if(!accel.begin())  {Serial.println("ERROR Accelerometer"); use_ADA10DOF = false;}
    if(!mag.begin())  {Serial.println("ERROR Magnetometer"); use_ADA10DOF = false;}
    if(!bmp.begin())  {Serial.println("ERROR Pressure"); use_ADA10DOF = false;}
    if(!gyro.begin()) {Serial.println("ERROR Gyroscope"); use_ADA10DOF = false;}
  }
  void adafruit_function (float *y_alpha, float *x_alpha, float *z_alpha, float *z_rollrate, float *Altitude, float *Temperature){
    sensors_event_t accel_event;        
    sensors_event_t mag_event;       
    sensors_event_t gyro_event;          
    sensors_event_t bmp_event;   
    sensors_vec_t   orientation;
    
    accel.getEvent(&accel_event);                                        
    gyro.getEvent(&gyro_event);
    mag.getEvent(&mag_event);
    bmp.getEvent(&bmp_event);
    
    if (dof.fusionGetOrientation(&accel_event,&mag_event,&orientation)){
     *y_alpha = orientation.pitch;
     *x_alpha = orientation.roll;
     *z_alpha =  orientation.heading;
      }

    if (bmp_event.pressure)
    {float Temp;
     bmp.getTemperature(&Temp);
     *Temperature = Temp;
     *Altitude = bmp.pressureToAltitude(seaLevelPressure, bmp_event.pressure, Temp); 
     
     *z_rollrate = (gyro_event.gyro.z) * (180/3.142); //deg/s
     
    }
  }


void Adafunction_IndividualSensors (){
  float Xaccel, Yaccel, Zaccel;
float Xgyro, Ygyro, Zgyro;
float Xmag, Ymag, Zmag;
   sensors_event_t event;
   
   accel.getEvent(&event);
   Xaccel = event.acceleration.x;
   Yaccel = event.acceleration.y;
   Zaccel = event.acceleration.z;

  gyro.getEvent(&event);
  Xgyro = event.gyro.x;
  Ygyro = event.gyro.y;
  Zgyro = event.gyro.z;

    mag.getEvent(&event);
    Xmag = event.magnetic.x;
    Ymag = event.magnetic.y;
    Zmag = event.magnetic.z;

    Tdata[7] = Xaccel;  Tdata[8] = Yaccel;  Tdata[9] = Zaccel;
    Tdata[10] = Xgyro;  Tdata[11] = Ygyro;  Tdata[12] = Zgyro;
    Tdata[13] = Xmag;   Tdata[14] = Ymag;   Tdata[15] = Zmag;
  
  
  }







