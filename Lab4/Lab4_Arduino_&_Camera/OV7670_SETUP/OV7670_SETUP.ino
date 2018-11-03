/*
   @date: 11.01.2018
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
int FPGA_comms_pin2 = 6;
int FPGA_comms_pin3 = 7;

void setup(){
  Serial.begin(9600);
  pinMode(FPGA_comms_pin1, INPUT);
  pinMode(FPGA_comms_pin2, INPUT);
  pinMode(FPGA_comms_pin3, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //setup_camera();
}
void loop(){
  
  //Sends 1 bit [0 (blue) or 1 (red)] over 1 single wire
  int value = digitalRead(FPGA_comms_pin1);
  one_bit_color_detection(value);


  //Sends 3 bits over 3 single wires
  int bit0 = digitalRead(FPGA_comms_pin1);
  int bit1 = digitalRead(FPGA_comms_pin2);
  int bit2 = digitalRead(FPGA_comms_pin2);
  parallel_communication(bit2, bit1, bit0);
}
