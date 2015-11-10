
void setup() {
    Serial.begin(9600);
}
 
void loop(){
  float speed_mps;
  Update_PitotSpeed(&speed_mps);
  delay (1000);
}

float Update_PitotSpeed(float *Pitotspeed_mps){
    int DeltaP_Voltage = map (analogRead(A1), 0, 1023, 0, 5); //Gets differental pressure voltage
    float DeltaP_kpa = (DeltaP_Voltage+0.5) /(0.2*5); // Returns a value in Kpa
    float DeltaP_bars = DeltaP_kpa * 0.01; //Get value in milibars
    *Pitotspeed_mps = sqrt ((2.0 * DeltaP_kpa)/1.225);
    
    Serial.print("Delta_Pressure(volts)= ");  Serial.print(DeltaP_Voltage);
    Serial.print("Delta_Pressure(Kpa)= ");    Serial.print(DeltaP_kpa);
    Serial.print("Delta_Pressure(bars)= ");   Serial.print(DeltaP_bars); //1Kpa = 0.01bars
    Serial.print("Airspeed(m/s)= ");          Serial.println(*Pitotspeed_mps);
}
