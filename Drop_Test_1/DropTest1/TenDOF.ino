
/*void callDOF(struct dofDataUnit* unit) {
  adafruit_function (&unit->y_alpha, &unit->x_alpha, &unit->z_alpha, &unit->z_rollrate, &unit->Altitude, &unit->Temperature, &unit->Pressure);
}*/


void  initilize_Adafruit_10_DOF_Sensors()
{
  accel.begin();
  mag.begin();
  bmp.begin();
  gyro.begin();

}
void adafruit_function (float *y_alpha, float *x_alpha, float *z_alpha, float *z_rollrate, float *Altitude, float *Temperature, float *Pressure)
{
  sensors_event_t accel_event;        sensors_event_t mag_event;       sensors_event_t gyro_event;          sensors_event_t bmp_event;
  sensors_vec_t   orientation;
  accel.getEvent(&accel_event);                                        gyro.getEvent(&gyro_event);

  if (dof.accelGetOrientation(&accel_event, &orientation))
  { /* 'orientation' should have valid .roll and .pitch fields *///Serial.print(F("Roll: "));  Serial.print(orientation.roll);Serial.print(orientation.pitch);
    *y_alpha = orientation.pitch;
    *x_alpha = orientation.roll;
  }
  mag.getEvent(&mag_event);
  if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
  {
    *z_alpha = orientation.heading;
  }
  bmp.getEvent(&bmp_event);
  if (bmp_event.pressure)
  { float Temp;
    bmp.getTemperature(&Temp);
    *Temperature = Temp;
    *Altitude = bmp.pressureToAltitude(seaLevelPressure, bmp_event.pressure, Temp);
    *Pressure = bmp_event.pressure;
    //z_rollrate = gyro_event.gyro.z; //rad/s
    *z_rollrate = (gyro_event.gyro.z) * (180 / 3.142); //deg/s




  }
}

