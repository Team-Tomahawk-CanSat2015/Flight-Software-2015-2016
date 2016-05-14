//void setup(){} 

//void loop(){Buzzer();}

void Buzzer(){
  tone (BuzzerPin, 262);
  delay (3000);
  noTone (BuzzerPin);
  delay (3000);
}

void Buzzer_feedback(){
  tone (BuzzerPin, 262);
  delay (3000);
  noTone (BuzzerPin);
  delay (1000);
}
