#include <Adafruit_VC0706.h>
#include <SPI.h>
#include <SD.h>

// comment out this line if using Arduino V23 or earlier
#include <SoftwareSerial.h>         
#define chipSelect 5

// Using SoftwareSerial (Arduino 1.0+) or NewSoftSerial (Arduino 0023 & prior):
#if ARDUINO >= 100
// On Uno: camera TX connected to pin 3, camera RX to pin 4:
SoftwareSerial cameraconnection = SoftwareSerial(3, 4);
// On Mega: camera TX connected to pin 67 (A15), camera RX to pin 3:
//SoftwareSerial cameraconnection = SoftwareSerial(67, 3);
#else
NewSoftSerial cameraconnection = NewSoftSerial(3, 4);
#endif

Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

// Using hardware serial on Mega: camera TX conn. to RX1,
// camera RX to TX1, no SoftwareSerial object is required:
//Adafruit_VC0706 cam = Adafruit_VC0706(&Serial1);
int RSTpin = 8;
int spin = 9;
int MasterCanUseSD = 7;


void setup() {

  // When using hardware SPI, the SS pin MUST be set to an
  // output (even if not connected or used).  If left as a
  // floating input w/SPI on, this can cause lockuppage.
#if !defined(SOFTWARE_SPI)
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  if(chipSelect != 53) pinMode(53, OUTPUT); // SS on Mega
#else
  if(chipSelect != 10) pinMode(10, OUTPUT); // SS on Uno, etc.
#endif
#endif

  Serial.begin(9600);
  Serial.println ("Begin");

  //Setup Reset pin
    digitalWrite(RSTpin, HIGH);
    pinMode (RSTpin, OUTPUT);
    digitalWrite(RSTpin, HIGH);

  //Tell MAster that slave restarted
  Serial.print("Talking to Master");
  
    //Initialize SD;
  pinMode(5, INPUT);pinMode(11, INPUT);
  pinMode(12, INPUT);pinMode(13, INPUT);

  //Initialize spapsot triger pin
  pinMode (spin, INPUT);
  Serial.println ("Waiting...");

  //Initialize master comms
  pinMode(MasterCanUseSD, OUTPUT); digitalWrite(MasterCanUseSD,HIGH);
  
  delay (5000);
}

void loop() {
  digitalWrite(MasterCanUseSD,HIGH);
  if (digitalRead(spin) == HIGH || Serial.available()){
    digitalWrite(MasterCanUseSD,LOW);
    Serial.println("TAKING PIC");
    Serial.println (Serial.readString());
    snapper ();
    delay(500);
    digitalWrite(RSTpin, LOW);
    }
  delay(500);
  
}









