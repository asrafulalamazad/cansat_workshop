#include "I2Cdev.h"
#include "MPU6050.h"
#include <Wire.h>

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO 
#define LED_PIN 13
bool blinkStage = false;



void setup(){
	#if I2CDEV_IMPLEMENTARION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
	#elif I2CDEV_IMPLEMENTARION == I2CDEV_BUILTIN_FASTWIRE
        FastWire::setup(400,true);
    #endif

    Serial.begin(115200);
    accelgyro.initialize();
    pinMode(LED_PIN, OUTPUT);
}


void loop(){
	accelgyro.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);

	#ifdef OUTPUT_READABLE_ACCELGYRO 
	Serial.print("\t");
    Serial.print(ax);Serial.print("\t");
    Serial.print(ay);Serial.print("\t");
    Serial.print(az);Serial.print("\t");
    Serial.print(":::::");

    Serial.print("\t");
    Serial.print(gx);Serial.print("\t");
    Serial.print(gy);Serial.print("\t");
    Serial.print(gz);Serial.print("\t");
    Serial.println("");
    #endif


    #ifdef OUTPUT_BINARY_ACCELGYRO
       Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
       Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
       Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
       Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
       Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
       Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif	

    blinkStage = !blinkStage;
    digitalWrite(LED_PIN, blinkStage);
}