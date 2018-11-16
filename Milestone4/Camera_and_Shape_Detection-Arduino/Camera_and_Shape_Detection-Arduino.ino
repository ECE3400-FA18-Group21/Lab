/*
   @date: 11.15.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Milestone 4 - color & shape detection
*/

/**NOTE - all values will be read in hexadecimal format. All addresses & write values should also be written in hex**/
#include <Wire.h>
#include <Arduino.h>
#include "camera.h"
#include "FPGA_to_Arduino.h"

int pin5 = 5;
int pin6 = 6; 
int pin7 = 7;
bool testMode = false;

void setup(){
  Serial.begin(9600);
  pinMode(pin5, INPUT);
  pinMode(pin6, INPUT);
  pinMode(pin7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  setup_camera(testMode);
}

void loop(){
  int bit0 = digitalRead(pin5);
  int bit1 = digitalRead(pin6);
  int bit2 = digitalRead(pin7);
  parallel_communication(bit2, bit1, bit0);
}
