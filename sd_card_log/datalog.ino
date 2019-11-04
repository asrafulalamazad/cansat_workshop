#include <SPI.h>
#include <SD.h>
#include <dht.h>

const int chipSelect = 4;
const int data_pin = 8;
dht DHT;


void setup() {
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
}


void loop() {
  DHT.read11(data_pin);
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    Serial.print("Temperature");
    Serial.println(DHT.temperature);
    Serial.print("Humidity");
    Serial.println(DHT.humidity);
    dataFile.print(DHT.temperature);
    dataFile.print(",");
    dataFile.println(DHT.humidity);
    dataFile.close();
  }
 
  else {
    Serial.println("error opening datalog.txt");
  }
}