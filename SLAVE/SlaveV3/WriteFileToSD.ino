void WriteFileToSD() {
  //Open the file for writing
 

//if (!SD.begin(10)) {
//    Serial.println("Card failed, or not present");
//    // don't do anything more:
//    return;
//  }  

File    myFile = SD.open("test.txt", FILE_WRITE);
File otherFile = SD.open("asd.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  // Get the size of the image (frame) taken
  uint32_t jpglen = cam.frameLength();
  transLength_1 = jpglen;

  //Determine Number of 1600 byte files (which is 25 * 64 bytes) to subdivide image into.
  //The larger this file is, the shorter the total transmission time as ther will be less packets
  //Data is sent to the ground at 2400 bytes per sec
  // This packet size will take ~~0.667 sec to transmit. This leaves time for telemertry to be sent

  int imgPacketCount = jpglen / imgPacketSize + 1;
  //Sets a global variable for transmitting
  numSegments = imgPacketCount;

  
    File imgFile = SD.open(fileName, FILE_WRITE);
    Serial.println(fileName);
  
  //Loops through each file segment
  for ( int i = 1 ; i <= imgPacketCount ; i++ ) {

    //Set File Segment Name
      //fileName[3] = '0' + i / 10;// '0' + i is an efficient typecast from int to char
      //fileName[4] = '0' + i % 10;

    //Creates new file segment
    
  
    //Fills each segment with data
    for (int a = 0 ; a < min(jpglen / 32 + 1, imgPacketSize / 32) ; a++) {
      //read 64 bytes at a time;
      //Serial.print(a, DEC);
      //Serial.println(min(jpglen / 32 + 1, imgPacketSize / 32), DEC);
      uint8_t *buffer;
      
      //If there are less than 64 bytes remaining in the image it reads that many bytes
      uint8_t bytesToRead = min(64, jpglen);
      buffer = cam.readPicture(bytesToRead);
      //Serial.println((int) *buffer, HEX);
      imgFile.write(buffer, bytesToRead);
      //Serial.write(buffer, bytesToRead);
    }
    
    //Subtracts written data from image length
    //jpglen represents the remaining bytes to read
    jpglen -= imgPacketSize;
    
    // closes the image
    
    Serial.print("Packet ");
    Serial.print(i, DEC);
    Serial.print(" of ");
    Serial.println(numSegments, DEC);
  }
  imgFile.close();
  Serial.println("File Closed");
  //Allows the Master board to use the SD card
}

