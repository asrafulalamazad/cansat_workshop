#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <SPI.h>

Adafruit_BMP280 bmp;

void setup(){
	Serial.begin(9600);
	if(!bmp.begin()){
		Serial.println("Error with BMP sensor");
	}
	bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
					Adafruit_BMP280::SAMPLING_X2,
					Adafruit_BMP280::SAMPLING_X16,
					Adafruit_BMP280::FILTER_X16,
					Adafruit_BMP280::STANDBY_MS_500);
}
void loop(){
	Serial.println(bmp.readAltitude(1009.00));
	delay(100);
}
