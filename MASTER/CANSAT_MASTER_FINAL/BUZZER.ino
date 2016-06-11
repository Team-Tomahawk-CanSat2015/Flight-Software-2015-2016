void Buzzer(){
  pinMode(BuzzerPin, OUTPUT);
  tone (BuzzerPin, 262);
  delay (3000);
  noTone (BuzzerPin);
  delay (3000);
  pinMode(BuzzerPin, INPUT);
}

void Buzzer_feedback(){
  pinMode(BuzzerPin, OUTPUT);
  tone (BuzzerPin, 262);
  delay (500);
  noTone (BuzzerPin);
  pinMode(BuzzerPin, INPUT);
}

bool isBuzzer = false;
void Buzzer_Command(){
  if (isBuzzer == true){ //If buzzer is on switch off
    noTone (BuzzerPin);
    pinMode(BuzzerPin, INPUT);
    isBuzzer = false;
  }
  else{ //turn buzzer on
    pinMode(BuzzerPin, OUTPUT);
    tone (BuzzerPin, 262);
    isBuzzer = true;
  }
}



