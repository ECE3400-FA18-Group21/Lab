/* Team 21
 * 9/1/18
 * 
 */
 
#include "move_commands.h"

void stopMotors(Servo servo_L, Servo servo_R){
  servo_R.write(90);
  servo_L.write(90);
}

void moveForward(Servo servo_L, Servo servo_R){
  servo_R.write(180);
  servo_L.write(30);
}

void moveBackward(Servo servo_L, Servo servo_R){
  servo_R.write(0);
  servo_L.write(150);
}

void adjustRight(Servo servo_L, Servo servo_R, int amount){
  servo_R.write(180 - amount);
  servo_L.write(0);
}

void adjustLeft(Servo servo_L, Servo servo_R, int amount){
  servo_R.write(180);
  servo_L.write(0 + amount);
}

void turnRight(Servo servo_L, Servo servo_R){
  servo_R.write(180);
  servo_L.write(180);
  delay(550);
  stopMotors(servo_L, servo_R);
}


void turnLeft(Servo servo_L, Servo servo_R){
  servo_R.write(0);
  servo_L.write(0);
  delay(530);
  stopMotors(servo_L, servo_R);
}


void turnRightIntersection(Servo servo_L, Servo servo_R){
  moveForward(servo_L, servo_R);
  delay(350);
  stopMotors(servo_L, servo_R);
  turnRight(servo_L, servo_R);
}

void turnLeftIntersection(Servo servo_L, Servo servo_R){
  moveForward(servo_L, servo_R);
  delay(350);
  stopMotors(servo_L, servo_R);
  turnLeft(servo_L, servo_R);
}
