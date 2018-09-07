#include "line_sensors.h"

unsigned int * checkSensors() {
  static unsigned int sensorValues[NUM_SENSORS]; //declare output array
  sensorValues[0] = analogRead(A0);
  sensorValues[1] = analogRead(A1);
  sensorValues[2] = analogRead(A2);
  
  for (unsigned int i = 0; i < NUM_SENSORS; i++) {
    if (sensorValues[i] < THRESHOLD)
      sensorValues[i] = 0; //Sees Bright Line
    else
      sensorValues[i] = 1; //Sees Dark Background
    }
  return sensorValues;
}
