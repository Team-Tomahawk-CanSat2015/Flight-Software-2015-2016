#define voltageMeasurementPin A0

void setup (){
  digitalWrite (2, HIGH);
  pinMode(2, INPUT);
  
  
  Serial.begin(9600);  
  Serial.println ("Start");
}


void loop(){
  Serial.print ("Button State :");
  Serial.println (digitalRead(3));

  if (millis() > 10000){
    pinMode(2, OUTPUT);
    digitalWrite (2, LOW);
  }

  delay (1000);
  
  
}











