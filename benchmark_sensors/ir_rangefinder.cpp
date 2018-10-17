/*
 * @date: 09.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Benchmark Sensors
 */
#define VAL_6_INCH 140
#define VAL_2_INCH 140
#define TOLERANCE 10

#include "ir_rangefinder.h"
#include <Arduino.h>

int read_range_sensor(int pin){
  return analogRead(pin);
}

bool detect_wall_6in(int pin){
  int val = read_range_sensor(pin);
  if(val < (VAL_6_INCH + TOLERANCE) && val > (VAL_6_INCH - TOLERANCE))
    return true;
  else
    return false;
}

bool detect_wall_2in(int pin){
  int val = read_range_sensor(pin);
  if(val < (VAL_2_INCH + TOLERANCE) && val > (VAL_2_INCH - TOLERANCE))
    return true;
  else
    return false;
}
