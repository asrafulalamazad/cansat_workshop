//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(9, 8);  

//address through which two modules communicate.
const byte address[6] = "00001";

struct package{
  float temperature;
  float pressure;
  float humidity ;
  float altitude;
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
};
typedef struct package Package;
Package data;

void setup(){
  while (!Serial);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop(){
  
  if (radio.available()){
    radio.read(&data, sizeof(data));
    Serial.print(data.temperature);Serial.print(",");
    Serial.print(data.humidity);Serial.print(",");
    Serial.print(data.pressure);Serial.print(",");
    Serial.print(data.altitude);Serial.print(",");
    Serial.print(data.ax);Serial.print(",");
    Serial.print(data.ay);Serial.print(",");
    Serial.print(data.az);Serial.print(",");
    Serial.print(data.gx);Serial.print(",");
    Serial.print(data.gy);Serial.print(",");
    Serial.print(data.gz);Serial.print(",");
    Serial.println();
  }
}