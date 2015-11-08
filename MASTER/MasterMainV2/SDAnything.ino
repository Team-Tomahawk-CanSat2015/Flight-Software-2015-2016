void SavetoSD(String datatosave, char* filetosave){
 if (!SD.begin(10)){Serial.println("SD Error");}
  else{
  Serial.println ("--SD active--");
    myFile = SD.open(filetosave, FILE_WRITE);
    if (myFile){
      myFile.println(datatosave);
      myFile.close();
      Serial.println("--Master SD write Success!!--");  
      }
      else {Serial.println ("-File Error-");}
  }
  SD.end();
}

