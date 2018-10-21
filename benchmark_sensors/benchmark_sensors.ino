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

RF24 radio(7, 8);

Maze maze = Maze();

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  servo_R.attach(3);
  servo_L.attach(5);
//  RF24_tx_setup(radio);
  RF24_rx_setup(radio);
}

void loop() {
  byte received;
  maze.printInfo();
  maze.advanceIntersection(false, false, true);
  maze.printInfo();
  maze.turnLeft();
  maze.advanceIntersection(true, true, true);
  maze.printInfo();
  maze.turnLeft();
  maze.advanceIntersection(true, true, true);
  maze.printInfo();
  maze.turnLeft();
  maze.advanceIntersection(true, true, true);
  maze.printInfo();
  while(true);
//  byte to_send = 5;
//  RF24_tx_send(radio, &to_send);
//received = RF24_rx_read(radio);
//  Serial.println(received);
}
