/* Team 21
 * 9/1/18
 * Calibrates the right and left servos so that a value of 90 corresponds to the servo staying still.
 * This runs both servos at "90", adjust potentiometer on servos until servo does not turn.
 */


#include <Servo.h>
int servoSpeed = 90;
Servo servo_R;
Servo servo_L;

void setup() {
  // put your setup code here, to run once:
  servo_R.attach(3);
  servo_L.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo_R.write(servoSpeed);
  servo_L.write(servoSpeed);
}
