SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

void setupCAM() {  
  if (!cam.begin()) {Serial.println("Error Camera");}
  cam.setImageSize(VC0706_640x480);
}

void takepic (char* pictureName){
    if (!cam.takePicture())
      Serial.println("Failed to snap!");
      
     //Amro, What exactly is this loop for? 
    // Create an image with the name pictureName
    for (int i = 0; i < 100; i++) {
      // create if does not exist, do not open existing, write, sync after write
       if (!SD.exists(pictureName)) {
        break;
      }
    }
    
    // open file for writing
    File imgFile = SD.open(pictureName, FILE_WRITE);

    // Get the size of the image (frame) taken
    uint16_t jpglen = cam.frameLength();

    // black magic
    int32_t time = millis();
    pinMode(8, OUTPUT);
    while (jpglen > 0) {
      // read 64 bytes at a time;
      uint8_t *buffer;
      uint8_t bytesToRead = min(64, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
      buffer = cam.readPicture(bytesToRead);
      imgFile.write(buffer, bytesToRead);
      jpglen -= bytesToRead;
    }
    
    imgFile.close();
    time = millis() - time;
    Serial.println(time); 
  }
