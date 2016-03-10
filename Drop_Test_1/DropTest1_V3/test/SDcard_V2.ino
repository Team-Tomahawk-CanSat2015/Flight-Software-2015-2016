void SavetoSD(String datatosave) {
  myFile = SD.open("Data1.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(datatosave);
    myFile.close();
  } 
}

void magicSD_save(){
 //NEVER TO BE TOUCHED,WERID THINGS ARE BOUND TO HAPPEN
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(temp);
    dataFile.close();
    // print to the serial port too:
    Serial.println(temp);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
