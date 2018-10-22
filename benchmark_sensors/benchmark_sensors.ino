/*
   @date: 09.28.2018
   @version: 01
   @course: ECE 3400, Fall 2018
   @team: 21
   Benchmark Sensors
*/
#include "mic.h"
#include "ir_hat.h"
#include "ir_rangefinder.h"
#include "move_commands.h"
#include "nordic_rf.h"
#include "maze.h"

#include <Servo.h>
#include <RF24.h>

Servo servo_R;
Servo servo_L;

RF24 radio(9, 10);

Maze maze();

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  //servo_R.attach(3);
  //servo_L.attach(5);
  RF24_tx_setup(radio);
  //RF24_rx_setup(radio);
}

void loop() {
  //byte received;
  
  //received = RF24_rx_read(radio);
  //Serial.println(received);
}
