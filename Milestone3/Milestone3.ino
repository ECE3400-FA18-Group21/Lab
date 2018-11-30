/*
 * @date: 10.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Mielstone 3
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

int MIC_COUNTER = 0;
int MIC_THRESHOLD = 4;           //better value
int i = 0;

bool BEGIN_OPERATIONS = false;
bool wall_detected = false;

bool front_wall;
bool left_wall;
bool right_wall;

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
  stopMotors(servo_L, servo_R);
  
  maze.advanceIntersection(false, false, true);
  Serial.print("Next Command: ");
  Serial.println(maze.getNextCommand(false, false, true));
  maze.turnLeft();
  maze.printInfo();
  Serial.println("");
  Serial.println("");
  Serial.println("");

  
  
  maze.advanceIntersection(false, false, false);
  Serial.print("Next Command: ");
  Serial.println(maze.getNextCommand(false, false, false));
  maze.turnLeft();
  maze.printInfo();
  Serial.println("");
  Serial.println("");
  Serial.println("");

  
  
  maze.advanceIntersection(true, false, false);
  Serial.print("Next Command: ");
  Serial.println(maze.getNextCommand(true, false, false));
  maze.turnLeft();
  maze.printInfo();
  Serial.println("");
  Serial.println("");
  Serial.println("");

  
  
  maze.advanceIntersection(true, false, true);
  Serial.print("Next Command: ");
  Serial.println(maze.getNextCommand(true, false, true));
  maze.turnRight();
  maze.turnRight();
  maze.printInfo();
  Serial.println("");
  Serial.println("");
  Serial.println("");

  
  
  maze.advanceIntersection(false, true, false);
  Serial.print("Next Command: ");
  Serial.println(maze.getNextCommand(false, true, false));
  maze.printInfo();
  Serial.println("");
  Serial.println("");
  Serial.println("");

  
  
  maze.advanceIntersection(true, true, false);
  Serial.print("Next Command: ");
  Serial.println(maze.getNextCommand(true, true, false));
  maze.printInfo();
  Serial.println("");
  Serial.println("");
  Serial.println("");
  while(true){
    
      
    unsigned int * sensorStatus = checkSensorsDigital();
  }

  
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
    if ((sensorStatus[0] == 0) && (sensorStatus[1] == 0) && (sensorStatus[2] == 0)) { // Intersection Detected!
      front_wall = detect_wall_6in(3);
      left_wall = detect_wall_6in(2);
      right_wall = detect_wall_6in(1);
      
      maze.advanceIntersection(front_wall, left_wall, right_wall); //A3 is front, A2 is left, A1 is right
      //send_advance_intersection(radio, front_wall, left_wall, right_wall);
      
      byte next_command = maze.getNextCommand(front_wall, left_wall, right_wall);
      Serial.print(F("Next Command: "));
      Serial.println(next_command);
      maze.printInfo();
      Serial.print(F(" Wall Sensor Readings"));
      Serial.print(front_wall); Serial.print(F("   ")); Serial.print(left_wall); Serial.print(F("   ")); Serial.print(right_wall); Serial.println(F("   "));
      

      if (next_command == 0){
        moveForward(servo_L, servo_R);
      }
      else if (next_command == 1){
        turnLeftIntersection(servo_L, servo_R);
        maze.turnLeft();
        //send_turn_left(radio);
      }
      else if (next_command == 2){
        turnRightIntersection(servo_L, servo_R);
        maze.turnRight();
        //send_turn_right(radio);
      }
      else if (next_command == 3){
        digitalWrite(7, HIGH);
        //send_turn_right(radio);
        turnRightIntersection(servo_L, servo_R);
        turnRight(servo_L, servo_R);
        maze.turnRight();
        maze.turnRight(); 
        //send_turn_right(radio);

      }
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
