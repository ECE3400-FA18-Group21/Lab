/*
 * @date: 09.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Benchmark Sensors
 */
#include "mic.h"
#include "ir_hat.h"
#include "ir_rangefinder.h"
#include "move_commands.h"

#include <Servo.h>

Servo servo_R;
Servo servo_L;

int counter = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 
  servo_R.attach(3);
  servo_L.attach(5);
  //fft_setup_mic();
}

void loop() {
  moveForward(servo_R, servo_L);
  Serial.println(read_range_sensor(3));
}
