/*
 * @date: 10.17.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Used to complete Milestone 2 documentation
 */
#define VAL_6_INCH 100
#define VAL_3_INCH 300
 
#include "ir_rangefinder.h"
#include <Arduino.h>

int read_range_sensor(int pin){
  return analogRead(pin);
}

bool detect_wall_6in(int pin){
  int val = read_range_sensor(pin);
  if(val > VAL_6_INCH)
    return true;
  else
    return false;
}

bool detect_wall_3in(int pin){
  int val = read_range_sensor(pin);
  if(val > VAL_3_INCH)
    return true;
  else
    return false;
}
