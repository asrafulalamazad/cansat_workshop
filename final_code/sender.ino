#include "DHT.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

  
#define DHTTYPE DHT11
#define OUTPUT_READABLE_ACCELGYRO
#define OUTPUT_READABLE_ACCELGYRO



// PIN NUMBER
#define DHTPIN 2  
#define LED_PIN 13 
int led1 = 5;
int led2 = 6; 
int RXPin = 4;
int TXPin = 3;
int buzzer = A2;
const int chipSelect = 4;
RF24 radio(9, 8); 



// Object creating
MPU6050 accelgyro;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;
bool blinkState = false;
int GPSBaud = 9600;
int16_t ax, ay, az;
int16_t gx, gy, gz;
SoftwareSerial gpsSerial(RXPin, TXPin);
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
  float readPressure;
};
typedef struct package Package;
Package data;

// Setup function

void setup(){
	Serial.begin(9600);
	dht.begin();
	pinMode(RXPin, INPUT);
	pinMode(TXPin, OUTPUT);
	gpsSerial.begin(9600);
	if (!bmp.begin()) {
	    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
	    while (1);
	}

	radio.begin();
	radio.openWritingPipe(address);
	radio.stopListening();

	bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,      
                  Adafruit_BMP280::SAMPLING_X2,     
                  Adafruit_BMP280::SAMPLING_X16, 
                  Adafruit_BMP280::FILTER_X16,       
                  Adafruit_BMP280::STANDBY_MS_500); 

	accelgyro.initialize();
	pinMode(LED_PIN, OUTPUT);
	pinMode(buzzer, OUTPUT);
}


void loop(){

	read_Sendor_data(); 
	blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    radio.write(&data, sizeof(data));

}

void read_Sendor_data(){
	data.humidity = dht.readHumidity(); 
	data.temperature = dht.readTemperature();
	data.pressure =bmp.readPressure();
	data.altitude =bmp.readAltitude(1009.00);

	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	#ifdef OUTPUT_READABLE_ACCELGYRO
	    data.ax = ax;
	    data.ay = ay;
	    data.az = az;
	    data.gx = gx;
	    data.gy = gy;
	    data.gz = gz;
	#endif

	#ifdef OUTPUT_BINARY_ACCELGYRO
	        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
	        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
	        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
	        Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
	        Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
	        Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
	#endif
 
}