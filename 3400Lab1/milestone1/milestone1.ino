#include <Servo.h>
#include <avr/interrupt.h>      // library for interrupt handling
#include <avr/sleep.h>          // library for low power operation
#include <avr/power.h>          // library for power control
#include "move_commands.h"
#include "line_sensors.h";

Servo servo_R;
Servo servo_L;

/*
 * A figure 8 formation on the grid requires 8 turns.
 * Assuming the robot starts in the middle, it will take
 * 4 left turns followed by 4 right turns. This count
 * variable keeps track of what turn the robot is on.
 */
int turnCount = 0;


/*
    TIMING Helper Functions
*/
void init_timer1() {
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 500000;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
}

void start_timer1(int microseconds) {
  TCNT1 = 34286 * 2;
}

//Interrupt Service Routines
ISR(TIMER1_OVF_vect) {

}
/*
   END Timing Helper Functions
*/



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  servo_R.attach(3);
  servo_L.attach(5);

}

void loop() {
  // put your main code here, to run repeatedly:

  //Line tracking code
  int * sensorStatus = checkSensors();
  if (sensorStatus[0] == 0 && sensorStatus[1] == 0 && sensorStatus[2] == 0){
    //All three sensors read white- we're at an intersection
    if(turnCount < 4){
      turnLeftIntersection(servo_L, servo_R);
    }else{
      turnRightIntersection(servo_L, servo_R);
    }
    if(turnCount == 7)
      turnCount = 0; //Reset count at 7
    else
      turnCount++;
  }
  // Else just track the line
  else if (sensorStatus[0] == 0) //turn Right
    adjustRight(servo_L, servo_R, 85);
  else if (sensorStatus[2] == 0) //turn Left
    adjustLeft(servo_L, servo_R, 85);
  else
    moveForward(servo_L, servo_R);

}
