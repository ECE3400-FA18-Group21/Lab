#include "mic.h"
#include "ir_hat.h"
#include "ir_rangefinder.h"
#include "move_commands.h"
#include "line_sensors.h"
#include <Servo.h>

/*
 * @date: 10.11.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Code to complete Milestone 2
 */

Servo servo_R;
Servo servo_L;

int IR_COUNTER = 0;
int IR_THRESHOLD = 5;     //pick better value?
int MIC_COUNTER = 0;
int MIC_THRESHOLD = 5;    //pick better value?
int SPEED_THRESHOLD = 1.0;
bool BEGIN_OPERATION = false;

byte ADCSRA_default;
byte ADMUX_default;
byte ADCSRB_default;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);             //set pin as output to toggle LED --> IR circuit
  pinMode(8, OUTPUT);             //set pin as output to toggle LED --> Microphone circuit
  servo_R.attach(3);              //setup right servo
  servo_L.attach(5);              //setup left servo
  stopMotors(servo_L, servo_R, SPEED_THRESHOLD);   //motors initially are not running
}

void loop() {
  ADCSRA_default = ADCSRA;
  ADMUX_default = ADMUX;
  ADCSRB_default = ADCSRB;
  
  //Mic detection code
  //Must observe 660 Hz on consecutive passes > MIC_THRESHOLD
  while(!BEGIN_OPERATION) {
    stopMotors(servo_L, servo_R, SPEED_THRESHOLD);
    BEGIN_OPERATION = begin_operation(); //runs mic detection 
  }
  
  reset_ADC();
  
  while(BEGIN_OPERATION) {
  
    //Line tracking code
    unsigned int * sensorStatus = checkSensors();
    Serial.println(sensorStatus[0]);
    if(detect_wall_2in(3)){ // wall detected at intersection!
      turnLeftIntersection(servo_L, servo_R, SPEED_THRESHOLD);
    }
    //Else just track the line
    else if (sensorStatus[0] == 0) //turn Right
      adjustRight(servo_L, servo_R, 85, SPEED_THRESHOLD);
    else if (sensorStatus[2] == 0) //turn Left
      adjustLeft(servo_L, servo_R, 85, SPEED_THRESHOLD);
    else
      moveForward(servo_L, servo_R, SPEED_THRESHOLD);
      
    //IR Detection Code
    if(detect_6080hz()) {
        digitalWrite(7, HIGH); 
        stopMotors(servo_L, servo_R);
    }
    else
        digitalWrite(7, LOW); 
        
    reset_ADC();
  }
}

//Thresholds the microphone circuit
//Helps eliminate false positives, like human speech
bool begin_operation() {
  bool detected_on_this_run = detect_660hz();  
  if(detected_on_this_run)
      MIC_COUNTER++;
  else
      MIC_COUNTER=0;
  if(MIC_COUNTER > MIC_THRESHOLD) {        
      digitalWrite(8, HIGH);  //use LED for visible indication
      return true;
   }
   else {
      digitalWrite(8, LOW);   //use LED for visible indication
      return false;
   }
}

void reset_ADC() {
    ADCSRA = ADCSRA_default;
    ADMUX = ADMUX_default;
    ADCSRB = ADCSRB_default;
}
