/*
   @date: 11.09.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Lab 4
*/

/**NOTE - all values will be read in hexadecimal format. All addresses & write values should also be written in hex**/
#include <Wire.h>
#include <Arduino.h>
#include "camera.h"
#include "FPGA_to_Arduino.h"


int FPGA_comms_pin1 = 5; 
int valRed=0;
int FPGA_comms_pin2 = 6;
int valBlue=0;
//int FPGA_comms_pin3 = 7;
bool testMode = false;

void setup(){
  Serial.begin(9600);
  pinMode(FPGA_comms_pin1, INPUT);
  pinMode(FPGA_comms_pin2, INPUT);
  //pinMode(FPGA_comms_pin3, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  setup_camera(testMode);
}
void loop(){
  //Sends 1 bit [0 (blue) or 1 (red)] over 1 single wire
  valRed = digitalRead(FPGA_comms_pin1);
  one_bit_color_detection(valRed);
}

void loops(){
  //Sends 2 bits over 2 wires
  valRed = digitalRead(FPGA_comms_pin1);
  valBlue = digitalRead(FPGA_comms_pin2);
  two_bit_communication(valBlue, valRed);

  
  //int bit2 = digitalRead(FPGA_comms_pin2);
  //parallel_communication(bit2, bit1, bit0);
}
