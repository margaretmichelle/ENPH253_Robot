#include <Arduino.h>
#include <Constants.h>
#include <Helper.h>

int Helper::getAverageAnalogValue(int analogPin, int numReadings) {
  int sensorValue = 0;
  for (int k = 0; k < numReadings; k++) sensorValue += analogRead(analogPin);
  return sensorValue / numReadings;
}