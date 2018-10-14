#define VAL_5_INCH 190
#define VAL_2_INCH 370

#include "ir_rangefinder.h"
#include <Arduino.h>

int read_range_sensor(int pin){
  return analogRead(pin);
}

bool detect_wall_5in(int pin){
  int val = read_range_sensor(pin);
  if(val > VAL_5_INCH)
    return true;
  else
    return false;
}

bool detect_wall_2in(int pin){
  int val = read_range_sensor(pin);
  Serial.print("IR RANGE FINDER VALUE = ");
  Serial.print(val);
  Serial.println(" ");
  if(val > VAL_2_INCH)
    return true;
  else
    return false;
}
