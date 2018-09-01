/* Team 21
 * 9/1/18
 * 
 */

void moveForward(Servo servo_L, Servo servo_R)
{
  servo_R.write(180);
  servo_L.write(0);
}


void adjustRight(Servo servo_L, Servo servo_R, int amount){
  servo_R.write(180 - amount);
  servo_L.write(0);
}

void adjustLeft(Servo servo_L, Servo servo_R, int amount){
  servo_R.write(180);
  servo_L.write(0 + amount);
}

void turnRightIntersection(Servo servo_L, Servo servo_R){
  
}


void turnLeftIntersection(Servo servo_L, Servo servo_R){
  
}



