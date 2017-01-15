//M-Fly Flight Control Software

// NOTE: Servos do work, but interrupt input from
// receiver frequently drops, causing servos to jitter
// uncontrollably

// NOTE: Altitude Measurement in Meters

#include <Adafruit_Sensor.h>

#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>//Accel/Magneto sensor library
#include <Adafruit_L3GD20_U.h>//Gyroscope library
#include <SFE_BMP180.h>

#include "Data.h"
#include <Wire.h>

Data *data;

// Hertz Rate for Data Collection
const int hertz = 50;
const int delayTime = 1000 / hertz;

long lastLoopTime = 0;

void setup() {
  // Initiate Serial Port
  Serial.begin(115200);

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
  // M-Fly,TIME,ALTITUDE,GYROX,GYROY,GYROZ,ACCELX,ACCELY,ACCELZ,

  Serial.print("M-Fly,");
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

