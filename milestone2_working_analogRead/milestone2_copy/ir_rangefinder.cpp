<<<<<<< HEAD:Lab2/milestone2/milestone2/ir_rangefinder.cpp
#define VAL_6_INCH 100
#define VAL_3_INCH 200

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
=======
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
  Serial.print("IR RANGE FINDER VALUE = ");
  Serial.print(val);
  Serial.println(" ");
  if(val > (VAL_2_INCH - TOLERANCE))
    return true;
  else
    return false;
}
>>>>>>> b02d3f38c8e9e3c82baa50f78e912414c552d5a4:milestone2_working_analogRead/milestone2_copy/ir_rangefinder.cpp
