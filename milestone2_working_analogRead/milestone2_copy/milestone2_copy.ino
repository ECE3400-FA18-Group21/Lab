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

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);             //set pin as output to toggle LED --> IR circuit
  pinMode(8, OUTPUT);             //set pin as output to toggle LED --> Microphone circuit
  servo_R.attach(3);              //setup right servo
  servo_L.attach(5);              //setup left servo
  stopMotors(servo_L, servo_R, SPEED_THRESHOLD);   //motors initially are not running
}

void loop() {
    //LONG DISTANCE IR CODE
    if(detect_wall_2in(3)){              // wall detected
      digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
    else {
      digitalWrite(8, LOW); 
    }
    byte ADCSRA_default = ADCSRA;
    byte ADMUX_default = ADMUX;
    byte ADCSRB_default = ADCSRB;

    delay(1000);
    //IR Detection Code
    bool ir_detection = detect_6080hz();  
    if(ir_detection) {
        digitalWrite(7, HIGH); 
    }
    else {
        digitalWrite(7, LOW); 
    }
    Serial.println("After IR");
    Serial.println(ADCSRA);
    Serial.println(ADMUX);
    Serial.println(ADCSRB);
    Serial.println("---");

    ADCSRA = ADCSRA_default;
    ADMUX = ADMUX_default;
    ADCSRB = ADCSRB_default;
    Serial.println("After reset to default");
    Serial.println(ADCSRA);
    Serial.println(ADMUX);
    Serial.println(ADCSRB);
    Serial.println("---");
}
