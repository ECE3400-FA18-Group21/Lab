#include "line_sensors.h"
#include <Arduino.h> 

//Analog read & threshold function
unsigned int * checkSensorsAnalog() {
  static unsigned int sensorValuesAnalog[NUM_SENSORS_ANALOG]; //declare output array
  sensorValuesAnalog[0] = analogRead(0);
  sensorValuesAnalog[1] = analogRead(1);
  sensorValuesAnalog[2] = analogRead(2);
  
  for (unsigned int i = 0; i < NUM_SENSORS_ANALOG; i++) {
    if (sensorValuesAnalog[i] < THRESHOLD_ANALOG)
      sensorValuesAnalog[i] = 0; //sees bright white
    else
      sensorValuesAnalog[i] = 1; //sees dark color (black)
    }
  return sensorValuesAnalog;
}

//Digital read function
int readQD(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  pinMode(pin, INPUT);
  long time = micros();
  while((digitalRead(pin) == HIGH) && (micros()-time<3000));
  int diff = micros() - time;
  if(pin ==3)
  Serial.println(diff);
  return diff;
}
//Digital read threshold function
unsigned int * checkSensorsDigital() {
  static unsigned int sensorValuesDigital[NUM_SENSORS_DIGITAL]; //declare output array
  sensorValuesDigital[0] = readQD(2);
  sensorValuesDigital[1] = readQD(3);
  sensorValuesDigital[2] = readQD(4);
  sensorValuesDigital[3] = readQD(10);
  
  for (unsigned int i = 0; i < NUM_SENSORS_DIGITAL; i++) {
    if (sensorValuesDigital[i] < THRESHOLD_DIGITAL)
      sensorValuesDigital[i] = 0; //sees bright white
    else
      sensorValuesDigital[i] = 1; //sees dark color (black)
    }
  return sensorValuesDigital;
}
