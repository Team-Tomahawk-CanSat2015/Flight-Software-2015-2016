void TakePicture(){
  //Takes Picture
  if (! cam.takePicture()) {
    Serial.println("Failed to snap!");
  } else {
    Serial.println("Picture taken!");
  }
}
  

