#include <Servo.h>
#include <avr/interrupt.h>      // library for interrupt handling
#include <avr/sleep.h>          // library for low power operation
#include <avr/power.h>          // library for power control
#include "move_commands.h"
#include "line_sensors.h";

Servo servo_R;
Servo servo_L;

//enum State = {DRIVE, TURN_PREPARE, TURN_RIGHT, TURN_LEFT};

//State currentState;


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
  int * sensorStatus = checkSensors();
  if (sensorStatus[0] == 0) //turn Right
    adjustRight(servo_L, servo_R, 85);
  else if (sensorStatus[2] == 0) //turn Left
    adjustLeft(servo_L, servo_R, 85);
  else
    moveForward(servo_L, servo_R);


  /*unsigned int * sensorReadings = checkSensors();
    for(int i = 0; i < NUM_SENSORS; i++){
    Serial.print(sensorReadings[i]);
    Serial.print("\t");
    }
    Serial.println("");*/

}
