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
int MIC_COUNTER_THRESHOLD = 5;
bool BEGIN_OPERATIONS = false;
bool wall_detected = false;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);   //set pin as output to toggle LED --> IR circuit
  pinMode(8, OUTPUT);   //set pin as output to toggle LED --> microphone circuit
  servo_R.attach(6);
  servo_L.attach(5);
  stopMotors(servo_L, servo_R);
}

void loop() {
  while(!BEGIN_OPERATIONS) {
    stopMotors(servo_L, servo_R);

    //Microphone detection code
    if(detect_660hz())
        MIC_COUNTER++;
    else
        MIC_COUNTER=0;
    if(MIC_COUNTER > MIC_COUNTER_THRESHOLD) {
        digitalWrite(8, HIGH);
        BEGIN_OPERATIONS = true;
    }
    else
        digitalWrite(8, LOW);
  }
  
  while(BEGIN_OPERATIONS) {
    //Line tracking & Wall detection Code
    unsigned int * sensorStatus = checkSensorsDigital();
    Serial.println(sensorStatus[0]);
    if((sensorStatus[0] == 0) && (sensorStatus[1] == 0) && (sensorStatus[2] == 0) && detect_wall_6in(3) ){ // wall detected at intersection!
      turnLeftIntersection(servo_L, servo_R);
    }
    else if(detect_wall_3in(3)){
      turnLeft(servo_L, servo_R);
    }
    // Else just track the line
    else if (sensorStatus[0] == 0) //turn Right
      adjustRight(servo_L, servo_R, 85);
    else if (sensorStatus[2] == 0) //turn Left
      adjustLeft(servo_L, servo_R, 85);
    else{
      moveForward(servo_L, servo_R);
    }
    
    //IR detection Code
    while(detect_6080hz()){  
        digitalWrite(7, HIGH);
        stopMotors(servo_L, servo_R);
    }
    digitalWrite(7, LOW);  
  }
}
