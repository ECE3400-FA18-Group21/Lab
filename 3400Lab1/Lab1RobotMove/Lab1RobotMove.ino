#include <Servo.h>
#include "move_commands.h"
#include "line_sensors.h";

Servo servo_R;
Servo servo_L;



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  servo_R.attach(3);
  servo_L.attach(5);

}

void loop() {
  // put your main code here, to run repeatedly:
  moveForward(servo_L, servo_R);
  delay(800);
  stopMotors(servo_L, servo_R);
  turnRight(servo_L, servo_R);
  moveForward(servo_L, servo_R);
  delay(800);
  stopMotors(servo_L, servo_R);
  turnRight(servo_L, servo_R);
  moveForward(servo_L, servo_R);
  delay(800);
  stopMotors(servo_L, servo_R);
  turnRight(servo_L, servo_R);
  moveForward(servo_L, servo_R);
  delay(800);
  stopMotors(servo_L, servo_R);
  moveBackward(servo_L, servo_R);
  delay(800);
  stopMotors(servo_L, servo_R);
  turnLeft(servo_L, servo_R);
  
  while(1);

  
  /*unsigned int * sensorReadings = checkSensors();
  for(int i = 0; i < NUM_SENSORS; i++){
    Serial.print(sensorReadings[i]);
    Serial.print("\t");
  }
  Serial.println("");*/
  
}
