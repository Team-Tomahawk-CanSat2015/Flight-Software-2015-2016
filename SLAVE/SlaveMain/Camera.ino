SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

/****************************************************************************/
void takepicture (char* pictureName){
  if (!SD.begin(10)){Serial.println("SD Error");}
  if (!cam.begin()) {Serial.println("Error Camera");}
  Serial.println ("Camera Activated");
  char *reply = cam.getVersion();
  cam.setImageSize(VC0706_640x480);
  delay(100);
  
    if (!cam.takePicture())
      Serial.println("Failed to snap!");

   // Create an image with the name IMAGExx.JPG
  char filename[13];
  strcpy(filename, "IMAGE00.JPG");
  for (int i = 0; i < 100; i++) {
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (SD.exists(filename) == false) {
      lastImgNum = i;
      Serial.println (filename);
      i = 101;
    }
  }
       
    File imgFile = SD.open(filename, FILE_WRITE);
    if (!imgFile){Serial.println("Camera File Error");}
     
    else {
    uint16_t jpglen = cam.frameLength();

    // black magic
    int32_t time = millis();
    int wCount = 0;
    while (jpglen > 0) {
    uint8_t *buffer;
    uint8_t bytesToRead = min(64, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
    buffer = cam.readPicture(bytesToRead);
    imgFile.write(buffer, bytesToRead);
    if(++wCount >= 64) { // Every 2K, give a little feedback so it doesn't appear locked up
      Serial.print("...");
      wCount = 0;
    }
    jpglen -= bytesToRead;
  }
    
    imgFile.close();
    time = millis() - time;
    Serial.print("Total Time for Pic transfer = ");Serial.println(time); 
     }
  }

/*void SendPictureonSerial(){
  int sec_count=0;
  char filename[13];
  strcpy(filename, "IMAGE00.JPG");
    int i = lastImgNum;
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    if (! SD.exists(filename)) {
      Serial.println ("Picture File Not Alive-00");
      return;
    }
    myFile = SD.open(filename);
    if (myFile){
      // read from the file until there's nothing else in it:
    while (myFile.available() && ++sec_count < 10 *1000) {
      Serial.write(myFile.read());
    }
      }
    else{
      Serial.println ("Picture File Not Alive-01");
      }
    Serial.println("");
    Serial.println("File Serial print Done");
    
    }
*/








  
