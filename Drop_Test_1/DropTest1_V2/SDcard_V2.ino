void SavetoSD(String datatosave) {
  myFile = SD.open("Data1.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(datatosave);
    myFile.close();
  }
  
}
