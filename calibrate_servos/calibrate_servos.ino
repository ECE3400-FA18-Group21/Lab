#include <Servo.h>

Servo servo_R;
Servo servo_L;

void setup() {
  servo_R.attach(3);              //setup right servo
  servo_L.attach(5);              //setup left servo
}

void loop() {
  servo_R.write(90);
  servo_L.write(90);
  delay(3000); //3 seconds
  servo_R.write(180);
  servo_L.write(45);
  delay(6000); //10 seconds
}
