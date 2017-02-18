//M-Fly Datalogger Software
//
// Units:
//  - Altitude Measurement in Meters
//  - Gyroscope Measurment in Rad/Sec
//  - Accelerometer Measurment in Meters/Sec

#include <Adafruit_Sensor.h>

#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>//Accel/Magneto sensor library
#include <Adafruit_L3GD20_U.h>//Gyroscope library
#include <SFE_BMP180.h>

#include "Data.h"
#include <Wire.h>

Data *data;

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
  // Blink LED and Write Data to Serial regularly
  if (millis() - lastLoopTime > delayTime) {
    lastLoopTime = millis();

    data->update();
    writeData();
  }
}

void writeData() {
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

