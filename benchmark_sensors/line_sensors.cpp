#include "line_sensors.h"

/*
 * Inspired by http://bildr.org/2011/06/qre1113-arduino/
 */

int read_digital_sensor(int pin){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  pinMode(pin, INPUT);
  long time = micros();
  
  while (digitalRead(QRE1113_Pin) == HIGH && micros() – time < 3000){
    int diff = micros() - time; return diff; 
  } 
}
