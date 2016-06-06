void TransmitSegment_OLD(){
  //Check to see if new picture has been taken
  if (lastPicNum != latestPicNum){
    //resets segment count
    segment = 1;
  }

  //Selects file to transmit
  strcpy(readName, fileName);
  readName[0] = '0' + latestPicNum / 10;
  readName[1] = '0' + latestPicNum % 10;
  readName[3] = '0' + segment / 10;
  readName[4] = '0' + segment % 10;

  //Opens File Segment
  File readFile;
  readFile = SD.open(readName);

  //if the file segment exists
  if (readFile){
    //Prints the current segment and the number of segments
    Serial.print(segment, DEC);
    Serial.print(",");
    Serial.print(numSegments, DEC);
    Serial.print(",");
    //while there is data remaining in segment
    while ( readFile.available() ){
      //writes byte of data to serial in HEX
      Serial.print(readFile.read(), HEX);
    }
    Serial.print("\n");
    //closes the file
    readFile.close();
  }

  //iterates/loops the segment number
  if (segment == numSegments){
    segment = 1;
  } else {
    segment++;
  }
  
}

