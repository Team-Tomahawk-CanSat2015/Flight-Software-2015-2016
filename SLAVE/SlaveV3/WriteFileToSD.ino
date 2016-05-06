void WriteFileToSD() {
  //Open the file for writing
  SD.begin(4);//NOT SURE IF 4 IS CORRECT////////////////////////////////////////////////////////////////////////

  // Get the size of the image (frame) taken
  uint32_t jpglen = cam.frameLength();

  //Determine Number of 1600 byte files (which is 25 * 64 bytes) to subdivide image into.
  //The larger this file is, the shorter the total transmission time as ther will be less packets
  //Data is sent to the ground at 2400 bytes per sec
  // This packet size will take ~~0.667 sec to transmit. This leaves time for telemertry to be sent
  int imgPacketSize = 1600;
  int imgPacketCount = jpglen / imgPacketSize + 1;
  //Sets a global variable for transmitting
  numSegments = imgPacketCount;
  
  //Loops through each file segment
  for ( int i = 1 ; i <= imgPacketCount ; i++ ) {

    //Set File Segment Name
      fileName[8] = '0' + i / 10;// '0' + i is an efficient typecast from int to char
      fileName[9] = '0' + i % 10;

    //Creates new file segment
    File imgFile = SD.open(fileName, FILE_WRITE);

    //Fills each segment with data
    for (int a = 0 ; a < min(jpglen / 64 + 1, imgPacketSize / 64) ; a++) {
      // read 64 bytes at a time;
      uint8_t *buffer;
      //If there are less than 64 bytes remaining in the image it reads that many bytes
      uint8_t bytesToRead = min(64, jpglen);
      buffer = cam.readPicture(bytesToRead);
      imgFile.write(buffer, bytesToRead);
    }
    
    //Subtracts written data from image length
    //jpglen represents the remaining bytes to read
    jpglen -= imgPacketSize;
    
    // closes the image
    imgFile.close();
  }

  //Allows the Master board to use the SD card
  SD.end();
}




