#include <Wire.h>
#include <Servo.h>

Servo cam_Servo;

float datafromMaster[1], datatoMaster[1];
int MasterI2Caddress = 11, SlaveI2Caddress = 12;
int cam_servopos;

void setup() {
  cam_Servo.attach (6);
  Wire.begin(SlaveI2Caddress);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  Serial.begin(9600);           // start serial for output
}

void loop() {
  //Loop for Slave is needed.
  //Slave is only Active when Master Requests of it.
}

void receiveEvent(int unnessesary_int) {
  int i=0;
  while (0 < Wire.available()) { 
    datafromMaster[i] = Wire.read(); 
    ++i;
  } 
  
  Serial.println(""); Serial.print ("From Master I2C: ");
  for (int j=0; j<i; ++j){
  Serial.print (datafromMaster[j]); Serial.print (", ");
  }

  cam_Servo.write (datafromMaster[0]);
}

void requestEvent() {
  int d = 33;
  Wire.write(d); // respond with # of bytes asked by master
}

