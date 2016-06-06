/*************************
 * FUNCTIONS For TMP36 and PITOT SENSOR*
 * **********************/
void UpdatePitotSensor(){
/*
//int DeltaP_Voltage = map (analogRead(A1), 0, 1023, 0, 5); //Gets differental pressure voltage
float DeltaP_Voltage = ((float)analogRead(PitotPin)/1023.00) * 5.00;
//float DeltaP_kpa = (DeltaP_Voltage+0.5) /(0.2*5); // Returns a value in Kpa
float DeltaP_kpa = (DeltaP_Voltage-(1.0)-(0.025*3.92))/(1.0) ;
float DeltaP_bars = DeltaP_kpa * 0.01; //Get value in milibars
SensorData[2] = sqrt ((2.0 * (abs(DeltaP_kpa)*1000))/1.1792);
*/
float x = (float)abs(analogRead(PitotPin) - 350.00);
if (x<2){SensorData[0]=0; return;}
float p1=-0.0046591; float p2=0.666;
float p3=3.1511;
SensorData[2]= p1*pow(x,2) +p2*x +p3;
//SensorData[2] = x;
}

