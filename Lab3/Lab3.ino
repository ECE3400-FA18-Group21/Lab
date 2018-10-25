/*
 * @date: 10.25.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Lab 3
 */
#include "mic.h"
#include "ir_hat.h"
#include "ir_rangefinder.h"
#include "move_commands.h"
#include "line_sensors.h"
#include "nordic_rf.h"
#include "maze.h"
#include <Servo.h>
#include <RF24.h>
#include <printf.h>

Servo servo_R;
Servo servo_L;

RF24 radio(9,10);
Maze maze = Maze();

int IR_COUNTER = 0;
int MIC_COUNTER = 0;
int MIC_THRESHOLD = 4;                //better value
bool BEGIN_OPERATIONS = false;

bool wall_detected = false;

int i = 0;

void setup() {
  Serial.begin(9600);
  printf_begin();       //Leave this here
  pinMode(7, OUTPUT);   //set pin as output to toggle LED --> IR circuit
  pinMode(8, OUTPUT);   //set pin as output to toggle LED --> microphone circuit
  servo_R.attach(6);
  servo_L.attach(5);
  stopMotors(servo_L, servo_R);
  RF24_tx_setup(radio);
  radio.printDetails(); //Leave this here
}

// THIS LOOP IS USED FOR DEBUGGING - please don't delete me
void loops() {
  Serial.println(i);
  send_turn_left(radio);
  send_turn_right(radio);
  send_advance_intersection(radio, true, false, true);
  bool microphone_detection = detect_660hz();
  bool ir = detect_6080hz();
  //moveForward(servo_L, servo_R);
  //unsigned int * sensorStatus = checkSensorsDigital();
  digitalWrite(8, HIGH);
  i++;
  //delay(500);
}

// THIS IS THE REAL LOOP
void loop() {
  while (!BEGIN_OPERATIONS) {
    unsigned int * sensorStatus = checkSensorsDigital();
    stopMotors(servo_L, servo_R);
    bool microphone_detection = detect_660hz();
    if (microphone_detection)
      MIC_COUNTER++;
    else
      MIC_COUNTER = 0;
    if (MIC_COUNTER > MIC_THRESHOLD) {          //set this to a better threshold
      digitalWrite(8, HIGH);
      BEGIN_OPERATIONS = true;
    }
    else
      digitalWrite(8, LOW);
  }
  while (BEGIN_OPERATIONS) {
    //Line tracking code
    unsigned int * sensorStatus = checkSensorsDigital();
    if ((sensorStatus[0] == 0) && (sensorStatus[1] == 0) && (sensorStatus[2] == 0) && detect_wall_6in(3) ) { // wall detected at intersection!
      if (detect_wall_6in(1)){
        Serial.println(F("Turn Left Intersection"));
        turnLeftIntersection(servo_L, servo_R);
        send_advance_intersection(radio, true, false, true);
        send_turn_left(radio);
      }
      else{
        Serial.println(F("Turn Right Intersection"));
        turnRightIntersection(servo_L, servo_R);
        send_advance_intersection(radio, true, false, false);
        send_turn_right(radio);
      }
    }
    else if (detect_wall_3in(3)) {
      Serial.println(F("Turn Left Evasive"));
      turnLeft(servo_L, servo_R);
      send_turn_left(radio);
    }
    // Else just track the line
    else if (sensorStatus[0] == 0) //turn Right
      adjustRight(servo_L, servo_R, 85);
    else if (sensorStatus[2] == 0) //turn Left
      adjustLeft(servo_L, servo_R, 85);
    else {
      moveForward(servo_L, servo_R);
    }

    //IR Detection Code
    while (detect_6080hz()) {
      digitalWrite(7, HIGH);
      stopMotors(servo_L, servo_R);
    }
    digitalWrite(7, LOW);
  }
}
