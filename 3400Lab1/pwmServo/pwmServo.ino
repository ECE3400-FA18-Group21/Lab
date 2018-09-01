#include <Servo.h>
int val = 90;
int readValue = 0;
int pinName = A0;
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  readValue = analogRead(pinName);
  val = map(readValue, 0, 670, 0, 180);
  myservo.write(val);
}
