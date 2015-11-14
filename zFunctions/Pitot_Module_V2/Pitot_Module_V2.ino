
void setup() {
    Serial.begin(9600);
}
 
void loop(){
  float speed_mps;
  Update_PitotSpeed(&speed_mps);
  delay (1000);
}

float Update_PitotSpeed(float *Pitotspeed_mps){
    //int DeltaP_Voltage = map (analogRead(A1), 0, 1023, 0, 5); //Gets differental pressure voltage
    float DeltaP_Voltage = ((float)analogRead(A1)/1023.00) * 5.00;
    //float DeltaP_kpa = (DeltaP_Voltage+0.5) /(0.2*5); // Returns a value in Kpa
    float DeltaP_kpa = (DeltaP_Voltage-(1.0)-(0.025*3.92))/(1.0) ;
    float DeltaP_bars = DeltaP_kpa * 0.01; //Get value in milibars
    *Pitotspeed_mps = sqrt ((2.0 * (DeltaP_kpa*1000))/1.1792);
    
    Serial.print("Delta_Pressure(volts)= ");  Serial.println(DeltaP_Voltage);
    Serial.print("Delta_Pressure(Kpa)= ");    Serial.println(DeltaP_kpa);
    Serial.print("Delta_Pressure(bars)= ");   Serial.println(DeltaP_bars); //1Kpa = 0.01bars
    Serial.print("Airspeed(m/s)= ");          Serial.println(*Pitotspeed_mps);
}
