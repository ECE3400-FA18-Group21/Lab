/*
   @date: 11.02.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Lab 4 - Arduino & Camera Team 
*/
#include <Arduino.h>
#include "FPGA_to_Arduino.h"

void one_bit_color_detection(int value) {
  if(value) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("------------------------------------------------------------------");
    Serial.println("                           RED DETECTED                           ");
    Serial.println("------------------------------------------------------------------");
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("------------------------------------------------------------------");
    Serial.println("                          BLUE DETECTED                           ");
    Serial.println("------------------------------------------------------------------");
  }
}

void two_bit_communication(int bit1, int bit0) {
  if(bit0) {
    Serial.println("RED TREASURE DETECTED");
  }
  else if(bit1) {
    Serial.println("BLUE TREASURE DETECTED"); 
  }
  else {
    Serial.println("NO TREASURE DETECTED");
  }
}

void parallel_communication(int bit2, int bit1, int bit0) {
  //Command Type = 000
  if (bit2==0 && bit1==0 && bit0==0) {
    Serial.println("No treasure detected");
  }
  //Command Type = 001
  else if(bit2==0 && bit1==0 && bit0==1) {
    Serial.println("Red Triangle Treasure detected");
  }
  //Command Type = 010
  else if(bit2==0 && bit1==1 && bit0==0) {
    Serial.println("Blue Triangle Treasure detected");
  }
  //Command Type = 011
  else if(bit2==0 && bit1==1 && bit0==1) {
    Serial.println("Red Square Treasure detected");
  }
  //Command Type = 100
  else if(bit2==1 && bit1==0 && bit0==0) {
    Serial.println("Blue Square Treasure detected");
  }
  //Command Type = 101
  else if(bit2==1 && bit1==0 && bit0==1) {
    Serial.println("Red Circle Treasure detected");
  }
  //Command Type = 110
  else if(bit2==1 && bit1==1 && bit0==0) {
    Serial.println("Blue Circle Treasure detected");
  }
  else
    Serial.println("Invalid command");
}
