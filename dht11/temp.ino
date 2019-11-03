#include <dht.h>

const int data_pin = 8;

dht DHT;

void setup(){
	Serial.begin(9600);
}

void loop(){
	DHT.read11(data_pin);
	Serial.print("Temperature");
	Serial.println(DHT.temperature);
	Serial.print("Humidity");
	Serial.println(DHT.humidity);
	
}