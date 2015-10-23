//Purpose: This function is used to obyain voltage from the voltageMeasurementPin.
//An 82 ohm resistor is used as the voltage divider.
void readBUSVoltage(float* voltage) 
{
  *voltage =  analogRead(voltageMeasurementPin) * 2.0 * (5.0 / 1023.0);
}
