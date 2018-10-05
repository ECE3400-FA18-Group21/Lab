#include "mic.h"
#include "ir_hat.h"
/*
 * @date: 10.04.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 * Current 660 Hz detection (microphone) & 6008 Hz detection (IR)
 *    Used to complete Lab 2 documentation
 */

int IR_COUNTER = 0;
int MIC_COUNTER = 0;
bool BEGIN_OPERATIONS = false;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);   //set pin as output to toggle LED --> IR circuit
  pinMode(8, OUTPUT);   //set pin as output to toggle LED --> microphone circuit
}

void loop() {
  while(!BEGIN_OPERATIONS) {
    fft_setup_mic();
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
    fft_setup_ir();
    bool ir_detection = detect_6080hz();  
    if(ir_detection)
        IR_COUNTER++;
    else
        IR_COUNTER=0;
    if(IR_COUNTER > 5) {            //set this to a better threshold
        digitalWrite(7, HIGH);
        Serial.println("Hostile robot detected. Implementing evasive maneuver");
    }
    else
        digitalWrite(7, LOW);  
  }
}
