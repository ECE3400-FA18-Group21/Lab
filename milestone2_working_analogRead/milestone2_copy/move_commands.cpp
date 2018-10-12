#include "move_commands.h"
#include "ir_rangefinder.h"
/* Team 21
 * 9/1/18
 * 
 */


void stopMotors(Servo servo_L, Servo servo_R, int SPEED_THRESHOLD){
  servo_R.write(90);
  servo_L.write(90);
}

void moveForward(Servo servo_L, Servo servo_R, int SPEED_THRESHOLD){
  servo_R.write(180);
  servo_L.write(30);
}

void moveBackward(Servo servo_L, Servo servo_R, int SPEED_THRESHOLD){
  servo_R.write(0);
  servo_L.write(150);
}

void adjustRight(Servo servo_L, Servo servo_R, int amount, int SPEED_THRESHOLD){
  servo_R.write(180 - amount);
  servo_L.write(0);
}

void adjustLeft(Servo servo_L, Servo servo_R, int amount, int SPEED_THRESHOLD){
  servo_R.write(180);
  servo_L.write(0 + amount);
}

void turnRight(Servo servo_L, Servo servo_R, int SPEED_THRESHOLD){
  servo_R.write(180);
  servo_L.write(180);
  delay(550);
  stopMotors(servo_L, servo_R, SPEED_THRESHOLD);
}


void turnLeft(Servo servo_L, Servo servo_R, int SPEED_THRESHOLD){
  servo_R.write(0);
  servo_L.write(0);
  delay(530);
  stopMotors(servo_L, servo_R, SPEED_THRESHOLD);
}


void turnRightIntersection(Servo servo_L, Servo servo_R, int SPEED_THRESHOLD){
  moveForward(servo_L, servo_R, SPEED_THRESHOLD);
  delay(350);
  stopMotors(servo_L, servo_R, SPEED_THRESHOLD);
  turnRight(servo_L, servo_R, SPEED_THRESHOLD);
}

void turnLeftIntersection(Servo servo_L, Servo servo_R, int SPEED_THRESHOLD){
  moveForward(servo_L, servo_R, SPEED_THRESHOLD);
  delay(350);
  stopMotors(servo_L, servo_R, SPEED_THRESHOLD);
  turnLeft(servo_L, servo_R, SPEED_THRESHOLD);
}
