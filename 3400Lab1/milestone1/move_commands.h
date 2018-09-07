/* Team 21
 * 9/1/18
 * Header for movement functions.
 */
 
#include <Servo.h>
#include <Arduino.h>



/*
 * [stopMotors] stops the robot's motors
 * 
 * args: [servo_L] is the Servo object for the left motor,
 *       [servo_R] is the Servo object for the right motor
 */
void stopMotors(Servo servo_L, Servo servo_R);

/*
 * [moveForward] moves the robot forward at full speed
 * 
 * args: [servo_L] is the Servo object for the left motor,
 *       [servo_R] is the Servo object for the right motor
 */
void moveForward(Servo servo_L, Servo servo_R);


/*
 * [moveBackward] moves the robot backward at full speed
 * 
 * args: [servo_L] is the Servo object for the left motor,
 *       [servo_R] is the Servo object for the right motor
 */
void moveBackward(Servo servo_L, Servo servo_R);

/*
 * [adjustRight] and [adjustLeft] adjust the robot's direction by [amount]
 * These functions can be called to adjust the robot's direction while still
 * moving forward at full speed. [adjustRight] turns the robot right by a bit,
 * and [adjustLeft] turns the robot left by a bit
 * 
 * args: [servo_L] is the Servo object for the left motor,
 *       [servo_R] is the Servo object for the right motor,
 *       [amount] is an input that adjusts how much the robot turns, from a 
 *       scale of 0-90, corresponding to the Arduino Servo.write() scaling
 */
void adjustRight(Servo servo_L, Servo servo_R, int amount);

void adjustLeft(Servo servo_L, Servo servo_R, int amount);

/*
 * [turnRight] and [turnLeft] are functions that
 * turn the robot 90 degrees at an intersection. [turnRight]
 * turns right by 90 degrees, adn [turnLeft] turns the robot
 * left by 90 degrees.
 * 
 * args: [servo_L] is the Servo object for the left motor,
 *       [servo_R] is the Servo object for the right motor
 */

void turnRight(Servo servo_L, Servo servo_R);

void turnLeft(Servo servo_L, Servo servo_R);
