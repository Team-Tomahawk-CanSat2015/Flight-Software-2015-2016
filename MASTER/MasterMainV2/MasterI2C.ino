void Collect_Slave_Data(){
  Wire.requestFrom(19, 1, true);//request 8 bytes from slave device #19
  //Serial.println ("Asking Slave for data"); 
  if (Wire.available()>0){
  char d = Wire.read();
  Serial.println (d);
  if (d != '0'){ //not equal to 0 is for picture
  //readSend_SDcontents(&d);
  }
  
  }

}
void readSend_SDcontents(char* filetoSend){
  int count=0; 
  myFile = SD.open(strcat (filetoSend, ".txt"));
  if (myFile) {
    while (myFile.available()) {
      Serial.write(myFile.read());
      ++count;
      if (count == myFile.size()/2){
      delay (700);
      Serial.print("\n");
      //Update_Sensor_Data();
      ++packet_count;
      TransmitandSave_data(0); 
      delay (700);
      }
    }
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    //Serial.println("error opening test.txt");
  }


}






