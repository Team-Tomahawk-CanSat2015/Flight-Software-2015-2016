//BMP 18-0 Global variables
SFE_BMP180 BMP180;
double baselineAltitude;

//BMP 180 initialization function
void initialize_BMP180 (){
  //Initialize BMP 180
  if (BMP180.begin()){
    //Serial.println("BMP180 Initialized success");
  }
  else{
    //Serial.println("BMP180 init fail (disconnected?)\n");
  }
  
  baselineAltitude = getPressure(); //Get Baseline pressure for Altitude caliberation
  //Serial.print("baseline pressure: ");Serial.print(baseline);Serial.println(" mb");
}

//BMP 180 get pressure function
double T;
double getPressure(){
char status;
double P,p0,a;
  
  status = BMP180.startTemperature();
  if (status != 0){
    delay(status);
    status = BMP180.getTemperature(T);
    if (status != 0){
      status = BMP180.startPressure(3);
      if (status != 0){
        delay(status);
        status = BMP180.getPressure(P,T);
        if (status != 0){
          return(P);
        }
        else 
        1+1;
        //Serial.println("error retrieving pressure measurement\n");
      }
      else 
      1+1;
      //Serial.println("error starting pressure measurement\n");
    }
    else 
    1+1;
    //Serial.println("error retrieving temperature measurement\n");
  }
  else
  1+1; 
  //Serial.println("error starting temperature measurement\n");
  return(990);
}



void UpdateBMP180(){
  SensorData[1] = 100.00*(float)getPressure(); //Update pressure;
  //SensorData[0] = (float)BMP180.altitude(SensorData[1]/100,baselineAltitude); //Update Reltive Altitude
  SensorData[3] = (float)T;//Temp

  //
  
  //SensorData[0] = (pow((SensorData[1]/101300.0), 1.0/5.2561) -1.0)/(-6.8735*pow(10.0,-6.0));
  //SensorData[0]  = 9;

  
}






