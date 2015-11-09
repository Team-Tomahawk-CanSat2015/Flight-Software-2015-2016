
void setup() {
    Serial.begin(9600);
}
 
void loop(){
    float pressure = readPressure(A1);
    float millibars = pressure/100;
    float airspeed= sqrt ((2.0 * pressure)/1.225); 
    
     
 
    Serial.println();
    Serial.print("Pressure = ");
    Serial.print(pressure);
    Serial.println(" pascals");
    Serial.print("Pressure = ");
    Serial.print(millibars);
    Serial.println(" millibars");
    Serial.print("Airspeed=");
    Serial.print(airspeed);
    Serial.println("meters per second");
    delay(1000);
}
 
//Reads pressure from the given A1.

float readPressure(int A1){
    int pressureValue = analogRead(A1);
    float pressure=((pressureValue/1023.0)+0.5);
    // Returns a value in Pascals
    return pressure;
    //int airspeed=
    //float airspeed = sqrt ( (2.0 * pressureValue)/1.225);
    //return airspeed;
    
 //Serial.println(airspeed);

}
