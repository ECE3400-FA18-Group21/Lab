#include "mic.h"
#include "ir_hat.h"
#include "ir_rangefinder.h"
#include "move_commands.h"
#include "line_sensors.h"
#include <Servo.h>

Servo servo_R;
Servo servo_L;


int IR_COUNTER = 0;
int MIC_COUNTER = 0;
bool BEGIN_OPERATIONS = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(7, OUTPUT);   //set pin as output to toggle LED --> IR circuit
  pinMode(8, OUTPUT);   //set pin as output to toggle LED --> microphone circuit
  servo_R.attach(3);
  servo_L.attach(5);
  stopMotors(servo_L, servo_R);
}

void loop() {
  while(!BEGIN_OPERATIONS) {
    stopMotors(servo_L, servo_R);
    bool microphone_detection = detect_660hz();  
    if(microphone_detection)
        MIC_COUNTER++;
    else
        MIC_COUNTER=0;
    if(MIC_COUNTER > 5) {           //set this to a better threshold
        digitalWrite(8, HIGH);
        BEGIN_OPERATIONS = true;
    }
    else
        digitalWrite(8, LOW);
  }
  while(BEGIN_OPERATIONS) {
    //Line tracking code
    unsigned int * sensorStatus = checkSensors();
    Serial.println(sensorStatus[0]);
    if(detect_wall_2in(3)){ // wall detected at intersection!
      turnLeftIntersection(servo_L, servo_R);
    }
    // Else just track the line
    else if (sensorStatus[0] == 0) //turn Right
      adjustRight(servo_L, servo_R, 85);
    else if (sensorStatus[2] == 0) //turn Left
      adjustLeft(servo_L, servo_R, 85);
    else{
      moveForward(servo_L, servo_R);
    }
    
    //IR Detection Code
    bool ir_detection = detect_6080hz();  
    if(ir_detection)
        IR_COUNTER++;
    else
        IR_COUNTER=0;
    if(IR_COUNTER > 5) {            //set this to a better threshold
        digitalWrite(7, HIGH);
        stopMotors(servo_L, servo_R);
    }
    else
        digitalWrite(7, LOW);  
  }
}
