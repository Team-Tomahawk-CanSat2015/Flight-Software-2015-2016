 void NichromeBurnBaBBY (){ //Start A Nichrome burn
  NichromeActiveCount = 0;
  digitalWrite(NichromeBurnPin,HIGH);
  NichromeActive = true;
  ++Tdata[0];
  }

  void NichromeStopBaBBY (){ //Stop A nichrome Bur
  NichromeActiveCount = 0;
  digitalWrite(NichromeBurnPin,LOW);
  NichromeActive = false;
  ++Tdata[0];
  }
