#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>              
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20); //Gyro deceleration

#define NichromeBurnPin 6
const int sizeTdata = 16;
float Tdata[sizeTdata];
bool NichromeActive = false;
int NichromeBurnDuration = 15*2;
int NichromeActiveCount = 0;
/*
 * 0. commandcount
 * 1. Altitude
 * 2. Temp
 * 3. y_alpha 
 * 4. x_alpha
 * 5. z_alpha
 * 6. z_rollrate
 * 7. Xaccel
 * 8. Yaccel
 * 9. Zaccel
 * 10. Xgyro 
 * 11. Ygyro 
 * 12. Zgyro
 * 13. Xmag
 * 14. Ymag
 * 15. Zmag
 * 
 */


bool use_ADA10DOF = true;
void setup() {
  Serial.begin (19200);
  Serial.print("Begin");

  //SetupADA 10DOF
  Wire.begin();
  initilize_Adafruit_10_DOF_Sensors();  //Enable adafruit sensors;
  //gyro.enableAutoRange(true);           //Enable auto range gyro

  //Setup Nichrome burner
  pinMode (NichromeBurnPin, OUTPUT);
  digitalWrite (NichromeBurnPin, LOW);

}

void loop() {
  delay(500);
  if (Serial.available()){
    String RadioRecieve = Serial.readString();
    if (RadioRecieve.indexOf("%") != -1){//Nichrome burn Command recoeved
     NichromeBurnBaBBY();
    }
    Serial.println(RadioRecieve);
    
    
    }

  
  ++NichromeActiveCount;
  if (use_ADA10DOF == true){
   adafruit_function (&Tdata[3],&Tdata[4],&Tdata[5],&Tdata[6],&Tdata[1],&Tdata[2]);
    Adafunction_IndividualSensors();
  }
  
  if (NichromeActive==true&&NichromeActiveCount>NichromeBurnDuration){NichromeStopBaBBY();}
  sendTele();
  
 

}




void sendTele(){
  Serial.print ("6643,");
  Serial.print (millis()/1000); Serial.print (",");
   for (int i=0;i<sizeTdata;++i){
    Serial.print (Tdata[i]);
    Serial.print (",");
    }
    Serial.println("");

  
  }
