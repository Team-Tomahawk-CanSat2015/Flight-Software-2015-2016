/* This file contains functions need to transfer data from 
 *  Master MCU to the Slave MCU via the I2C Bus
 */

//Used to update data array holder for slave processor
void Update_Slave_Data(){
  Wire.requestFrom(Slave_I2C_Adress, Slave_Array_Size, true);
  if (Wire.available()>0){
    for (int i=0; i<Slave_Array_Size; ++i){
      Slave_data[i] = Wire.read();
      }
  }
}






