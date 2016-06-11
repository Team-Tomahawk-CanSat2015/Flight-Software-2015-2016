void SendLatestFileSD (){
  //Serial.println("ss");
  char fileName[16];
  File myFile;

   if (!SD.begin(8)) {
    //Serial.println("Card failed, or not present");
    return;
  } 
  strcpy(fileName, "00_00.JPG");
  for (int i = 1; i < 200; i++) {
    fileName[0] = '0' + i / 10; //'0' + i is an efficent typecast from int to char
    fileName[1] = '0' + i % 10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(fileName)) {
      fileName[0] = '0' + (i-1) / 10; //'0' + i is an efficent typecast from int to char
      fileName[1] = '0' + (i-1) % 10;
      break;
    }
  }
  myFile = SD.open(fileName);
  if (myFile) {

    // read from the file until there's nothing else in it:
    unsigned long datacount=0;
    while (myFile.available()) {
      if (datacount%2000 == 0){
        if (datacount!=0)Serial.println();
        UpdateTelemetery ();
        UpdateMissionTime();
        SendTelemetery (false);
        SaveTelemetery(); 
        if (datacount==0) Serial.print(fileName);
        }
      Serial.print(myFile.read(), HEX);
      ++datacount;
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    //Serial.println("error opening picyure file");
  }
  
  SD.end();//You need to change your libary to the cansat SD libary to include this function
   pinMode(8, INPUT);for (int i=0;i<=13; ++i){pinMode(i, INPUT);}
  //Serial.println ("END");

  snapedapic = false;

}
