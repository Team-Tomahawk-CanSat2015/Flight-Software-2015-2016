void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4,OUTPUT);

}

void loop() {
  digitalWrite(4, LOW);
  Serial.println (digitalRead(3));
  delay (5*1000);

  digitalWrite(4, HIGH);
  Serial.println (digitalRead(3));
  delay (5*1000);
  

}
