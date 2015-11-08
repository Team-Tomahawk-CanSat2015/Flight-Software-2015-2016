//Purpose: This function is used to obyain voltage from the voltageMeasurementPin.
//An 82 ohm resistor is used as the voltage divider.
void readBUSVoltage() 
{
  voltage =  analogRead(voltageMeasurementPin) * 2.0 * (5.0 / 1023.0);
  Serial.print("Voltage = ");Serial.println(voltage);
  voltage1 = (byte) ((int) (voltage));
  voltagesplit[0] = (byte) ((int) (voltage));
  Serial.print("voltage1 = ");Serial.println(voltage1);
  voltage2 = (byte)( (int)((voltage -(int)voltage) *100));
  voltagesplit[1] = (byte)( (int)((voltage -(int)voltage) *100));
  Serial.print("voltage2 = ");Serial.println(voltage2);
  floattobytes (voltage ,0);
  
  
  
}
