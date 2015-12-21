
void setup(){} 

void loop(){Buzzer();}

void Buzzer()
{
  tone (5, 262);
  delay (2000);
  noTone (5);
  delay (1000);
}
