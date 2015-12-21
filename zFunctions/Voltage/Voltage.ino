#define voltageMeasurementPin A0

void setup (){
  Serial.begin(9600);  
}


void loop(){
  float v;
  Serial.print("Voltage Bus is: ");
  readVoltage(&v);
  Serial.println(v);
  delay (1000);
  }

void readVoltage(float* voltage){
  //Standard way
  //*voltage =  analogRead(voltageMeasurementPin) * 2.0 * (5 / 1023.0); 
  //Fine Tuned (More Accurate than Standard)
  *voltage =  analogRead(voltageMeasurementPin) * 2.0 * (4.62 / 1023.0);
}













