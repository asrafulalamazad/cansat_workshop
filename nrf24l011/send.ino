#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
//address through which two modules communicate.
const byte address[6] = "00001";

// data package
struct package{
  float humidity;
  float temprature;
};
typedef struct package Package;
Package data;


void setup(){

  while (!Serial);
  Serial.begin(9600);
  radio.begin();
  //set the address
  radio.openReadingPipe(0, address);
  //Set module as receiver
  radio.startListening();
}

void loop(){
  //Read the data if available in buffer
  if (radio.available()){
    radio.read(&data, sizeof(data));
    Serial.println(data.temprature);
    Serial.println(data.humidity);
  }
}
