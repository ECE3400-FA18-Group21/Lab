#include <Servo.h>
#include "move_commands.h"

Servo servo_R;
Servo servo_L;

void setup() {
  // put your setup code here, to run once:
  servo_R.attach(3);
  servo_L.attach(5);

}

void loop() {
  // put your main code here, to run repeatedly:
  moveForward(servo_L, servo_R);
}
