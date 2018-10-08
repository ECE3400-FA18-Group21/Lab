#define VAL_6_INCH 170
#define VAL_2_INCH 220
#define TOLERANCE 30

#include "ir_rangefinder.h"
#include <Arduino.h>

int read_range_sensor(int pin){
  return analogRead(pin);
}

bool detect_wall_6in(int pin){
  int val = read_range_sensor(pin);
  if(val > (VAL_6_INCH - TOLERANCE))
    return true;
  else
    return false;
}

bool detect_wall_2in(int pin){
  int val = read_range_sensor(pin);
  if(val > (VAL_2_INCH - TOLERANCE))
    return true;
  else
    return false;
}
