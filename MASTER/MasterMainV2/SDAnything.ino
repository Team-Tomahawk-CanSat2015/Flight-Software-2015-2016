/*Save or read SD data functions are kept prisoners of this file
 * NOTE: Modified SD libary is needed
 */

//Used to save data to SD file
void SavetoSD(String datatosave, char* filetosave){
 if (!SD.begin(10)){Serial.println("SD Error");}
  else{
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

