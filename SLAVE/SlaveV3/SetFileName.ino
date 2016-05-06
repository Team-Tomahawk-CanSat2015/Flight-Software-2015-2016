void SetFileName() {

  //Create an image with the name IMAGExx_xx.JPG
  //Avoids Overwriting Multiple Images
  strcpy(fileName, "IMAGE00_00.JPG");
  for (int i = 0; i < 200; i++) {
    fileName[5] = '0' + i / 10; //'0' + i is an efficent typecast from int to char
    fileName[6] = '0' + i % 10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(fileName)) {
      char picNum[2];
      picNum[0] = fileName[5];
      picNum[1] = fileName[6];
      latestPicNum = atoi(picNum);
      break;
    }
  }

}

