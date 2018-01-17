//M-Fly Datalogger Software
//
// Units:
//  - Altitude Measurement in Meters
//  - Gyroscope Measurment in Rad/Sec
//  - Accelerometer Measurment in Meters/Sec

#include <XBee.h>
#include <stdlib.h>

#include <Adafruit_Sensor.h>

#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>//Accel/Magneto sensor library
#include <Adafruit_L3GD20_U.h>//Gyroscope library
#include <SFE_BMP180.h>

#include "Data.h"
#include <Wire.h>

//Initialize our data object
Data *data = 0;

//Initialize our xbee
const HardwareSerial *xbeeSerial = &Serial1;

// Hertz Rate for Data Collection
const int hertz = 10;
const int delayTime = 1000 / hertz;

long lastLoopTime = 0;

void setup() {
  // Initiate Serial Port
  Serial.begin(9600);

  // Create Data class instance
  data = new Data();
  data->update();
}

void loop() {
  // Loop at a certain frequency
  if (millis() - lastLoopTime > delayTime) {
    lastLoopTime = millis();

    data->update();
    printData();
  }
}

//prints information to serial monitor
void printData() {
  // MILLIS,ALTITUDE,GYROX,GYROY,GYROZ,ACCELX,ACCELY,ACCELZ,
  Serial.print(millis());
  Serial.print(',');
  Serial.print(data->getAltitude());
  Serial.print(',');
  Serial.print(data->getGyroX());
  Serial.print(',');
  Serial.print(data->getGyroY());
  Serial.print(',');
  Serial.print(data->getGyroZ());
  Serial.print(',');
  Serial.print(data->getAccelX());
  Serial.print(',');
  Serial.print(data->getAccelY());
  Serial.print(',');
  Serial.println(data->getAccelZ());
}

//Creates A message
void messageA()
{
  // A,MX2,MILLIS,ALT_BARO,ANALOG_PITOT,PRESS,TEMP,DROP_TIME,DROP_ALT

  
}

//Creates B message
void messageB()
{
  // B,MX2,MILLIS,GPS_SYSTEM,LAT,LON,GPS_SPEED,GPS_COURSE,GPS_ALT,GPS_HDOP

}

//Creates C message
void messageC()
{
  // C,MX2,MILLIS,GYROX,GYROY,GYROZ,ACCELX,ACCELY,ACCELZ

}

