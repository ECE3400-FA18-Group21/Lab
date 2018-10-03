#include "mic.h"
#include "ir_hat.h"
/*
 * @date: 09.28.2018
 * @version: 01
 * @course: ECE 3400, Fall 2018
 * @team: 21
 */
int counter = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 
  fft_setup();
}

//IMPLEMENT SIMILAR CODE FOR IR DEMONSTRATION
//ADD CODE FOR PUSHBOTTON FAIL SAFE (if microphone circuit fails)
void loop() {
  int count = 0;
  Serial.println(detect_660hz());
  if(detect_660hz())
    counter++;
  else
    counter = 0;
  if(counter>6)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}
