void SetFileName() {

  //Create an image with the name IMAGExx_xx.JPG
  //Avoids Overwriting Multiple Images
  

  
  strcpy(fileName, "00_00.JPG");
  for (int i = 1; i < 200; i++) {
    fileName[0] = '0' + i / 10; //'0' + i is an efficent typecast from int to char
    fileName[1] = '0' + i % 10;
    Serial.println(fileName);
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(fileName)) {
      Serial.println("DNE");
      char picNum[2];
      picNum[0] = fileName[0];
      picNum[1] = fileName[1];
      latestPicNum = atoi(picNum);
      break;
    }
  }

}

