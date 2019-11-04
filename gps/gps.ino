#include <SoftwareSerial.h>
 
// choose pins that connect to UBlox Neo 6m
int RXPin = 2;
int TXPin = 3;
 
int GPSBaud = 9600;
SoftwareSerial gpsSerial(RXPin, TXPin);
 
void setup() {
  // put your setup code here, to run once:
  // define pin modes for tx, rx:
  pinMode(RXPin, INPUT);
  pinMode(TXPin, OUTPUT);
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Serial.write("Welcome to the GPS Show");
}
 
void loop() {
  // put your main code here, to run repeatedly:
  while(gpsSerial.available() > 0) {
    Serial.write(gpsSerial.read());
  }
}